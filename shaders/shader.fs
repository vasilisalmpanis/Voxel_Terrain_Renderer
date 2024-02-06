#version 330 core
out vec4 FragColor;

in vec3 vertexPos;
uniform float uOffset;

void main()
{
    FragColor = vec4(vertexPos.x + uOffset, vertexPos.y, vertexPos.y, 1.0f);
}
