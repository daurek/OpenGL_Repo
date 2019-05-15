#ifndef MODEL_HEADER
#define MODEL_HEADER

// Header
#include "Mesh.hpp"
#include "Node.hpp"

// System
#include <vector>
#include <map>
// Libraries
#include <SFML/OpenGL.hpp>
#include <assimp/scene.h>
#include "glm/glm.hpp"

namespace openglScene
{

    class Model : public Node
    {
    public:

		Model(const std::string & modelPath, const std::string & texturePath = "");

		virtual void Update(glm::mat4 _transform = glm::mat4(1.0f)) override;

        void Render ();

    private:

		std::shared_ptr<Mesh> LoadMesh(aiMesh * mesh, const aiScene * scene, const std::string & texturePath = "");

        // Mesh List
		std::vector<std::shared_ptr<Mesh>> meshes;


	};

}

#endif
