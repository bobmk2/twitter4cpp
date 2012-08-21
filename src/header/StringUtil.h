/*
 * StringUtil.h
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>
#include <vector>

class StringUtil {
private:
	static const int MAX_BUF_LENGTH = 256;

	StringUtil();
public:
	static std::string urlEncode(const std::string& str);
	static std::string encodeBase64(const std::string& str);
	static std::vector<std::string> split(const std::string& str, const std::string& separator);
	static std::string trim(const std::string& str);
	static std::vector<std::string> mysplit(const std::string& str, const std::string& separator);
	static std::string toStr(long num);
};

#endif /* STRINGUTIL_H_ */
