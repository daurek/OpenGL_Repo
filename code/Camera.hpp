#ifndef CAMERA_HEADER
#define CAMERA_HEADER

// Libraries
#include "glm/glm.hpp"

namespace openglScene
{

    class Camera
    {
    public:

		Camera(glm::vec3 position, glm::vec3 rotation, float fov, float aspectRation, float nearPlane, float farPlane);

		void Move(glm::vec3 direction);

		glm::vec3 getPosition() const
		{
			return glm::vec3(view[3].x, view[3].y, view[3].z);
		}

		glm::mat4 getView() const
		{
			return view;
		}

		glm::mat4 getProjection() const
		{
			return projection;
		}


	private:

		glm::mat4   view;
		glm::mat4	projection;

		float		speed = 1.f;
    };

}

#endif
