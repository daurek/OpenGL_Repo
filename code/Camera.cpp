#include "Camera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace openglScene
{
	Camera::Camera(float _fov, float _aspectRatio, float _nearPlane, float _farPlane) : fov(_fov), aspectRatio(_aspectRatio), nearPlane(_nearPlane), farPlane(_farPlane)
	{

		projection = glm::perspective(_fov, _aspectRatio, _nearPlane, _farPlane);
	}

	void Camera::Update(glm::mat4 _transform)
	{

	}

	void Camera::Move(glm::vec3 _movement)
	{
		Translate(_movement * speed);
	}

}
