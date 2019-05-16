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

		Camera(float _fov, float _aspectRatio, float _nearPlane, float _farPlane);

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) override;

		void Move(glm::vec3 _movement);

		void setFov(float _fov)
		{
			projection = glm::perspective(_fov, aspectRatio, nearPlane, farPlane);
		}

		void setAspectRatio(float _aspectRatio)
		{
			projection = glm::perspective(fov, _aspectRatio, nearPlane, farPlane);
		}

		void setNearPlane(float _nearPlane)
		{
			projection = glm::perspective(fov, aspectRatio, _nearPlane, farPlane);
		}

		void setFarPlane(float _farPlane)
		{
			projection = glm::perspective(fov, aspectRatio, nearPlane, _farPlane);
		}

		glm::mat4 getProjection() const
		{
			return projection;
		}

		void setSpeed(float _speed)
		{
			speed = _speed;
		}


	private:

		glm::mat4	projection;

		float		fov;
		float		aspectRatio;
		float		nearPlane;
		float		farPlane;

		float		speed = 0.05f;

	};

}

#endif
