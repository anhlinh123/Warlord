#ifndef __MODEL_H__
#define __MODEL_H__

#include <config.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <chunk.h>

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