/*
 * Date.cpp
 *
 *  Created on: 2012/08/15
 */

#include "TwitterDate.h"
#include "RegexUtil.h"
#include <iostream>
#include <sstream>
#include <regex.h>
#include <DateUtil.h>

using namespace std;


TwitterDate::TwitterDate()
:year_(-1),
 month_(-1),
 date_(-1),
 dayOfWeek_(-1),
 hour_(-1),
 minute_(-1),
 second_(-1){
}

TwitterDate::~TwitterDate() {
}

//文字列からインスタンスを生成する
TwitterDate* TwitterDate::createPointerInstance(const string& dateStr) {
	return new TwitterDate(createInstance(dateStr));
}

TwitterDate TwitterDate::createInstance(const std::string& dateStr) {
	regex_t preg;
	if(regcomp(&preg,"^([A-Z][a-z][a-z]) ([A-Z][a-z][a-z]) ([0-9]{2}) ([0-9]{2}):([0-9]{2}):([0-9]{2}) \\+0000 ([0-9]{4})$",REG_EXTENDED) != 0){
		printf("regex compile filed");
	}

	int nmatch = 8;
	regmatch_t pmatch[nmatch];

	TwitterDate date;
	if(regexec(&preg, dateStr.c_str(), nmatch, pmatch ,0) != 0){
	}else{
		int indexDayOfWeek = 1;
		int indexMonth = 2;
		int indexDate = 3;
		int indexHour = 4;
		int indexMinute = 5;
		int indexSecond = 6;
		int indexYear = 7;

		string strDayOfWeek;
		string strMonth;
		string strDate;
		string strHour;
		string strMinute;
		string strSecond;
		string strYear;

		RegexUtil::assignRegexValue(dateStr,pmatch[indexDayOfWeek],strDayOfWeek);
		RegexUtil::assignRegexValue(dateStr,pmatch[indexMonth],strMonth);
		RegexUtil::assignRegexValue(dateStr,pmatch[indexDate],strDate);
		RegexUtil::assignRegexValue(dateStr,pmatch[indexHour],strHour);
		RegexUtil::assignRegexValue(dateStr,pmatch[indexMinute],strMinute);
		RegexUtil::assignRegexValue(dateStr,pmatch[indexSecond],strSecond);
		RegexUtil::assignRegexValue(dateStr,pmatch[indexYear],strYear);

		date.year_ = atoi(strYear.c_str());
		date.month_ = DateUtil::convertToIntMonth(strMonth);
		date.date_ = atoi(strDate.c_str());
		date.dayOfWeek_ = DateUtil::convertToIntDayOfWeek(strDayOfWeek);
		date.hour_ = atoi(strHour.c_str());
		date.minute_ = atoi(strMinute.c_str());
		date.second_ = atoi(strSecond.c_str());
	}

	return date;
}

std::string TwitterDate::toString(StringTemplate strTemplate) const {
	ostringstream oss;
	switch(strTemplate){
		case DEFAULT:
			oss << year_ << "/";
			oss << month_ << "/";
			oss << date_ << " ";
			oss << hour_ << ":";
			oss << minute_ << ":";
			oss << second_;
			break;
		default:
			break;
	}
	return oss.str();
}

