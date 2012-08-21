/*
 * User.cpp
 *
 *  Created on: 2012/08/20
 */

#include "User.h"

User::User()
:id_(-1),
 protected_(false),
 followersCount_(-1),
 friendsCount_(-1),
 favouritesCount_(-1),
 utcOffset_(-1),
 getEnabled_(false),
 verified_(false),
 contributorsEnabled_(false),
 isTranslator_(false),
 showAllInlineMedia_(false),
 defaultProfile_(false),
 defaultProfileImage_(false),
 following_(false){
}

User::~User() {
}
