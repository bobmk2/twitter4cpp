/*
 * TokenFactory.h
 *
 *  Created on: 2012/08/08
 *      Author: tsugutoshi_aoshima
 */

#ifndef TOKENFACTORY_H_
#define TOKENFACTORY_H_


#include <string>
#include "RequestToken.h"
#include "AccessToken.h"

/**
 * @brief トークンファクトリ
 * @todo 汚いので直す
 * @todo ApiParameterを適用する
 */
class TokenFactory {
private:
	static const std::string OAUTH_VERSION;

	static std::string getRequestParameter(const std::string& consumerKey, std::string& nonce, std::string& timestamp);
	static std::string getAccessTokenParameter(const std::string& consumerKey, std::string& nonce, std::string& timestamp,const oauth::RequestToken& reqToken, const std::string& pin);

public:
	TokenFactory();
	virtual ~TokenFactory();

	void getRequestToken(const std::string& consumerKey, const std::string& consumerSecret);

	/**
	 * @brief リクエストトークンを作る
	 * @param consumerKey	　コンシューマキー
	 * @param consumerSecret　コンシューマシークレット
	 * @return 認証に成功した場合はリクエストトークン、失敗した場合はNULL
	 */
	static oauth::RequestToken* createRequestToken(const std::string& consumerKey, const std::string& consumerSecret);

	/**
	 * @brief アクセストークンを作る
	 * @param consumerKey　　　コンシューマキー
	 * @param consumerSecret　コンシューマシークレット
	 * @param reqToken	リクエストトークン
	 * @param pin	PINコード
	 * @return　認証に成功した場合はアクセストークン、失敗した場合はNULL
	 */
	static oauth::AccessToken* createAccessToken(const std::string& consumerKey, const std::string& consumerSecret, const oauth::RequestToken& reqToken, const std::string& pin);
};


#endif /* TOKENFACTORY_H_ */
