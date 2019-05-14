#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Color_Buffer_Rgba8888.hpp"
#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4

namespace openglScene
{

    class Skybox
    {
    private:

		GLuint         vbo_id;                      // Id del VBO de las coordenadas
		GLuint         vao_id;                      // Id del VAO del cubo

        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;

		typedef Color_Buffer_Rgba8888 Buffer;


    public:

        Skybox(const std::string & texture_path);

        void   Render ();

    private:

        GLuint compile_shaders        ();
        void   show_compilation_error (GLuint  shader_id);
        void   show_linkage_error     (GLuint program_id);

    };

}

#endif
