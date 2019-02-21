#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform float uExposure;
uniform sampler2D uTexture;
uniform sampler2D uBloomMap;
uniform float uBloomValue;

const float offset = 1.0f / 300.0f;

void main () {
	vec2 offsets[9] = vec2[9](
		vec2(-offset, offset), //����
		vec2(0.0f, offset),     //����
		vec2(offset, offset),  //����
		vec2(-offset, 0.0f),   //����
		vec2(0.0f, 0.0f),       //����
		vec2(offset, 0.0f),    //����
		vec2(-offset, -offset),//����
		vec2(0.0f, -offset),    //����
		vec2(offset, -offset) //����
	);

	float kernel[9] = float[9](
		-1.0f, -1.0f, -1.0f,
		-1.0f, 9.0f, -1.0f,
		-1.0f, -1.0f, -1.0f
	);
	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++) {
		sampleTex[i] = vec3(texture(uTexture, TexCoord + offsets[i]));
	}
	vec3 ave = vec3(0.0f);
	for(int i = 0; i < 9; i++) {
		ave += sampleTex[i] * kernel[i];
	}

	vec3 result = vec3(1.0f) - exp(-ave * uExposure);
	FragColor = vec4(result, 1.0f);
}