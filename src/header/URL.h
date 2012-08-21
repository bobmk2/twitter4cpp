/*
 * URL.h
 *
 *  Created on: 2012/08/10
 */

#ifndef URL_H_
#define URL_H_

#include <string>

namespace http {

class URL {
private:
	std::string url_;	//!< Url

	/* ex. http://[Host]:[Port]/[Path] */
	std::string host_;	//!< Host
	std::string port_;	//!< Port
	std::string path_;	//!< Path

	void parse();

public:
	URL(const std::string& url);
	~URL();

	inline std::string getHost() const{return host_;}
	inline std::string getPort() const{return port_;}
	inline std::string getPath() const{return path_;}
	bool hasPort() const;
};

} /* namespace http */
#endif /* URL_H_ */
