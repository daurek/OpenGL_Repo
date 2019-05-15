#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace openglScene
{
	Camera::Camera(float fov, float aspectRation, float nearPlane, float farPlane)
	{
		projection = glm::perspective(fov, aspectRation, nearPlane, farPlane);
	}

	void Camera::Update(glm::mat4 _transform)
	{
	}

}
