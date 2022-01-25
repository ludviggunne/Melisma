#version 450 core

layout (location = 0) in vec3	a_Position;
layout (location = 1) in vec2	a_TexCoord;
layout (location = 2) in float	a_TexID;
layout (location = 3) in vec4	a_Color;

out vec2		v_TexCoord;
flat out float	v_TexID;
out vec4		v_Color;

uniform mat4 u_View;

void main(){
	gl_Position = u_View * vec4(a_Position, 1.0f);
	v_TexCoord = a_TexCoord;
	v_TexID = a_TexID;
	v_Color = a_Color;
}