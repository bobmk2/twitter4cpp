/*
 * TokenFactory.cpp
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#include "TokenFactory.h"
#include "OAuthUtil.h"
#include "StringUtil.h"
#include "HttpUrlConnection.h"

#include "HttpRequest.h"

#include "AccessToken.h"

#include <iostream>

using namespace std;
using namespace http;
using namespace oauth;


const string TokenFactory::OAUTH_VERSION = "1.0";

TokenFactory::TokenFactory() {
}

TokenFactory::~TokenFactory() {
}


string TokenFactory::getRequestParameter(const string& consumerKey, string& nonce, string& timestamp) {
	string str;// = "GET&";

	nonce = OAuthUtil::getNonce();
	timestamp = OAuthUtil::getTimestamp();

	str += "oauth_consumer_key=" + consumerKey + "&";
	str += "oauth_nonce="+ nonce +"&";
	str += "oauth_signature_method=" + OAuthUtil::getSignatureMethod() + "&";
	str += "oauth_timestamp=" + timestamp + "&";

	str += "oauth_version=" + OAuthUtil::getVersion();
	return str;
}

string TokenFactory::getAccessTokenParameter(const string& consumerKey, string& nonce, string& timestamp, const RequestToken& reqToken , const string& pin) {
	string str;// = "GET&";

	nonce = OAuthUtil::getNonce();
	timestamp = OAuthUtil::getTimestamp();

	str += "oauth_consumer_key=" + consumerKey + "&";
	str += "oauth_nonce="+ nonce +"&";
	str += "oauth_signature_method=" + OAuthUtil::getSignatureMethod() + "&";
	str += "oauth_timestamp=" + timestamp + "&";
	str += "oauth_token=" + reqToken.getToken()  + "&";
	str += "oauth_verifier=" + pin + "&";
	str += "oauth_version=" + OAuthUtil::getVersion();
	return str;
}

void TokenFactory::getRequestToken(const string& consumerKey, const string& consumerSecret) {
	string method = "POST";
	string url = OAuthUtil::OAUTH_REQUEST_TOKEN_URL;

	string nonce;
	string timestamp;
	string body = getRequestParameter(consumerKey, nonce,timestamp);

	string sigBase = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(url) + "&" + StringUtil::urlEncode(body);

	for(int i=0;i<sigBase.length();i++){
		cout << "[" << i << "]" << sigBase[i] << endl;
	}

	string signature;

	OAuthUtil::makeSignature(signature,consumerSecret + "&", sigBase);

	string header = "OAuth ";
	header += "oauth_nonce="+ nonce +",";
	header += "oauth_signature_method=" + OAuthUtil::getSignatureMethod() + ",";
	header += "oauth_timestamp=" + timestamp + ",";
	header += "oauth_consumer_key=" + consumerKey + ",";
	header += "oauth_signature=" +signature+",";
	header += "oauth_version=" + OAuthUtil::getVersion();

	string urlStr = "http://twitter.com/oauth/request_token?" +  body + "&oauth_signature=" + signature;
	cout << urlStr << endl;
	HttpRequest::URL reqUrl(OAuthUtil::OAUTH_REQUEST_TOKEN_URL);
	HttpRequest req(reqUrl);
	req.setMethod(method);
	req.putHeader("Authorization",header);
	req.execute();


}

RequestToken* TokenFactory::createRequestToken(const string& consumerKey, const string& consumerSecret) {
	string method = "POST";

	string nonce;
	string timestamp;
	string body = getRequestParameter(consumerKey, nonce,timestamp);

	string sigBase = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(OAuthUtil::OAUTH_REQUEST_TOKEN_URL) + "&" + StringUtil::urlEncode(body);

	string signature;
	OAuthUtil::makeSignature(signature,consumerSecret + "&", sigBase);

	string header = "OAuth ";
	header += "oauth_nonce="+ nonce +",";
	header += "oauth_signature_method=" + OAuthUtil::getSignatureMethod() + ",";
	header += "oauth_timestamp=" + timestamp + ",";
	header += "oauth_consumer_key=" + consumerKey + ",";
	header += "oauth_signature=" +signature+",";
	header += "oauth_version=" + OAuthUtil::getVersion();

	URL reqUrl(OAuthUtil::OAUTH_REQUEST_TOKEN_URL);
	HttpUrlConnection urlConn(reqUrl);
	urlConn.setRequestMethod("POST");
	urlConn.putHeader("Authorization", header);

	HttpResponse response = urlConn.getResponse();
	response.print();

	return RequestToken::createInstance(response);
}

oauth::AccessToken* TokenFactory::createAccessToken(const std::string& consumerKey, const std::string& consumerSecret,
		const oauth::RequestToken& reqToken, const std::string& pin) {
	cout << "PIN:" << pin << "(" << pin.length() << ")" << endl;

	string method = "POST";

	string nonce;
	string timestamp;
	string body = getAccessTokenParameter(consumerKey, nonce,timestamp, reqToken, pin);

	string sigBase = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(OAuthUtil::OAUTH_ACCESS_TOKEN_URL) + "&" + StringUtil::urlEncode(body);

	string signature;
	OAuthUtil::makeSignature(signature,consumerSecret + "&" + reqToken.getTokenSecret(), sigBase);

	string header = "OAuth ";
	header += "oauth_nonce="+ nonce +",";
	header += "oauth_signature_method=" + OAuthUtil::getSignatureMethod() + ",";
	header += "oauth_timestamp=" + timestamp + ",";
	header += "oauth_consumer_key=" + consumerKey + ",";
	header += "oauth_signature=" +signature+",";
	header += "oauth_token=" + reqToken.getToken()  + ",";
	header += "oauth_verifier=" + pin + ",";
	header += "oauth_version=" + OAuthUtil::getVersion();

	URL reqUrl(OAuthUtil::OAUTH_ACCESS_TOKEN_URL);
	HttpUrlConnection urlConn(reqUrl);
	urlConn.setRequestMethod("POST");
	urlConn.putHeader("Authorization", header);

	HttpResponse response = urlConn.getResponse();
	response.print();

	return AccessToken::createInstance(response);

}
