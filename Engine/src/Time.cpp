#include "time.h"

void Time::calculateDeltaTime(){



}

void Time::initTime(){
}

Time::Time(){
	_time = 0.0f;
	_deltaTime = 0.0f;
	_timeScale = 1.0f;
}

Time::~Time(){
}

float Time::getDeltaTime(){
	return _deltaTime;
}

float Time::getTimeSinceStart(){
	return _time;
}

float Time::getTimeInSeconds(){
	return 0.0f;
}

float Time::getTimeInMinutes(){
	return 0.0f;
}

void Time::setTimeScale(float value){
	_timeScale = value;
}

float Time::getTimeScale(){
	return _timeScale;
}
