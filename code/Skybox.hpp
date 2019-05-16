#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Drawable.hpp"
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4

namespace openglScene
{

    class Skybox : public Drawable
    {

    public:

		unsigned int					cubemapTexture;
		GLuint							vbo_id;                      // Id del VBO de las coordenadas
		GLuint							vao_id;                      // Id del VAO del cubo

        Skybox(Shader * shader, const std::string & texture_path);

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) override;
        virtual void Render () override;

	private:

		unsigned int LoadCubemap(std::vector<std::string> faces);
	};

}

#endif
