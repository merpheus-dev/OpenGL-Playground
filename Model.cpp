struct Model {
public:
	int vaoId;
	int vertexCount;
	Model(int vertexAttributeId,int vertexCount)
	{
		this->vaoId = vertexAttributeId;
		this->vertexCount = vertexCount;
	}
};