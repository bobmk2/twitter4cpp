/*
 * StringUtil.cpp
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#include "StringUtil.h"

#include <sstream>
#include <stdio.h>
#include <iostream>

StringUtil::StringUtil() {
	// TODO Auto-generated constructor stub

}

string StringUtil::urlEncode(const string &str) {
	/*
	ostringstream os;

	int length = str.size();
	for (int i = 0; i < length; i++) {
		char c = str[i];

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-' || c == '_'
				|| c == '.' || c == '~') {
			os << c;
		}else {
			char s[4];
			snprintf(s, sizeof(s), "%%%02x", c & 0xff);
			for(int j=0;j<4;j++){
				char sc = s[j];
				if(sc >= 'a' && sc <= 'z'){
					os << char(toupper(sc));
				}else{
					os << sc;
				}
			}
		}
	}

	return os.str();
	*/
	string encodedStr = "";

	int length = str.size();
	for (int i = 0; i < length; i++) {
		char c = str[i];

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-' || c == '_'
				|| c == '.' || c == '~') {
			encodedStr += c;
		}else {
			char s[4];
			snprintf(s, sizeof(s), "%%%02x", c & 0xff);

			for(int j=0;j<4;j++){
				char sc = s[j];
				if(sc == 0){continue;}

				if(sc >= 'a' && sc <= 'z'){
					encodedStr += char(toupper(sc));
				}else{
					encodedStr += sc;
				}
			}
		}
	}

	return encodedStr;
}


string StringUtil::encodeBase64(const string& str) {
	const char* table =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	string cdst;

	const char* chars = str.c_str();
	for (int i = 0; i < str.length(); i++) {
		switch (i % 3) {
		case 0:
			cdst = cdst + (table[(chars[i] & 0xFC) >> 2]);
			if (i + 1 == str.length()) {
				cdst = cdst + table[(chars[i] & 0x03) << 4];
				cdst = cdst + "==";
			}

			break;
		case 1:
			cdst = cdst
					+ table[((chars[i - 1] & 0x03) << 4)
							| ((chars[i + 0] & 0xF0) >> 4)];
			if (i + 1 == str.length()) {
				cdst = cdst + table[(chars[i] & 0x0F) << 2];
				cdst = cdst + "=";
			}

			break;
		case 2:
			cdst = cdst
					+ (table[((chars[i - 1] & 0x0F) << 2)
							| ((chars[i + 0] & 0xC0) >> 6)]);
			cdst = cdst + (table[chars[i] & 0x3F]);

			break;
		}
	}
	return cdst;
}
