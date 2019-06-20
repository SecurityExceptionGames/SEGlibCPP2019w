#version 120
uniform vec2 pos;

void main() {
	vec4 vertex = gl_Vertex;
	vertex.xy += pos;
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}