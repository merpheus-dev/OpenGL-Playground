#version 400 core

in vec3 color;
out vec4 output_color;

void main(void){
	output_color = vec4(color,1.0);
}