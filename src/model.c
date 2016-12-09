#include <model.h>
#include <mesh.h>
#include <material.h>

typedef struct Frame Frame;
struct Frame
{
	Frame* children;
	uint32 childrenCount;
	uint32* meshes;
	uint32 meshCount;
	Frame* parent;
	matrix4x4 transformation;
};

struct Model
{
	Material* materials;
	uint32 materialCount;
	Mesh* meshes;
	uint32 meshCount;
	Frame* rootFrame;
};

Model* Model_Create(const char* name)
{

}

void Model_Destroy(Model* model)
{

}

void Model_Draw(Model* model)
{

}

void Frame_Draw(const Model* model, const Frame* frame, const matrix4x4* transform)
{
	matrix4x4 transformation = frame->transformation;// *transform;
	for (int i = 0; i < frame->childrenCount; i++)
	{
		Frame_Draw(&frame->children[i], &transformation);
	}

	for (int i = 0; i < frame->meshCount; i++)
	{
	}
}