#include <list>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>
#include "Engine/VertexData.cpp"

class Loader {
private:
	unsigned int vertexArrayObject;
	unsigned int vertexBuffer;
	unsigned int indicesBuffer;

	void initVertexAttribObjects() {
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);
	}

	void loadDataInObjects(int attributeNumber, float data[], int size) {
		vertexBuffer = 0;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
		//3 dimension vector for vertices, thats why we pass 3.
		glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind the buffer
	}
	void unbindArrayObject() {
		glBindVertexArray(0);
	}

	void bindIndices(int indices[], int indiceArraySize)
	{
		glGenBuffers(1, &indicesBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indiceArraySize, indices, GL_STATIC_DRAW);
	}

public:
	Model loadModel(Lava::VertexData vertexData,Lava::IndiceData indiceData) {
		initVertexAttribObjects();
		bindIndices(indiceData.indices, indiceData.size);
		loadDataInObjects(0, vertexData.positions, vertexData.size);
		unbindArrayObject();
		return Model(vertexArrayObject, indiceData.size);
	}
};