/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Camera
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Camera.hpp"

namespace openglScene
{
	Camera::Camera(float _fov, float _aspectRatio, float _nearPlane, float _farPlane) : fov(_fov), aspectRatio(_aspectRatio), nearPlane(_nearPlane), farPlane(_farPlane)
	{
		// Create Camera Projection
		projection = glm::perspective(_fov, _aspectRatio, _nearPlane, _farPlane);
	}

	void Camera::Update(glm::mat4 _transform)
	{
		// Empty
	}

	void Camera::Move(glm::vec3 _movement)
	{
		// Moves the Node Transform with our speed and movement
		Translate(_movement * speed);
	}

}
