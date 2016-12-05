#include <material.h>

#define Material_GetSet(T)														\
Result Material_Get_##T(const Material* material, const char* name, T* value)	\
{																				\
	Property_##T* prop = NULL;													\
	HASH_FIND_STR(material->T##s, name, prop);									\
	if (prop != NULL && value != NULL)											\
	{																			\
		*value = prop->value;													\
		return Result_SUCCESS;													\
	}																			\
	return Result_FAILURE;														\
}																				\
																				\
Result Material_Set_##T(const Material* material, const char* name, T* value)	\
{																				\
	Property_##T* prop = NULL;													\
	HASH_FIND_STR(material->T##s, name, prop);									\
	if (prop != NULL && value != NULL)											\
	{																			\
		prop->value = *value;													\
		return Result_SUCCESS;													\
	}																			\
	return Result_FAILURE;														\
}																				\

Material_GetSet(float);
Material_GetSet(float3);
Material_GetSet(float4);
Material_GetSet(matrix3x3);
Material_GetSet(matrix4x4);