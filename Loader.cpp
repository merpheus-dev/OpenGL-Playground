#include <list>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>

class Loader {
private:
	unsigned int vertexArrayObject;
	unsigned int vertexBuffer;
	
	void initVertexAttribObjects() {
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);
	}
	
	void loadDataInObjects(int attributeNumber,float data[],int size) {
		vertexBuffer = 0;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size*sizeof(float), data, GL_STATIC_DRAW);
		//3 dimension vector for vertices, thats why we pass 3.
		glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind the buffer
	}
	void unbindArrayObject() {
		glBindVertexArray(0);
	}

public:
	Model loadModel(float positions[],int size) {
		initVertexAttribObjects();
		loadDataInObjects(0, positions,size);
		unbindArrayObject();
		return Model(vertexArrayObject, size/3);
	}
};