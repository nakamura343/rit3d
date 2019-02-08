#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D uTexture;

void main () {
	FragColor = texture(uTexture, TexCoord);
	float ave = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;//���۶���ɫ��������
	FragColor = vec4(ave, ave, ave, 1.0f);
}