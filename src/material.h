#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <config.h>
#include <uthash.h>
#include <shader.h>

typedef struct MaterialProperty
{
	char key[INTRINSIC_STRING_LENGTH];
	char* value;
	uint32 valueLength;	
	UT_hash_handle hh;
} MaterialProperty;

typedef struct Material
{
	MaterialProperty* properties;
	Shader* shader;
} Material;

Result GetMaterialProperty(const Material* material, const char* key, Generic out);
Result SetMaterialProperty(const Material* material, const char* key, Generic value);

#endif