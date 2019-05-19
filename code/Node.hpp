/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Node
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef NODE_HEADER
#define NODE_HEADER

// System
#include <memory>
#include <map>
#include <string>
// Libraries
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace openglScene
{
	/// Base Class for every Entity on the Scene, contains a Transform 
    class Node
    {
    public:

		/// Creates a Node with resetted Transformations
		Node();

		virtual ~Node() = default;

		/// Base Update
		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) = 0;

		/// Changes the Translation matrix according to the given movement vector
		void Translate(glm::vec3 _movement);

		/// Changes the Rotation matrix according to the given axis vector and angle
		void Rotate(glm::vec3 _axis, float angle);

		/// Changes the Scale matrix according to the given scale vector
		void Scale(glm::vec3 _scale);

		/// Sets the current parent as the new given one
		void SetParent(Node * newParent);

		/// Adds a given Node as child with the given name and sets it's parent as this one
		void AddChild(std::string name, std::shared_ptr<Node> child);

		/// Returns the child with the given name
		std::shared_ptr<Node> GetChild(std::string name);

		/// Returns the calculated total transformation
		const glm::mat4 & getTransform();

	protected:

		/// Translation matrix
		glm::mat4	translation;

		/// Rotation matrix
		glm::mat4	rotation;

		/// Scaling matrix
		glm::mat4	scaling;

		/// Transformations matrix
		glm::mat4	transform;

		/// Reference to the parent Node
		Node	  *	parent;

		/// Map of Child references
		std::map<std::string, std::shared_ptr < Node >> children;

    };

}

#endif
