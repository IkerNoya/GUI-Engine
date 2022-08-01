#include "frustrum.h"
#include "../camera.h"
Frustrum GetFrustrumFromCamera(class Camera* camera, float aspect, float fov, float near, float far) {
	Frustrum frustrum;
	float halfVerticalSide = far * glm::tan(fov * .5f);
	float halfHorizontalSide = halfVerticalSide * aspect;
	glm::vec3 frontTimesFar = far * camera->getForward();

	frustrum.Near = { camera->transform.position + near * camera->getRight(), camera->getForward() };
	frustrum.Far = { camera->transform.position + frontTimesFar, -camera->getForward() };
	frustrum.Right = { camera->transform.position, glm::cross(camera->getUp(),frontTimesFar + camera->getRight() * halfHorizontalSide) };
	frustrum.Left = { camera->transform.position, glm::cross(frontTimesFar - camera->getRight() * halfHorizontalSide, camera->getUp()) };
	frustrum.Top = { camera->transform.position, glm::cross(camera->getRight(),frontTimesFar - camera->getUp() * halfVerticalSide) };
	frustrum.Bottom = { camera->transform.position, glm::cross(frontTimesFar + camera->getUp() * halfVerticalSide, camera->getRight()) };

	return frustrum;
}