#version 120
uniform sampler2D atlas;

void main() {
	gl_FragColor = vec4(gl_Color.r, gl_Color.g, gl_Color.b, gl_Color.a * texture2D(atlas, gl_TexCoord[0].xy).r);
}