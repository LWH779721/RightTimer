#ifndef __SCHEDULE_H__
#define __SCHEDULE_H__

#include "TimeWalker.h"

namespace TimeWalker {

/**
 * Schedule使用现实时间（Real Time）实现，例如：设置早上8点钟闹铃
 **/
class Schedule:
	public TimeWalker,
    public std::enable_shared_from_this<Schedule>{
	friend class TimerDetector;
public:
	Schedule(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	bool Init() override;
	
    bool Init(std::shared_ptr<TimerDetector> timerDetector) override;
	
    //在绝对时间abstime时回调
    bool at(const string& abstime);
    
	bool Start(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	~Schedule();
private:
	
};
};
	
#endif