/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::PostProcessing
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "PostProcessing.hpp"

namespace openglScene
{
	PostProcessing::PostProcessing(std::shared_ptr<Shader> _shader, int width, int height)
	{
		// Save PostProcessing shader
		postProcessingShader = _shader;
		// Create and bind framebuffer
		glGenFramebuffers(1, &frameBufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
		{
			// Bind screen texture
			glGenTextures(1, &screenTexture);
			glBindTexture(GL_TEXTURE_2D, screenTexture);
			{
				// Create texture
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			// Unbind Texture
			glBindTexture(GL_TEXTURE_2D, 0);

			// Attach texture to framebuffer
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

			// Render buffer 
			glGenRenderbuffers(1, &renderBufferID);
			glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);
			{
				// Create render buffer storage based on given screen dimensions
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
				// Attach render buffer to frame buffer
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferID);
				// Check if the framebuffer has been succesfully completed
				assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
			}
			// Unbind render buffer
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			// Screen vertices (position and texture coordinates
			float screenVertices[] =
			{
				-1.0f,  1.0f,  0.0f, 1.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				1.0f, -1.0f,  1.0f, 0.0f,

				-1.0f,  1.0f,  0.0f, 1.0f,
				1.0f, -1.0f,  1.0f, 0.0f,
				1.0f,  1.0f,  1.0f, 1.0f
			};

			// Screen VAO generation
			glGenVertexArrays(1, &screenVAO);
			glBindVertexArray(screenVAO);
			{
				// VBO generation, fill with screen vertices
				glGenBuffers(1, &screenVBO); 
				glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertices), &screenVertices, GL_STATIC_DRAW);
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
			}
			// Unbind Screen VAO
			glBindVertexArray(0);
		}
		// Unbind framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	PostProcessing::~PostProcessing()
	{
		// Delete buffers
		glDeleteVertexArrays(1, &screenVAO);
		glDeleteBuffers(1, &screenVBO);
		glDeleteFramebuffers(1, &renderBufferID);
		glDeleteFramebuffers(1, &frameBufferID);
		glDeleteTextures(1, &screenTexture);
	}

	void PostProcessing::Bind()
	{
		// Bind the framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
		// Enable depth test to render scene 
		glEnable(GL_DEPTH_TEST);
	}

	void PostProcessing::Render()
	{
		// Bind to default framebuffer (normal screen)
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		// Disable depth testing in order to render the texture from the framebuffer
		glDisable(GL_DEPTH_TEST);
		// Clear Color buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Use Postprocessing shader (in this case it's Blur)
		postProcessingShader->Use();
		// Draw binded screen vertex array object with texture
		glBindVertexArray(screenVAO);
		glBindTexture(GL_TEXTURE_2D, screenTexture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}


}
