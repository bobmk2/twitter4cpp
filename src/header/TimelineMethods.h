/*
 * TimelineMethods.h
 *
 *  Created on: 2012/08/13
 */

#ifndef TIMELINEMETHODS_H_
#define TIMELINEMETHODS_H_

#include <vector>
#include <string>
#include "Tweet.h"

namespace method{

class TimelineMethods {
public:
	class TimeLineParameter;
protected:
	static const std::string TIMELINE_HOMETIMELINE_URL;
	static const unsigned int DEFAULT_LOAD_COUNT = 20;
	static const unsigned int UNUSED = -1;

	TimelineMethods();
public:
	virtual ~TimelineMethods();

	virtual int getHomeTimeline(
			std::vector<Tweet*>* const tweetList,
			unsigned int count = DEFAULT_LOAD_COUNT,
			unsigned long sinceId = UNUSED,
			unsigned long maxId = UNUSED,
			unsigned int page = UNUSED
	) const = 0;
};

}
#endif /* TIMELINEMETHODS_H_ */
