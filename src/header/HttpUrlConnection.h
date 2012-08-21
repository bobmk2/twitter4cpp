/*
 * HttpUrlConnection.h
 *
 *  Created on: 2012/08/10
 */

#ifndef HTTPURLCONNECTION_H_
#define HTTPURLCONNECTION_H_

#include <string>
#include <map>
#include "URL.h"
#include "HttpResponse.h"

using namespace std;

namespace http{

//TODO Timeoutの実装
class HttpUrlConnection {
private:
	URL* url_;

	string reqMethod_;
	string httpVer_;

	map<string, string> header_;
	string body_;

	long timeOutMs_;

	void openSocket(int& sock);
	void sendRequest(FILE* const fp);
	void readResponse(const int& socket,FILE* const fp, HttpResponse& response);

	void parseHeader(HttpResponse& response, const string& headerStr);

	//TODO delete later
	bool debug_;

public:
	HttpUrlConnection(const URL& url);
	virtual ~HttpUrlConnection();

	void setRequestMethod(const string& method);
	void putHeader(const string& name, const string& value);
	void setBody(const string& body);
	void setTimeOutMs(const long& timeOutMs);

	HttpResponse getResponse();

	//TODO delete later
	void setDebug(bool b){debug_ = b;}
};

}

#endif /* HTTPURLCONNECTION_H_ */
