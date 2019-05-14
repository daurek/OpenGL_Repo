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
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);

		// Create camera
		camera = std::make_shared<Camera>(glm::vec3{0.f, 0.f, -10.f}, glm::vec3{ 0.f, 0.f, 0.f }, 2.f, GLfloat(width) / height, 1.f, 50.f);

		// Load models
		models["car"] = std::make_shared<Model>("../../../../assets/meshes/car.fbx");

        // Compile and Use Shader
		defaultShader = std::make_shared<Shader>("../../../../assets/shaders/vertex_shader.txt", "../../../../assets/shaders/fragment_shader.txt");
		defaultShader->Use();
		// Configure Shader Lighting
		defaultShader->setVector4("light.position",		{ 10.f, 10.f, 10.f, 1.f });
		defaultShader->setVector3("light.color",		{ 0.7f, 0.3f, 0.2f });
		defaultShader->setFloat("ambient_intensity", 0.2f );
		defaultShader->setFloat("diffuse_intensity", 0.8f );

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

		// Update Shader properties
		defaultShader->setMatrix4("model_view_matrix", camera->getView());
		defaultShader->setMatrix4("normal_matrix", glm::transpose(glm::inverse(camera->getView())));

    }

    void Scene::Render ()
    {
		// Clear buffer
        glClear (GL_COLOR_BUFFER_BIT);

        // Render every model
		for (auto & model : models)
			model.second->Render();
    }

    void Scene::Resize (int width, int height)
    {
		defaultShader->setMatrix4("projection_matrix", camera->getProjection());

        glViewport (0, 0, width, height);
    }


}
