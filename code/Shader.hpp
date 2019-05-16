#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <GL/glew.h> 
#include <string>
#include <vector>
#include "Drawable.hpp"
#include <glm/gtc/type_ptr.hpp>    

namespace openglScene
{

    class Shader
    {

    private:

		GLuint      shaderId;

    public:

        Shader(const char* vertexFilePath, const char* fragmentFilePath);

		void Use();

		void Render();


		void AddDrawable(Drawable * drawable);

        GLuint getShaderID() const
        {
            return shaderId;
        }
		// Shader Property Setters

		void setInt(const std::string &name, int value) const
		{
			glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
		}

		void setFloat(const std::string &name, float value) const
		{
			glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
		}

		void setVector3(const std::string &name, glm::vec3 value) const
		{
			glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, glm::value_ptr(value));
		}

		void setVector4(const std::string &name, glm::vec4 value) const
		{
			glUniform4fv(glGetUniformLocation(shaderId, name.c_str()), 1, glm::value_ptr(value));
		}

		void setMatrix4(const std::string &name, glm::mat4 value) const
		{
			glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}

		enum Type
		{
			DEFAULT,
			ALPHA
		};

		Type shaderType;

	private:

		std::vector<Drawable *> drawablesByShader;

		void CheckErrors(unsigned int shader, std::string type);

    };

}

#endif
