#ifndef __TIMERWALKER_H__
#define __TIMERWALKER_H__

#include <string>
#include <functional>
#include <memory>

using namespace std;

namespace TimeWalker {

class TimerDetector;
class TimeWalker {
	friend class TimerDetector;
public:
    enum class TimeType {
        REAL,                     //真实时间
        MONOTONIC,                //计算机运行时间，从计算机启动开始计时
    };
    
	TimeWalker (string name,
		TimeType timeType = TimeType::REAL, 
        bool absOrRelative = false,
		unsigned int delaySec = 0, 
		unsigned int delayNsec = 0, 
		unsigned int intervalSec = 0, 
		unsigned int intervalNsec = 0,
		function<void()> callback = nullptr);
	
	virtual bool Init();
    
    virtual bool Init(std::shared_ptr<TimerDetector> timerDetector) = 0;
	
	// start walking
	virtual bool start();
	
    // stop walking
	virtual bool stop();
    
    ~TimeWalker();
protected:
	string m_name;  // walker name 
    int m_id;       // walker id 即底层接口使用到的timerfd;
	TimeType m_timeType; //walker的时间类型
    
    bool m_absOrRelative; //设置的节点时间是绝对时间还是相当时间
    
    bool m_inited;
    
    bool m_actived;
	
	// Timer exec times
	int m_execTimes;
	
	unsigned int m_delaySec;
	
	unsigned int m_delayNsec;
	
	unsigned int m_intervalSec;
	
	unsigned int m_intervalNsec;
	
	function<void()> m_callback;
};
}
	
#endif