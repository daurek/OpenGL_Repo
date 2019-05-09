#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4

namespace openglScene
{

    class Skybox
    {
    private:

        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;

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
