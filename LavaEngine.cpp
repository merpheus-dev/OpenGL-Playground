#include "Model.cpp"
#include "Loader.cpp"
#include "Renderer.cpp"
#include "DisplayAdapter.cpp"
#include "VertexData.cpp"
class LavaEngine {
public:
	static void bootstrap() {
		DisplayAdapter* display = new DisplayAdapter();
		GLFWwindow* window = display->createWindow();
		float vertices[12] = {
			//bottom right triangle of quad
			   //-1.0f, -1.0f, 0.0f,
			   //1.0f, -1.0f, 0.0f,
			   //1.0f,  1.0f, 0.0f,
			//top left triangle of quad
			   -1.0f,  1.0f, 0.0f,
			   -1.f,  -1.f, 0.0f,
			   1.f,  1.f, 0.0f,
			   1.f,  -1.f, 0.0f
		};

		int indices[3] = {
			//0,1,2,
			1,3,2
		};
		Loader* loader = new Loader();
		Lava::VertexData* vertex_data = new Lava::VertexData(vertices, sizeof(vertices) / sizeof(vertices[0]));
		Lava::IndiceData* indice_data = new Lava::IndiceData(indices,sizeof(indices)/sizeof(indices[0]));
		Model model = loader->loadModel(*vertex_data,*indice_data);
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