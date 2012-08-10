/*
 * OAuthManager.h
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#ifndef OAUTHMANAGER_H_
#define OAUTHMANAGER_H_

using namespace std;

#include <string>

class OAuthManager {

private:

	static const string OAUTH_VERSION;

	string getRequestParameter(const string& consumerKey, string& nonce,string& timestamp);

public:
	OAuthManager();
	virtual ~OAuthManager();

	void getRequestToken(const string& consumerKey, const string& consumerSecret);

	void testSha1(string key, string value);
	void testBase64(string value);
	void testEncode(string key, string value);

};


#endif /* OAUTHMANAGER_H_ */
