#version 330 core
out vec4 FragColor;

in vec3 tangent;
in vec3 position;

//ƽ�й�ṹ��
struct DirLight {
	vec3 direction;
	vec3 color;
	float ambInt;
	float difInt;
	float speInt;
	bool castShadow;
};

uniform DirLight uLight;//��Դ
uniform vec3 uViewPos;//���λ��

float calcSpecular(vec3 T, vec3 H, float exponent, float ks) {
	float cosTH = dot(T, H);
	float sinTH = sqrt(1.0f - cosTH * cosTH);
	return ks * pow(sinTH, exponent);
}

float rand(float x, float y) {
	return fract(cos(x * (12.9898) + y * (4.1414)) * 43758.5453);
}

void main () {
	//ͷ����ɫ
	vec4 color = vec4(0.42f, 0.22f, 0.0f, 1.0f);
	//��������
	vec3 L = -normalize(uLight.direction);
	vec3 E = normalize(uViewPos - position);
	float cosTL = dot(tangent, L);
	float sinTL = sqrt(1 - cosTL * cosTL);
	vec3 diffuse = uLight.difInt * sinTL * uLight.color * vec3(color);

	//���淴����
	//���߲���
	vec3 H = normalize(L + E);
	vec3 T = tangent;//����
	vec3 TH = normalize(cross(T, H));//ƽ��TH�ķ�����
	vec3 HN = normalize(cross(TH, T));//ƽ��TH����T��ֱ������
	float r1 = rand(position.x, position.y) * 0.1f;
	//float r1 = 0.1f;
	vec3 t1 = normalize(T - HN * r1);
	vec3 t2 = normalize(T + HN * r1);
	vec3 specular1 = uLight.speInt * calcSpecular(t1, H, 32.0f, 1.0f) * uLight.color * vec3(color);
	vec3 specular2 = uLight.speInt * calcSpecular(t2, H, 32.0f, 0.5f) * uLight.color * vec3(0.8f,0.8f,0.8f);

	vec3 result = (diffuse + specular1 +  specular2);
	result = vec3(1.0f) - exp(-result * 1.0f);
	FragColor = vec4(result, 1.0f);
}