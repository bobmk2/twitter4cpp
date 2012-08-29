/*
 * TwitterXmlParser.cpp
 *
 *  Created on: 2012/08/29
 */

#include "TwitterXmlParser.h"
#include "tinyxml/tinyxml2.h"

using namespace std;
using namespace http;
using namespace tinyxml2;

TwitterXmlParser::TwitterXmlParser() {
}

bool TwitterXmlParser::parseStatusXml(vector<Tweet*>* const tweetList, const HttpResponse& res){
	XMLDocument doc;
	doc.Parse(res.getBody().c_str());
	XMLElement* statuses = doc.FirstChildElement("statuses");

	//何かしらの理由で読み込みに失敗している
	//@todo 理由を特定した上で例外として投げるように変更する
	if(statuses == NULL){
		return false;
	}

	XMLElement* status = statuses->FirstChildElement("status");
	while(status != NULL){
		Tweet* tweet = new Tweet();
		tweet->setId(atol(status->FirstChildElement("id")->GetText()));
		tweet->setText(status->FirstChildElement("text")->GetText());
		tweet->setSource(status->FirstChildElement("source")->GetText());
		tweet->setFromUserScreenName(status->FirstChildElement("user")->FirstChildElement("screen_name")->GetText());
		tweet->setFromUserName(status->FirstChildElement("user")->FirstChildElement("name")->GetText());

		//TODO hack later
		TwitterDate date = TwitterDate::createInstance(status->FirstChildElement("created_at")->GetText());
		tweet->setCreatedAt(date);

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
		//TODO add another element later

		tweet->setUser(user);

		tweetList->push_back(tweet);

		status = status->NextSiblingElement("status");
	}
	return true;
}
