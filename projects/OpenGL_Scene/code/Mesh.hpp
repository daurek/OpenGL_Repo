
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef MESH_HEADER
#define MESH_HEADER

    #include <SFML/OpenGL.hpp>
	#include <vector>
	#include "Color_Buffer_Rgba8888.hpp"

    namespace example
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

            // Vertex Data
			std::vector<GLfloat> coordinates;
			std::vector<GLfloat> colors;
			std::vector<GLfloat> normals;
			std::vector<GLfloat> uv;
			// Face Data
			std::vector<GLuint> indices;

        private:

            GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
            GLuint vao_id;                  // Id del VAO del cubo

        public:

            Mesh();
           ~Mesh();

            void Render ();

        };

    }

#endif
