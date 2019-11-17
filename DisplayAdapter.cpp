#include <GL/glew.h>
#include <GLFW/glfw3.h>

class DisplayAdapter {
private:
	GLFWwindow* window;
public:
	GLFWwindow* createWindow() {
		if (!glfwInit())
			return nullptr;
		//return -1;

		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			//return -1;
		}

		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
			std::cout << "Error" << std::endl;

		std::cout << glGetString(GL_VERSION) << std::endl;
		return window;
	}

	void updateWindow() {
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	void destroyWindow() {
		glfwTerminate();
	}

	bool isWindowClosed() {
		return glfwWindowShouldClose(window);
	}

};