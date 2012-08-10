/*
 * OAuthUtil.cpp
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#include <time.h>
#include <iostream>
#include <sstream>

#include "base64.h"
#include "hmac.h"

#include "StringUtil.h"
#include "OAuthUtil.h"

const string OAuthUtil::OAUTH_REQUEST_URL = "http://twitter.com/oauth/request_token";
const string OAuthUtil::SIGNATURE_METHOD = "HMAC-SHA1";
const string OAuthUtil::OAUTH_VERSION = "1.0";

OAuthUtil::OAuthUtil() {
}

const string OAuthUtil::getRequestUrl() {
	return OAUTH_REQUEST_URL;
}

const string OAuthUtil::getNonce() {
	uuid_t u;
	char buf[37];
	uuid_generate(u);
	uuid_unparse(u, buf);

	string str = buf;
	for(int pos = str.find("-");
			pos != string::npos;
			pos = str.find("-", 1 + pos))
	{
		str.replace(pos,1,"A");
	}

	return str;
}

const string& OAuthUtil::getSignatureMethod() {
	return SIGNATURE_METHOD;
}

const string& OAuthUtil::getVersion(){
	return OAUTH_VERSION;
}

const string OAuthUtil::getTimestamp() {
	time_t now;
	time(&now);

	stringstream ss;
	ss << now;

	return ss.str();
}

const void OAuthUtil::makeSignature(string& signature, const string& key, const string& value) {
	cout << "makeSig key: " << key << endl;
	cout << "makeSig val: " << value << endl;
	cout << "key size:" << key.length() << endl;
	cout << "val size:" << value.length() << endl;

	int bufLen = 1024;
	char sha1Buf[bufLen];
	char base64buf[bufLen];
	memset(sha1Buf,bufLen,'\0');
	memset(base64buf,bufLen,'\0');

	hmac_sha1(key.c_str(),key.size(),value.c_str(),value.size(),sha1Buf);
	base64_encode(sha1Buf,20,base64buf,64);
	signature = StringUtil::urlEncode(base64buf);
}
