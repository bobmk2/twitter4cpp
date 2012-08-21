/*
 * Tweet.h
 *
 *  Created on: 2012/08/15
 */

#ifndef TWEET_H_
#define TWEET_H_

#include <string>
#include <time.h>
#include "User.h"

class Tweet {
private:
	static const long NOT_SPECIFIED = -1;

	long id_;
	std::string* text_;
	std::string* source_;

	time_t* createdAt_;

	long fromUserId_;
	std::string* fromUserName_;
	std::string* fromUserScreenName_;

	long toUserId_;
	std::string* toUserName_;
	std::string* toUserScreenName_;

	User* user_;

public:
	Tweet();
	virtual ~Tweet();
	std::string toString() const;

	/* Setter */
	void setId(const long& id);
	void setText(const std::string& text);
	void setSource(const std::string& source);
	void setCreatedAt(const time_t& createdAt);

	void setFromUserId(const long& fromUserid);
	void setFromUserName(const std::string& fromUserName);
	void setFromUserScreenName(const std::string& fromUser);

	void setToUserId(const long& toUserId);
	void setToUserName(const std::string& toUserName);
	void setToUserScreenName(const std::string& toUser);

	void setUser(const User& user);

	/* Getter */
	long getId() const;
	const std::string* getText() const;
	const std::string* getSource() const;
	const time_t* getCreatedAt() const;

	long getFromUserId() const;
	const std::string* getFromUserName() const;
	const std::string* getFromUserScreenName() const;

	long getToUserId() const;
	const std::string* getToUserName() const;
	const std::string* getToUserScreenName() const;

	const User* getUser() const;
};

#endif /* TWEET_H_ */
