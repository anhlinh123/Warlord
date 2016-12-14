#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "config.h"
#include "maths.h"
#include "shader.h"
#include "texture.h"

typedef struct Material Material;

Material* Material_Create();
void Material_Destroy(Material* material);

void Material_Apply(Material* material);

Result Material_Get_Float(const Material* material, const char* name, float* value);
Result Material_Get_Float3(const Material* material, const char* name, float3* value);
Result Material_Get_Float4(const Material* material, const char* name, float4* value);
Result Material_Get_Matrix3x3(const Material* material, const char* name, matrix3x3* value);
Result Material_Get_Matrix4x4(const Material* material, const char* name, matrix4x4* value);
Result Material_Get_Texture(const Material* material, const char* name, Texture** value);
Shader* Material_Get_Shader(const Material* material);

Result Material_Set_Float(Material* material, const char* name, float* value);
Result Material_Set_Float3(Material* material, const char* name, float3* value);
Result Material_Set_Float4(Material* material, const char* name, float4* value);
Result Material_Set_Matrix3x3(Material* material, const char* name, matrix3x3* value);
Result Material_Set_Matrix4x4(Material* material, const char* name, matrix4x4* value);
Result Material_Set_Texture(const Material* material, const char* name, Texture** value);
void Material_Set_Shader(Material* material, Shader* shader);

#endif