/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Drawable
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Drawable.hpp"
// Project
#include "Shader.hpp"

namespace openglScene
{
	Drawable::Drawable(Shader * shader)
	{
		// Add this object to the Shader's list
		if (shader != nullptr)
			shader->AddDrawable(this);
	}
}
