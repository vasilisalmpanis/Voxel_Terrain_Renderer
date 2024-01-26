#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <iostream>
#include <GLFW/glfw3.h>



void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "Escape key pressed" << std::endl;
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Voxel Terrain Renderer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl; 
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//gladLoadGL();
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);
	    while (!glfwWindowShouldClose(window)) {
		    processInput(window);

		    glClear(GL_COLOR_BUFFER_BIT);

		    // Render your scene here

		    glfwSwapBuffers(window);
		    glfwPollEvents();
	    }
	glfwDestroyWindow(window);
	glfwTerminate();
	return (EXIT_SUCCESS);
}
