#include "Skybox.hpp"
#include <iostream>
#include <cassert>

#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

namespace openglScene
{
    using namespace std;

    const string Skybox::vertex_shader_code =
		"#version 330\n"
		""
		"uniform mat4 model_view_matrix;"
		"uniform mat4 projection_matrix;"
		""
		"layout (location = 0) in vec3 vertex_coordinates;"
		""
		"out vec3 texture_coordinates;"
		""
		"void main()"
		"{"
		"   texture_coordinates = vec3(vertex_coordinates.x, -vertex_coordinates.y, vertex_coordinates.z);"
		"   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
		"}";

	const string Skybox::fragment_shader_code =
		"#version 330\n"
		""
		"in  vec3 texture_coordinates;"
		"out vec4 fragment_color;"
		""
		"uniform samplerCube texture_cube;"
		""
		"void main()"
		"{"
		"    fragment_color = texture (texture_cube, texture_coordinates);"
		"}";

    Skybox::Skybox(const std::string & texture_path)
    {
		GLuint program_id = compile_shaders();

		glUseProgram(program_id);

		model_view_matrix_id = glGetUniformLocation(program_id, "model_view_matrix");
		projection_matrix_id = glGetUniformLocation(program_id, "projection_matrix");
    }

    void Skybox::Render ()
    {
		
    }

    GLuint Skybox::compile_shaders ()
    {
        GLint succeeded = GL_FALSE;

        // Se crean objetos para los shaders:
        GLuint   vertex_shader_id = glCreateShader (GL_VERTEX_SHADER  );
        GLuint fragment_shader_id = glCreateShader (GL_FRAGMENT_SHADER);

        // Se carga el código de los shaders:
        const char *   vertex_shaders_code[] = {   vertex_shader_code.c_str () };
        const char * fragment_shaders_code[] = { fragment_shader_code.c_str () };
        const GLint    vertex_shaders_size[] = {   vertex_shader_code.size  () };
        const GLint  fragment_shaders_size[] = { fragment_shader_code.size  () };

        glShaderSource  (  vertex_shader_id, 1,   vertex_shaders_code,   vertex_shaders_size);
        glShaderSource  (fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

        // Se compilan los shaders:
        glCompileShader (  vertex_shader_id);
        glCompileShader (fragment_shader_id);

        // Se comprueba que si la compilación ha tenido éxito:
        glGetShaderiv   (  vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (  vertex_shader_id);

        glGetShaderiv   (fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (fragment_shader_id);

        // Se crea un objeto para un programa:
        GLuint program_id = glCreateProgram ();

        // Se cargan los shaders compilados en el programa:
        glAttachShader  (program_id,   vertex_shader_id);
        glAttachShader  (program_id, fragment_shader_id);

        // Se linkan los shaders:
        glLinkProgram   (program_id);

        // Se comprueba si el linkage ha tenido éxito:
        glGetProgramiv  (program_id, GL_LINK_STATUS, &succeeded);
        if (!succeeded) show_linkage_error (program_id);

        // Se liberan los shaders compilados una vez se han linkado:
        glDeleteShader (  vertex_shader_id);
        glDeleteShader (fragment_shader_id);

        return (program_id);
    }



    void Skybox::show_compilation_error (GLuint shader_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetShaderInfoLog (shader_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        //#ifdef _MSC_VER
        //    OutputDebugStringA (info_log.c_str ());
        //#endif

        assert(false);
    }

    void Skybox::show_linkage_error (GLuint program_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetProgramInfoLog (program_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

       /* #ifdef _MSC_VER
            OutputDebugStringA (info_log.c_str ());
        #endif*/

        assert(false);
    }

}
