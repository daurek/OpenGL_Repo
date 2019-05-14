#ifndef CAMERA_HEADER
#define CAMERA_HEADER

// Libraries
#include <SFML/OpenGL.hpp>
#include "glm/glm.hpp"

namespace openglScene
{

    class Camera
    {
    public:

		Camera(float fov, float aspectRation, float nearPlane, float farPlane);

		void Move(glm::vec3 direction);

		glm::mat4 GetProjection() const
		{
			return projectionMatrix;
		}

	private:

		glm::vec3	position;
		glm::mat4	projectionMatrix;
		float		speed;
    };

}

#endif
