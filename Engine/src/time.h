#ifndef TIME_H
#define TIME_H
#include "export.h"

class ENGINE_API Time{
private:
	float _time;
	float _deltaTime;
	float _timeScale;
	
	void calculateDeltaTime();

public:
	Time();
	~Time();

	float getDeltaTime();
	float getTimeSinceStart();
	float getTimeInSeconds();
	float getTimeInMinutes();

	float getFTime();
	void setTimeScale(float value);
	float getTimeScale();
};


#endif // !TIME_H


