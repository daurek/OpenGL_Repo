#include "Node.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace openglScene
{
	Node::Node()
	{
		parent = nullptr;
		translation = glm::translate(translation, glm::vec3(0.f, 0.f, 0.f));
		scaling = glm::scale(scaling, glm::vec3(1.f, 1.f, 1.f));
		transform = glm::mat4(1.0f);
	}

	void Node::Move(glm::vec3 _movement)
	{
		translation = glm::translate(translation, _movement);
	}

	void Node::Rotate(glm::vec3 _axis, float angle)
	{
		rotation = glm::rotate(rotation, angle, _axis);
	}

	void Node::Scale(glm::vec3 _scale)
	{
		scaling = glm::scale(scaling, _scale);
	}

	void Node::SetParent(Node * newParent)
	{
		parent = newParent;
	}

	void Node::AddChild(std::string name, std::shared_ptr<Node> child)
	{
		if (!name.empty() && child)
		{
			children[name] = child;
			child->parent = this;
		}
	}

	std::shared_ptr<Node> Node::GetChild(std::string name)
	{
		if (name.empty())
			return nullptr;

		return children[name];
	}

	const glm::mat4 & Node::getTransform()
	{
		if (parent != nullptr)
			transform = parent->getTransform() * translation * rotation * scaling;
		else
			transform = translation * rotation * scaling;

		return transform;
	}


}
