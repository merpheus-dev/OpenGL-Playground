#include <array>
namespace Lava
{
#ifndef VertexData_Obj
#define VertexData_Obj
	struct VertexData
	{
	public:
		float* positions;
		int size;
		VertexData(float* vertices,int size)
		{
			positions = vertices;
			this->size = size;
		}
	};
#endif

#ifndef IndiceData_Obj
#define IndiceData_Obj
	struct IndiceData
	{
	public:
		int* indices;
		int size;
		IndiceData(int* indices,int size)
		{
			this->indices = indices;
			this->size = size;
		}
	};
#endif
}