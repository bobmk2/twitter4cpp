/*
 * Date.h
 *
 *  Created on: 2012/08/15
 */

#ifndef DATE_H_
#define DATE_H_

class Date {
private:
	int year_;
	int month_;
	int day_;

	int hour_;
	int minute_;
	int second_;

public:
	Date();
	virtual ~Date();
};

#endif /* DATE_H_ */
