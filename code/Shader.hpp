/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Shader
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef SHADER_HEADER
#define SHADER_HEADER

// System
#include <vector>
// Libraries
#include <GL/glew.h> 
#include <glm/gtc/type_ptr.hpp>    
// Project
#include "Drawable.hpp"

namespace openglScene
{
	/// Handles and renders a List of drawables that use this Shader
    class Shader
    {

    public:

		/// Creates a Shader with the given vertex and fragment file paths
        Shader(const char* vertexFilePath, const char* fragmentFilePath);

		/// Deletes the shader program
		~Shader();

		/// Changes OpenGL shader to this one
		void Use();

		/// Renders every drawable
		void Render();

		/// Adds the given drawable reference to the list
		void AddDrawable(Drawable * drawable);

		/// Return the ID of the current shader program
        GLuint getShaderID() const
        {
            return shaderId;
        }

		//________________________________________________________ Shader Property Setters

		/// Sets the given integer value into the uniform location by the given name into the Shader Program
		void setInt(const std::string &name, int value) const
		{
			glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
		}

		/// Sets the given float value into the uniform location by the given name into the Shader Program
		void setFloat(const std::string &name, float value) const
		{
			glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
		}

		/// Sets the given bool value into the uniform location by the given name into the Shader Program
		void setBool(const std::string &name, bool value) const
		{
			glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
		}

		/// Sets the given vector3 value into the uniform location by the given name into the Shader Program
		void setVector3(const std::string &name, glm::vec3 value) const
		{
			glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, glm::value_ptr(value));
		}

		/// Sets the given vector4 value into the uniform location by the given name into the Shader Program
		void setVector4(const std::string &name, glm::vec4 value) const
		{
			glUniform4fv(glGetUniformLocation(shaderId, name.c_str()), 1, glm::value_ptr(value));
		}

		/// Sets the given matrix4 value into the uniform location by the given name into the Shader Program
		void setMatrix4(const std::string &name, glm::mat4 value) const
		{
			glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}

		/// Type enumerator used to toggle between OpenGL declarations
		enum Type
		{
			DEFAULT,
			ALPHA
		};

		/// Type used by the shader 
		Type shaderType;

	private:

		/// Shader Program ID
		GLuint      shaderId;

		/// List of drawable references using this Shader
		std::vector<Drawable *> drawablesByShader;

		/// Prints out Shader errors
		void CheckErrors(GLuint shader, std::string type);

    };

}

#endif
