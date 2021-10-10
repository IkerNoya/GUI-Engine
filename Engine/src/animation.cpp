#include "animation.h"
#include <iostream>

Animation::Animation(){
}

Animation::~Animation(){}

void Animation::Update(Time& time){
	_currentTime = (time.getTime() * _length);
	std::cout<< _currentTime << std::endl;
	while (_currentTime >= _length) {
		_currentTime -= _length;
	}
	float frameLength = _length / _animation[_currentAnimation].size();
	_currentFrame = static_cast<int>(_currentTime / frameLength);
}

void Animation::AddFrames(float frameX, float frameY, int spriteWidth, int spriteHeight, int spriteSheetWidth, int SpriteSheetHeight, float time, int totalFrames, int rowCount){
	int ms = 1000;
	_length = time * ms;

	totalFrames = totalFrames + rowCount;

	float xIndex = 0;
	float yIndex = 0;
	Frame frame;
	for (int i = 0; i < totalFrames; i++) {
		frame.frameCoords[0].u = ((frameX + xIndex) / spriteSheetWidth);
		frame.frameCoords[0].v = ((spriteHeight + yIndex) / SpriteSheetHeight);

		frame.frameCoords[1].u = (((frameX + xIndex) + spriteWidth) / spriteSheetWidth);
		frame.frameCoords[1].v = ((spriteHeight + yIndex) / SpriteSheetHeight);

		frame.frameCoords[2].u = (((frameX + xIndex) + spriteWidth) / spriteSheetWidth);
		frame.frameCoords[2].v = ((frameY + yIndex) / SpriteSheetHeight);

		frame.frameCoords[3].u = ((frameX + xIndex) / spriteSheetWidth);
		frame.frameCoords[3].v = ((frameY + yIndex) / SpriteSheetHeight);

		_frames.push_back(frame);
		xIndex += spriteWidth;

		if (i > 0) {
			if (i % rowCount == 0) {
				yIndex += spriteHeight;
				_animation.push_back(_frames);
				_frames.clear();
			}
		}

	}

}
void Animation::AddFrame(float frameX, float frameY, int spriteWidth, int spriteHeigth, int textureWidth, int textureHeigth, float timeToAnim)
{
	_length = timeToAnim;

	Frame frame;

	frame.frameCoords[0].u = ((frameX) / textureWidth);
	frame.frameCoords[0].v = ((spriteHeigth + frameY) / textureHeigth);


	frame.frameCoords[1].u = (((frameX)+spriteWidth) / textureWidth);
	frame.frameCoords[1].v = ((spriteHeigth + frameY) / textureHeigth);

	frame.frameCoords[2].u = (((frameX)+spriteWidth) / textureWidth);
	frame.frameCoords[2].v = ((frameY) / textureHeigth);

	frame.frameCoords[3].u = ((frameX) / textureWidth);
	frame.frameCoords[3].v = ((frameY) / textureHeigth);

	_frames.push_back(frame);
}

std::vector<Frame>& Animation::GetAnimation(){
	if (_currentAnimation < _animation.size())
		return _animation[_currentAnimation];

	return _animation[_animation.size() - 1];
}

void Animation::SetCurrentAnimation(int animation){
	_currentAnimation = animation;
}

void Animation::AddAnimation(){
	if (_frames.size() > 0) {
		_animation.push_back(_frames);
		_frames.clear();
	}
}

int Animation::GetCurrentFrame(){
	return _currentFrame;
}
