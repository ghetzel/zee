#include "zlinuxauthenticator.h"

struct z_pamCredentials{
    char *username;
    char *password;
};

ZLinuxAuthenticator::ZLinuxAuthenticator(const ZConfig &el, QObject *parent)
    : QObject(parent),
    ZConfigurable(el,this)
{
    init();
}

void ZLinuxAuthenticator::init(){
    _pam = NULL;

    zEvent->registerSignal(this, SIGNAL(authenticating()));
    zEvent->registerSignal(this, SIGNAL(granted()));
    zEvent->registerSignal(this, SIGNAL(denied()));
    zEvent->registerSlot(this, SLOT(authenticate(QString,QString)));

    parse(_config);
}

void ZLinuxAuthenticator::parse(const ZConfig &el){
    if(el.hasAttribute("service"))
	_serviceName = el.attribute("service");
    else if(!objectName().isEmpty())
	_serviceName = objectName();
    else
	_serviceName = ZEE_OBJNAME;
}

/*!
\brief Performs authentication of \a username against \a password.

    * Emits authenticating() signal before attempting the authentication.
    * Emits the granted() signal upon successful authentication.
    * Emits the denied() signal on authentication failure.
*/
void ZLinuxAuthenticator::authenticate(QString username, QString password){
    emit authenticating();

#ifdef USE_PAM
    struct z_pamCredentials cred = { CSTR(username), CSTR(password) };
    pam_conv pamConversation = {ZLinuxAuthenticator::_pamCallback,
				&cred};

    int status;
    // setup the PAM transaction
    // DEADLY-CRITICAL IMPORTANT INFORMATION
    //  if you are unfamiliar with how PAM does its thing, know this:
    //  you must first create a facility named the same as the value
    //  in _serviceName for PAM to work.  Create in /etc/pam.d/
    //
    status = pam_start(CSTR(_serviceName),
		       cred.username,
		       &pamConversation,
		       &_pam);

    // perform the authentication
    if(_pam && status == PAM_SUCCESS){
	z_log_debug("ZLinuxAuthenticator: PAM Initialized");
	status = pam_authenticate(_pam, 0);

	if(status == PAM_SUCCESS){
	    /*! \todo we'll want to add a check with pam_acct_mgmt() here to
		    make sure the user is *allowed* to login
	    */
	    emit granted();
	    return;
	}else{
	    z_log_debug("ZLinuxAuthenticator: PAM: "+STR(pam_strerror(_pam,
								      status)));
	}
    }

    // we're done here
    pam_end(_pam, status);
#endif

//  we may want to test this again
    /*
    char *challengePass = NULL;
    char *correctPass = NULL;
//							   get user info
    struct passwd *entry = getpwnam(qstrdup(username.toLocal8Bit().data()));
    endpwent();						// close passwd database

    if(entry){
//  if using the shadow file, grab the user's entry and the hashed password
#ifdef USE_SHADOW_FILE
	struct spwd *shadow = getspnam(entry->pw_name);	// get hashed password //! \todo <-- use strdup() ???
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


/*!
\brief The authentication callback function used by libpam

This static member function is called as part of a PAM transaction to perform
authentication based on the given username and a password stored in the
\ref z_pamCredentials structure.

Further Reading:
    * http://docs.sun.com/app/docs/doc/819-2145/emrbk?l=en&a=view
    * http://svn.berlios.de/wsvn/slim/trunk/PAM.cpp
    * http://svn.berlios.de/wsvn/slim/trunk/app.cpp
	function int conv(...);
	App::AuthenticateUser();
*/
int ZLinuxAuthenticator::_pamCallback(int num_msg,
				      const struct pam_message **msgm,
				      struct pam_response **response,
				      void *appdata_ptr)
{
    int retval = PAM_SUCCESS;
    z_pamCredentials *source = NULL;
    const struct pam_message *m = *msgm;
    struct pam_response *r;

    //  make sure we have the proper app data structure before we continue
    if((source = CAST(z_pamCredentials*,appdata_ptr))){
	// PAM message count sanity check
	if(num_msg <= 0 || num_msg >= PAM_MAX_NUM_MSG)
	{
	    z_log_error(QString("ZLinuxAuthenticator: PAM: Bad number of messages ("
				"have: %1, limit: %2").arg(num_msg,PAM_MAX_NUM_MSG));
	    *response = NULL;
	    retval = PAM_CONV_ERR;
	}

	// allocate space for the working object, put the derefed response in it
	*response = r = (struct pam_response *)calloc(num_msg,
						      sizeof(struct pam_response));

	// no response, no joy
	if(r == NULL)
	    retval = PAM_BUF_ERR;

	// if we haven't failed thus far:
	if(retval == PAM_SUCCESS){
	    //  for each message...
	    for(int i = 0; i < num_msg; i++){
		// fail if there is no message
		if(!m){
		    z_log_error(QString("ZLinuxAuthenticator: PAM message %1 error.").arg(i));
		    retval = PAM_CONV_ERR;
		    break;
		}

		// clear out our response data
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

		// move on to the next message/response
		m++;
		r++;
	    }
	}
    }else{
	// we failed to succeed, we have failed
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

    // throw back to PAM to let it do its ~!*MAGIC*!~
    return retval;
}
