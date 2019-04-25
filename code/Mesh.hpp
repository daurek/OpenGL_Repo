#ifndef MESH_HEADER
#define MESH_HEADER

#include <SFML/OpenGL.hpp>
#include <vector>
#include "Color_Buffer_Rgba8888.hpp"

namespace openglScene
{
	typedef Color_Buffer_Rgba8888 Texture;

    class Mesh
    {
    private:

        // Índices para indexar el array vbo_ids:
        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
			NORMALS_VBO,
			UV_VBO,
            INDICES_IBO,
            VBO_COUNT
        };

		struct Vertex
		{
			GLfloat coordinate;
			GLubyte color;
			GLfloat normals;
			GLfloat uvs;
		};

        // Vertex Data
		std::vector<GLfloat> coordinates;
		std::vector<GLubyte> colors;
		std::vector<GLfloat> normals;
		std::vector<GLfloat> uvs;
		// Face Data
		std::vector<GLuint> indices;

    private:

        GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
        GLuint vao_id;                  // Id del VAO del cubo

    public:

		Mesh(std::vector<GLfloat> _coordinates, std::vector<GLfloat> _normals, std::vector<GLfloat> _uv, std::vector<GLuint> _indices);
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> _indices);
        ~Mesh();

        void Render ();

    };

}

#endif
