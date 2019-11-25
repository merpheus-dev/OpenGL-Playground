namespace Lava
{
#ifndef MODEL_Obj
#define MODEL_Obj
	struct Model {
	public:
		int vaoId;
		int vertexCount;
		Model(int vertexAttributeId, int vertexCount)
		{
			this->vaoId = vertexAttributeId;
			this->vertexCount = vertexCount;
		}
	};
#endif
}