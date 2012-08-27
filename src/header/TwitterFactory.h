/*
 * TwitterFactory.h
 *
 *  Created on: 2012/08/13
 */

#ifndef TWITTERFACTORY_H_
#define TWITTERFACTORY_H_

#include "Twitter.h"
#include "AccessToken.h"

/**
 * @brief Twitterファクトリ
 */
class TwitterFactory {
private:
	TwitterFactory();
public:
	static Twitter* createInstance(
				const std::string& consumerKey, const std::string& consumerSecret,
				const std::string& oauthToken, const std::string& oauthTokenSecret);

	static Twitter* createInstance(
			const std::string& consumerKey, const std::string& consumerSecret,
			const oauth::AccessToken& accessToken);
};

#endif /* TWITTERFACTORY_H_ */
