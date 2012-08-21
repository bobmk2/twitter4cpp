/*
 * RequestToken.h
 *
 *  Created on: 2012/08/10
 */

#ifndef REQUESTTOKEN_H_
#define REQUESTTOKEN_H_

#include <string>
#include <HttpResponse.h>

namespace oauth {

class RequestToken {
private:
	std::string* token_;
	std::string* tokenSecret_;

	RequestToken(const std::string& token, const std::string& tokenSecret);
public:
	RequestToken(const RequestToken& reqToken);
	const RequestToken& operator=(const RequestToken& reqToken);

	virtual ~RequestToken();

	static RequestToken createInstance(const http::HttpResponse response);

	std::string getAuthenticationUrl() const;
	const std::string& getToken() const;
	const std::string& getTokenSecret() const;
};

} /* namespace oauth */
#endif /* REQUESTTOKEN_H_ */
