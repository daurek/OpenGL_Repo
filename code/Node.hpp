#ifndef NODE_HEADER
#define NODE_HEADER

// Libraries
#include "glm/glm.hpp"
#include <memory>
#include <map>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

namespace openglScene
{

    class Node
    {
    public:

		Node();

		virtual ~Node() = default;

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) = 0;

		void Move(glm::vec3 _movement);

		void Rotate(glm::vec3 _axis, float angle);

		void Scale(glm::vec3 _scale);

		void SetParent(Node * newParent);

		void AddChild(std::string name, std::shared_ptr<Node> child);

		std::shared_ptr<Node> GetChild(std::string name);

		const glm::mat4 & getTransform();

	protected:

		glm::mat4	translation;
		glm::mat4	rotation;
		glm::mat4	scaling;
		glm::mat4	transform;

		Node	  *	parent;
		std::map<std::string, std::shared_ptr < Node >> children;

    };

}

#endif
