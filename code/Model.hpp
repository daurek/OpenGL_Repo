#ifndef MODEL_HEADER
#define MODEL_HEADER

// Header
#include "Mesh.hpp"

// System
#include <vector>
// Libraries
#include <SFML/OpenGL.hpp>
#include <assimp/scene.h>
#include "glm/glm.hpp"

namespace openglScene
{

    class Model
    {
    public:

		Model(const std::string & path);

        void Render ();

		glm::mat4 transform;

    private:

		std::shared_ptr<Mesh> LoadMesh(aiMesh * mesh, const aiScene * scene);

        // Mesh List
		std::vector<std::shared_ptr<Mesh>> meshes;

    };

}

#endif
