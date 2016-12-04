#include <material.h>

Result GetMaterialProperty(const Material* material, const char* key, Generic out)
{
	MaterialProperty* property = NULL;
	HASH_FIND_STR(material->properties, key, property);
	if (property != NULL)
	{
		if (property->valueLength < out.size) {
			return Result_FAILURE;
		}
		memcpy(out.data, property->value, out.size);
		return Result_SUCCESS;
	}
	return Result_FAILURE;
}

Result SetMaterialProperty(const Material* material, const char* key, Generic value)
{
	MaterialProperty* property = NULL;
	HASH_FIND_STR(material->properties, key, property);
	if (property != NULL)
	{
		if (property->valueLength < value.size) {
			return Result_FAILURE;
		}
		memcpy(property->value, value.data, value.size);
		return Result_SUCCESS;
	}
	return Result_FAILURE;
}