/*
 * TwitterDate.h
 *
 *  Created on: 2012/08/15
 */

#ifndef TWITTERDATE_H_
#define TWITTERDATE_H_

#include <string>

/**
 * @brief 日付クラス
 * @note WxWidgetsからstrptimeを触る際に、振るまいが異なったので専用の日付クラスを作った。
 */
class TwitterDate {
private:
	int year_;	//!< 年（西暦）
	int month_;	//!< 月（01〜12)
	int date_;	//!< 日（01〜31）

	int dayOfWeek_;	//!< 曜日(0〜6)

	int hour_;	//!< 時（00〜23)
	int minute_;//!< 分（00〜59)
	int second_;//!< 秒（00〜59）

public:
	enum StringTemplate{
		DEFAULT
	};

	TwitterDate();
	static TwitterDate createInstance(const std::string& dateStr);
	static TwitterDate* createPointerInstance(const std::string& dateStr);
	virtual ~TwitterDate();
	std::string toString(StringTemplate strTemplate) const;
};

#endif /* DATE_H_ */
