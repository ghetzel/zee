#include "media.h"

bool ZMediaManager::invoke(QString action)
{
//	fail if there is no player to control
	if(player() == NULL)
		return false;
	
	if(action == "library"){
		return library()->invoke(action);
	}

	return player()->invoke(action);
}
