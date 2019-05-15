#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Shader.hpp"
#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4

namespace openglScene
{

    class Skybox
    {

    public:

		unsigned int					cubemapTexture;
		GLuint							vbo_id;                      // Id del VBO de las coordenadas
		GLuint							vao_id;                      // Id del VAO del cubo
		std::shared_ptr<Shader>			skyboxShader;

        Skybox(const std::string & texture_path);

        void   Render ();

	private:

		unsigned int LoadCubemap(std::vector<std::string> faces);

    };

}

#endif
