/*
 * AccessToken.cpp
 *
 *  Created on: 2012/08/10
 */

#include "AccessToken.h"
#include "RegexUtil.h"
#include <regex.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace http;

namespace oauth {

AccessToken::AccessToken()
:token_(new string()),
 tokenSecret_(new string()),
 userId_(-1),
 screenName_(new string())
{
}

AccessToken::AccessToken(const string& token, const string& tokenSecret)
:token_(new string(token)),
 tokenSecret_(new string(tokenSecret)),
 userId_(-1),
 screenName_(new string())
{
	//TODO userIdはtokenから特定可能
}

AccessToken::AccessToken(const string& token, const string& tokenSecret, long userId, const string& screenName)
:token_(new string(token)),
 tokenSecret_(new string(tokenSecret)),
 userId_(userId),
 screenName_(new string(screenName))
{
}

AccessToken::~AccessToken() {
	delete(screenName_);
	delete(tokenSecret_);
	delete(token_);
}

AccessToken::AccessToken(const AccessToken& accessToken)
:token_(new string(*accessToken.token_)),
 tokenSecret_(new string(*accessToken.tokenSecret_)),
 userId_(accessToken.userId_),
 screenName_(new string(*accessToken.screenName_))
{
}

const AccessToken& AccessToken::operator =(const AccessToken& accessToken) {
	*token_ = *accessToken.token_;
	*tokenSecret_ = *accessToken.tokenSecret_;
	userId_ = accessToken.userId_;
	*screenName_ = *accessToken.screenName_;
	return *this;
}

AccessToken* AccessToken::createInstance(const http::HttpResponse response) {
	string body = response.getBody();

	regex_t preg;

	if(regcomp(&preg,"^oauth_token=(.*)?&oauth_token_secret=(.*)?&user_id=(.*)?&screen_name=(.*)?",REG_EXTENDED|REG_NEWLINE) != 0){
		printf("regex compile filed");
	}

	int nmatch = 5;
	regmatch_t pmatch[5];

	int indexToken = 1;
	int indexTokenSecret = 2;
	int indexUserId= 3;
	int indexScreenName= 4;


	string token;
	string tokenSecret;
	string userId;
	string screenName;

	AccessToken* accessToken = NULL;
	//TODO hack later
	if(regexec(&preg, body.c_str(), nmatch, pmatch ,0) != 0){
	}else{
		RegexUtil::assignRegexValue(body,pmatch[indexToken],token);
		RegexUtil::assignRegexValue(body,pmatch[indexTokenSecret],tokenSecret);
		RegexUtil::assignRegexValue(body,pmatch[indexUserId],userId);
		RegexUtil::assignRegexValue(body,pmatch[indexScreenName],screenName);

		accessToken = new AccessToken(token,tokenSecret, atol(userId.c_str()),screenName);
	}

	return accessToken;
}

void AccessToken::setToken(const string& token) {
	*token_ = token;
}

void AccessToken::setTokenSecret(const string& tokenSecret) {
	*tokenSecret_ = tokenSecret;
}

void AccessToken::setUserId(const long & userId) {
	userId_ = userId;
}

void AccessToken::setScreenName(const string& screenName) {
	*screenName_ = screenName;
}

const string* AccessToken::getToken() const {
	return token_;
}

const string* AccessToken::getTokenSecret() const {
	return tokenSecret_;
}

long AccessToken::getUserId() const{
	return userId_;
}

const string* AccessToken::getScreenName() const{
	return screenName_;
}

}




/* namespace oauth */
