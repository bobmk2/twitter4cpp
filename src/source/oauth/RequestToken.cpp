/*
 * RequestToken.cpp
 *
 *  Created on: 2012/08/10
 */

#include "RequestToken.h"
#include "OAuthUtil.h"
#include "RegexUtil.h"
#include <regex.h>
#include <iostream>

using namespace std;
using namespace http;

namespace oauth {

RequestToken::RequestToken(const std::string& token, const std::string& tokenSecret)
:token_(new string(token)),
 tokenSecret_(new string(tokenSecret))
{
}

RequestToken::~RequestToken() {
	delete(tokenSecret_);
	delete(token_);
}

string RequestToken::getAuthenticationUrl() const{
	string url(OAuthUtil::OAUTH_OAUTHORIZE_URL);
	url += "?oauth_token=";
	url += *token_;
	return url;
}

RequestToken::RequestToken(const RequestToken& reqToken)
:token_(new string(*reqToken.token_)),
 tokenSecret_(new string(*reqToken.tokenSecret_)){
}

const RequestToken& RequestToken::operator=(const RequestToken& reqToken) {
	*token_ = *reqToken.token_;
	*tokenSecret_ = *reqToken.tokenSecret_;
	return *this;
}

RequestToken* RequestToken::createInstance(const http::HttpResponse response){
	string body = response.getBody();

	regex_t preg;
	if(regcomp(&preg,"^oauth_token=(.*)?&oauth_token_secret=(.*)?&",REG_EXTENDED|REG_NEWLINE) != 0){
		printf("regex compile filed");
	}

	int nmatch = 3;
	regmatch_t pmatch[3];

	int indexToken = 1;
	int indexTokenSecret = 2;

	string token;
	string tokenSecret;

	//TODO hack later
	RequestToken* reqToken = NULL;
	if(regexec(&preg, body.c_str(), nmatch, pmatch ,0) != 0){
	}else{
		RegexUtil::assignRegexValue(body,pmatch[indexToken],token);
		RegexUtil::assignRegexValue(body,pmatch[indexTokenSecret],tokenSecret);

		cout << "TOKEN:" << token << endl;
		cout << "S_TOKEN:" << tokenSecret << endl;
		reqToken = new RequestToken(token, tokenSecret);
	}

	return reqToken;
}

const string& RequestToken::getToken() const{
		return *token_;
}

const string& RequestToken::getTokenSecret() const{
	return *tokenSecret_;
}

}



/* namespace oauth */
