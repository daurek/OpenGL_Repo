/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Model
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Model.hpp"
// System
#include <iostream>
// Libraries
#include <GL/glew.h>            
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
extern "C"
{
	#include <SOIL2.h>
}

namespace openglScene
{
	Model::Model(Shader * shader, const std::string & path, const std::string & texturePath) : Drawable(shader)
	{
		// Create Assimp Importer
		Assimp::Importer importer;
		// Load file with given path
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		// Check if valid path and file
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << importer.GetErrorString() << std::endl;
			return;
		}
		std::cout << "______________________________________________________" << std::endl;
		std::cout << "Loading Model: " << path << std::endl;
		// Load meshes
		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
			meshes.push_back(LoadMesh(scene->mMeshes[i], scene, texturePath));
		
		std::cout << "______________________________________________________" << std::endl;
	}

	void Model::Update(glm::mat4 parentTransform)
	{
		// Update current Transform depending on the parent given one
		transform = parentTransform * translation * rotation * scaling;

		// Update every child transform giving out our transform 
		for (auto & model : children)
			model.second->Update(transform);
	}

	void Model::Render()
	{
		// Render every mesh
		for (auto & mesh : meshes)
			mesh->Render();
	}

	std::shared_ptr<Mesh> Model::LoadMesh(aiMesh * mesh, const aiScene * scene, const std::string & texturePath)
	{
		std::cout << "	Loading Mesh: " << mesh->mName.C_Str() << std::endl;

		// Create vertex data list and face data list
		std::vector<GLfloat>	coordinates;
		std::vector<GLfloat>	normals;
		std::vector<GLfloat>	uv;
		std::vector<GLuint>		indices;

		// Loop Vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			// Get Vertex Position
			coordinates.push_back(mesh->mVertices[i].x);
			coordinates.push_back(mesh->mVertices[i].y);
			coordinates.push_back(mesh->mVertices[i].z);

			// Get Vertex Color
			//colors.push_back(mesh->mColors[i]->r);
			//colors.push_back(mesh->mColors[i]->g);
			//colors.push_back(mesh->mColors[i]->b);

			// Get Vertex Normal
			normals.push_back(mesh->mNormals[i].x);
			normals.push_back(mesh->mNormals[i].y);
			normals.push_back(mesh->mNormals[i].z);

			// Get Vertex Texture Coord
			if (mesh->mTextureCoords[0])
			{
				uv.push_back(mesh->mTextureCoords[0][i].x);
				uv.push_back(mesh->mTextureCoords[0][i].y);
			}
			else
			{
				uv.push_back(0.f);
				uv.push_back(0.f);
			}
		}

		// Loop Faces
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				// Get Face Indices
				indices.push_back(face.mIndices[j]);
		}

		// Debug prints
		std::cout << "		Vertices: " << mesh->mNumVertices << std::endl;
		std::cout << "		Indices:  " << indices.size() << std::endl;

		// Returns loaded Mesh
		return std::make_shared<Mesh>(coordinates, normals, uv, indices, texturePath);
	}

}
