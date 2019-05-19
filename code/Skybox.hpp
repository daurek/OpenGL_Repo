/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Skybox
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef SKYBOX_HEADER
#define SKYBOX_HEADER

// System
#include <vector>
// Libraries
#include <GL/glew.h>          
// Project
#include "Drawable.hpp"

namespace openglScene
{
	/// Handles and Renders a Cubemap Skybox texture 
    class Skybox : public Drawable
    {

    public:

		/// Creates a Cubemap texture with the given map using the given Shader
        Skybox(Shader * shader, const std::string & texture_path);

		/// Deletes buffers
		~Skybox();

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) override;

		/// Renders the Skybox
        virtual void Render () override;

	private:

		/// Skybox Cubemap texture ID
		GLuint							cubemapTexture;
		/// Skybox VBO ID
		GLuint							skyboxVBO;                      
		/// Skybox VAO ID
		GLuint							skyboxVAO;                  

		/// Loads the given cubemap path into a texture
		void LoadCubemap(std::vector<std::string> cubemapPath);
	};

}

#endif
