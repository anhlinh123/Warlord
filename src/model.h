#ifndef __MODEL_H__
#define __MODEL_H__

#include <config.h>
#include <mesh.h>
#include <frame.h>
#include <material.h>

typedef struct Model
{
	Material* materials;
	uint32 materialCount;
	Mesh* meshes;
	uint32 meshCount;
	Frame* rootFrame;
} Model;

#endif