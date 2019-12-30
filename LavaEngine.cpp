#include "Model.cpp"
#include "Loader.cpp"
#include "Renderer.cpp"
#include "DisplayAdapter.cpp"
#include "VertexData.cpp"
#include "ShaderBank.cpp"
#include "MeshRendererData.cpp"
#include "MathManager.cpp"
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
			   .5f,  -.5f, 0.0f,
			  .5f,  .5f, 0.0f
		};

		int indices[6] = {
			0,1,3,
			3,1,2
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

		Lava::MeshRendererData rendererData = loader->loadRenderData(&model, "Assets/e.jpg");
		
		Renderer* renderer = new Renderer();
		ShaderBank* bank = new ShaderBank("vertexShader.vp", "fragmentShader.fp");
		bank->BindAttribute(0, "position");
		bank->BindAttribute(1, "textureCoords");
		bank->Prepare();
		bank->GetAllUniformLocations();
		//Lava::
		
		glm::vec3 position = glm::vec3(0);
		glm::vec3 rotation = glm::vec3(0);
		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		while (!display->isWindowClosed())
		{
			if (glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
			{
				position[0] -= 0.001f;
			}
			else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
				position[0] += 0.001f;
			}

			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				position[2] += 0.001f;
			}
			else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
				position[2] -= 0.001f;
			}

			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			{
				rotation[1] += 0.01f;
			}
			else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				rotation[1] -= 0.01f;
			}

			renderer->prepare();
			bank->Activate();
			modelMatrix = math_manager::CreateTRSMatrix(position,rotation, glm::vec3(1));
			projectionMatrix = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 1000.0f);
			viewMatrix = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			bank->LoadTRSToBuffer(modelMatrix);
			bank->LoadMVPToBuffer(modelMatrix, viewMatrix, projectionMatrix);
			renderer->render(&rendererData);
			bank->Deactivate();
			display->updateWindow();
		}
		bank->Dispose();
		display->destroyWindow();
	}
};