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
#include "TwitterDate.h"

/**
 * @brief ツイートクラス
 */
class Tweet {
private:
	static const long NOT_SPECIFIED = -1;

	long id_;				//!< ツイートID
	std::string* text_;		//!< 本文
	std::string* source_;	//!< ソース（from XXXの箇所)

	TwitterDate* createdAt_;//!< 投稿日時

	long fromUserId_;					//!< 投稿者のユーザID
	std::string* fromUserName_;			//!< 投稿者のユーザ名
	std::string* fromUserScreenName_;	//!< 投稿者のスクリーン名

	long toUserId_;						//!< 宛先のユーザID
	std::string* toUserName_;			//!< 宛先のユーザ名
	std::string* toUserScreenName_;		//!< 宛先の

	User* user_;						//!< 投稿ユーザ情報

public:
	Tweet();
	virtual ~Tweet();
	std::string toString() const;

	/* Setter */
	void setId(const long& id);
	void setText(const std::string& text);
	void setSource(const std::string& source);
	void setCreatedAt(const TwitterDate& createdAt);

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
	const TwitterDate* getCreatedAt() const;

	long getFromUserId() const;
	const std::string* getFromUserName() const;
	const std::string* getFromUserScreenName() const;

	long getToUserId() const;
	const std::string* getToUserName() const;
	const std::string* getToUserScreenName() const;

	const User* getUser() const;
};

#endif /* TWEET_H_ */
