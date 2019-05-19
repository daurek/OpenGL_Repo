/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Node
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Node.hpp"

namespace openglScene
{
	Node::Node()
	{
		// Reset parent and transformation matrices
		parent = nullptr;
		translation = glm::translate(translation, glm::vec3(0.f, 0.f, 0.f));
		rotation = glm::mat4(1.0f);
		scaling = glm::scale(scaling, glm::vec3(1.f, 1.f, 1.f));
		transform = glm::mat4(1.0f);
	}

	void Node::Translate(glm::vec3 _movement)
	{
		// Moves with the given vector
		translation = glm::translate(translation, _movement);
	}

	void Node::Rotate(glm::vec3 _axis, float angle)
	{
		// Rotates in the given axis and angle
		rotation = glm::rotate(rotation, angle, _axis);
	}

	void Node::Scale(glm::vec3 _scale)
	{
		// Scale into the given vector
		scaling = glm::scale(scaling, _scale);
	}

	void Node::SetParent(Node * newParent)
	{
		// Sets a new Node parent
		parent = newParent;
	}

	void Node::AddChild(std::string name, std::shared_ptr<Node> child)
	{
		// Check validity
		if (!name.empty() && child)
		{
			// Set child and parent
			children[name] = child;
			child->parent = this;
		}
	}

	std::shared_ptr<Node> Node::GetChild(std::string name)
	{
		// Check validity
		if (name.empty())
			return nullptr;

		// Return child
		return children[name];
	}

	const glm::mat4 & Node::getTransform()
	{
		// If is a child then calculate transformation with the parent's transform
		if (parent != nullptr)
			transform = parent->getTransform() * translation * rotation * scaling;
		// If no parent the calculate it normally
		else
			transform = translation * rotation * scaling;
		// Return calculated total transformation
		return transform;
	}


}
