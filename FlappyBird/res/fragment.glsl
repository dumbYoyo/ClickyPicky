#version 330 core

out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D tex_sampler;

vec4 color;

void main()
{
	color = texture(tex_sampler, texCoords);
	if (color.a < 0.1)
		discard;
	fragColor = color;
}