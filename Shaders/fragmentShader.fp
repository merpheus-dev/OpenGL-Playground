#version 400 core

in vec3 pass_textureCoords;
out vec4 output_color;
uniform sampler2D textureSampler;

void main(void){
	output_color = texture(textureSampler,pass_textureCoords);
}