#include <material.h>

struct Material
{
	table floats;
	table float3s;
	table float4s;
	table matrix3x3s;
	table matrix4x4s;
	Shader* shader;
};

#define Material_GetSet(T)														\
Result Material_Get_##T(const Material* material, const char* name, T* value)	\
{																				\
	Property_##T* prop = table_search(material->T##s, name);					\
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
	if (value != NULL)															\
	{																			\
		Property_##T* prop = table_search(material->floats, name);				\
		if (prop == NULL)														\
		{																		\
			prop = (Property_##T*)malloc(sizeof(Property_##T));					\
			strcpy(prop->name, name);											\
			table_insert(material->T##s, prop);									\
		}																		\
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