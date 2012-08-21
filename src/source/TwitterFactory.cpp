/*
 * TwitterFactory.cpp
 *
 *  Created on: 2012/08/13
 */

#include "TwitterFactory.h"

#include "TwitterImplementer.h"

TwitterFactory::TwitterFactory() {
	// TODO Auto-generated constructor stub

}

Twitter* TwitterFactory::createInstance(const std::string& consumerKey, const std::string& consumerSecret,
		const std::string& oauthToken, const std::string& oauthTokenSecret) {
	return new TwitterImplementer(consumerKey, consumerSecret, oauthToken, oauthTokenSecret);
}


