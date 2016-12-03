#version 300 es
in vec3 aPosition;
in vec4 aColor;
out vec4 color;
void main()
{
vec4 posL = vec4(aPosition, 1.0);
color = aColor;
gl_Position = posL;
}