/*
 * OAuthUtil.h
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#ifndef OAUTHUTIL_H_
#define OAUTHUTIL_H_

#include <uuid/uuid.h>
#include <string>

/**
 * @brief OAuth用のユーティリティクラス
 */
namespace oauth{
class OAuthUtil {
private:

	OAuthUtil();
public:
	static const std::string OAUTH_OAUTHORIZE_URL;
	static const std::string OAUTH_REQUEST_TOKEN_URL;
	static const std::string OAUTH_ACCESS_TOKEN_URL;

	static const std::string SIGNATURE_METHOD;
	static const std::string OAUTH_VERSION;

	static const std::string getNonce();
	static const std::string& getSignatureMethod();
	static const std::string getTimestamp();
	static const std::string& getVersion();
	static const void makeSignature(std::string& signature, const std::string& key, const std::string& value);
};

}

#endif /* OAUTHUTIL_H_ */
