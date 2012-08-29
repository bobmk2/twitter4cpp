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
#include <iostream>

namespace http {

/**
 * @brief HTTPレスポンス格納用クラス
 */
class HttpResponse {
private:
	//TODO modify later
	std::string* statusLine_;	//!< ステータスライン

	std::map<std::string, std::vector<std::string> >* header_;	//!< ヘッダ

	std::string* body_;	//!< ボディ

public:
	HttpResponse();
	virtual ~HttpResponse();
	HttpResponse(const HttpResponse& response);
	HttpResponse& operator=(const HttpResponse& response);

	void putHeader(const std::string& key, const std::string& value){
		((*header_)[key]).push_back(value);
	}

	void print() const;

	//TODO delete later
	/* Setter */
	void setStatusLine(const std::string& statusLine){*statusLine_ = statusLine;}
	void setBody(const std::string& body){*body_ = body;}

	/* Getter */
	const std::string& getStatusLine() const {return *statusLine_;}
	const std::map<std::string, std::vector<std::string> >& getHeader() const {return *header_;}
	std::map<std::string, std::vector<std::string> >* getHeaderPointer() const {return header_;}
	const std::string& getBody() const {return *body_;}

};

} /* namespace http */
#endif /* HTTPRESPONSE_H_ */
