#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include "TimeWalker.h"

namespace TimeWalker {

/**
 * Schedule使用现实时间（Real Time）实现，例如：设置早上8点钟闹铃
 **/
class Schedule:
	public TimeWalker{
	friend class TimerDetector;
public:
	Schedule(string name);
	
    //在绝对时间abstime时回调
    bool at(const string& abstime);
	
	~Schedule();
private:
	
};
};
	
#endif