#version 120
uniform sampler2D atlas;

void main() {
	gl_FragColor = vec4(1.0, 1.0, 1.0, texture2D(atlas, gl_TexCoord[0].xy).r);
}