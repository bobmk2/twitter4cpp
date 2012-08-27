/*
 * User.h
 *
 *  Created on: 2012/08/20
 */

#ifndef USER_H_
#define USER_H_

#include <string>

/**
 * @brief ユーザクラス
 */
class User {
private:
	long id_;
	std::string name_;
	std::string screenName_;
	std::string location_;
	std::string profileImageUrl_;
	std::string profileImageUrlHttps_;
	std::string url_;
	std::string description_;
	bool protected_;
	int followersCount_;
	std::string profileBackgroundColor_;
	std::string profileTextColor_;
	std::string profileSidebarFillColor_;
	std::string profileSidebarBorderColor_;
	int friendsCount_;
	int favouritesCount_;
	std::string createdAt_;
	int utcOffset_;
	std::string timeZone_;
	std::string profileBackgroundImageUrl_;
	std::string profileBackgroundImageUrlHttps_;
	std::string profileBackgroundTile_;
	std::string profileUseBackgroundImage_;
	bool getEnabled_;
	bool verified_;
	int statusesCount_;
	std::string lang_;
	bool contributorsEnabled_;
	bool isTranslator_;
	bool showAllInlineMedia_;
	bool defaultProfile_;
	bool defaultProfileImage_;
	bool following_;
	std::string followRequestSent_;
	std::string notifications_;

public:
	User();
	virtual ~User();

	bool isContributorsEnabled() const {
		return contributorsEnabled_;
	}

	void setContributorsEnabled(bool contributorsEnabled) {
		contributorsEnabled_ = contributorsEnabled;
	}

	std::string getCreatedAt() const {
		return createdAt_;
	}

	void setCreatedAt(std::string createdAt) {
		createdAt_ = createdAt;
	}

	bool isDefaultProfile() const {
		return defaultProfile_;
	}

	void setDefaultProfile(bool defaultProfile) {
		defaultProfile_ = defaultProfile;
	}

	bool isDefaultProfileImage() const {
		return defaultProfileImage_;
	}

	void setDefaultProfileImage(bool defaultProfileImage) {
		defaultProfileImage_ = defaultProfileImage;
	}

	std::string getDescription() const {
		return description_;
	}

	void setDescription(std::string description) {
		description_ = description;
	}

	int getFavouritesCount() const {
		return favouritesCount_;
	}

	void setFavouritesCount(int favouritesCount) {
		favouritesCount_ = favouritesCount;
	}

	int getFollowersCount() const {
		return followersCount_;
	}

	void setFollowersCount(int followersCount) {
		followersCount_ = followersCount;
	}

	bool isFollowing() const {
		return following_;
	}

	void setFollowing(bool following) {
		following_ = following;
	}

	std::string getFollowRequestSent() const {
		return followRequestSent_;
	}

	void setFollowRequestSent(std::string followRequestSent) {
		followRequestSent_ = followRequestSent;
	}

	int getFriendsCount() const {
		return friendsCount_;
	}

	void setFriendsCount(int friendsCount) {
		friendsCount_ = friendsCount;
	}

	bool isGetEnabled() const {
		return getEnabled_;
	}

	void setGetEnabled(bool getEnabled) {
		getEnabled_ = getEnabled;
	}

	long getId() const {
		return id_;
	}

	void setId(long id) {
		id_ = id;
	}

	bool isIsTranslator() const {
		return isTranslator_;
	}

	void setIsTranslator(bool isTranslator) {
		isTranslator_ = isTranslator;
	}

	std::string getLang() const {
		return lang_;
	}

	void setLang(std::string lang) {
		lang_ = lang;
	}

	std::string getLocation() const {
		return location_;
	}

	void setLocation(std::string location) {
		location_ = location;
	}

	std::string getName() const {
		return name_;
	}

	void setName(std::string name) {
		name_ = name;
	}

	std::string getNotifications() const {
		return notifications_;
	}

	void setNotifications(std::string notifications) {
		notifications_ = notifications;
	}

	std::string getProfileBackgroundColor() const {
		return profileBackgroundColor_;
	}

	void setProfileBackgroundColor(std::string profileBackgroundColor) {
		profileBackgroundColor_ = profileBackgroundColor;
	}

	std::string getProfileBackgroundImageUrl() const {
		return profileBackgroundImageUrl_;
	}

	void setProfileBackgroundImageUrl(std::string profileBackgroundImageUrl) {
		profileBackgroundImageUrl_ = profileBackgroundImageUrl;
	}

	std::string getProfileBackgroundImageUrlHttps() const {
		return profileBackgroundImageUrlHttps_;
	}

	void setProfileBackgroundImageUrlHttps(std::string profileBackgroundImageUrlHttps) {
		profileBackgroundImageUrlHttps_ = profileBackgroundImageUrlHttps;
	}

	std::string getProfileBackgroundTile() const {
		return profileBackgroundTile_;
	}

	void setProfileBackgroundTile(std::string profileBackgroundTile) {
		profileBackgroundTile_ = profileBackgroundTile;
	}

	std::string getProfileImageUrl() const {
		return profileImageUrl_;
	}

	void setProfileImageUrl(std::string profileImageUrl) {
		profileImageUrl_ = profileImageUrl;
	}

	std::string getProfileImageUrlHttps() const {
		return profileImageUrlHttps_;
	}

	void setProfileImageUrlHttps(std::string profileImageUrlHttps) {
		profileImageUrlHttps_ = profileImageUrlHttps;
	}

	std::string getProfileSidebarBorderColor() const {
		return profileSidebarBorderColor_;
	}

	void setProfileSidebarBorderColor(std::string profileSidebarBorderColor) {
		profileSidebarBorderColor_ = profileSidebarBorderColor;
	}

	std::string getProfileSidebarFillColor() const {
		return profileSidebarFillColor_;
	}

	void setProfileSidebarFillColor(std::string profileSidebarFillColor) {
		profileSidebarFillColor_ = profileSidebarFillColor;
	}

	std::string getProfileTextColor() const {
		return profileTextColor_;
	}

	void setProfileTextColor(std::string profileTextColor) {
		profileTextColor_ = profileTextColor;
	}

	std::string getProfileUseBackgroundImage() const {
		return profileUseBackgroundImage_;
	}

	void setProfileUseBackgroundImage(std::string profileUseBackgroundImage) {
		profileUseBackgroundImage_ = profileUseBackgroundImage;
	}

	bool isProtedted() const {
		return protected_;
	}

	void setProtedted(bool protected_) {
		this->protected_ = protected_;
	}

	std::string getScreenName() const {
		return screenName_;
	}

	void setScreenName(std::string screenName) {
		screenName_ = screenName;
	}

	bool isShowAllInlineMedia() const {
		return showAllInlineMedia_;
	}

	void setShowAllInlineMedia(bool showAllInlineMedia) {
		showAllInlineMedia_ = showAllInlineMedia;
	}

	int getStatusesCount() const {
		return statusesCount_;
	}

	void setStatusesCount(int statusesCount) {
		statusesCount_ = statusesCount;
	}

	std::string getTimeZone() const {
		return timeZone_;
	}

	void setTimeZone(std::string timeZone) {
		timeZone_ = timeZone;
	}

	std::string getUrl() const {
		return url_;
	}

	void setUrl(std::string url) {
		url_ = url;
	}

	int getUtcOffset() const {
		return utcOffset_;
	}

	void setUtcOffset(int utcOffset) {
		utcOffset_ = utcOffset;
	}

	bool isVerified() const {
		return verified_;
	}

	void setVerified(bool verified) {
		verified_ = verified;
	}
};

#endif /* USER_H_ */
