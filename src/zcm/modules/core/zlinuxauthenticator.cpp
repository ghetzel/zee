#include "zlinuxauthenticator.h"

struct z_pamCredentials{
    char *username;
    char *password;
};

int z_pamCallback(int num_msg,
				      const struct pam_message **msgm,
				      struct pam_response **response,
				      void *appdata_ptr)
{
    int retval = PAM_SUCCESS;
    z_pamCredentials *source = NULL;
    const struct pam_message *m = *msgm;
    struct pam_response *r;

    if((source = CAST(z_pamCredentials*,appdata_ptr))){
	if(num_msg <= 0 || num_msg >= PAM_MAX_NUM_MSG)
	{
	    z_log_error(QString("ZLinuxAuthenticator: PAM: Bad number of messages ("
				"have: %1, limit: %2").arg(num_msg,PAM_MAX_NUM_MSG));
		*response = NULL;
		retval = PAM_CONV_ERR;
	}

	*response = r = (struct pam_response *)calloc(num_msg,
						      sizeof(struct pam_response));

	if(r == NULL)
	    retval = PAM_BUF_ERR;

    //  for each message
	if(retval == PAM_SUCCESS){
	    for(int i = 0; i < num_msg; i++){
		if(!m){
		    z_log_error(QString("ZLinuxAuthenticator: PAM message %1 error.").arg(i));
		    retval = PAM_CONV_ERR;
		    break;
		}

		r->resp = NULL;
		r->resp_retcode = 0;

		switch(m->msg_style){
		case PAM_PROMPT_ECHO_ON:    // username?
		    r->resp = strdup(source->username);
		    break;
		case PAM_PROMPT_ECHO_OFF:   // password?
		    r->resp = strdup(source->password);
		    break;
		case PAM_ERROR_MSG:
		    z_log_error("ZLinuxAuthenticator: "+STR(m->msg));
		    break;
		case PAM_TEXT_INFO:
		    z_log("ZLinuxAuthenticator: "+STR(m->msg));
		    break;
		}

		m++;
		r++;
	    }
	}
    }else{
	retval = PAM_CONV_ERR;
    }

//  on error, cleanup all the allocated junk
    if(retval != PAM_SUCCESS){
	if(r){
	    struct pam_response *fr = r;
	    for(int i = 0; i < num_msg; i++, r++){
		if(fr->resp){
		    bzero(fr->resp, strlen(fr->resp));	    // zero memory
		    free(fr->resp);			    // free memory
		    fr->resp = NULL;
		}
		free(r);
	    }
	}
    }

    return retval;
}



ZLinuxAuthenticator::ZLinuxAuthenticator(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    init();
}

void ZLinuxAuthenticator::init(){
    _pam = NULL;

    zEvent->registerSignal(this, SIGNAL(granted()));
    zEvent->registerSignal(this, SIGNAL(denied()));
    zEvent->registerSlot(this, SLOT(authenticate(QString,QString)));

    parse(_config);
}

void ZLinuxAuthenticator::parse(const ZConfig &el){

}

void ZLinuxAuthenticator::authenticate(QString username, QString password){
#ifdef USE_PAM
    struct z_pamCredentials cred = { CSTR(username), CSTR(password) };
    pam_conv pamConversation = {z_pamCallback, &cred};

    int status;
    status = pam_start(CSTR(objectName()),
		       cred.username,
		       &pamConversation,
		       &_pam);

    if(status==PAM_SUCCESS && _pam){
	z_log_debug("ZLinuxAuthenticator: PAM Initialized");
	status = pam_authenticate(_pam, 0);

	if(status == PAM_SUCCESS){
	    emit granted();
	    return;
	}else{
	    z_log_debug("ZLinuxAuthenticator: PAM: "+STR(pam_strerror(_pam,
								      status)));
	}
    }

    pam_end(_pam, status);
#endif
/*
    char *challengePass = NULL;
    char *correctPass = NULL;
//							   get user info
    struct passwd *entry = getpwnam(qstrdup(username.toLocal8Bit().data()));
    endpwent();						// close passwd database

    if(entry){
//  if using the shadow file, grab the user's entry and the hashed password
#ifdef USE_SHADOW_FILE
	struct spwd *shadow = getspnam(entry->pw_name);	// get hashed password
	endspent();					// close shadow file
	if(shadow)
	    correctPass = shadow->sp_pwdp;
	else
#endif
//  else, grab the password in the passwd database
	    correctPass = entry->pw_passwd;

//	encrypt the submitted password
	challengePass = crypt(qstrdup(password.toLocal8Bit().data()),
			      correctPass);

	z_log_debug("ZLinuxAuthenticator: "+STR(challengePass)+"("+STR(strlen(challengePass))+") == "+STR(entry->pw_passwd)+"("+STR(strlen(entry->pw_passwd))+")");

//	test for the correctitude of the password
	if(strcmp(challengePass, correctPass) == 0){
	    z_log("ZLinuxAuthenticator: Username '"+username+"' authenticated "
		  "successfully.");
	    emit granted();
	    return;
	}

    }
*/

    z_log_error("ZLinuxAuthenticator: Access Denied for user '"+username+"'");
    emit denied();
}
