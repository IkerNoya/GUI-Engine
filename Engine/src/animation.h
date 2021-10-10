#ifndef ANIMATION_H
#define ANIMATION_H
#include "export.h"
#include "time_manager.h"
#include "frame.h"

#include <vector>
#include <algorithm>

class ENGINE_API Animation {
private:
	int _currentFrame = 0;
	float _currentTime = 0;
	float _length = 0;
	int _accumulationWidth = 0;
	int _accumulationHeight = 0;
	std::vector<Frame> _frames;
	std::vector<std::vector<Frame>> _animation;
	int _currentAnimation = 0;
	float* vertex;
public: 
	Animation();
	~Animation();
	void Update(Time& time);
	void AddFrames(float frameX, float frameY, int spriteWidth, int spriteHeigth, int spriteSheetWidth, int SpriteSheetHeight, float time, int totalFrames, int rowCount);
	void AddFrame(float frameX, float frameY, int spriteWidth, int spriteHeigth, int textureWidth, int textureHeigth, float timeToAnim);
	std::vector<Frame>& GetAnimation();
	void SetCurrentAnimation(int animation);
	void AddAnimation();
	int GetCurrentFrame();

};

#endif // !ANIMATION_H

