#include "Model.cpp"
#include "VertexData.cpp"
namespace Lava
{
#ifndef RenderData_Obj
#define RenderData_Obj
	struct MeshRendererData
	{
	public:
		Model* mesh;
		TextureData* texture;
		MeshRendererData(Model* mesh, TextureData* texture)
		{
			this->mesh = mesh;
			this->texture = texture;
		}
	};
#endif
}