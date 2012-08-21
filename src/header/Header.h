/*
 * Header.h
 *
 *  Created on: 2012/08/13
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <string>

class Header {
private:
	std::string key_;
	std::string header_;
public:
	Header(std::string key, std::string header);
	virtual ~Header();

	std::string getKey(){return key_;};
	std::string getHeader(){return header_;}
};

#endif /* HEADER_H_ */
