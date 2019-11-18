#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Renderer {
public:
	void prepare() {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void render(Model* model) {
		glBindVertexArray(model->vaoId); //bind current vao to opengl state machine
		glEnableVertexAttribArray(0);
		glDrawElements(GL_TRIANGLES, model->vertexCount, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, model->vertexCount);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0); //unbind vao since we are done with it
	}
};