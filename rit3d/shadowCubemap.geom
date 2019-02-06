#version 330 core
layout (triangles) in;//��������ͼԪ����
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 uShadowMatrices[6];

//ÿһ��EmitVertex(),out�ı����������һ��
out vec4 fragPos;// FragPos from GS (output per emitvertex)

void main() {
	for(int face = 0; face < 6; face++) {
		gl_Layer = face;
		for(int i = 0; i < 3; i++) {
			fragPos = gl_in[i].gl_Position;
			gl_Position = uShadowMatrices[face] * fragPos;
			EmitVertex();
		}
		EndPrimitive();//ע��EndPrimitive()��λ�ò�����for����
	}
}