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

using namespace std;

StringUtil::StringUtil() {
}

string StringUtil::urlEncode(const string &str) {
	string encodedStr = "";

	int length = str.size();
	for (int i = 0; i < length; i++) {
		char c = str[i];

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '-' || c == '_'
				|| c == '.' || c == '~') {
			encodedStr += c;
		} else {
			char s[4];
			snprintf(s, sizeof(s), "%%%02x", c & 0xff);

			for (int j = 0; j < 4; j++) {
				char sc = s[j];
				if (sc == 0) {
					continue;
				}

				if (sc >= 'a' && sc <= 'z') {
					encodedStr += char(toupper(sc));
				} else {
					encodedStr += sc;
				}
			}
		}
	}

	return encodedStr;
}

string StringUtil::encodeBase64(const string& str) {
	const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
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
				cdst = cdst + table[((chars[i - 1] & 0x03) << 4) | ((chars[i + 0] & 0xF0) >> 4)];
				if (i + 1 == str.length()) {
					cdst = cdst + table[(chars[i] & 0x0F) << 2];
					cdst = cdst + "=";
				}

				break;
			case 2:
				cdst = cdst + (table[((chars[i - 1] & 0x0F) << 2) | ((chars[i + 0] & 0xC0) >> 6)]);
				cdst = cdst + (table[chars[i] & 0x3F]);

				break;
		}
	}
	return cdst;
}


std::vector<std::string> StringUtil::split(const std::string& str, const std::string& separator) {
	string cpyStr = str;

	std::vector<std::string> items;
	std::size_t sepIndex;

	if (cpyStr.npos == (sepIndex = cpyStr.find_first_of(separator))) {
		items.push_back(cpyStr.substr(0, sepIndex));
		return items;
	}

	while (cpyStr.npos != (sepIndex = cpyStr.find_first_of(separator))) {
		if (cpyStr.npos == cpyStr.find_first_not_of(separator)) {
			break;
		}
		items.push_back(cpyStr.substr(0, sepIndex));
		sepIndex++;
		cpyStr = cpyStr.erase(0, sepIndex);
		if (cpyStr.npos == cpyStr.find_first_of(separator) && "" != cpyStr) {
			items.push_back(string(cpyStr));
			break;
		}
	}
	return items;
}

std::string StringUtil::trim(const std::string& str) {
	//前後の半角スペース、\tを取り除いた部分文字列を返す
	int baseSize = str.length();

	cout << "trim start" << endl;

	//頭の位置を確定させる
	int head = -1;
	for (int i = 0; i < baseSize; i++) {
		if (str[i] != ' ' && str[i] != '\t' && str[i] != 0) {
			head = i;
			break;
		}
	}

	//末尾の位置を確定させる
	int tail = -1;
	for (int i = baseSize - 1; i >= 0; i--) {
		if (str[i] != ' ' && str[i] != '\t' && str[i] != 0) {
			tail = i;
			break;
		}
	}
	if (head == -1 || tail == -1) {
		//全部半角スペースのため
		return "";
	}

	int bufSize = tail - head + 1 + 1; //終了文字\0
	char buf[bufSize];
	memset(buf, '\0', bufSize);
	for (int i = head, j = 0; i <= tail; i++, j++) {
		buf[j] = str[i];
	}
	return string(buf);

}

std::vector<std::string> StringUtil::mysplit(const std::string& str, const std::string& separator) {
	int j;
	bool allMatch = true;

	vector<string> list;

	int tmpSize = 0;
	int startPos = 0;

	int strSize = str.size();
	int sepSize = separator.size();

	for (int i = 0; i < strSize; i++) {
		char strTmp = str[i];
		if(strTmp == 0){continue;}
		allMatch = true;

		for (j = 0; j < sepSize && (i + j) < strSize; j++) {
			if (str[i + j] == separator[j]) {
			} else {
				allMatch = false;
				break;
			}
		}

		if (allMatch) {
			//セパレートが見つかった場合
			string tmpStr = "";
			cout << "i = " << i << endl;
			for (int k = startPos; k < i; k++) {
				tmpStr += str[k];
			}
			cout << tmpStr << "-> size" << tmpStr.length() << endl;
			if(tmpStr.size() > 0){
				list.push_back(tmpStr);
			}
			i += j - 1;
			startPos = i + 1;
		} else {
			//セパレートが見つからなかった場合
		}
	}

	return list;

}

std::string StringUtil::toStr(long num) {
	char buf[MAX_BUF_LENGTH];
	memset(buf,0,MAX_BUF_LENGTH);
	sprintf(buf,"%ld",num);
	return string(buf);
}



