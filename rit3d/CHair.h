#pragma once
#include "RCommon.h"
#include "IComponent.h"
#include "GLProgram.h"

struct HairNode {
	glm::vec3 p0;//ǰһ֡��λ��
	glm::vec3 p1;//��֡��λ��
	RFloat maxLength;//����һ���ڵ��ֹ������
};

struct HairStrand {
	int nodeStart, nodeEnd;//��������������ʼ��ĩβ�ڵ������
	glm::vec3 rootP;//������λ��
};

class CHair : public IComponent
{
private:
	CHair();
	virtual ~CHair();

	void _init();
public:
	RUInt m_VAO;
	RUInt m_VBO;
	std::vector<HairNode> m_nodes;//���нڵ�
	std::vector<glm::vec3> m_drawData;//������Ҫ������
	std::vector<HairStrand> m_strands;//���з���
	glm::vec3 a{ 0.0f, -9.8f, 0.0f };//���ٶ�
	RFloat d{ 1.0f };//����
	glm::vec3 center{ 0.0f, 0.0f, 0.0f };//��ײ������
	RFloat raduis{ 0.5f };//��ײ��뾶
	RInt nodeInStrand{ 7 };//һ�������еĽڵ���
	RFloat minLength{ 0.05f };//������һ�εĳ���

	GLProgram* shader;
	static CHair* CreateInstance();
};

