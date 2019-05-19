/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Camera
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef CAMERA_HEADER
#define CAMERA_HEADER

// Project
#include "Node.hpp"

namespace openglScene
{
	/// Handles Camera projection and movement
    class Camera : public Node
    {

    public:

		/// Creates Camera's projection with the given properties
		Camera(float _fov, float _aspectRatio, float _nearPlane, float _farPlane);

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) override;

		/// Moves the Camera with the given movement and it's speed
		void Move(glm::vec3 _movement);

		/// Creates a new Camera Projection with the given FOV
		void setFov(float _fov)
		{
			projection = glm::perspective(_fov, aspectRatio, nearPlane, farPlane);
		}

		/// Creates a new Camera Projection with the given Aspect Ratio
		void setAspectRatio(float _aspectRatio)
		{
			projection = glm::perspective(fov, _aspectRatio, nearPlane, farPlane);
		}

		/// Creates a new Camera Projection with the given Near Plane
		void setNearPlane(float _nearPlane)
		{
			projection = glm::perspective(fov, aspectRatio, _nearPlane, farPlane);
		}

		/// Creates a new Camera Projection with the given Far Plane
		void setFarPlane(float _farPlane)
		{
			projection = glm::perspective(fov, aspectRatio, nearPlane, _farPlane);
		}

		/// Returns the Camera's projection
		glm::mat4 getProjection() const
		{
			return projection;
		}

		/// Sets the Camera's speed with the given value
		void setSpeed(float _speed)
		{
			speed = _speed;
		}


	private:

		/// Camera's Projection Matrix
		glm::mat4	projection;

		/// Camera's FOV
		float		fov;
		/// Camera's Aspect Ratio
		float		aspectRatio;
		/// Camera's Near Plane
		float		nearPlane;
		/// Camera's Far Plane
		float		farPlane;

		/// Camera's current Speed
		float		speed = 0.05f;

	};

}

#endif
