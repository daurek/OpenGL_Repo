#include "Scene.hpp"
#include <iostream>
#include <cassert>
#include "SFML/Window/Keyboard.hpp"

#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

extern "C"
{
	#include <SOIL2.h>
}


namespace openglScene
{
    using namespace std;

	Scene::Scene(int width, int height)
	{
		// Basic OpenGL Config:
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// Create camera
		camera = std::make_shared<Camera>(70.f, GLfloat(width) / height, 0.1f, 100.f);
		camera->Move({ 0,0,-10 });

		// Create skybox
		skybox = std::make_shared<Skybox>("../../../../assets/textures/skybox/");

		// Compile Shaders
		CompileShaders();

		// Load models
		models["car"] = std::make_shared<Model>("../../../../assets/meshes/car.fbx", "../../../../assets/textures/lambo.jpeg");
		models["car"]->Scale({ 0.01f, 0.01f, 0.01f });
		models["car"]->Move({ -5.f, 0.f, 0.f });

		models["box"] = std::make_shared<Model>("../../../../assets/meshes/box.fbx", "../../../../assets/textures/albedo.png");
		models["box"]->Scale({ 0.005f, 0.005f, 0.005f });
		models["box"]->Move({ 0.f, 0.f, 0.f });

		models["sword"] = std::make_shared<Model>("../../../../assets/meshes/sword.fbx", "../../../../assets/textures/swordAlbedo.png");
		models["sword"]->Scale({ 0.05f, 0.05f, 0.05f });
		models["sword"]->Move({ 6.f, 0.f, 0.f });
		


		models["box"]->AddChild("boxChild", std::make_shared<Model>("../../../../assets/meshes/box.fbx", "../../../../assets/textures/albedo.png"));

		std::shared_ptr<Model> boxChild = std::dynamic_pointer_cast<Model>(models["box"]->GetChild("boxChild"));
		boxChild->Move({ 300.f, 0.f, 0.f });

		// Set Their shaders
		shaderList["default"]->AddModel(models["car"]);
		shaderList["default"]->AddModel(models["sword"]);
		shaderList["default"]->AddModel(boxChild);
		shaderList["transparent"]->AddModel(models["box"]);


        Resize (width, height);

    }

    void Scene::Update ()
    {
		// Camera Movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			camera->Move({ 0, 0, 1	});
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			camera->Move({ 0, 0, -1 });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			camera->Move({ 1, 0, 0	});
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			camera->Move({ -1, 0, 0 });

		// Update every model
		for (auto & model : models)
			model.second->Update();

		// Custom
		models["box"]->Rotate({ 0.f, 1.f, 0.f }, 0.5f);
		models["sword"]->Rotate({ 0.f, 1.f, 0.f }, 0.3f);
    }

    void Scene::Render ()
    {
		// Clear buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		skybox->skyboxShader->Use();
		skybox->skyboxShader->setMatrix4("model_view_matrix", glm::mat4(glm::mat3(camera->getTransform())));
		skybox->skyboxShader->setMatrix4("projection_matrix", camera->getProjection());
		skybox->Render();

		// Loop shaders
		for (auto & shader : shaderList)
		{
			// Get Shader
			auto shaderProgram = shader.second;

			// TO_DO: Only check if it's not the same type than the previous one
			// Check type 
			switch (shaderProgram->shaderType)
			{
				// Set it to opaque
				case Shader::DEFAULT:
				{
					glEnable(GL_CULL_FACE);
					glDisable(GL_BLEND);
					break;
				}
				// Set it to transparent
				case Shader::ALPHA:
				{
					glDisable(GL_CULL_FACE);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					break;
				}
				default:
					break;
			}
			
			// Use shader to send MVP matrices (model matrix is sent per model on render)
			shaderProgram->Use();
			shaderProgram->setMatrix4("view_matrix", camera->getTransform());
			shaderProgram->setMatrix4("normal_matrix", glm::transpose(glm::inverse(camera->getTransform())));
			shaderProgram->setMatrix4("projection_matrix", camera->getProjection());

			// Render every model using that shader
			shaderProgram->Render();
		}
    }

    void Scene::Resize (int width, int height)
    {
		// Reset projection here

		// Set new viewport
        glViewport (0, 0, width, height);
    }

	void Scene::CompileShaders()
	{
		// Create Default Shader
		shaderList["default"] = std::make_shared<Shader>("../../../../assets/shaders/default/vertex_shader.txt", "../../../../assets/shaders/default/fragment_shader.txt");
		shaderList["default"]->shaderType = Shader::DEFAULT;
		// Set Properties
		shaderList["default"]->Use();
		shaderList["default"]->setVector4("light.position", { 10.f, 10.f, 10.f, 1.f });
		shaderList["default"]->setVector3("light.color", { 1.0f, 1.0f, 1.0f });
		shaderList["default"]->setFloat("ambient_intensity", 0.2f);
		shaderList["default"]->setFloat("diffuse_intensity", 0.8f);

		// Create Transparent Shader
		shaderList["transparent"] = std::make_shared<Shader>("../../../../assets/shaders/transparent/vertex_shader.txt", "../../../../assets/shaders/transparent/fragment_shader.txt");
		shaderList["transparent"]->shaderType = Shader::ALPHA;
		// Set Properties
		shaderList["transparent"]->Use();
		shaderList["transparent"]->setVector4("light.position", { 10.f, 10.f, 10.f, 1.f });
		shaderList["transparent"]->setVector3("light.color", { 1.0f, 1.0f, 1.0f });
		shaderList["transparent"]->setFloat("ambient_intensity", 0.2f);
		shaderList["transparent"]->setFloat("diffuse_intensity", 0.8f);


	}


}
