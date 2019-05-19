/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Skybox
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Skybox.hpp"
// System
#include <iostream>
// Libraries
extern "C"
{
	#include <SOIL2.h>
}

namespace openglScene
{
    Skybox::Skybox(Shader * shader, const std::string & texture_path) : Drawable(shader)
    {
		// Load cubemap skybox textures
		LoadCubemap({
			texture_path + "right.jpg",
			texture_path + "left.jpg",
			texture_path + "top.jpg",
			texture_path + "bottom.jpg",
			texture_path + "front.jpg",
			texture_path + "back.jpg"
		});

		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			1.0f,  1.0f, -1.0f,
			1.0f,  1.0f,  1.0f,
			1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			1.0f, -1.0f,  1.0f
		};

		// Generate and bind Skybox VAO
		glGenVertexArrays(1, &skyboxVAO);
		glBindVertexArray(skyboxVAO);
		{
			// Generate and bind Skybox VBO
			glGenBuffers(1, &skyboxVBO);
			glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		}
		// Unbind VBO
		glBindVertexArray(0);
    }

	Skybox::~Skybox()
	{
		// Delete buffers
		glDeleteVertexArrays(1, &skyboxVAO);
		glDeleteBuffers(1, &skyboxVBO);
		glDeleteTextures(1, &cubemapTexture);
	}

	void Skybox::Update(glm::mat4 _transform)
	{
		// Empty
	}

    void Skybox::Render ()
    {
		// Change depth so if it's equal then make the depth test pass
		glDepthFunc(GL_LEQUAL);

		// Bind Skybox VAO, enable and bind cubemap
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		// Draw Skybox 
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Depth back to default
		glDepthFunc(GL_LESS);
    }

	void Skybox::LoadCubemap(std::vector<std::string> faces)
	{
		// Error check
		if (faces.size() != 6)
		{
			std::cout << "Cubemap texture does not have 6 faces " << std::endl;
			return;
		}

		// Generate and bind cubemap texture
		glGenTextures(1, &cubemapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		
		// Loop every path (6 paths to make cubemap)
		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			// Load texture
			unsigned char *imageData = SOIL_load_image(faces[i].c_str(), &width, &height, &nrChannels, 0);
			// Check validity
			if (imageData)
				// Generate 2D texture
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			else
				// Incorrect texture path
				std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			// Free image data in any case
			SOIL_free_image_data(imageData);
		}
		// Set texture properties
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}


    

}
