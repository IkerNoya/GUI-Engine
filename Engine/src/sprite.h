#ifndef SPRITE_H
#define SPRITE_H
#include "shape.h"
#include "export.h"

class ENGINE_API Sprite : public Shape {


public:

	Sprite(Type type, Renderer* renderer, std::string name);
	~Sprite();

};

#endif // !SPRITE_H
