#ifndef SCENE_HEADER
#define SCENE_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Model.hpp"
#include "Shader.hpp"
#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4

namespace openglScene
{

    class Scene
    {
    private:

		std::shared_ptr<Shader>			vertex_shader;
        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;
		GLint      normal_matrix_id;

        std::map<std::string, std::shared_ptr < Model >>   models;

        float  angle;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 view;

    public:

        Scene(int width, int height);

        void   Update ();
        void   Render ();
        void   Resize (int width, int height);

    private:

        GLuint compile_shaders        ();
        void   show_compilation_error (GLuint  shader_id);
        void   show_linkage_error     (GLuint program_id);
		void   configure_light		  (GLuint program_id);

    };

}

#endif
