#version 420

in vec4 in_Position;
in vec2 in_TexCoord;

out vec2 fTexCoord;

void main(void) {
	gl_Position = in_Position;
	fTexCoord = in_TexCoord;
}
