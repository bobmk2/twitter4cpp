/*
 * StatusMethods.h
 *
 *  Created on: 2012/08/13
 */

#ifndef STATUSMETHODS_H_
#define STATUSMETHODS_H_

#include <string>

namespace method {

class StatusMethods {
protected:
	static const std::string STATUS_UPDATESTATUS_URL;

	StatusMethods();
public:
	virtual ~StatusMethods();

	virtual void updateStatus(std::string status) = 0;

};

} /* namespace oauth */
#endif /* STATUSMETHODS_H_ */
