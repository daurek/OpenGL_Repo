/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Mesh
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Mesh.hpp"
// System
#include <iostream>
// Libraries
#include <SFML/OpenGL.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
extern "C"
{
	#include <SOIL2.h>
}

namespace openglScene
{

    Mesh::Mesh(std::vector<GLfloat> _coordinates, std::vector<GLfloat> _normals, std::vector<GLfloat> _uv, std::vector<GLuint> _indices, const std::string & texturePath)
		: coordinates(_coordinates), normals(_normals), uvs(_uv), indices(_indices)
    {
		//------------------------- Vertex Data

        // Generate buffers for the VBOs
        glGenBuffers (VBO_COUNT, meshVBOs);
        glGenVertexArrays (1, &meshVAO);

        // Bind VAO to fill out with Mesh data
        glBindVertexArray (meshVAO);

        // Bind Verter Coordinates to VBO and link to VAO 
        glBindBuffer (GL_ARRAY_BUFFER, meshVBOs[COORDINATES_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray (0);
        glVertexAttribPointer (COORDINATES_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Bind Vertex Colors to VBO and link to VAO 
        glBindBuffer (GL_ARRAY_BUFFER, meshVBOs[COLORS_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(GLubyte) * colors.size(), colors.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray (1);
        glVertexAttribPointer (COLORS_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind Vertex Normals to VBO and link to VAO 
		glBindBuffer(GL_ARRAY_BUFFER, meshVBOs[NORMALS_VBO]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), normals.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(NORMALS_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind Vertex Texture Coordinates to VBO and link to VAO 
		glBindBuffer(GL_ARRAY_BUFFER, meshVBOs[UV_VBO]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size(), uvs.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(UV_VBO, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
		//------------------------- Texture

		// If has texture then load it
		if (!texturePath.empty())
		{
			texture = LoadTexture(texturePath, "diffuse");
			hasTexture = true;
		}

		//------------------------- Faces

        // Bind Index data
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, meshVBOs[INDICES_IBO]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

		// Unbind VAO after finishing everything
        glBindVertexArray (0);
    }

    Mesh::~Mesh()
    {
        // Free buffers
        glDeleteVertexArrays (1, &meshVAO);
        glDeleteBuffers      (VBO_COUNT, meshVBOs);
		if(hasTexture)
			glDeleteTextures(1, &texture->id);
    }

    void Mesh::Render ()
    {
		// Bind texture if it has any
		if (hasTexture)
			glBindTexture(GL_TEXTURE_2D, texture->id);
		else
			glBindTexture(GL_TEXTURE_2D, 0);

        // Bind VAO and draw
        glBindVertexArray (meshVAO);
        glDrawElements    (GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		// Unbind
        glBindVertexArray (0);
    }

	std::shared_ptr<Mesh::Texture> Mesh::LoadTexture(std::string texturePath, std::string type)
	{
		// Create a texture index
		GLuint tex;
		glGenTextures(1, &tex);
		glActiveTexture(GL_TEXTURE0);

		int width, height;

		// Bind Texture
		glBindTexture(GL_TEXTURE_2D, tex);
		// Load image data
		unsigned char* imageData = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		// Check Validity
		if (imageData)
			// Generate 2D texture
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		else
			// Incorrect texture path
			std::cout << "Texture failed to load at path: " << texturePath << std::endl;
		// Free image data in any case
		SOIL_free_image_data(imageData);

		// Send image to Shader
		GLint id;
		glGetIntegerv(GL_CURRENT_PROGRAM, &id);
		glUniform1i(glGetUniformLocation(id, type.c_str()), 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// return Final Texture (id and type)
		return std::make_shared<Texture>(tex, type);
	}

}
