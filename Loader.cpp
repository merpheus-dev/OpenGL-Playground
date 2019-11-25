#include <list>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <iostream>
#include "Engine/VertexData.cpp"
#include "Engine/MeshRendererData.cpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
class Loader {
private:
	unsigned int vertexArrayObject;
	unsigned int vertexBuffer;
	unsigned int indicesBuffer;
	unsigned int texture;

	void initVertexAttribObjects() {
		glGenVertexArrays(1, &vertexArrayObject);
		glBindVertexArray(vertexArrayObject);
	}

	void loadDataInObjects(int attributeNumber, int vectorDimensions, float data[], int size) {
		vertexBuffer = 0; //empty vbo
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
		glVertexAttribPointer(attributeNumber, vectorDimensions, GL_FLOAT, GL_FALSE, 0, (void*)0);
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

	Lava::TextureData loadTexture(std::string fileName)
	{
		const char* file = fileName.c_str();
		Lava::TextureData textureData = Lava::TextureData();
		textureData.data = stbi_load(file,
			&textureData.width, &textureData.height, &textureData.normalChannelCount, 0);
		if (textureData.data)
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0,
				GL_RGB, GL_UNSIGNED_BYTE, textureData.data);

			glGenerateMipmap(GL_TEXTURE_2D);
			textureData.textureId = texture;
		}
		else
		{
			std::cout << "Failed to load" + fileName << std::endl;
		}
		stbi_image_free(textureData.data);
		return textureData;
	}

public:
	Lava::Model loadModel(Lava::VertexData vertexData,Lava::TextureCoordinate texCoord, Lava::IndiceData indiceData) {
		initVertexAttribObjects();
		bindIndices(indiceData.indices, indiceData.size);
		loadDataInObjects(0, 3, vertexData.positions, vertexData.size);
		loadDataInObjects(1, 2, texCoord.coords, texCoord.size);
		unbindArrayObject();
		return Lava::Model(vertexArrayObject, indiceData.size);
	}

	Lava::MeshRendererData loadRenderData(Lava::Model* model,std::string mainTexturePath)
	{
		Lava::TextureData texDat = loadTexture(mainTexturePath);
		
		return Lava::MeshRendererData(model, &texDat);
	}
};