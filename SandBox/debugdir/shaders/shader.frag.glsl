#version 450 core

in vec2			v_TexCoord;
flat in float	v_TexID;
in vec4			v_Color;

uniform sampler2D u_Textures[32];

void main() {
	vec4 texColor = texture(u_Textures[int(v_TexID)], v_TexCoord);
	//if(texColor.a < 1.0) discard;
	gl_FragColor = v_Color * texColor;
}