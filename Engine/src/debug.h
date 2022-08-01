#ifndef DEBUG_H
#define DEBUG_H
#include "export.h"
#include "entity.h"


class ENGINE_API Line :  public Entity {
	unsigned int _vbo;
	unsigned int _vao;
	Shader _shader;
	std::vector<float> vertices;
	glm::vec3 lineColor;
	glm::mat4 model;
public:
	Line();
	Line(Shader& shader, Renderer* renderer);
	~Line();
	void Init();
	void draw(glm::vec3 pos1, glm::vec3 pos2, glm::vec3 color);
	void setColor(glm::vec3 color);
};



#endif // !DEBUG_H

