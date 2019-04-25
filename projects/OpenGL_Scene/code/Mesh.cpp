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

namespace example
{

    Mesh::Mesh()
    {
		// Create Assimp Importer
		Assimp::Importer importer;
		// Load file with given path
		const aiScene *scene = importer.ReadFile("../../../../assets/meshes/car.fbx", aiProcess_Triangulate | aiProcess_FlipUVs);
		// Check if valid path and file
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << importer.GetErrorString() << std::endl;
			return;
		}

		// Get Mesh
		auto * mesh = scene->mMeshes[0];
		// Loop Vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// Get Vertex Position
			coordinates.push_back(mesh->mVertices[i].x);
			coordinates.push_back(mesh->mVertices[i].y);
			coordinates.push_back(mesh->mVertices[i].z);

			// Get Vertex Normal
			normals.push_back(mesh->mNormals[i].x);
			normals.push_back(mesh->mNormals[i].y);
			normals.push_back(mesh->mNormals[i].z);

			// Get Vertex Normal
			uv.push_back(mesh->mTextureCoords[0][i].x);
			uv.push_back(mesh->mTextureCoords[0][i].y);
		}

		// Loop Faces
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				// Get Face Indices
				indices.push_back(face.mIndices[j]);
		}

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
        //glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), colors.data(), GL_STATIC_DRAW);
        //glEnableVertexAttribArray (1);
        //glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), normals.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(NORMALS_VBO, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//-------------------------
		GLuint tex;
		glGenTextures(1, &tex);

		int width, height;
		unsigned char* image;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);

		image = SOIL_load_image("../../../../assets/textures/lambo.jpeg", &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
		GLint id;
		glGetIntegerv(GL_CURRENT_PROGRAM, &id);
		glUniform1i(glGetUniformLocation(id, "diffuse"), 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//-------------------------
		glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[UV_VBO]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uv.size(), uv.data(), GL_STATIC_DRAW);
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
        // Se selecciona el VAO que contiene los datos del objeto y se dibujan sus elementos:
        glBindVertexArray (vao_id);
        glDrawElements    (GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray (0);
    }

}
