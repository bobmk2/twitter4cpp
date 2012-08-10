/*
 * OAuthManager.cpp
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#include "OAuthManager.h"
#include "OAuthUtil.h"
#include "StringUtil.h"


#include "HttpRequest.h"

#include <iostream>

using namespace std;


const string OAuthManager::OAUTH_VERSION = "1.0";

OAuthManager::OAuthManager() {

}

OAuthManager::~OAuthManager() {
}


string OAuthManager::getRequestParameter(const string& consumerKey, string& nonce, string& timestamp) {
	string str;// = "GET&";

	//nonce = "CT0%26Oz%22W";// OAuthUtil::getNonce();
	nonce = OAuthUtil::getNonce();
	timestamp = OAuthUtil::getTimestamp();

	//str += OAuthUtil::getRequestUrl() + "&";
	str += "oauth_consumer_key=" + consumerKey + "&";
	str += "oauth_nonce="+ nonce +"&";
	str += "oauth_signature_method=" + OAuthUtil::getSignatureMethod() + "&";
	str += "oauth_timestamp=" + timestamp + "&";

	//str += "oauth_timestamp=1344566300&";

	str += "oauth_version=" + OAuthUtil::getVersion();
	return str;
}

void OAuthManager::getRequestToken(const string& consumerKey, const string& consumerSecret) {
	string method = "POST";
	string url = OAuthUtil::getRequestUrl();

	string nonce;
	string timestamp;
	string body = getRequestParameter(consumerKey, nonce,timestamp);
	cout << "$  " << body << endl;
	cout << "$$ " << "oauth_consumer_key=y5GQSPPBM9ZX4J7VQeWhbw&oauth_nonce=CT0%26Oz%22W&oauth_signature_method=HMAC-SHA1&oauth_timestamp=1344566300&oauth_version=1.0" << endl;

	//"oauth_consumer_key=y5GQSPPBM9ZX4J7VQeWhbw&oauth_nonce=CT0%26Oz%22W&oauth_signature_method=HMAC-SHA1&oauth_timestamp=1344566300&oauth_version=1.0"
	// GET&http%3A%2F%2Ftwitter.com%2Foauth%2Frequest_token&oauth_consumer_key%3Dy5GQSPPBM9ZX4J7VQeWhbw%26oauth_nonce%3DCT0%2526Oz%2522W%26oauth_signature_method%3DHMAC-SHA1%26oauth_timestamp%3D1344566300%26oauth_version%3D1.0
	// sig: FsqOeppvHZQKugXO3MzSjWiyFlc%3D

	string sigBase = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(url) + "&" + StringUtil::urlEncode(body);

	cout << "#  " << sigBase << endl;
	cout << "## " << "GET&http%3A%2F%2Ftwitter.com%2Foauth%2Frequest_token&oauth_consumer_key%3Dy5GQSPPBM9ZX4J7VQeWhbw%26oauth_nonce%3DCT0%2526Oz%2522W%26oauth_signature_method%3DHMAC-SHA1%26oauth_timestamp%3D1344566300%26oauth_version%3D1.0" << endl;

	for(int i=0;i<sigBase.length();i++){
		cout << "[" << i << "]" << sigBase[i] << endl;
	}

	string signature;

	OAuthUtil::makeSignature(signature,consumerSecret + "&", sigBase);

	cout << "*  " << signature << endl;
	cout << "** " << "FsqOeppvHZQKugXO3MzSjWiyFlc%3D" << endl;

	string header = "OAuth ";
	header += "oauth_nonce="+ nonce +",";
	header += "oauth_signature_method=" + OAuthUtil::getSignatureMethod() + ",";
	header += "oauth_timestamp=" + timestamp + ",";
	header += "oauth_consumer_key=" + consumerKey + ",";
	header += "oauth_signature=" +signature+",";
	header += "oauth_version=" + OAuthUtil::getVersion();

	//cout << header << endl;

	/*
	string reqStr = "POST /oauth/request_token HTTP/1.1\r\n";
	reqStr += "Host:twitter.com\r\n";
	reqStr += "Content-Length:0\r\n";
	reqStr += "Authorization Header:" + header + "\r\n";
	reqStr += "\r\n";

	cout << reqStr << endl;
	*/

	//string ssss =   "http://twitter.com/oauth/request_token?"+body+"&oauth_signature="+signature;


	//cout << ssss << endl;
	//cout << urlStr << endl;

	string urlStr = "http://twitter.com/oauth/request_token?" +  body + "&oauth_signature=" + signature;
	cout << urlStr << endl;
	HttpRequest::URL reqUrl(OAuthUtil::getRequestUrl());
	HttpRequest req(reqUrl);
	req.setMethod(method);
	req.putHeader("Authorization",header);
	req.execute();


}


/*
void mastermakeSignature(string& signature, const string& consumerSecret, const string& baseStr) {
	char sha1Buf[1024];
	char base64buf[1024];

	//1. hash_hmacで16進数のダイジェスト値に変換
	hmac_sha1(consumerSecret.c_str(),consumerSecret.size(),baseStr.c_str(),baseStr.size(),sha1Buf);

	//2. base64でエンコード
	base64_encode(sha1Buf,20,base64buf,64);

	//3. それをurlencode
	signature = StringUtil::urlEncode(base64buf);
}

void makeSignature(string& signature, const string& consumerSecret, const string& method, const string& url, const string& body) {
	char sha1Buf[1024];
	char base64buf[1024];

	//元になる文字列を生成
	string baseStr = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(url) + "&" + StringUtil::urlEncode(body);

	//1. hash_hmacで16進数のダイジェスト値に変換
	hmac_sha1(consumerSecret.c_str(),consumerSecret.size(),baseStr.c_str(),baseStr.size(),sha1Buf);

	//2. base64でエンコード
	base64_encode(sha1Buf,20,base64buf,64);

	//3. それをurlencode
	//signature = StringUtil::urlEncode(StringUtil::encodeBase64(base64buf));
	signature = StringUtil::urlEncode(base64buf);
}

void OAuthManager::testSha1(string key, string value) {
	char sha1Buf[1024];
	memset(sha1Buf,1024,'\0');
	hmac_sha1(key.c_str(),key.size(),value.c_str(),value.size(),sha1Buf);
	cout << sha1Buf << endl;
}

void OAuthManager::testBase64(string value) {
	char buf[1024];
	memset(buf,1024,'\0');
	base64_encode(value.c_str(),value.size(),buf,64);
	string mem = StringUtil::urlEncode(buf);
	//string buf = StringUtil::urlEncode(StringUtil::encodeBase64("abcdefgh1jk"));
	cout << mem << endl;
}

void OAuthManager::testEncode(string key, string value) {
	char sha1Buf[1024];
	char base64buf[1024];
	memset(sha1Buf,1024,'\0');
	hmac_sha1(key.c_str(),key.size(),value.c_str(),value.size(),sha1Buf);
	base64_encode(sha1Buf,20,base64buf,64);
	cout << base64buf << endl;
}
*/
