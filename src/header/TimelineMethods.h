/*
 * TimelineMethods.h
 *
 *  Created on: 2012/08/13
 */

#ifndef TIMELINEMETHODS_H_
#define TIMELINEMETHODS_H_

#include <vector>
#include <string>
#include "Tweet.h"

namespace method{

/**
 * @brief ツイートを取得するためのメソッド群を持つインターフェース
 */
class TimelineMethods {
public:
	class TimeLineParameter;
protected:
	static const std::string TIMELINE_HOMETIMELINE_URL; //!< HomeTimeLineを取得するAPIのURL
	static const unsigned int DEFAULT_LOAD_COUNT = 20;	//!< 読み込むツイート数の初期値
	static const unsigned int UNUSED = -1;				//!< 使わないパラメータには-1が入る

	TimelineMethods();
public:
	virtual ~TimelineMethods();

	/**
	 * @brief 認証ユーザのHomeTimeLineを取得する
	 * @param[in] tweetList ツイート格納用のリスト
	 * @param count		読み込むツイート数
	 * @param sinceId	このID以降のツイートを読み込むためのツイートID
	 * @param maxId		このID以下のツイートを読み込むためのツイート
	 * @param page		ページ番号
	 * @return
	 */
	virtual int getHomeTimeline(
			std::vector<Tweet*>* const tweetList,
			unsigned int count = DEFAULT_LOAD_COUNT,
			unsigned long sinceId = UNUSED,
			unsigned long maxId = UNUSED,
			unsigned int page = UNUSED
	) const = 0;
};

}
#endif /* TIMELINEMETHODS_H_ */
