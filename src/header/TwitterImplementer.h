/*
 * TwitterImplementer.h
 *
 *  Created on: 2012/08/13
 */

#ifndef TWITTERIMPLEMENTER_H_
#define TWITTERIMPLEMENTER_H_

#include "Twitter.h"

class TwitterImplementer: public Twitter {
private:
	void test();
public:
	TwitterImplementer(const std::string& consumerKey, const std::string& consumerSecret, const std::string& oauthToken,
			const std::string& oauthTokenSecret);
	virtual ~TwitterImplementer();

	//# StatusMethods
	void updateStatus(std::string text);

	//# TimelineMethods
	int getHomeTimeline(std::vector<Tweet*>* const tweetList, unsigned int count = DEFAULT_LOAD_COUNT,
			unsigned long sinceId = UNUSED, unsigned long maxId = UNUSED, unsigned int page = UNUSED) const;
};

#endif /* TWITTERIMPLEMENTER_H_ */
