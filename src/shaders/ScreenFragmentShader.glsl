#version 420

in vec2 fTexCoord;

out vec4 out_Color;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main(void) {
	out_Color = uColor * texture(uTexture, fTexCoord);
}
