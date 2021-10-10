#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H
#include "export.h"
#include <chrono>

class ENGINE_API Time {
private:
	std::chrono::system_clock::time_point _prevTime;
	std::chrono::system_clock::time_point _currentTime;
	std::chrono::duration<float> _deltaTime;
	float _time;
	float _fps;
	float _fpsElapesedTime;
	int _frames;

public:
	Time();
	~Time();

	void tick();
	void reset();
	void calculateFPS();

	float getFPS();
	float getDeltaTime();
	float getTime();
};


#endif // !TIME_MANAGER_H

