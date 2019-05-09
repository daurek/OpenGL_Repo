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

    Mesh::Mesh(std::vector<GLfloat> _coordinates, std::vector<GLfloat> _normals, std::vector<GLfloat> _uv, std::vector<GLuint> _indices)
		: coordinates(_coordinates), normals(_normals), uvs(_uv), indices(_indices)
    {
        // Se generan índices para los VBOs del cubo:
        glGenBuffers (VBO_COUNT, vbo_ids);
        glGenVertexArrays (1, &vao_id);

        // Se activa el VAO del cubo para configurarlo:
        glBindVertexArray (vao_id);

        // Se suben a un VBO los datos de coordenadas y se vinculan al VAO:
        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * coordinates.size(), coordinates.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray (0);
        glVertexAttribPointer (COORDINATES_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

        // Se suben a un VBO los datos de color y se vinculan al VAO:
        //glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        //glBufferData (GL_ARRAY_BUFFER, sizeof(GLubyte) * colors.size(), colors.data(), GL_STATIC_DRAW);
        //glEnableVertexAttribArray (1);
        //glVertexAttribPointer (COLORS_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), normals.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(NORMALS_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//-------------------------

		//GLuint tex;
		//glGenTextures(1, &tex);
		//int width, height;


		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, tex);	

		//unsigned char* image = SOIL_load_image("../../../../assets/textures/lambo.jpeg", &width, &height, 0, SOIL_LOAD_RGB);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		//SOIL_free_image_data(image);
		//GLint id;
		//glGetIntegerv(GL_CURRENT_PROGRAM, &id);
		//glUniform1i(glGetUniformLocation(id, "diffuse"), 0);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//-------------------------
		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[UV_VBO]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uvs.size(), uvs.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(UV_VBO, 2, GL_FLOAT, GL_FALSE, 0, 0);
		
        // Se suben a un IBO los datos de índices
        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDICES_IBO]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
        glBindVertexArray (0);
    }

    Mesh::~Mesh()
    {
        // Free buffers
        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
    }

    void Mesh::Render ()
    {
        // Bind VAO and draw
        glBindVertexArray (vao_id);
        glDrawElements    (GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		// Unbind
        glBindVertexArray (0);
    }

}
