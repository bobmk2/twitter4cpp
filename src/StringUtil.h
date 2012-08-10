/*
 * StringUtil.h
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_

#include <string>

using namespace std;

class StringUtil {
private:
	StringUtil();
public:
	static string urlEncode(const string& str);
	static string encodeBase64(const string& str);
};

#endif /* STRINGUTIL_H_ */
