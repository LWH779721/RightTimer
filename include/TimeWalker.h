#ifndef __TIMERWALKER_H__
#define __TIMERWALKER_H__

#include <string>
#include <functional>
#include <memory>

using namespace std;

namespace TimeWalker {

class TimerDetector;
class TimeWalker:
	public std::enable_shared_from_this<TimeWalker>{
	friend class TimerDetector;
public:
    enum class TimeType {
        REAL,                     //真实时间
        MONOTONIC,                //计算机运行时间，从计算机启动开始计时
    };
	
	enum class TimeRelation {
		ABSOLUTE,           	  //绝对
		RELATIVE,				  //相对当前
	};
    
	TimeWalker (string name,
		TimeType timeType = TimeType::REAL,
		TimeRelation timeRelation = TimeRelation::RELATIVE);
		
	void setTarget(unsigned int sec, unsigned int nsec); 	//设置目标时间
		
	void setInterval(unsigned int sec, unsigned int nsec); 	//设置间隔时间

	void setCallback(function<void()> callback); 			//设置回调函数
	
	virtual bool init();
    
    virtual bool init(std::shared_ptr<TimerDetector> timerDetector);
	
	// start walking
	virtual bool start();
	
    // stop walking
	virtual bool stop();
    
    ~TimeWalker();

private:
	bool __init();
	
protected:
	string m_name;  		// walker name 
    
	int m_id;       		// walker id 即底层接口使用到的timerfd;
	
	TimeType m_timeType; 	//walker的时间类型
    
    TimeRelation m_timeRelation; 	//设置的节点时间是绝对时间还是相当时间
    
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