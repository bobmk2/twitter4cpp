/*
 * TimeUtil.h
 *
 *  Created on: 2012/08/15
 */

#ifndef TIMEUTIL_H_
#define TIMEUTIL_H_

#include <time.h>
#include <string>

/**
 * @brief 時間に関連するユーティリティクラス
 */
class TimeUtil {
private:
	static const int BUF_MAX_LENGTH = 256;
	TimeUtil();
public:
	static const void toFormatedStr(std::string* toStr, const time_t& fromTime,const std::string& format);
	static const void toFormatedTime(time_t* toTime, const std::string& fromStr, const std::string& format);
};

#endif /* TIMEUTIL_H_ */
