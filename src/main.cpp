# include <includes/Texture.hpp>
# include <math.h>

/*
  Function: readShader
  Args:		std::string fileName
  Opens and reads the whole file into a string object
  Return: 	String or Null
*/

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "Escape key pressed" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}


void frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "LearnOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
	
	// Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl; 
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	
	if (!gladLoadGL())
	{
		std::cout << "failed";
		return 1;
	}
	
	// Specify the viewport of OpenGL in the window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Create shader program from files
	// Shader firstProgram("../shaders/default.vert", "../shaders/boxshader.frag");
	Shader secondProgram("../shaders/boxshader.vert", "../shaders/boxshader.frag");
	Texture texture1("../textures/wood.jpg", GL_RGB);
	Texture texture2("../textures/shrek.png", GL_RGBA);
	Texture texture3("../textures/awesomeface.png", GL_RGBA);




    float triangle1[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	GLuint indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	
	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VBO1, VAO1, EBO;

	// Generate VAO before VBO
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);
	// glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO1);
	
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);

	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// stream means modiefied once and used many times
	// static means modiefied once and used many many times
	// dynamic means modiefied multiple times and used many many times

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 *sizeof(float), (void *)0);
	// Enable the vertex attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// SECOND PAIR OF VAO AND VBO
	// GLuint VAO2, VBO2;

	// glGenVertexArrays(1, &VAO2);
	// glBindVertexArray(VAO2);
	// glGenBuffers(1, &VBO2);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 *sizeof(float), (void *)0);
	// // Enable the vertex attribute so that OpenGL knows to use it
	// glEnableVertexAttribArray(0);

	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Tell glfw that we want to reset the viewport every time a user resizes the window
	// texture2.bind(1);
	glUseProgram(secondProgram.getID());
    secondProgram.setInt("texture1", 0);
    secondProgram.setInt("texture2", 1);
	// secondProgram.setInt("extraTexture", 1);
	// secondProgram.setInt("boxTexture", 0);
	// secondProgram.setInt("extraTexture", 1);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	int i = 0;
	while (!glfwWindowShouldClose(window)) 
	{
		// Input
	    processInput(window);

		// Specify the color of the background
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// View matrix
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
		// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		// Projection matrix
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(100.0f), 800.0f / 800.0f, 0.1f, 100.0f);

		// Bind textures
		texture1.bind(0);


		// Use the shader program
		secondProgram.use();

		// Bind the VAO
		glBindVertexArray(VAO1);

		// Set uniforms
		secondProgram.setMatrix4fv("view", view);
		secondProgram.setMatrix4fv("projection", projection);

		secondProgram.setFloat("rate", sin(glfwGetTime()));
		for (int i = 0; i < 10; i++)
		{
			if (i % 4)
				texture2.bind(1);
			else
				texture3.bind(1);
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;

			if (i % 3 || i == 0)
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians((10.0f * (1.4f + (float)i))), glm::vec3(1.0f, 0.3f, 0.5f));
			else
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			secondProgram.setMatrix4fv("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &EBO);
	// firstProgram.del();
	secondProgram.del();
	texture1.del();
	// texture2.del();
	glfwDestroyWindow(window);
	// // Terminate GLFW before ending the program
	glfwTerminate();
	
	return (EXIT_SUCCESS);

}
