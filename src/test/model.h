#ifndef __MODEL_H__
#define __MODEL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <core/config.h>
#include <core/chunk.h>

#ifdef __cplusplus
}
#endif


class Model
{
public:
	Model(const char* fileName);
	~Model();

	void Draw();

private:
	Chunk* m_chunk;
};

#endif