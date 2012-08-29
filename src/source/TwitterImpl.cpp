/*
 * TwitterImpl.cpp
 *
 *  Created on: 2012/08/13
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "tinyxml/tinyxml2.h"

#include "TwitterImpl.h"
#include "OAuthUtil.h"
#include "StringUtil.h"
#include "HttpUrlConnection.h"
#include "URL.h"
#include "ApiParameter.h"
#include "User.h"
#include "TwitterXmlParser.h"

using namespace std;
using namespace oauth;
using namespace http;
using namespace tinyxml2;


TwitterImpl::TwitterImpl(const std::string& consumerKey, const std::string& consumerSecret,
		const std::string& oauthToken, const std::string& oauthTokenSecret)
:Twitter(consumerKey,consumerSecret, oauthToken, oauthTokenSecret)
{

}

TwitterImpl::~TwitterImpl() {
}

void TwitterImpl::updateStatus(const std::string& text,const long& replyTo) const{
	string method = "POST";
	string url = STATUS_UPDATESTATUS_URL;
	string nonce = OAuthUtil::getNonce();
	string timestamp = OAuthUtil::getTimestamp();

	ApiParameter para;
	para.put("include_entities","true");
	para.put("oauth_consumer_key",*consumerKey_);
	para.put("oauth_nonce",nonce);
	para.put("oauth_signature_method","HMAC-SHA1");
	para.put("oauth_timestamp",timestamp);
	para.put("oauth_token",*oauthToken_);
	para.put("oauth_version","1.0");
	para.put("status",StringUtil::urlEncode(text));
	if(replyTo != -1){
		para.put("in_reply_to_status_id", StringUtil::toStr(replyTo));
	}

	//signatureの元となる文字列を生成
	string sigBase = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(url) + "&" + StringUtil::urlEncode(para.toUrlString());

	//signatureを作る
	string signature;
	OAuthUtil::makeSignature(signature, *consumerSecret_ + "&" + *oauthTokenSecret_, sigBase);

	url += "?" + para.toUrlString() + "&oauth_signature=" + signature;

	string body = "status=" + StringUtil::urlEncode(text);

	URL postUrl(url);
	HttpUrlConnection urlConn(url);
	urlConn.setRequestMethod(method);
	urlConn.putHeader("Authorization", "OAuth");

	HttpResponse response = urlConn.getResponse();
	response.print();
}

int TwitterImpl::getHomeTimeline(std::vector<Tweet*>* const tweetList, unsigned int count,unsigned long sinceId,unsigned long maxId,unsigned int page) const{
	string method = "GET";
	string url = TIMELINE_HOMETIMELINE_URL;

	//ランダム文字列と現在時間を取得
	string nonce = OAuthUtil::getNonce();
	string timestamp = OAuthUtil::getTimestamp();

	//パラメータを格納していく
	ApiParameter para;
	para.put("include_entities","true");
	para.put("oauth_consumer_key", *consumerKey_);
	para.put("oauth_nonce", nonce);
	para.put("oauth_signature_method", "HMAC-SHA1");
	para.put("oauth_timestamp", timestamp);
	para.put("oauth_token", *oauthToken_);
	para.put("oauth_version","1.0");

	if(count != DEFAULT_LOAD_COUNT){
		para.put("count",StringUtil::toStr(count));
	}

	if(maxId != UNUSED){
		para.put("max_id",StringUtil::toStr(maxId));
	}

	if(sinceId != -1){
		para.put("since_id",StringUtil::toStr(sinceId));
	}

	if(page != UNUSED){
		para.put("page",StringUtil::toStr(page));
	}

	//パラメータ部分の文字列を取得
	string paraStr = para.toUrlString();

	//signatureの元となる文字列を生成
	string sigBase = StringUtil::urlEncode(method) + "&" + StringUtil::urlEncode(url) + "&" + StringUtil::urlEncode(paraStr);

	//signatureを作る
	string signature;
	OAuthUtil::makeSignature(signature, *consumerSecret_ + "&" + *oauthTokenSecret_, sigBase);

	url += "?" + paraStr + "&oauth_signature=" + signature;

	//リクエストを送る
	URL postUrl(url);
	HttpUrlConnection urlConn(postUrl);
	urlConn.setRequestMethod(method);
	urlConn.putHeader("Authorization", "OAuth");

	//レスポンスを受け取る
	HttpResponse response = urlConn.getResponse();
	response.print();

	//Tweetを格納する
	TwitterXmlParser::parseStatusXml(tweetList, response);

	return 1;
}
