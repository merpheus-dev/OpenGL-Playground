#include "Model.cpp"
#include "Loader.cpp"
#include "Renderer.cpp"
#include "DisplayAdapter.cpp"
#include "VertexData.cpp"
#include "ShaderBank.cpp"
#include "MeshRendererData.cpp"
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
			   -.5f,  .5f, 0.0f,
			   -.5f,  -.5f, 0.0f,
			   .5f,  .5f, 0.0f,
			  .5f,  -.5f, 0.0f
		};

		int indices[6] = {
			0,1,2,
			1,3,2
		};

		float texCoords[8] = {
			0,0,
			0,1,
			1,1,
			1,0
		};
		Loader* loader = new Loader();
		Lava::VertexData* vertex_data = new Lava::VertexData(vertices, sizeof(vertices) / sizeof(vertices[0]));
		Lava::IndiceData* indice_data = new Lava::IndiceData(indices,sizeof(indices)/sizeof(indices[0]));
		Lava::TextureCoordinate* texture_coordinate = new Lava::TextureCoordinate(texCoords, sizeof(texCoords) / sizeof(texCoords[0]));
		
		Lava::Model model = loader->loadModel(*vertex_data,*texture_coordinate ,*indice_data);

		Lava::MeshRendererData rendererData = loader->loadRenderData(&model, "Assets/container.jpg");
		
		Renderer* renderer = new Renderer();
		ShaderBank* bank = new ShaderBank("vertexShader.vp", "fragmentShader.fp");
		bank->BindAttribute(0, "position");
		bank->BindAttribute(1, "textureCoords");

		//Lava::
		
		
		while (!display->isWindowClosed())
		{
			renderer->prepare();
			bank->Activate();
			renderer->render(&rendererData);
			bank->Deactivate();
			display->updateWindow();
		}
		bank->Dispose();
		display->destroyWindow();
	}
};