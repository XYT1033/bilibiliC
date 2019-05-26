
   https://learnopengl.com/ 
glfw download ：   https://www.glfw.org/
glew download ：       http://glew.sourceforge.net/
   
   
   
#include <iostream>

#define GLEW_STATIC 
#include <GL/glew.h>
#include<GLFW/glfw3.h>
#include<GLFW/glfw3.h>

int main() {
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR,3);


	system("pause");
}

	
-- 
#include <iostream>

#define GLEW_STATIC 
#include <GL/glew.h>
#include<GLFW/glfw3.h>


int main() {
	glfwInit();
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 400, "xyt", NULL, NULL);

	if (window ==NULL )
	{
		std::cout << "failed " << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit()!=GLEW_OK)
	{
		std::cout << "glew init failed." << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glViewport(0,0,800,600);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0,0,0,1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	system("pause");
}



 
   
	 
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	