#include "Model.cpp"
#include "Loader.cpp"
#include "Renderer.cpp"
#include "DisplayAdapter.cpp"

class LavaEngine {
public:
	static void bootstrap() {
		DisplayAdapter* display = new DisplayAdapter();
		GLFWwindow* window = display->createWindow();
		float vertices[9] = {
			   -1.0f, -1.0f, 0.0f,
			   1.0f, -1.0f, 0.0f,
			   0.0f,  1.0f, 0.0f,
		};
		Loader* loader = new Loader();
		Model model = loader->loadModel(vertices, sizeof(vertices) / sizeof(vertices[0]));
		Renderer* renderer = new Renderer();

		while (!display->isWindowClosed())
		{
			renderer->prepare();
			renderer->render(&model);
			display->updateWindow();
		}

		display->destroyWindow();
	}
};