#version 420

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
out vec4 fColor;

void main(void) {
	gl_Position = in_Position;
	fColor = in_Color;
}
