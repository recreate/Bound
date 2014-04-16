#version 420

in vec2 fTexCoord;

out vec4 out_Color;

uniform vec3 uAmbientProduct;
uniform vec3 uDiffuseProduct;
uniform vec3 uSpecularProduct;
uniform float uSpecularHighlight;

uniform sampler2D uTexture;

void main(void) {
	out_Color = vec4(1.0, 1.0, 1.0, 1.0) * texture(uTexture, fTexCoord);
}
