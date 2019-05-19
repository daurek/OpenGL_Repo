/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Scene
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

#ifndef SCENE_HEADER
#define SCENE_HEADER

// Project
#include "Camera.hpp"
#include "PostProcessing.hpp"

namespace openglScene
{
	/// Handles every Drawables Rendering through a Shaderlist and stores Camera and PostProcessing instances
    class Scene
    {

    public:

		/// Creates a Scene, a Camera with the given dimensions, loads every Drawable (model and skybox) and a new Post Processing profile
        Scene(int width, int height);

		/// Update every Drawable (transform Update) along with Input handling and custom movements
        void	Update ();

		/// Renders every Shader's drawable list references in order 
        void	Render ();

		/// Creates a new OpenGL viewport with the given dimensions
        void	Resize (int width, int height);


	private:

		/// Stores a Scene Camera instance
		std::shared_ptr<Camera>								camera;

		/// Store a Scene PostProcessing instance
		std::shared_ptr<PostProcessing>						postProcessing;

		/// List of every Drawable on the Scene (Used only to update them)
		std::map<std::string, std::shared_ptr < Drawable >>	drawables;

		/// List of every Shader on the Scene (Used to add Drawables to them)
		std::map<std::string, std::shared_ptr < Shader >>	shaderList;

		/// Loads every drawable
		void	LoadDrawables();

		/// Compiles and add initial data into Shaders
		void	CompileShaders();

    };

}

#endif
