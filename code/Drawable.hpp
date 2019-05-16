#ifndef DRAWABLE_HEADER
#define DRAWABLE_HEADER

// Libraries
#include "Node.hpp"
#include <memory>

namespace openglScene
{

	class Shader;

    class Drawable : public Node
    {
	public:

		Drawable(Shader * shader);
		

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) = 0;

		virtual void Render() = 0;
	};

}

#endif
