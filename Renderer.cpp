#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "MeshRendererData.cpp"
class Renderer {
public:
	void prepare() {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void render(Lava::MeshRendererData* renderData) {
		glBindVertexArray(renderData->mesh->vaoId); //bind current vao to opengl state machine
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderData->texture->textureId);
		glDrawElements(GL_TRIANGLES, renderData->mesh->vertexCount, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindVertexArray(0); //unbind vao since we are done with it
	}
};