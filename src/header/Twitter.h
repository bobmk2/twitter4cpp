/*
 * Twitter.h
 *
 *  Created on: 2012/08/10
 */

#ifndef TWITTER_H_
#define TWITTER_H_

#include "StatusMethods.h"
#include "TimelineMethods.h"

class Twitter : public method::StatusMethods, public method::TimelineMethods{
protected:
	std::string* consumerKey_;
	std::string* consumerSecret_;

	std::string* oauthToken_;
	std::string* oauthTokenSecret_;

	Twitter(
			const std::string& consumerKey, const std::string& consumerSecret,
			const std::string& accessToken, const std::string& tokenSecret);
	Twitter(const Twitter& twitter);

	const std::string& getConsumerKey(){return *consumerKey_;}
	const std::string& getConsumerSecret(){return *consumerSecret_;}
	const std::string& getOAuthToken(){return *oauthToken_;}
	const std::string& getOAuthTokenSecret(){return *oauthTokenSecret_;}

public:

	virtual ~Twitter();
};

#endif /* TWITTER_H_ */
