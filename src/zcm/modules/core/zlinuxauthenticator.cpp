#include "zlinuxauthenticator.h"

ZLinuxAuthenticator::ZLinuxAuthenticator(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    init();
}

void ZLinuxAuthenticator::init(){
    zEvent->registerSignal(this, SIGNAL(granted()));
    zEvent->registerSignal(this, SIGNAL(denied()));
    zEvent->registerSlot(this, SLOT(authenticate(QString,QString)));

    parse(_config);
}

void ZLinuxAuthenticator::parse(const ZConfig &el){

}

void ZLinuxAuthenticator::authenticate(QString username, QString password){
    char *challengePass, *correctPass;
//							   get user info
    struct passwd *entry = getpwnam(username.toLocal8Bit().data());
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
	challengePass = crypt(password.toLocal8Bit().data(),
			      correctPass);

//	test for the correctitude of the password
	if(strcmp(challengePass, correctPass) == 0){
	    z_log("ZLinuxAuthenticator: Username '"+username+"' authenticated "
		  "successfully.");
	    emit granted();
	    return;
	}

    }

    z_log_error("ZLinuxAuthenticator: Access Denied for user '"+username+"'");
    emit denied();
}
