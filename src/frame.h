#ifndef __FRAME_H__
#define __FRAME_H__

#include <config.h>
#include <maths.h>

typedef struct Frame Frame;
struct Frame
{
	Frame* m_children;
	uint32 m_childrenCount;
	uint32* m_meshes;
	uint32 m_meshCount;
	Frame* parent;
	matrix4x4 transformation;
};

#endif