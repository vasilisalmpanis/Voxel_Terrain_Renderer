#version 330 core
out vec4 FragColor;

in vec3 myColor;
in vec2 TexCoord;

uniform sampler2D boxTexture;
uniform sampler2D extraTexture;

void main()
{
    FragColor = mix(texture(boxTexture, TexCoord), 
                    texture(extraTexture, TexCoord),
                    0.2); // mixture of 2 textures
}