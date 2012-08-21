/*
 * OAuthManager.h
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#ifndef OAUTHMANAGER_H_
#define OAUTHMANAGER_H_


#include <string>
#include "RequestToken.h"
#include "AccessToken.h"

class OAuthManager {

private:

	static const std::string OAUTH_VERSION;

	std::string getRequestParameter(const std::string& consumerKey, std::string& nonce, std::string& timestamp);
	std::string getAccessTokenParameter(const std::string& consumerKey, std::string& nonce, std::string& timestamp,const oauth::RequestToken& reqToken, const std::string& pin);

public:
	OAuthManager();
	virtual ~OAuthManager();

	void getRequestToken(const std::string& consumerKey, const std::string& consumerSecret);
	oauth::RequestToken createRequestToken(const std::string& consumerKey, const std::string& consumerSecret);

	oauth::AccessToken createAccessToken(const std::string& consumerKey, const std::string& consumerSecret, const oauth::RequestToken& reqToken, const std::string& pin);
};


#endif /* OAUTHMANAGER_H_ */
