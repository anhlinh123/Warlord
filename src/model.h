#ifndef __MODEL_H__
#define __MODEL_H__

#include <config.h>

typedef struct Model Model;

Model* Model_Create(const char* name);
void Model_Destroy(Model* model);
void Model_Draw(Model* model);

#endif