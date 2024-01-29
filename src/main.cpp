#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <math.h>

std::string readShader(std::string file_name)
{
	std::ifstream shader_file;
	shader_file.open(file_name);
	if (!shader_file.is_open() && !shader_file.good())
	{
		std::cout << "Failed to open file: " << file_name << std::endl;
		return NULL;
	}
	std::stringstream shader_code;
	shader_code << shader_file.rdbuf();
	return shader_code.str();
}

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


GLuint createShader(const char *shaderSource, GLenum shaderType)
{

	GLuint shader = glCreateShader(shaderType);
	// Attach the vertex shader source code to the vertex shader object
	glShaderSource(shader, 1, &shaderSource, NULL);
	// Compile the vertex shader into machine code
	glCompileShader(shader);
	int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
	return (shader);
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
	std::string vertexShaderSource = readShader("../shaders/default.vert");
	std::string fragmentShaderSource = readShader("../shaders/default.frag");
	std::string fragmentShaderSource2 = readShader("../shaders/second.frag");
	std::cout << vertexShaderSource;
	std::cout << fragmentShaderSource;
	if (vertexShaderSource.empty() || fragmentShaderSource.empty())
	{
		std::cout << "Failed to read shader files" << std::endl;
		return 1;
	}

	// Create and compile the vertex shader and get its reference
	GLuint vertexShader = createShader(vertexShaderSource.c_str(), GL_VERTEX_SHADER);

	// Create fragment shader object and get its reference
	GLuint fragmentShader[2];
	fragmentShader[0] = createShader(fragmentShaderSource.c_str(), GL_FRAGMENT_SHADER);
	fragmentShader[1] = createShader(fragmentShaderSource2.c_str(), GL_FRAGMENT_SHADER);
	// Create shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	GLuint shaderProgram2 = glCreateProgram();
	// Attach vertex and fragment shader to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader[0]);
	// Wrap-up/Link all the shaders together into the shader program
	glLinkProgram(shaderProgram);

	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader[1]);
	glLinkProgram(shaderProgram2);


	// Delete the vertex and fragment shaders once linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader[0]);
	glDeleteShader(fragmentShader[1]);

	GLfloat triangle1[] =
	{
		-0.5f, 0.5f, 0.0f, // Lower left corner
		0.0f, -0.5f, 0.0f, // Lower right corner
		-1.0f, -0.5f, 0.0f,
	};

	GLfloat triangle2[] = 
	{
		0.5f , 0.5f, 0.0f, // Upper corner
		1.0f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 *sizeof(float), (void *)0);

	// Enable the vertex attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);
	
	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// SECOND PAIR OF VAO AND VBO
	GLuint VAO2, VBO2;

	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
	glEnableVertexAttribArray(0);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Tell glfw that we want to reset the viewport every time a user resizes the window
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window)) {
	    	processInput(window);
		// Specify the color of the background
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram2);
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO1);
		// Draw the triangle using the GL_TRIANGLES primitive
		// glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram);
		vertexColorLocation = glGetUniformLocation(shaderProgram, "myColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO1);
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram2);
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	
	return (EXIT_SUCCESS);

}
