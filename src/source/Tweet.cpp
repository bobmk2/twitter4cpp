/*
 * Tweet.cpp
 *
 *  Created on: 2012/08/15
 */

#include "Tweet.h"
#include "StringUtil.h"
#include "TimeUtil.h"
#include <iostream>

using namespace std;


Tweet::Tweet()
:id_(NOT_SPECIFIED),
 text_(NULL),
 source_(NULL),
 createdAt_(NULL),
 fromUserId_(NOT_SPECIFIED),
 fromUserName_(NULL),
 fromUserScreenName_(NULL),
 toUserId_(NOT_SPECIFIED),
 toUserName_(NULL),
 toUserScreenName_(NULL),
 user_(new User())
{
}

Tweet::~Tweet() {
	delete(toUserScreenName_);
	delete(toUserName_);

	delete(fromUserScreenName_);
	delete(fromUserName_);

	delete(createdAt_);
	delete(source_);
	delete(text_);
}

string Tweet::toString() const{
	string str;
	if(fromUserScreenName_ != NULL && fromUserName_ != NULL){
		str += *fromUserScreenName_ + "(" + *fromUserName_ +"): ";
	}

	if(text_ != NULL){
		str += *text_ + " ";
	}

	if(createdAt_ != NULL){
		//string tmpstr;
		//TimeUtil::toFormatedStr(&tmpstr, *createdAt_, "%Y-%m-%d %H:%M");
		//str += "at " + tmpstr;
	}

	if(source_ != NULL){
		//
	}

	return str;
}


void Tweet::setId(const long& id) {
	id_ = id;
}

void Tweet::setText(const string& text) {
	if(text_ == NULL){text_ = new string();}
	*text_ = text;
}

void Tweet::setSource(const string& source) {
	if(source_ == NULL){source_ = new string();}
	*source_ = source;
}

void Tweet::setCreatedAt(const time_t& createdAt){
	if(createdAt_ == NULL){createdAt_ = new time_t();}

	tm* tss = localtime(&createdAt);
	char buf[256];
	strftime(buf, sizeof(buf),"%Y-%m-%d %H:%M", tss);
	std::cout << "INSERT:" << buf << std::endl;

	*createdAt_ = createdAt;
}

void Tweet::setFromUserId(const long& fromUserid) {
	fromUserId_ = fromUserid;
}

void Tweet::setFromUserName(const string& fromUserName) {
	if(fromUserName_ == NULL){fromUserName_ = new string();}
	*fromUserName_ = fromUserName;
}

void Tweet::setFromUserScreenName(const string& fromUser) {
	if(fromUserScreenName_ == NULL){fromUserScreenName_ = new string();}
	*fromUserScreenName_ = fromUser;
}

void Tweet::setToUserId(const long& toUserId) {
	toUserId_ = toUserId;
}

void Tweet::setToUserName(const string& toUserName) {
	if(toUserName_ == NULL){toUserName_ = new string();}
	*toUserName_ = toUserName;
}

void Tweet::setToUserScreenName(const string& toUser) {
	if(toUserScreenName_ == NULL){toUserScreenName_ = new string();}
	*toUserScreenName_ = toUser;
}

void Tweet::setUser(const User& user){
	*user_ = user;
}

long Tweet::getId() const {
	return id_;
}

const string* Tweet::getText() const {
	return text_;
}

const string* Tweet::getSource() const{
	return source_;
}

const time_t* Tweet::getCreatedAt() const{
	return createdAt_;
}

long Tweet::getFromUserId() const {
	return fromUserId_;
}

const string* Tweet::getFromUserName() const {
	return fromUserName_;
}

const string* Tweet::getFromUserScreenName() const {
	return fromUserScreenName_;
}

long Tweet::getToUserId() const {
	return toUserId_;
}

const string* Tweet::getToUserName() const {
	return toUserName_;
}

const string* Tweet::getToUserScreenName() const {
	return toUserScreenName_;
}

const User* Tweet::getUser() const{
	return user_;
}
