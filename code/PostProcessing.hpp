/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::PostProcessing
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef POST_PROCESSING_HEADER
#define POST_PROCESSING_HEADER

#include "Shader.hpp"

namespace openglScene
{
	/// Handles PostProcessing with the given Shader applied on a Framebuffer
    class PostProcessing
    {

    public:

		/// Creates a Framebuffer with the given dimensions and stores the given Shader
		PostProcessing(std::shared_ptr<Shader> _shader, int width, int height);

		/// Deletes buffers
		~PostProcessing();

		/// Binds the Framebuffer 
		void Bind();

		/// Renders the framebuffer texture with the applied Shader effect
        void Render ();

	private:

		/// Framebuffer ID
		GLuint							frameBufferID;
		/// Renderbuffer ID
		GLuint							renderBufferID;

		/// Screen Texture ID
		GLuint							screenTexture;
		/// Screen VBO ID
		GLuint							screenVBO;
		/// Screen VAO ID
		GLuint							screenVAO;

		/// Post Processing Shader
		std::shared_ptr<Shader>			postProcessingShader;


	};

}

#endif
