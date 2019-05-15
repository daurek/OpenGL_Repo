#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include "Node.hpp"
// Libraries
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace openglScene
{

    class Camera : public Node
    {
    public:

		Camera(float fov, float aspectRation, float nearPlane, float farPlane);

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) override;

		glm::mat4 getProjection() const
		{
			return projection;
		}


	private:

		glm::mat4	projection;

		float		fov;
		float		speed = 0.1f;

	};

}

#endif
