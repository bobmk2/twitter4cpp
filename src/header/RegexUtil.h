/*
 * RegexUtil.h
 *
 *  Created on: 2012/08/10
 */

#ifndef REGEXUTIL_H_
#define REGEXUTIL_H_

#include <string>
#include <regex.h>

/**
 * @brief 正規表現用のユーティリティクラス
 */
class RegexUtil {
private:
	RegexUtil();

public:
	/**
	 * @brief 正規表現のマッチ結果を元に文字列を格納する
	 * @param from 対象文字列
	 * @param match　マッチ情報
	 * @param[in] to　格納先
	 */
	static void assignRegexValue(const std::string& from, const regmatch_t& match, std::string& to);
};

#endif /* REGEXUTIL_H_ */
