
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on may of 2014                                            *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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
    :
        angle(0)
    {
        // Basic OpenGL Config:
        glEnable	 (GL_CULL_FACE);
        glClearColor (0.1f, 0.1f, 0.1f, 1.f);

		// Create camera
		camera = std::make_shared<Camera>(2.f, GLfloat(width) / height, 1.f, 50.f);

		// Load models
		models["car"] = std::make_shared<Model>("../../../../assets/meshes/car.fbx");

        // Compile and Use Shader
		defaultShader = std::make_shared<Shader>("../../../../assets/shaders/vertex_shader.txt", "../../../../assets/shaders/fragment_shader.txt");
		defaultShader->Use();
		// Configure Shader
		defaultShader->setVector4("light.position",		{ 10.f, 10.f, 10.f, 1.f });
		defaultShader->setVector3("light.color",		{ 0.7f, 0.3f, 0.2f });
		defaultShader->setFloat("ambient_intensity", 0.2f );
		defaultShader->setFloat("diffuse_intensity", 0.8f );

        Resize (width, height);
    }

    void Scene::Update ()
    {
        angle += 0.5f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			cameraPos += 0.01f * glm::vec3{0, 0, 1};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			cameraPos -= 0.01f * cameraFront;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.01f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * 0.01f;

		// Update Shader properties
		glm::mat4 model_view_matrix;

		model_view_matrix = glm::translate(model_view_matrix, glm::vec3(0.f, 0.f, -10.f) + cameraPos);
		model_view_matrix = glm::rotate(model_view_matrix, angle, glm::vec3(0.f, 2.f, 0.f));
		model_view_matrix = glm::scale(model_view_matrix, glm::vec3(0.001f, 0.001f, 0.001f));

		defaultShader->setMatrix4("model_view_matrix", model_view_matrix);
		defaultShader->setMatrix4("normal_matrix", glm::transpose(glm::inverse(model_view_matrix)));

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
		defaultShader->setMatrix4("projection_matrix", camera->GetProjection());

        glViewport (0, 0, width, height);
    }


}
