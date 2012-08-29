/*
 * TwitterImpl.h
 *
 *  Created on: 2012/08/13
 */

#ifndef TWITTERIMPL_H_
#define TWITTERIMPL_H_

#include "Twitter.h"

/**
 * @brief Twitterの実装クラス
 */
class TwitterImpl: public Twitter {
private:
	void test();
public:
	TwitterImpl(const std::string& consumerKey, const std::string& consumerSecret, const std::string& oauthToken,
			const std::string& oauthTokenSecret);
	virtual ~TwitterImpl();

	//# StatusMethods
	void updateStatus(const std::string& text,const long& replyTo = -1) const;

	//# TimelineMethods
	int getHomeTimeline(std::vector<Tweet*>* const tweetList, unsigned int count = DEFAULT_LOAD_COUNT,
			unsigned long sinceId = UNUSED, unsigned long maxId = UNUSED, unsigned int page = UNUSED) const;
};

#endif /* TWITTERIMPL_H_ */
