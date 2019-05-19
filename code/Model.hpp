/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Model
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef MODEL_HEADER
#define MODEL_HEADER

// Header
#include "Mesh.hpp"

// System
#include <vector>
// Libraries
#include <assimp/scene.h>
// Project
#include "Shader.hpp"

namespace openglScene
{
	/// Stores a list of Meshes renderable through a Shader with a single Transform Node
    class Model : public Drawable
    {
    public:

		/// Loads a Model through the given path applying a Shader to it with an optional texture
		Model(Shader * shader, const std::string & modelPath, const std::string & texturePath = "");

		/// Updates this Transform with the given parent one and every child Transform with the new calculated one
		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) override;

		/// Renders every mesh on the list
		virtual void Render () override;

    private:

		/// Returns a Mesh imported via Assimp with an optional texture
		std::shared_ptr<Mesh> LoadMesh(aiMesh * mesh, const aiScene * scene, const std::string & texturePath = "");

        /// Mesh List
		std::vector<std::shared_ptr<Mesh>> meshes;

	};

}

#endif
