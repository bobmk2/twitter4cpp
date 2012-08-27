/*
 * ApiParameter.h
 *
 *  Created on: 2012/08/20
 */

#ifndef APIPARAMETER_H_
#define APIPARAMETER_H_

#include <string>
#include <map>
#include <sstream>

/**
 * @brief APIパラメータ格納クラス
 */
class ApiParameter {
private:
	std::map<std::string, std::string> parameterMap;	//!< パラメータ記憶用マップ

	/**
	 * @brief 第一引数のstreamにパラメータを格納する
	 * @param[in] oss　文字列格納用stream
	 * @param separator KeyとValueのセパレータ文字列
	 */
	void inputParameterString(std::ostringstream* oss, const std::string& separator) const;

public:
	ApiParameter();
	virtual ~ApiParameter();

	/**
	 * @brief パラメータを格納する
	 * @param key　キー
	 * @param value　バリュー
	 */
	void put(const std::string& key, const std::string& value);

	/**
	 * @brief URL用のパラメータ文字列として返す
	 * @return　パラメータ文字列
	 */
	std::string toUrlString() const;

	/**
	 * @brief ヘッダ用のポラメータ文字列として返す
	 * @return　パラメータ文字列
	 */
	std::string toHeaderString() const;
};

#endif /* APIPARAMETER_H_ */
