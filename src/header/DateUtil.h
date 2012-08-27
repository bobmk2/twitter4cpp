/*
 * DateUtil.h
 *
 *  Created on: 2012/08/21
 */

#ifndef DATEUTIL_H_
#define DATEUTIL_H_

#include <string>
#include <map>

/**
 * @brief 日付用ユーティリティクラス
 */
class DateUtil {
private:
	static std::map<std::string, int> monthMap_;	//!< 月文字列を数値の月に変換するためのマップ
	static std::map<std::string, int> dayOfWeekMap_;//!< 曜日文字列を数値の曜日に変換するためのマップ

	static void init();
	static bool isInitialized();

	DateUtil();
public:

	static int convertToIntMonth(const std::string& strMonth);
	static int convertToIntDayOfWeek(const std::string& strDayOfWeek);
};

#endif /* DATEUTIL_H_ */
