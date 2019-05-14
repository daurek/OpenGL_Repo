#include <cassert>
#include <fstream>
#include <iostream>
#include "Shader.hpp"

namespace openglScene
{

    Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
    :
        shader_object_id(0)
    {
        if (source_code.is_not_empty ())
        {
            // Se crea el shader object:
            shader_object_id = glCreateShader (shader_type);

            // Se carga el código del shader:

            const char * shader_code_list[] = {        source_code         };
            const GLint  shader_size_list[] = { (GLint)source_code.size () };

            glShaderSource  (shader_object_id, 1, shader_code_list, shader_size_list);

            // Se compila el shader:

            glCompileShader (shader_object_id);

            // Se comprueba si la compilación ha tenido éxito:

            GLint succeeded = 0;

            glGetShaderiv (shader_object_id, GL_COMPILE_STATUS, &succeeded);

            if (!succeeded)
            {
                // Se guarda el log del error que ha ocurrido:

                GLint log_length;

                glGetShaderiv (shader_object_id, GL_INFO_LOG_LENGTH, &log_length);

                if (log_length > 0)
                {
                    log_string.resize  (log_length);

                    glGetShaderInfoLog (shader_object_id, log_length, NULL, &log_string.front ());
                }

                // Se libera el shader object, ya que ahora es un recurso encapsulado no usable:

		

                glDeleteShader (shader_object_id);

                shader_object_id = 0;

                assert(false);
            }
        }
        else
            assert(false);
    }

	void Shader::Use()
	{
		glUseProgram(shader_object_id);
	}

}
