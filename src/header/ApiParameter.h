/*
 * ApiParameter.h
 *
 *  Created on: 2012/08/20
 */

#ifndef APIPARAMETER_H_
#define APIPARAMETER_H_

#include <string>
#include <map>
#include <sstream>

class ApiParameter {
private:
	std::map<std::string, std::string> parameterMap;

	void inputParameterString(std::ostringstream* oss, const std::string& separator) const;

public:
	ApiParameter();
	virtual ~ApiParameter();

	void put(const std::string& key, const std::string& value);

	std::string toUrlString() const;
	std::string toHeaderString() const;
};

#endif /* APIPARAMETER_H_ */
