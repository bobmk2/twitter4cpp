/*
 * RegexUtil.h
 *
 *  Created on: 2012/08/10
 */

#ifndef REGEXUTIL_H_
#define REGEXUTIL_H_

#include <string>
#include <regex.h>

class RegexUtil {
private:
	RegexUtil();

public:
	static void assignRegexValue(const std::string& from, const regmatch_t& match, std::string& to);
};

#endif /* REGEXUTIL_H_ */
