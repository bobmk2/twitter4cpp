/*
 * TimeUtil.cpp
 *
 *  Created on: 2012/08/15
 */

#include "TimeUtil.h"

using namespace std;


TimeUtil::TimeUtil() {
}

const void TimeUtil::toFormatedStr(string* toStr, const time_t& fromTime, const string& format) {
	if(toStr == NULL){return;}

	char buf[BUF_MAX_LENGTH];

	tm* tmptm = localtime(&fromTime);
	strftime(buf,BUF_MAX_LENGTH, format.c_str(),tmptm);
	*toStr = string(buf);
}

const void TimeUtil::toFormatedTime(time_t* toTime, const string& fromStr, const string& format) {
	if(toTime == NULL){return;}
	struct tm tmpTm;
	strptime(fromStr.c_str(),format.c_str(),&tmpTm);
	*toTime = mktime(&tmpTm);
}


