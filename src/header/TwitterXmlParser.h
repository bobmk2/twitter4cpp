/*
 * TwitterXmlParser.h
 *
 *  Created on: 2012/08/29
 */

#ifndef TWITTERXMLPARSER_H_
#define TWITTERXMLPARSER_H_

#include <vector>
#include "HttpResponse.h"
#include "Tweet.h"

class  TwitterXmlParser{
private:
	TwitterXmlParser();

public:

	/**
	 * @brief レスポンスをパースして、ツイートを読み込む
	 * @param[in] tweetList 読み込んだ
	 * @param res
	 * @return 読み込めたらtrue、何からの理由で読み込みに失敗した場合はfalse
	 */
	static bool parseStatusXml(std::vector<Tweet*>* const tweetList, const http::HttpResponse& res);
};

#endif /* TWITTERXMLPARSER_H_ */
