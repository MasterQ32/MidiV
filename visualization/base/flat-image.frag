#version 330

in vec2 fUV;

out vec4 fragment;

uniform sampler2D rFlatImage;

uniform ivec2 uScreenSize;

uniform float uStretch = 0.0;
uniform float uTile = 0.0;
uniform float uFlipped = 0.0;

void main()
{
	vec2 xy = 2.0 * fUV - 1.0;
	float aspect = float(uScreenSize.x) / float(uScreenSize.y);
	if(aspect >= 1.0)
	{
		xy.x *= aspect;
	}
	else
	{
		xy.y /= aspect;
	}

	vec2 uv = 0.5 + 0.5 * xy;

	uv = mix(uv, fUV, uStretch);

	uv = mix(uv, vec2(uv.x, 1.0 - uv.y), uFlipped);

	fragment = texture(rFlatImage, uv);
}
