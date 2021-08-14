#include <iostream>
#include <glad/glad.h>

#include "Blaze.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



#define WINDOW_H 600.0f 
#define WINDOW_W 800.0f

int main()
{
	Window* win = new Window(WINDOW_W, WINDOW_H, "BlazeRenderer", false, true, 3, 3);

	gladLoadGL();
	
	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int indices[] = {
		0, 1, 2, //Front face
		2, 3, 0,

		0, 4, 5, //TOP
		5, 1, 0,
		        
		0, 4, 7, //LEFT
		7, 3, 0,
		
		6, 2, 1, //Right
		1, 5, 6,

		6, 2, 3, //Bottom
		3, 7, 6,

		6, 7, 4, //Back
		4, 5, 6
	};

	//Shaders

	
	Shader shader("res/shaders/phongVertex.glsl", "res/shaders/phongFragmentBasic.glsl");
	Shader lampShader("res/shaders/lampShader.shader");

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.3f, 0.3f, 0.1f));

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat4 proj = glm::perspective(glm::radians(51.0f), (float)WINDOW_W / (float) WINDOW_H, 0.1f, 160.0f);

	//Set transformation
	shader.Bind();
	shader.SetUniformMatrix4f("transform.projection", proj);
	shader.SetUniformMatrix4f("transform.view", view);
	shader.SetUniformMatrix4f("transform.model", model);

	//Lighting
	shader.SetUniform3f("objectColor", 0.3f, 0.4f, 0.3f);
	shader.SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
	
	//LightLamp
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	lampShader.Bind();
	lampShader.SetUniformMatrix4f("transform.projection", proj);
	lampShader.SetUniformMatrix4f("transform.view", view);
	lampShader.SetUniformMatrix4f("transform.model", model);

	//Vertex Arrays
	VertexArray vertexArray;
	vertexArray.Bind();

	//Set buffer
	VertexBuffer vertexBuffer(vertices, sizeof(vertices));

	//Set layout
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	


	//Textures
	Texture texture("res/textures/container2.png");
	texture.Bind(0);


	//Index Buffer
	ElementBuffer elementBuffer(indices, 6 * 6);
	
	//Add buffer with layout
	vertexArray.AddBuffer(vertexBuffer, layout);


	//Add element buffer
	vertexArray.AddElementBuffer(elementBuffer);

	


	Renderer renderer;
	
	
	//renderer.SetDrawMode(DrawMode::WIRE_TWO_SIDED);
	

	while (!win->isClosing())
	{
		renderer.ClearWithColor(0.3f, 0.3, 0.4f, 1.0f);

		//shader.Bind();
		//shader.SetUniform4f("aColor", 0.1f, std::sin(glfwGetTime()), 0.4f, 1.0f);

		//lampShader.Bind();

		win->ProcessInput();

		view = win->camera.GetViewMatrix();


		// Draw the light
		glm::mat4 lampModel = glm::mat4(1.0f);
		lampModel = glm::translate(lampModel, lightPos);
		lampModel = glm::scale(lampModel, glm::vec3(0.2f));
		lampShader.Bind();
		lampShader.SetUniformMatrix4f("transform.model", lampModel);
		lampShader.SetUniformMatrix4f("transform.view", view);

		renderer.Draw(vertexArray, lampShader, 36);

		//Draw the box

		float angle = std::sin(glfwGetTime());
		model = glm::rotate(model, glm::radians(0.1f * angle), glm::vec3(0.1f, 1.2f, 0.3f));

		shader.Bind();
		shader.SetUniformMatrix4f("transform.model", model);
		shader.SetUniformMatrix4f("transform.view", view);
		

		shader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

		renderer.Draw(vertexArray, shader, 36);




		


		win->PollEvents();
		win->SwapBuffers();
	}

	//CLEAN UP
	delete win;
}

