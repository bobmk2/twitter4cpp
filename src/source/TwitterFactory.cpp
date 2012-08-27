/*
 * TwitterFactory.cpp
 *
 *  Created on: 2012/08/13
 */

#include "TwitterFactory.h"

#include "TwitterImplementer.h"

using namespace std;
using namespace oauth;

TwitterFactory::TwitterFactory() {
	// TODO Auto-generated constructor stub

}

Twitter* TwitterFactory::createInstance(const string& consumerKey, const string& consumerSecret,
		const string& oauthToken, const string& oauthTokenSecret) {
	return new TwitterImplementer(consumerKey, consumerSecret, oauthToken, oauthTokenSecret);
}

Twitter* TwitterFactory::createInstance(const string& consumerKey, const string& consumerSecret,
		const AccessToken& accessToken) {
	return createInstance(consumerKey, consumerSecret, *accessToken.getToken(), *accessToken.getTokenSecret());
}


