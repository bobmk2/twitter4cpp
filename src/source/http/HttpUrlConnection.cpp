/*
 * HttpUrlConnection.cpp
 *
 *  Created on: 2012/08/10
 */

#include "HttpUrlConnection.h"

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "StringUtil.h"
#include <string>
#include <map>
#include <vector>


namespace http{
using namespace std;


HttpUrlConnection::HttpUrlConnection(const URL& url)
:url_(new URL(url)),debug_(false){
}

HttpUrlConnection::~HttpUrlConnection() {
}

void HttpUrlConnection::openSocket(int& sock) {
	struct sockaddr_in server;
	int bufLen = 512;
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
}

void HttpUrlConnection::sendRequest(FILE* const fp){
	fprintf (fp, "%s %s HTTP/1.1\r\n",reqMethod_.c_str(),url_->getPath().c_str());

	string host = url_->getHost() + (url_->getPort().size() > 0 ? ":" + url_->getPort() : "");
	cout << "SEND HOST >>> " << host << endl;
	fprintf (fp, "Host: %s\r\n",host.c_str());

	map<string,string>::const_iterator iter = header_.begin();
	while(iter != header_.end()){
		fprintf(fp,"%s: %s\r\n",(*iter).first.c_str(),(*iter).second.c_str());
		++iter;
	}

	//fprintf(fp,"Content-Length: %d\r\n", (int)body_.size());
	//fprintf(fp,"Content-Length: %d\r\n", (int)body_.size());

	fprintf (fp, "\r\n");

	cout << "SEND-BODY >>> " << body_ << endl;
	cout << "SEND-BODY CHAR >>> " << body_.c_str() << endl;

	fprintf(fp,"%s", body_.c_str());
}


void HttpUrlConnection::setRequestMethod(const string& method) {
	reqMethod_ = method;
}

void HttpUrlConnection::setBody(const string& body) {
	body_ = body;

	cout << "(" << body_.length() << ") ->[" << body_ << "]" << endl;
}

void HttpUrlConnection::setTimeOutMs(const long & timeOutMs) {
	timeOutMs_ = timeOutMs;
}

HttpResponse HttpUrlConnection::getResponse() {
	int socket = -1;
	openSocket(socket);

	FILE* fp = fdopen(socket,"r+");
	setvbuf(fp, NULL, _IONBF, 0);

	sendRequest(fp);

	HttpResponse response;
	readResponse(socket,fp, response);

	fclose(fp);
	close(socket);
	return response;
}

void HttpUrlConnection::readResponse(const int& socket, FILE* const fp,HttpResponse& response) {
	int bufLen = 1024;
	char buf[bufLen];
	memset(buf,0,bufLen);

	int n = 0;

	string statusLine;
	string header;
	string body;

	bool isReadFirstLine = false;

	while (fgets (buf, sizeof (buf) - 1, fp) != NULL) {

		if(!isReadFirstLine){
			isReadFirstLine = true;
			statusLine.append(buf,strlen(buf));
		}else{
			header.append(buf,strlen(buf));

			// CRLFが来たらヘッダ終了
			if (buf[0] == 0x0d && buf[1] == 0x0a) {
				break;
			}
		}
		memset(buf,0,bufLen);
	}

	response.setStatusLine(statusLine);
	parseHeader(response, header);

	int contentLength = 0;
	//const map<string, vector<string> >& headerMap = response.getHeader();
	//if(headerMap.count("Content-Length") > 0){
	//	contentLength = atoi(headerMap.at("Content-Length").at(0).c_str());
	//}
	map<string, vector<string> >* pHeaderMap = response.getHeaderPointer();
	map<string, vector<string> >::iterator iter = pHeaderMap->begin();

	string key;
	string value;
	//cout << "size:" << pHeaderMap->size() << endl;
	while(iter != pHeaderMap->end()){
		const string& key = (*iter).first;
		const vector<string>& value = (*iter).second;
		//cout << "key[" << key << "]" << endl;
		if(key == "Content-Length"){
			//cout << "find" << endl;
			contentLength = atoi(value.at(0).c_str());
		}
		++ iter;
	}
	cout << "Content-Length:" << contentLength << endl;

	/*
	memset(buf,0,bufLen);
	while (fgets (buf, sizeof (buf) - 1 , fp) != NULL) {
		cout << " -> " << body.length()  << " (" << strlen(buf) << ")" << endl;

		body.append(buf,strlen(buf));

		memset(buf,0,bufLen);
	}
	 */
	if(contentLength > 0){
		while((n = recv(socket, buf, bufLen ,0)) > 0){
			body.append(buf,n);
			//cout << buf << endl;
			memset(buf,0,bufLen);

			//# hack
			if((int)body.length() >= contentLength){
				break;
			}
		}
	}

	//fd_set input_set, exc_set; // Create Input set
	//int s;
	//timeval timeout;
	//timeout.tv_sec = 2; // Attends 2 sec pour returner.
	//timeout.tv_usec = 0;

	/*
	n =  0;
	do{
		//FD_ZERO(&input_set);
		//FD_SET(socket, &input_set);
		//s = select(0 , &input_set, NULL, NULL, &timeout);

		//cout << "あったよー" << endl;
		cout << "s recv" << endl;
		n = recv(socket, buf, bufLen, 0);
		cout << "e recv(" << n << ")" << endl;
		if(n < 0){
			break;
		}
		body.append(buf,n);
		memset(buf, 0, bufLen);
	}while(n > 0);
	 */

	response.setBody(body);

	/*
	string responseStr;
	while((n = recv(socket, buf, bufLen ,0)) > 0){
		responseStr.append(buf,n);
		memset(buf,0,bufLen);
		if(n < bufLen){
			break;
		}
	}
	cout << responseStr << endl;
	 */


	//response.setStatusLine();
	//response.setHeader();
	//response.setBody();



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

	if( n = recv(sock, buf, bufLen ,0) > 0){
		cout << "# " << buf << endl;
	}
	 */
}

void HttpUrlConnection::parseHeader(HttpResponse& response, const string& headerStr) {
	//改行コードで分ける
	vector<string> headerStrList = StringUtil::split(headerStr, "\r\n");
	int size = headerStrList.size();
	for(int i=0; i<size;i++){
		string str = StringUtil::trim(headerStrList.at(i));
		cout << "[" << str << "](" << str.length() << ")" << endl;
		if(str.length() == 0 || str.find(":") == string::npos){continue;}
		int pos = str.find_first_of(":");
		cout << ": pos -> " << pos << endl;
		string key = str.substr(0,str.find_first_of(":"));

		string value = StringUtil::trim(str.substr(str.find(":")+1));

		cout << "k["<< key << "(" << key.size() << ")]:v[" << value << "]" << endl;
		response.putHeader(key,value);
	}
}

void HttpUrlConnection::putHeader(const string& name, const string& value) {
	header_[name] = value;
}


}


