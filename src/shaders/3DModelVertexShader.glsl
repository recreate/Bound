#version 420

in vec4 in_Position;
in vec3 in_Normals;
in vec2 in_TexCoord;

out vec2 fTexCoord;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main(void) {
	gl_Position = uProjectionMatrix * uViewMatrix * uModelMatrix * in_Position;
	fTexCoord = in_TexCoord;
}
