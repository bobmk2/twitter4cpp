/*
 * StatusMethods.h
 *
 *  Created on: 2012/08/13
 */

#ifndef STATUSMETHODS_H_
#define STATUSMETHODS_H_

#include <string>

namespace api {

/**
 * @brief ツイートの投稿するメソッドを持つインターフェース
 * @todo クラス名をTwitterAPIのDocにもとづいて変える
 */
class StatusMethods {
protected:
	static const std::string STATUS_UPDATESTATUS_URL;

	StatusMethods();
public:
	virtual ~StatusMethods();

	/**
	 * @brief ツイートを投稿する
	 * このメソッドでは http://twitter.com/statuses/update.xml を叩く
	 * @param text　本文
	 * @param replyTo　返信先のツイートID
	 */
	virtual void updateStatus(const std::string& text,const long& replyTo = -1) const = 0;

};

} /* namespace oauth */
#endif /* STATUSMETHODS_H_ */
