#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <math.h>



void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "Escape key pressed" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW we are using the CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
<<<<<<< HEAD

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "LearnOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
	
	// Error check if the window fails to create
=======
	GLFWwindow* window = glfwCreateWindow(800, 600, "Voxel Terrain Renderer", NULL, NULL);
>>>>>>> ded298412c1c0d8ecf34ef31a4887ddd099fa37a
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl; 
		glfwTerminate();
		return -1;
	}
<<<<<<< HEAD
=======
	glfwMakeContextCurrent(window);
	//gladLoadGL();
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	    while (!glfwWindowShouldClose(window)) {
		    processInput(window);
>>>>>>> ded298412c1c0d8ecf34ef31a4887ddd099fa37a

	while (!glfwWindowShouldClose(window)) {
	    processInput(window);
		// Specify the color of the background
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	}
}
