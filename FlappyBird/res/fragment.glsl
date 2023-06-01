#version 330 core

out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D tex_sampler;

void main()
{
	fragColor = texture(tex_sampler, texCoords);
}