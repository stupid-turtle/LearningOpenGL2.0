#version 330 core

in vec3 LightColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(LightColor, 1.0);
}