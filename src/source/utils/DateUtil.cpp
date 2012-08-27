/*
 * DateUtil.cpp
 *
 *  Created on: 2012/08/21
 */

#include "DateUtil.h"

using namespace std;

map<string, int> DateUtil::monthMap_;
map<string, int> DateUtil::dayOfWeekMap_;

DateUtil::DateUtil() {
}

void DateUtil::init() {
	monthMap_["Jan"] = 1;
	monthMap_["Feb"] = 2;
	monthMap_["Mar"] = 3;
	monthMap_["Apr"] = 4;
	monthMap_["May"] = 5;
	monthMap_["Jun"] = 6;
	monthMap_["Jul"] = 7;
	monthMap_["Aug"] = 8;
	monthMap_["Sep"] = 9;
	monthMap_["Oct"] = 10;
	monthMap_["Nov"] = 11;
	monthMap_["Dec"] = 12;

	dayOfWeekMap_["Sun"] = 0;
	dayOfWeekMap_["Mon"] = 1;
	dayOfWeekMap_["Tue"] = 2;
	dayOfWeekMap_["Wed"] = 3;
	dayOfWeekMap_["Thu"] = 4;
	dayOfWeekMap_["Fri"] = 5;
	dayOfWeekMap_["Sat"] = 6;
}

bool DateUtil::isInitialized() {
	if(monthMap_.size() == 0 || dayOfWeekMap_.size() == 0){
		return false;
	}
	return true;
}

int DateUtil::convertToIntMonth(const std::string& strMonth) {
	if(!isInitialized()){
		init();
	}

	if(monthMap_.find(strMonth) != monthMap_.end()){
		return monthMap_[strMonth];
	}
	return -1;
}

int DateUtil::convertToIntDayOfWeek(const std::string& strMonth) {
	if(!isInitialized()){
		init();
	}

	if(dayOfWeekMap_.find(strMonth) != dayOfWeekMap_.end()){
		return dayOfWeekMap_[strMonth];
	}
	return -1;
}
