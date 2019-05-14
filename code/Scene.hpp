#ifndef SCENE_HEADER
#define SCENE_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4

namespace openglScene
{

    class Scene
    {
    private:


        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;
		GLint      normal_matrix_id;
		std::shared_ptr<Shader>			defaultShader;
		std::shared_ptr<Camera>			camera;

        std::map<std::string, std::shared_ptr < Model >>   models;

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 view;

    public:

        Scene(int width, int height);

        void   Update ();
        void   Render ();
        void   Resize (int width, int height);

    };

}

#endif
