/*
 * HttpRequest.cpp
 *
 *  Created on: 2012/08/09
 */

#include "HttpRequest.h"
#include <iostream>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

const string HttpRequest::DEFAULT_METHOD = "GET";
const string HttpRequest::DEFAULT_HTTP_VER = "HTTP/1.1";

HttpRequest::HttpRequest(const URL& url)
: url_(new URL(url)),method_(DEFAULT_METHOD),httpVer_(DEFAULT_HTTP_VER), timeout_(DEFAULT_TIMEOUT) {

	cout << "Host:" << url.getHost() << endl;
	cout << "Path:" << url.getPath() << endl;


	if(url_->getHost().length() > 0){
		string hostStr;
		hostStr = url_->getHost();

		if(url_->getPort().length() > 0){
			hostStr += ":" + url_->getPort();
		}

		header_["Host"] = hostStr;
	}
}

HttpRequest::~HttpRequest() {
	delete(url_);
}

void HttpRequest::setMethod(const std::string& method) {
	method_ = method;
}

void HttpRequest::openConnection() {
	openSocket(socket_);
}

void HttpRequest::closeConnection() {
}


void HttpRequest::execute() {
	int sock = -1;
	openSocket(sock);
	sendData(sock);
}

void HttpRequest::openSocket(int& socket_) {
	struct sockaddr_in server;
	int sock;
	int bufLen = 512;
	char buf[bufLen];
	const char* deststr = url_->getHost().c_str();
	unsigned int **addrptr;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		return;
	}

	server.sin_family = AF_INET;

	if(url_->hasPort()){
		server.sin_port = htons(atoi(url_->getPort().c_str()));
	}else{
		server.sin_port = htons(80);
	}

	server.sin_addr.s_addr = inet_addr(deststr);
	if (server.sin_addr.s_addr == 0xffffffff) {
		struct hostent *host;

		host = gethostbyname(deststr);
		if (host == NULL) {
			if (h_errno == HOST_NOT_FOUND) {
				printf("host not found : %s\n", deststr);
			} else {
				printf("%s : %s\n", hstrerror(h_errno), deststr);
			}
			return;
		}

		addrptr = (unsigned int **)host->h_addr_list;

		while (*addrptr != NULL) {
			server.sin_addr.s_addr = *(*addrptr);

			// connect()が成功したらloopを抜けます
			if (connect(sock,
					(struct sockaddr *)&server,
					sizeof(server)) == 0) {
				break;
			}

			addrptr++;
			// connectが失敗したら次のアドレスで試します
		}

		// connectが全て失敗した場合
		if (*addrptr == NULL) {
			perror("connect");
			return;
		}
	} else {
		if (connect(sock,
				(struct sockaddr *)&server, sizeof(server)) != 0) {
			perror("connect");
			return;
		}
	}

	/* HTTPで「/」をリクエストする文字列を生成 */
	FILE *fp = fdopen(sock, "r+");

	setvbuf(fp, NULL, _IONBF, 0);
	fprintf (fp, "%s %s HTTP/1.1\r\n",method_.c_str(),url_->getPath().c_str());

	string host = url_->getHost() + (url_->getPort().size() > 0 ? ":" + url_->getPort() : "");
	fprintf (fp, "Host: %s\r\n",host.c_str());

	map<string,string>::const_iterator iter = header_.begin();
	while(iter != header_.end()){
		fprintf(fp,"%s: %s\r\n",(*iter).first.c_str(),(*iter).second.c_str());
		++iter;
	}

	fprintf (fp, "\r\n");

	int n = 0;
	bool readStatusLine = false;
	bool readHeader = false;
	string statusLine;
	string header;
	string body;

	memset(buf,0,bufLen);

	while (fgets (buf, sizeof (buf) - 1, fp) != NULL) {
		//printf ("%s", buf);

		// CRLFが来たらヘッダ終了
		if(!readStatusLine){
			readStatusLine = true;
			statusLine.append(buf,sizeof(buf));
			cout << "sl.append" << endl;
		}else{
			if(!readHeader){
				header.append(buf,sizeof(buf));
				if (buf[0] == 0x0d && buf[1] == 0x0a) {
					break;
				}
				cout << "header.append" << endl;
			}else{
			}
		}
		memset(buf,0,bufLen);
	}

	while((n = recv(sock, buf, bufLen ,0)) > 0){
		body.append(buf,n);
		memset(buf,0,bufLen);
		if(n < bufLen){
			break;
		}
	}


	cout << "SL: " << statusLine << endl;
	cout << "Header: " << header << endl;
	cout << "Body: " << body << endl;

	//受信
	/*
	int n = 0;
	string responseStr;
	while((n = recv(sock, buf, bufLen ,0)) > 0){
		responseStr.append(buf,n);
		memset(buf,0,bufLen);
		if(n < bufLen){
			break;
		}
	}
	cout << responseStr << endl;
	 */
	/*
	int n = 0;
	while (1) {
		if (fgets (buf, sizeof (buf), fp) == NULL) {
			break;
		}
		// レスポンスヘッダをリストに格納する
		// --- TO BE IMPLEMENTED --
		printf ("%s", buf);

		// CRLFが来たらヘッダ終了
		if (buf[0] == 0x0d && buf[1] == 0x0a) {
			break;
		}
	}

	while (1) {
			if (fgets (buf, sizeof (buf), fp) == NULL) {
				break;
			}
			// レスポンスヘッダをリストに格納する
			// --- TO BE IMPLEMENTED --
			printf ("%s", buf);

			// CRLFが来たらヘッダ終了
			if (buf[0] == 0x0d && buf[1] == 0x0a) {
				break;
			}
		}
	 */

	/*
	if( n = recv(sock, buf, bufLen ,0) > 0){
		cout << "# " << buf << endl;
	}
	 */

	/*
	while (1) {
		if (fgets (buf, sizeof (buf), fp) == NULL) {
			break;
		}
		// レスポンスヘッダをリストに格納する
		// --- TO BE IMPLEMENTED --
		printf ("%s", buf);

		// CRLFが来たらヘッダ終了
		if (buf[0] == 0x0d && buf[1] == 0x0a) {
			break;
		}
	}

	memset (buf, 0, sizeof (buf));
	int len;
	int bufLen = 1;
	while ((len = read (sock, buf, bufLen)) > 0) {
		printf ("$%s", buf);
		memset (buf, 0, sizeof (buf));
	}
	printf ("#%s", buf);
	 */

	fclose(fp);
	close(sock);

	return;
}

void HttpRequest::sendData(const int socket) {
}


void HttpRequest::putHeader(const string& name, const string& value) {
	header_[name] = value;
}

void HttpRequest::setBody(const string& body) {
	body_ = body;
}

inline void HttpRequest::setTimeOut(const int& timeout) {
	timeout_ = timeout;
}

string HttpRequest::toString() const {
	string str;

	//ステータスライン
	str += method_;
	str += " ";
	str += url_->getPath();
	str += " ";
	str += httpVer_;
	str += "\r\n";

	//ヘッダ
	map<string,string>::const_iterator iter = header_.begin();
	while(iter != header_.end()){
		str += (*iter).first;
		str +=":";
		str += (*iter).second;
		str += "\r\n";
		iter ++;
	}
	//str += "Content-Length:0";

	//str += "\r\n";

	//ボディ
	//str += body_;

	return str;
}


HttpRequest::URL::URL(const string& url)
:url_(url){
	parse();
}

HttpRequest::URL::~URL() {
}
void HttpRequest::URL::parse() {
	try{
		regex_t preg;
		if(regcomp(&preg,"^(([^:]+)://)?([^:/]+)(:([0-9]+))?(/.*)",REG_EXTENDED) != 0){
			printf("regex compile filed");
		}

		int nmatch = 7;
		regmatch_t pmatch[7];

		if(regexec(&preg, url_.c_str(), nmatch, pmatch ,0) != 0){
		}else{
			int indexHost = 3;
			int indexPort = 5;
			int indexPath = 6;

			assignRegexValue(url_,pmatch[indexHost],host_);
			assignRegexValue(url_,pmatch[indexPort],port_);
			assignRegexValue(url_,pmatch[indexPath],path_);
		}
	}catch(std::exception& e){
		host_ = "";
		port_ = "";
		path_ = "";
	}
}

void HttpRequest::URL::assignRegexValue(const string& from, const regmatch_t& match, string& to) {
	int s = (int)match.rm_so;
	int e = (int)match.rm_eo;
	if(s > 0 && e > 0){
		to = from.substr(s, e- s);
	}
}

bool HttpRequest::URL::hasPort() const {
	if(port_.length() > 0){
		return true;
	}
	return false;
}


