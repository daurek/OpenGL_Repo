/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Drawable
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef DRAWABLE_HEADER
#define DRAWABLE_HEADER

// Project
#include "Node.hpp"

namespace openglScene
{
	class Shader;

	/// Base class for every Drawable entity with a Shader
    class Drawable : public Node
    {
	public:

		/// Add the current Drawable object to the given Shader's list
		Drawable(Shader * shader);

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) = 0;

		virtual void Render() = 0;
	};

}

#endif
