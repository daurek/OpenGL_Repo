#ifndef OPENGL_TOOLKIT_SHADER_HEADER
#define OPENGL_TOOLKIT_SHADER_HEADER

    #include <string>
	#include <GL/glew.h> 

    namespace openglScene
    {

        class Shader
        {
 
        private:

      
            std::string log_string;

        private:

            Shader(const Shader & );

        public:

            Shader(const char* vertexFilePath, const char* fragmentFilePath);

			GLuint      shader_object_id;

            bool is_compiled () const
            {
                return (shader_object_id != 0);
            }

            bool compilation_failed () const
            {
                return (shader_object_id == 0);
            }

            const std::string & log () const
            {
                return (log_string);
            }

			void Use();

        public:

            operator GLuint () const
            {
                return (shader_object_id);
            }

        };

    }

#endif
