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

using namespace std;

class OAuthUtil {
private:
	static const string OAUTH_REQUEST_URL;
	static const string SIGNATURE_METHOD;
	static const string OAUTH_VERSION;

	OAuthUtil();
public:
	static const string getRequestUrl();
	static const string getNonce();
	static const string& getSignatureMethod();
	static const string getTimestamp();
	static const string& getVersion();
	static const void makeSignature(string& signature, const string& key, const string& value);
};

#endif /* OAUTHUTIL_H_ */
