#include <GL/glew.h>            
#include "Camera.hpp"
#include <iostream>
#include <SFML/OpenGL.hpp>
#include "glm/gtc/matrix_transform.hpp"

namespace openglScene
{
	Camera::Camera(float fov, float aspectRation, float nearPlane, float farPlane)
	{
		projectionMatrix = glm::perspective(fov, aspectRation, nearPlane, farPlane);
	}

	void Camera::Move(glm::vec3 direction)
	{

	}
}
