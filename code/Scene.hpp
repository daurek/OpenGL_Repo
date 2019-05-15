#ifndef SCENE_HEADER
#define SCENE_HEADER

#include <GL/glew.h>            // Debe incluirse antes que gl.h
#include "Model.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Skybox.hpp"
#include <string>
#include <memory>
#include <map>
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4

namespace openglScene
{

    class Scene
    {
    private:

		std::shared_ptr<Camera>			camera;
		std::shared_ptr<Skybox>			skybox;

        std::map<std::string, std::shared_ptr < Model >>	models;
        std::map<std::string, std::shared_ptr < Shader >>	shaderList;

    public:

        Scene(int width, int height);

        void	Update ();
        void	Render ();
        void	Resize (int width, int height);

	private:

		void	CompileShaders();

    };

}

#endif
