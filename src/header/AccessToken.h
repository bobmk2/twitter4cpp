/*
 * AccessToken.h
 *
 *  Created on: 2012/08/10
 */

#ifndef ACCESSTOKEN_H_
#define ACCESSTOKEN_H_

#include <string>
#include "HttpResponse.h"

namespace oauth {

/**
 * @brief アクセストークン
 */
class AccessToken {
private:
	std::string* token_;
	std::string* tokenSecret_;

	long userId_;				//!< 認証者のユーザID
	std::string* screenName_;	//!< 認証者のスクリーン名

public:
	AccessToken();
	AccessToken(const std::string& token, const std::string& tokenSecret);
	AccessToken(const std::string& token, const std::string& tokenSecret, long userId, const std::string& screenName);
	AccessToken(const AccessToken& accessToken);
	const AccessToken& operator=(const AccessToken& accessToken);

	virtual ~AccessToken();

	static AccessToken* createInstance(const http::HttpResponse response);

	/* Setter */
	void setToken(const std::string& token);
	void setTokenSecret(const std::string& tokenSecret);
	void setUserId(const long& userId);
	void setScreenName(const std::string& screenName);

	/* Getter */
	const std::string* getToken() const;
	const std::string* getTokenSecret() const;
	long getUserId() const;
	const std::string* getScreenName() const;
};

} /* namespace oauth */
#endif /* ACCESSTOKEN_H_ */
