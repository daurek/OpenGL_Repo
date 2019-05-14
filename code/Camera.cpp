#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace openglScene
{
	Camera::Camera(glm::vec3 position, glm::vec3 rotation, float fov, float aspectRation, float nearPlane, float farPlane)
	{
		view = glm::translate(view, position);
		view = glm::rotate(view, rotation.x, glm::vec3(1.f, 0.f, 0.f));
		view = glm::rotate(view, rotation.y, glm::vec3(0.f, 1.f, 0.f));
		view = glm::rotate(view, rotation.z, glm::vec3(0.f, 0.f, 1.f));
		view = glm::scale(view, glm::vec3(0.001f, 0.001f, 0.001f));
		projection = glm::perspective(fov, aspectRation, nearPlane, farPlane);
	}

	void Camera::Move(glm::vec3 direction)
	{
		view = glm::translate(view, direction * speed);
	}
}
