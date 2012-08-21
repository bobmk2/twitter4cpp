/*
 * HttpResponse.h
 *
 *  Created on: 2012/08/10
 */

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include <string>
#include <vector>
#include <map>
#include "Header.h"
#include <iostream>

namespace http {

class HttpResponse {
private:
	//TODO modify later
	std::string* statusLine_;

	std::map<std::string, std::vector<std::string> >* header_;

	std::string* body_;

public:
	HttpResponse();
	virtual ~HttpResponse();
	HttpResponse(const HttpResponse& response);
	HttpResponse& operator=(const HttpResponse& response);

	//TODO delete later
	void setStatusLine(const std::string& statusLine){*statusLine_ = statusLine;}
	//void setHeader(const std::string& header){*header_ = header;}
	void putHeader(const std::string& key, const std::string& value){
		std::cout << "いれるよ[" << key.c_str()<< "]" << "[" << value.c_str() << "]" << std::endl;
		((*header_)[key]).push_back(value);
	}
	void setBody(const std::string& body){*body_ = body;}

	const std::string& getStatusLine() const {return *statusLine_;}
	const std::map<std::string, std::vector<std::string> >& getHeader() const {return *header_;}
	std::map<std::string, std::vector<std::string> >* getHeaderPointer() const {return header_;}
	const std::string& getBody() const {return *body_;}

	void print() const;
};

} /* namespace http */
#endif /* HTTPRESPONSE_H_ */
