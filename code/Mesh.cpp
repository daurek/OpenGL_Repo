#include <GL/glew.h>            
#include "Mesh.hpp"
#include <iostream>
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
        glGenBuffers (VBO_COUNT, vbo_ids);
        glGenVertexArrays (1, &vao_id);

        // Bind VAO to fill out with Mesh data
        glBindVertexArray (vao_id);

        // Bind Verter Coordinates to VBO and link to VAO 
        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray (0);
        glVertexAttribPointer (COORDINATES_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Bind Vertex Colors to VBO and link to VAO 
        //glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        //glBufferData (GL_ARRAY_BUFFER, sizeof(GLubyte) * colors.size(), colors.data(), GL_STATIC_DRAW);
        //glEnableVertexAttribArray (1);
        //glVertexAttribPointer (COLORS_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind Vertex Normals to VBO and link to VAO 
		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), normals.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(NORMALS_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind Vertex Texture Coordinates to VBO and link to VAO 
		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[UV_VBO]);
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
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_IBO]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

		// Unbind VAO after finishing everything
        glBindVertexArray (0);
    }

    Mesh::~Mesh()
    {
		// Free texture
		if(hasTexture)
			glDeleteTextures(1, &texture->id);
        // Free buffers
        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
    }

    void Mesh::Render ()
    {
		// Bind texture if it has any
		if (hasTexture)
			glBindTexture(GL_TEXTURE_2D, texture->id);
		else
			glBindTexture(GL_TEXTURE_2D, 0);

        // Bind VAO and draw
        glBindVertexArray (vao_id);
        glDrawElements    (GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		// Unbind
        glBindVertexArray (0);
    }

	std::shared_ptr<Mesh::Texture> Mesh::LoadTexture(std::string texturePath, std::string type)
	{
		GLuint tex;
		glGenTextures(1, &tex);
		int width, height;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);

		unsigned char* image = SOIL_load_image(texturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		GLint id;
		glGetIntegerv(GL_CURRENT_PROGRAM, &id);
		glUniform1i(glGetUniformLocation(id, type.c_str()), 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		return std::make_shared<Texture>(tex, type);
	}

}
