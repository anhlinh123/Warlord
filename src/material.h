#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <config.h>
#include <shader.h>
#include <hashtable.h>

typedef struct Material Material;

#define MaterialProperty(T)														\
	typedef struct																\
	{																			\
		char name[INTRINSIC_STRING_LENGTH];										\
		T value;																\
	} Property_##T;																\
																				\
Result Material_Get_##T(const Material* material, const char* name, T* value);	\
Result Material_Set_##T(const Material* material, const char* name, T* value);	\

#define Material_Get(type, material, name, value) Material_Get_##type(material, name, value);
#define Material_Set(type, material, name, value) Material_Set_##type(material, name, value);

MaterialProperty(float);
MaterialProperty(float3);
MaterialProperty(float4);
MaterialProperty(matrix3x3);
MaterialProperty(matrix4x4);

#endif