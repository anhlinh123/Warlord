#include "material.h"
#include "khash.h"
#include <opengl/glad.h>

KHASH_MAP_INIT_STR(float, float)
KHASH_MAP_INIT_STR(float3, float3)
KHASH_MAP_INIT_STR(float4, float4)
KHASH_MAP_INIT_STR(matrix3x3, matrix3x3)
KHASH_MAP_INIT_STR(matrix4x4, matrix4x4)

struct Material
{
	khash_t(float)* floats;
	khash_t(float3)* float3s;
	khash_t(float4)* float4s;
	khash_t(matrix3x3)* matrix3x3s;
	khash_t(matrix4x4)* matrix4x4s;
	Shader* shader;
};

Material* Material_Create()
{
	Material* material = (Material*)malloc(sizeof(Material));
	material->floats = kh_init(float);
	material->float3s = kh_init(float3);
	material->float4s = kh_init(float4);
	material->matrix3x3s = kh_init(matrix3x3);
	material->matrix4x4s = kh_init(matrix4x4);
	material->shader = NULL;
	return material;
}

void Material_Destroy(Material* material)
{
	kh_destroy(float, material->floats);
	kh_destroy(float3, material->float3s);
	kh_destroy(float4, material->float4s);
	kh_destroy(matrix3x3, material->matrix3x3s);
	kh_destroy(matrix4x4, material->matrix4x4s);
	free(material);
}

void Material_Apply(Material* material)
{
	Shader* shader = material->shader;
	const char* name = NULL;
	float floatvalue;
	kh_foreach(material->floats, name, floatvalue,
		GLint location = Shader_GetLocation(shader, name);
		if (location != -1)
		{
			glUniform1f(location, floatvalue);
		}
	);

	float3 float3value;
	kh_foreach(material->float3s, name, float3value,
		GLint location = Shader_GetLocation(shader, name);
		if (location != -1)
		{
			glUniform3f(location, float3value.x, float3value.y, float3value.z);
		}
	);

	float4 float4value;
	kh_foreach(material->float4s, name, float4value,
		GLint location = Shader_GetLocation(shader, name);
		if (location != -1)
		{
			glUniform4f(location, float4value.x, float4value.y, float4value.z, float4value.w);
		}
	);

	matrix3x3 matrix3x3value;
	kh_foreach(material->matrix3x3s, name, matrix3x3value,
		GLint location = Shader_GetLocation(shader, name);
		if (location != -1)
		{
			glUniformMatrix3fv(location, 1, GL_FALSE, (GLfloat*)matrix3x3value.data);
		}
	);

	matrix4x4 matrix4x4value;
	kh_foreach(material->matrix4x4s, name, matrix4x4value,
		GLint location = Shader_GetLocation(shader, name);
		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)matrix4x4value.data);
		}
	);
}

Result Material_Get_Float(const Material* material, const char* name, float* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(float, material->floats, name);
		if (k != kh_end(material->floats))
		{
			*value = kh_value(material->floats, k);
			return Result_SUCCESS;
		}
	}
	return Result_FAILURE;
}

Result Material_Get_Float3(const Material* material, const char* name, float3* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(float3, material->float3s, name);
		if (k != kh_end(material->float3s))
		{
			*value = kh_value(material->float3s, k);
			return Result_SUCCESS;
		}
	}
	return Result_FAILURE;
}

Result Material_Get_Float4(const Material* material, const char* name, float4* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(float4, material->float4s, name);
		if (k != kh_end(material->float4s))
		{
			*value = kh_value(material->float4s, k);
			return Result_SUCCESS;
		}
	}
	return Result_FAILURE;
}

Result Material_Get_Matrix3x3(const Material* material, const char* name, matrix3x3* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(matrix3x3, material->matrix3x3s, name);
		if (k != kh_end(material->matrix3x3s))
		{
			*value = kh_value(material->matrix3x3s, k);
			return Result_SUCCESS;
		}
	}
	return Result_FAILURE;
}

Result Material_Get_Matrix4x4(const Material* material, const char* name, matrix4x4* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(matrix4x4, material->matrix4x4s, name);
		if (k != kh_end(material->matrix4x4s))
		{
			*value = kh_value(material->matrix4x4s, k);
			return Result_SUCCESS;
		}
	}
	return Result_FAILURE;
}

Result Material_Set_Float(Material* material, const char* name, float* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(float, material->floats, name);
		if (k == kh_end(material->floats))
		{
			int ret;
			k = kh_put(float, material->floats, name, &ret);
			if (ret != 0)
				return Result_FAILURE;
		}
		kh_value(material->floats, k) = *value;
		return Result_SUCCESS;
	}
	return Result_FAILURE;
}

Result Material_Set_Float3(Material* material, const char* name, float3* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(float3, material->float3s, name);
		if (k == kh_end(material->float3s))
		{
			int ret;
			k = kh_put(float3, material->float3s, name, &ret);
			if (ret != 0)
				return Result_FAILURE;
		}
		kh_value(material->float3s, k) = *value;
		return Result_SUCCESS;
	}
	return Result_FAILURE;
}

Result Material_Set_Float4(Material* material, const char* name, float4* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(float4, material->float4s, name);
		if (k == kh_end(material->float4s))
		{
			int ret;
			k = kh_put(float4, material->float4s, name, &ret);
			if (ret != 0)
				return Result_FAILURE;
		}
		kh_value(material->float4s, k) = *value;
		return Result_SUCCESS;
	}
	return Result_FAILURE;
}

Result Material_Set_Matrix3x3(Material* material, const char* name, matrix3x3* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(matrix3x3, material->matrix3x3s, name);
		if (k == kh_end(material->matrix3x3s))
		{
			int ret;
			k = kh_put(matrix3x3, material->matrix3x3s, name, &ret);
			if (ret != 0)
				return Result_FAILURE;
		}
		kh_value(material->matrix3x3s, k) = *value;
		return Result_SUCCESS;
	}
	return Result_FAILURE;
}

Result Material_Set_Matrix4x4(Material* material, const char* name, matrix4x4* value)
{
	if (value != NULL)
	{
		khiter_t k = kh_get(matrix4x4, material->matrix4x4s, name);
		if (k == kh_end(material->matrix4x4s))
		{
			int ret;
			k = kh_put(matrix4x4, material->matrix4x4s, name, &ret);
			if (ret != 0)
				return Result_FAILURE;
		}
		kh_value(material->matrix4x4s, k) = *value;
		return Result_SUCCESS;
	}
	return Result_FAILURE;
}

Shader* Material_Get_Shader(const Material* material)
{
	return material->shader;
}

void Material_Set_Shader(Material* material, Shader* shader)
{
	material->shader = shader;
}
