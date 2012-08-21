/*
 * TwitterImplementer.cpp
 *
 *  Created on: 2012/08/13
 */

#include "TwitterImplementer.h"
#include "OAuthUtil.h"
#include "StringUtil.h"
#include "HttpUrlConnection.h"
#include "URL.h"
#include <iostream>
#include "tinyxml/tinyxml2.h"
#include "ApiParameter.h"
#include "User.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace oauth;
using namespace http;
using namespace tinyxml2;

TwitterImplementer::TwitterImplementer(const std::string& consumerKey, const std::string& consumerSecret,
		const std::string& oauthToken, const std::string& oauthTokenSecret)
:Twitter(consumerKey,consumerSecret, oauthToken, oauthTokenSecret)
{

}

TwitterImplementer::~TwitterImplementer() {
}

void TwitterImplementer::updateStatus(std::string text) {
	string method = "POST";
	string url = STATUS_UPDATESTATUS_URL;
	string nonce = OAuthUtil::getNonce();
	string timestamp = OAuthUtil::getTimestamp();

	string str;
	str += "include_entities=true&";
	str += "oauth_consumer_key=" + *consumerKey_ + "&";
	str += "oauth_nonce=" + nonce + "&";
	str += "oauth_signature_method=HMAC-SHA1&";
	str += "oauth_timestamp=" + timestamp + "&";
	str += "oauth_token=" + *oauthToken_ + "&";
	str += "oauth_version=1.0&";
	str += "status=" + StringUtil::urlEncode(text);

	//signatureの元となる文字列を生成
	string sigBase = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(url) + "&" + StringUtil::urlEncode(str);

	//signatureを作る
	string signature;
	OAuthUtil::makeSignature(signature, *consumerSecret_ + "&" + *oauthTokenSecret_, sigBase);

	url += "?" + str + "&oauth_signature=" + signature;

	string body = "status=" + StringUtil::urlEncode(text);

	URL postUrl(url);
	HttpUrlConnection urlConn(url);
	urlConn.setRequestMethod(method);
	urlConn.putHeader("Authorization", "OAuth");

	HttpResponse response = urlConn.getResponse();
	response.print();
}

void TwitterImplementer::test(){
	URL postUrl("http://cboard.cprogramming.com/c-programming/89870-check-eof-when-using-fgets.html");
	HttpUrlConnection urlConn(postUrl);

	cout << "---------------- getResponse--------------" << endl;
	HttpResponse response = urlConn.getResponse();
	cout << "---------------- getResponse finish()--------------" << endl;
	response.print();

}

int TwitterImplementer::getHomeTimeline(std::vector<Tweet*>* const tweetList, unsigned int count,unsigned long sinceId,unsigned long maxId,unsigned int page) const{
	string method = "GET";
	string url = TIMELINE_HOMETIMELINE_URL;
	string nonce = OAuthUtil::getNonce();
	string timestamp = OAuthUtil::getTimestamp();

	ApiParameter para;
	para.put("include_entities","true");
	para.put("oauth_consumer_key", *consumerKey_);
	para.put("oauth_nonce", nonce);
	para.put("oauth_signature_method", "HMAC-SHA1");
	para.put("oauth_timestamp", timestamp);
	para.put("oauth_token", *oauthToken_);
	para.put("oauth_version","1.0");
	if(count != DEFAULT_LOAD_COUNT){para.put("count",StringUtil::toStr(count));}
	if(maxId != UNUSED){para.put("max_id",StringUtil::toStr(maxId));}
	if(sinceId != UNUSED){para.put("since_id",StringUtil::toStr(sinceId));}
	if(page != UNUSED){para.put("page",StringUtil::toStr(page));}

	string paraStr = para.toUrlString();

	//signatureの元となる文字列を生成
	string sigBase = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(url) + "&" + StringUtil::urlEncode(paraStr);

	//signatureを作る
	string signature;
	OAuthUtil::makeSignature(signature, *consumerSecret_ + "&" + *oauthTokenSecret_, sigBase);

	url += "?" + paraStr + "&oauth_signature=" + signature;

	URL postUrl(url);
	HttpUrlConnection urlConn(postUrl);
	urlConn.setRequestMethod(method);
	urlConn.putHeader("Authorization", "OAuth");

	HttpResponse response = urlConn.getResponse();
	response.print();

	XMLDocument doc;
	doc.Parse(response.getBody().c_str());
	XMLElement* statuses = doc.FirstChildElement("statuses");

	XMLElement* status = statuses->FirstChildElement("status");

	while(status != NULL){
		Tweet* tweet = new Tweet();
		tweet->setId(atol(status->FirstChildElement("id")->GetText()));
		tweet->setText(status->FirstChildElement("text")->GetText());
		tweet->setSource(status->FirstChildElement("source")->GetText());
		tweet->setFromUserScreenName(status->FirstChildElement("user")->FirstChildElement("screen_name")->GetText());
		tweet->setFromUserName(status->FirstChildElement("user")->FirstChildElement("name")->GetText());

		XMLElement* userElement = status->FirstChildElement("user");
		const char* id = userElement->FirstChildElement("id")->GetText();
		const char* name = userElement->FirstChildElement("name")->GetText();
		const char* screenName = userElement->FirstChildElement("screen_name")->GetText();
		const char* location = userElement->FirstChildElement("location")->GetText();
		const char* profileImageUrl = userElement->FirstChildElement("profile_image_url")->GetText();
		const char* profileImageUrlHttps = userElement->FirstChildElement("profile_image_url_https")->GetText();
		const char* url = userElement->FirstChildElement("url")->GetText();
		const char* desc = userElement->FirstChildElement("description")->GetText();

		User user;
		user.setId(atoi(id));
		if(name != NULL){user.setName(name);}
		if(screenName != NULL){user.setScreenName(screenName);}
		if(location != NULL){user.setLocation(location);}
		if(profileImageUrl != NULL){user.setProfileImageUrl(profileImageUrl);}
		if(profileImageUrlHttps != NULL){user.setProfileImageUrlHttps(profileImageUrlHttps);}
		if(url != NULL){user.setUrl(url);}
		if(desc != NULL){user.setDescription(desc);}
		//TODO add later

		tweet->setUser(user);
		/*
		const char* format = "%a %b %d %H:%M:%S +0000 %Y";

		struct tm createdAt;
		strptime(status->FirstChildElement("created_at")->GetText(),format,&createdAt);

		char buf[256];
		sprintf(buf, "%d %d",createdAt.tm_year,createdAt.tm_mon);
		cout << "PARSED: " << buf << endl;

		time_t ttt = mktime(&createdAt);
		tweet->setCreatedAt(ttt);
		 */
		//time_t t = mktime(NULL);
		//tweet->setCreatedAt(t);

		tweetList->push_back(tweet);

		status = status->NextSiblingElement("status");
	}

	return 1;
}
