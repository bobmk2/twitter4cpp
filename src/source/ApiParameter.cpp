/*
 * ApiParameter.cpp
 *
 *  Created on: 2012/08/20
 */

#include "ApiParameter.h"
#include <iostream>

using namespace std;

ApiParameter::ApiParameter() {
}

ApiParameter::~ApiParameter() {
}

void ApiParameter::put(const std::string& key, const std::string& value) {
	parameterMap[key] = value;
}

void ApiParameter::inputParameterString(std::ostringstream* oss, const std::string& separator) const{
	map<string,string>::const_iterator iter = parameterMap.begin();
	while(iter != parameterMap.end()){
		if(oss->tellp() > 0){
			*oss << separator;
		}
		std::cout << (*iter).first << " // " << (*iter).second << std::endl;

		*oss << (*iter).first;
		*oss << "=";
		*oss << (*iter).second;

		++iter;
	}


}

std::string ApiParameter::toUrlString() const {
	ostringstream oss;
	inputParameterString(&oss, "&");
	return oss.str();
}

std::string ApiParameter::toHeaderString() const {
	ostringstream oss;
	inputParameterString(&oss, ",");
	return oss.str();
}
