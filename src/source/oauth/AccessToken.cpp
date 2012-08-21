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

AccessToken::AccessToken(const std::string& token, const std::string& tokenSecret, long userId, const std::string& screenName)
:token_(new string(token)),
 tokenSecret_(new string(tokenSecret)),
 userId_(userId),
 screenName_(new string(screenName))
{
}

AccessToken::~AccessToken() {
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

AccessToken AccessToken::createInstance(const http::HttpResponse response) {
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

	//TODO hack later
	if(regexec(&preg, body.c_str(), nmatch, pmatch ,0) != 0){
	}else{
		RegexUtil::assignRegexValue(body,pmatch[indexToken],token);
		RegexUtil::assignRegexValue(body,pmatch[indexTokenSecret],tokenSecret);
		RegexUtil::assignRegexValue(body,pmatch[indexUserId],userId);
		RegexUtil::assignRegexValue(body,pmatch[indexScreenName],screenName);

		cout << "TOKEN  :" << token << endl;
		cout << "S_TOKEN:" << tokenSecret << endl;
		cout << "USER_ID:" << userId << endl;
		cout << "SC_NAME:" << screenName << endl;
	}

	return AccessToken(token,tokenSecret, atol(userId.c_str()),screenName);
	//"oauth_token=408291974-SnnDYEe3ys3iIKtFDnb18LibeAe9QlzGd0Uk65f6&oauth_token_secret=RZ9vp0sSKzTBbua9njuc27snURWAyTBJtpqTezsqfg&user_id=408291974&screen_name=ascii1020"
}

const std::string& AccessToken::getToken() const {
	return *token_;
}

const std::string& AccessToken::getTokenSecret() const {
	return *tokenSecret_;
}

}
/* namespace oauth */
