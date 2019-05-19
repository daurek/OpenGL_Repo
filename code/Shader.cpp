/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Shader
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Shader.hpp"
// System
#include <fstream>
#include <iostream>
#include <sstream>

namespace openglScene
{

    Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
    :
        shaderId(0), shaderType(DEFAULT)
    {
		// Create shader string and file containers
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vertShaderFile;
		std::ifstream fragShaderFile;

		// Check for errors
		vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// Open vertex and fragment files
			vertShaderFile.open(vertexFilePath);
			fragShaderFile.open(fragmentFilePath);
			// Create stream readers
			std::stringstream vertShaderStream, fragShaderStream;
			// Read both files and buffer the content into the stream readers
			vertShaderStream << vertShaderFile.rdbuf();
			fragShaderStream << fragShaderFile.rdbuf();
			// Close files
			vertShaderFile.close();
			fragShaderFile.close();
			// Convert stream into string
			vertexCode = vertShaderStream.str();
			fragmentCode = fragShaderStream.str();
		}
		catch (std::ifstream::failure error)
		{
			std::cout << "ERROR: Shader has not been read succesfully" << std::endl;
		}

		// Convert to string
		const char* vertShaderCode = vertexCode.c_str();
		const char * fragShaderCode = fragmentCode.c_str();
		// Create shader ID
		GLuint vertexID, fragmentID;
		// Create Shader by type
		vertexID	= glCreateShader(GL_VERTEX_SHADER);
		fragmentID	= glCreateShader(GL_FRAGMENT_SHADER);
		// Send source code to each Shader 
		glShaderSource(vertexID, 1, &vertShaderCode, NULL);
		glShaderSource(fragmentID, 1, &fragShaderCode, NULL);
		// Compile Shaders
		glCompileShader(vertexID);
		glCompileShader(fragmentID);
		// Check for errors
		CheckErrors(vertexID, "VERTEX");
		CheckErrors(fragmentID, "FRAGMENT");
		// Create Shader program
		shaderId = glCreateProgram();
		// Attach both shaders to the Shader program
		glAttachShader(shaderId, vertexID);
		glAttachShader(shaderId, fragmentID);
		// Link it
		glLinkProgram(shaderId);
		// Check for errors
		CheckErrors(shaderId, "PROGRAM");
		// Delete since they are already linked
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
    }

	Shader::~Shader()
	{
		// Delete shader program
		glDeleteProgram(shaderId);
	}

	void Shader::Use()
	{
		// Use shader program
		glUseProgram(shaderId);
	}

	void Shader::Render()
	{
		// Send Model matrix and render model
		for (auto & model : drawablesByShader)
		{
			setMatrix4("model_matrix", model->getTransform());
			model->Render();
		}
	}

	void Shader::AddDrawable(Drawable * drawable)
	{
		// Adds a drawable to the list
		if (drawable != nullptr)
			drawablesByShader.push_back(drawable);
	}

	void Shader::CheckErrors(GLuint shader, std::string type)
	{
		int success;
		// Buffer to store error into
		char infoLog[1024];

		// Check fragment or vertex error
		if (type != "PROGRAM")
		{
			// Check if it has been successful
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				// Set the log into the buffer
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				// Print shader error
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		// Check shader program error
		else
		{
			// Check if it has been successful
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				// Set the log into the buffer
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				// Print shader error
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

}
