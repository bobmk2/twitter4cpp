/*
 * Twitter.cpp
 *
 *  Created on: 2012/08/10
 */

#include "Twitter.h"

using namespace std;

Twitter::Twitter(const string& consumerKey, const string& consumerSecret,const string& accessToken, const string& tokenSecret)
:consumerKey_(new string(consumerKey)),
 consumerSecret_(new string(consumerSecret)),
 oauthToken_(new string(accessToken)),
 oauthTokenSecret_(new string(tokenSecret))
{
}

Twitter::~Twitter() {
	delete(oauthTokenSecret_);
	delete(oauthToken_);
	delete(consumerSecret_);
	delete(consumerKey_);
}

Twitter::Twitter(const Twitter& twitter)
:consumerKey_(new string(*twitter.consumerKey_)),
 consumerSecret_(new string(*twitter.consumerSecret_)),
 oauthToken_(new string(*twitter.oauthToken_)),
 oauthTokenSecret_(new string(*twitter.oauthTokenSecret_))
{
}
