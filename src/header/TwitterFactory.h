/*
 * TwitterFactory.h
 *
 *  Created on: 2012/08/13
 */

#ifndef TWITTERFACTORY_H_
#define TWITTERFACTORY_H_

#include "Twitter.h"

class TwitterFactory {
private:
	TwitterFactory();
public:
	static Twitter* createInstance(
				const std::string& consumerKey, const std::string& consumerSecret,
				const std::string& oauthToken, const std::string& oauthTokenSecret);
};

#endif /* TWITTERFACTORY_H_ */
