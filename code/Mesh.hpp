/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Mesh
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef MESH_HEADER
#define MESH_HEADER

// System
#include <vector>
#include <memory>
// Libraries
#include <GL/glew.h>

namespace openglScene
{
	/// Stores the 3D Mesh data into multiple Indices
    class Mesh
    {

    public:

		/// Creates Mesh with the given vertex data lists and face indices along with an optional texture path
		Mesh(std::vector<GLfloat> _coordinates, std::vector<GLfloat> _normals, std::vector<GLfloat> _uv, std::vector<GLuint> _indices, const std::string & texturePath = "");
        
		/// Delete Mesh buffers
		~Mesh();

		/// Renders Mesh
        void Render ();

	private:

		/// VBO Indices Types
		enum
		{
			COORDINATES_VBO,
			COLORS_VBO,
			NORMALS_VBO,
			UV_VBO,
			INDICES_IBO,
			VBO_COUNT
		};

		/// VBOs used
		GLuint meshVBOs[VBO_COUNT];
		/// VAO used
		GLuint meshVAO;

		/// Vertex position list
		std::vector<GLfloat> coordinates;

		/// Vertex Color list
		std::vector<GLubyte> colors;

		/// Vertex Normal list
		std::vector<GLfloat> normals;

		/// Vertex TextureCoordinate list
		std::vector<GLfloat> uvs;

		/// Face Indices
		std::vector<GLuint> indices;

		/// Texture Data Structure
		struct Texture
		{
			GLuint id;
			std::string type;

			Texture(GLuint _id, std::string _type)
			{
				id = _id;
				type = _type;
			}
		};

		/// If the mesh has a Texture
		bool	hasTexture = false;

		/// Current Texture Data 
		std::shared_ptr<Texture> texture;

		/// Loads Texture with the given path and type
		std::shared_ptr<Texture> LoadTexture(std::string texturePath, std::string type);

    };

}

#endif
