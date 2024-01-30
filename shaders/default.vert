#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 myColor;
void main()
{
   gl_Position = 1 * vec4(-aPos.x, -aPos.y, aPos.z, 1.0);
   myColor = aColor;
}