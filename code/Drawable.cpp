#include "Drawable.hpp"
#include "Shader.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace openglScene
{
	Drawable::Drawable(Shader * shader)
	{
		// Set shader
		shader->AddDrawable(this);
	}
}
