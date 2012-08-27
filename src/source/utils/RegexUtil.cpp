/*
 * RegexUtil.cpp
 *
 *  Created on: 2012/08/10
 */

#include "RegexUtil.h"
#include <iostream>

using namespace std;

void RegexUtil::assignRegexValue(const string& from, const regmatch_t& match, string& to) {
	int s = (int)match.rm_so;
	int e = (int)match.rm_eo;
	if(s >= 0 && e >= 0){
		to = from.substr(s, e- s);
	}
}

RegexUtil::RegexUtil() {
}

