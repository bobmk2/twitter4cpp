/*
 * URL.cpp
 *
 *  Created on: 2012/08/10
 */

#include "URL.h"
#include <regex.h>
#include "RegexUtil.h"
#include <iostream>

using namespace std;


namespace http {
URL::URL(const string& url)
:url_(url){
	parse();
}

URL::~URL() {
}
void URL::parse() {
	try{
		regex_t preg;
		if(regcomp(&preg,"^(([^:]+)://)?([^:/]+)(:([0-9]+))?(/.*)",REG_EXTENDED) != 0){
			printf("regex compile filed");
		}

		int nmatch = 7;
		regmatch_t pmatch[7];

		if(regexec(&preg, url_.c_str(), nmatch, pmatch ,0) != 0){
		}else{
			int indexHost = 3;
			int indexPort = 5;
			int indexPath = 6;

			RegexUtil::assignRegexValue(url_,pmatch[indexHost],host_);
			RegexUtil::assignRegexValue(url_,pmatch[indexPort],port_);
			RegexUtil::assignRegexValue(url_,pmatch[indexPath],path_);

			cout << "Host:" << host_ << endl;
			cout << "Port:" << port_ << endl;
			cout << "Path:" << path_ << endl;
		}
	}catch(std::exception& e){
		host_ = "";
		port_ = "";
		path_ = "";
	}
}

bool URL::hasPort() const {
	if(port_.length() > 0){
		return true;
	}
	return false;
}


}

