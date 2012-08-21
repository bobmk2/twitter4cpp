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

class AccessToken {
private:
	std::string* token_;
	std::string* tokenSecret_;

	long userId_;
	std::string* screenName_;

	AccessToken(const std::string& token, const std::string& tokenSecret, long userId, const std::string& screenName);
public:
	AccessToken(const AccessToken& accessToken);
	const AccessToken& operator=(const AccessToken& accessToken);

	virtual ~AccessToken();

	static AccessToken createInstance(const http::HttpResponse response);

	const std::string& getToken() const;
	const std::string& getTokenSecret() const;
};

} /* namespace oauth */
#endif /* ACCESSTOKEN_H_ */
