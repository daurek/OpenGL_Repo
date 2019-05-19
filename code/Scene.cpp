/// ----------------------------------------------------------------------------------------------------------------------
/// OPENGL SCENE
/// \class openglScene::Scene
///
/// \author Ilyass Sofi Hlimi
/// \date 19/05/2019
///
/// Contact: ilyassgame@gmail.com
/// ----------------------------------------------------------------------------------------------------------------------

// Header
#include "Scene.hpp"
// System
#include <iostream>
// Libraries
#include "SFML/Window/Keyboard.hpp"
extern "C"
{
	#include <SOIL2.h>
}
// Project
#include "Skybox.hpp"
#include "Model.hpp"

namespace openglScene
{
	Scene::Scene(int width, int height)
	{
		// Basic OpenGL Config
		glEnable(GL_CULL_FACE);

		// Create camera
		camera = std::make_shared<Camera>(70.f, GLfloat(width) / height, 0.1f, 100.f);
		camera->Translate({ 0,0,-10 });

		// Resize Viewport and projection
		Resize (width, height);

		// Compile Shaders and Load Drawables (skybox and models)
		CompileShaders();
		LoadDrawables();

		// Create PostProcess
		postProcessing = std::make_shared<PostProcessing>(shaderList["postProcess"], width, height);
    }

    void Scene::Update ()
    {
		// Update every model
		for (auto & drawable : drawables)
			drawable.second->Update();

		// ______________________________ Custom
		camera->Rotate({ 0.f, 1.f, 0.f }, 0.1f);
		drawables["box"]->Rotate({ 0.f, 1.f, 0.f }, 0.5f);
		drawables["sword"]->Rotate({ 0.f, 1.f, 0.f }, 0.3f);

		// Camera Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			camera->Move({ 0, 0, 1 });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			camera->Move({ 0, 0, -1 });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			camera->Move({ -1, 0, 0 });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			camera->Move({ 1, 0, 0 });

		// Camera Speed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			camera->setSpeed(0.5f);
		else
			camera->setSpeed(0.05f);

		// Enable Postprocessing Blur
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			shaderList["postProcess"]->Use();
			shaderList["postProcess"]->setBool("blur", true);
			glUseProgram(0);
		}

		// Disable Postprocessing Blur
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
		{
			shaderList["postProcess"]->Use();
			shaderList["postProcess"]->setBool("blur", false);
			glUseProgram(0);
		}
    }

    void Scene::Render ()
    {
		// Bind the framebuffer and enable depth test to render Scene
		postProcessing->Bind();

		// _____________________________ Render Scene

		// Clear buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		// Loop shaders
		for (auto & shader : shaderList)
		{
			// Get and Use Shader
			auto shaderProgram = shader.second;
			shaderProgram->Use();

			// TO_DO: Only check if it's not the same type than the previous one
			// Check type 
			switch (shaderProgram->shaderType)
			{
				// Set it to opaque
				case Shader::DEFAULT:
				{
					glDisable(GL_BLEND);
					break;
				}
				// Set it to transparent
				case Shader::ALPHA:
				{
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				}
				default:
					break;
			}
			
			// Send MVP matrices (model matrix is sent per model on render)
			shaderProgram->setMatrix4("view_matrix", camera->getTransform());
			shaderProgram->setMatrix4("normal_matrix", glm::transpose(glm::inverse(camera->getTransform())));
			shaderProgram->setMatrix4("projection_matrix", camera->getProjection());

			// Render every model using that shader
			shaderProgram->Render();
		}

		// _____________________________ Render Framebuffer screen texture after rendering scene
		postProcessing->Render();
		
    }

    void Scene::Resize (int width, int height)
    {
		// Reset aspect ratio
		camera->setAspectRatio(GLfloat(width) / height);

		// Set new viewport
        glViewport (0, 0, width, height);
    }

	void Scene::LoadDrawables()
	{
		std::cout << "________________________________________________________________________ Loading Drawables" << std::endl;

		// Create skybox
		drawables["skybox"] = std::make_shared<Skybox>(shaderList["skybox"].get(), "../../../../assets/textures/skybox/");

		// Load models
		drawables["box"] = std::make_shared<Model>(shaderList["default"].get(), "../../../../assets/meshes/box.fbx", "../../../../assets/textures/albedo.png");
		drawables["box"]->Scale({ 0.005f, 0.005f, 0.005f });
		drawables["box"]->Translate({ 0.f, 0.f, 0.f });

		drawables["sword"] = std::make_shared<Model>(shaderList["default"].get(), "../../../../assets/meshes/sword.fbx", "../../../../assets/textures/swordAlbedo.png");
		drawables["sword"]->Scale({ 0.05f, 0.05f, 0.05f });
		drawables["sword"]->Translate({ 6.f, 0.f, 0.f });

		drawables["electricBox"] = std::make_shared<Model>(shaderList["default"].get(), "../../../../assets/meshes/electricBox.fbx", "../../../../assets/textures/electricBoxAlbedo.tga");
		drawables["electricBox"]->Scale({ 0.02f, 0.02f, 0.02f });
		drawables["electricBox"]->Translate({ -5.f, 0.f, 0.f });
		drawables["electricBox"]->Rotate({ 1.f, 0.f, 0.f }, -90);
		drawables["electricBox"]->Rotate({ 0.f, 0.f, 1.f }, -90);

		drawables["shield"] = std::make_shared<Model>(shaderList["default"].get(), "../../../../assets/meshes/shield.fbx", "../../../../assets/textures/shieldAlbedo.png");
		drawables["shield"]->Scale({ 0.05f, 0.05f, 0.05f });
		drawables["shield"]->Translate({ -2.f, -1.f, 0.f });

		drawables["box"]->AddChild("boxChild", std::make_shared<Model>(shaderList["transparent"].get(), "../../../../assets/meshes/box.fbx", "../../../../assets/textures/albedo.png"));

		std::shared_ptr<Model> boxChild = std::dynamic_pointer_cast<Model>(drawables["box"]->GetChild("boxChild"));
		boxChild->Translate({ 300.f, 0.f, 0.f });
		boxChild->Scale({ 0.8f, 0.8f, 0.8f });

		std::cout << "__________________________________________________________________________________________" << std::endl;
	}

	void Scene::CompileShaders()
	{
		// Create Default Shader
		shaderList["default"] = std::make_shared<Shader>("../../../../assets/shaders/default/vertex_shader.txt", "../../../../assets/shaders/default/fragment_shader.txt");
		auto defaultShader = shaderList["default"];
		defaultShader->shaderType = Shader::DEFAULT;
		// Set Properties
		defaultShader->Use();
		defaultShader->setVector4("light.position", { 10.f, 10.f, 10.f, 1.f });
		defaultShader->setVector3("light.color", { 1.0f, 1.0f, 1.0f });
		defaultShader->setFloat("ambient_intensity", 0.2f);
		defaultShader->setFloat("diffuse_intensity", 0.8f);

		// Create Transparent Shader
		shaderList["transparent"] = std::make_shared<Shader>("../../../../assets/shaders/transparent/vertex_shader.txt", "../../../../assets/shaders/transparent/fragment_shader.txt");
		auto transparentShader = shaderList["transparent"];
		transparentShader->shaderType = Shader::ALPHA;
		// Set Properties
		transparentShader->Use();
		transparentShader->setVector4("light.position", { 10.f, 10.f, 10.f, 1.f });
		transparentShader->setVector3("light.color", { 1.0f, 1.0f, 1.0f });
		transparentShader->setFloat("ambient_intensity", 0.2f);
		transparentShader->setFloat("diffuse_intensity", 0.8f);

		// Create PostProcessing Shader
		shaderList["postProcess"] = std::make_shared<Shader>("../../../../assets/shaders/postProcessing/vertex_shader.txt", "../../../../assets/shaders/postProcessing/fragment_shader.txt");
		auto postProcessShader = shaderList["postProcess"];
		postProcessShader->shaderType = Shader::DEFAULT;

		// Create Skybox Shader
		shaderList["skybox"] = std::make_shared<Shader>("../../../../assets/shaders/skybox/skybox_vertex_shader.txt", "../../../../assets/shaders/skybox/skybox_fragment_shader.txt");
		shaderList["skybox"]->shaderType = Shader::DEFAULT;
	
	}


}
