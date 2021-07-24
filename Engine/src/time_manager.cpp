#include "time_manager.h"



Time::Time(){
	_time = 0.0f;
	_deltaTime = std::chrono::duration<float>(0.0f);
	_fps = 0.0f;
	_frames = 0;
}

Time::~Time(){

}

void Time::tick() {
	_currentTime = std::chrono::system_clock::now();
	_deltaTime =_currentTime - _prevTime;
	reset();
}

void Time::reset(){
	_prevTime = std::chrono::system_clock::now();
}

float Time::getFPS(){
	return _fps;
}

float Time::getDeltaTime(){
	return _deltaTime.count();
}
