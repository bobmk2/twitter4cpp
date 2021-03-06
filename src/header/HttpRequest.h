/*
 * HttpRequest.h
 *
 *  Created on: 2012/08/09
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <string>
#include <map>
#include "regex.h"

using namespace  std;

/**
 * @brief HTTPリクエストを行うためのクラス
 * @todo 汚いので直す
 */
class HttpRequest {
public:
	class URL;

private:
	class RequestLine;

	const URL* url_;//!< URL

	string method_;	//!< リクエスト方法
	string httpVer_;//!< HTTPバージョン

	map<string, string> header_;	//!< ヘッダ
	string body_;	//!< ボディ

	int timeout_;	//!< タイムアウト時間

	int socket_;	//!< ソケット

	static const string DEFAULT_METHOD;
	static const string DEFAULT_HTTP_VER;
	static const int DEFAULT_TIMEOUT = 5000;

	void openSocket(int& socket);
	void sendData(const int socket);

	HttpRequest();

public:
	HttpRequest(const URL& url);
	virtual ~HttpRequest();

	void openConnection();
	void execute();
	void closeConnection();

	/**
	 * @brief ヘッダを追加する
	 * @param name　　ヘッダ名
	 * @param value　ヘッダの値
	 */
	void putHeader(const string& name, const string& value);

	string toString() const;

	/* Setter */
	void setMethod(const string& method);
	void setBody(const string& body);
	void setTimeOut(const int& timeout);

	/* Getter */
	inline URL getUrl() const{return *url_;}
	inline map<string, string> getHeader() const{return header_;};
	inline string getBody() const{return body_;}
	inline int getTimeOut() const{return timeout_;}

	class URL{
	private:
		string url_;

		string host_;
		string port_;
		string path_;

		void parse();
		void assignRegexValue(const string& from, const regmatch_t& match, string& to);
	public:
		URL(const string& url);
		~URL();

		/* Geter */
		inline string getHost() const{return host_;}
		inline string getPort() const{return port_;}
		inline string getPath() const{return path_;}
		bool hasPort() const;
	};
};

#endif /* HTTPREQUEST_H_ */
