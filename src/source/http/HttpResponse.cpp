/*
 * HttpResponse.cpp
 *
 *  Created on: 2012/08/10
 */

#include "HttpResponse.h"

#include <iostream>
using namespace std;


namespace http {

HttpResponse::HttpResponse()
:statusLine_(new string()),header_(new std::map<std::string, std::vector<std::string> >()),body_(new string()){

}

HttpResponse::~HttpResponse() {
	delete(body_);
	delete(header_);
	delete(statusLine_);
}

void HttpResponse::print() const{
	cout << *statusLine_ << endl;
	//cout << *header_ << endl;
	cout << *body_ << endl;
}

HttpResponse::HttpResponse(const HttpResponse& response)
:statusLine_(new string(*response.statusLine_)),header_(new std::map<std::string, std::vector<std::string> >(*response.header_)),body_(new string(*response.body_)){
}

HttpResponse& HttpResponse::operator =(const HttpResponse& response)
{
	*statusLine_ = *response.statusLine_;
	*header_ = *response.header_;
	*body_ = *response.body_;
}

}
 /* namespace http */
