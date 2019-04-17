#pragma once
#include "RCommon.h"
#include "IComponent.h"
#include "Texture.h"
#include "GLProgram.h"

enum EMISSIONTYPE {
	ET_CONSECUTIVE,
	ET_PILSING,
};

struct Particle {
	glm::vec3 position;//λ��ƫ��
	glm::vec3 velocity;//�ٶȷ��� 
	RFloat size;//��С
	RFloat rotation;//��ת
	RFloat brightness;//����
	RFloat life;//ʣ����ʱ��

	Particle() : position(0.0f), velocity(0.0f), size(1.0f), rotation(0.0f), life(0.0f) {}
};

class CParticle : public IComponent {
private:
	CParticle();
	~CParticle();

public:
	static CParticle* CreateInstance();

public:
	//----���������----
	RFloat duration{ 1.0f };//���ӷ�������
	RBool loop{ true };//�Ƿ�ѭ������
	RFloat startSpeed{ 1.0f };//����ʱ�ĳ��ٶ�
	glm::vec3 accelerat{ 0.0f, 0.0f, 0.0f };//���ٶ�
	RFloat lifeTime{ 5.0f };//���Ӵ��ʱ��
	RFloat startSize{ 0.0f };//����ʱ���Ӵ�С
	RFloat endSize{ 1.0f };//��������ʱ��С
	RFloat rateOverTime{ 5.0f };//��λʱ���������ӵ���������������
	RInt rateOnce{ 10 };//һ�����巢������������巢��
	EMISSIONTYPE emissionType{ ET_CONSECUTIVE };//����������

	//----��Ⱦ���----
	Texture* spirit;//���ӵ�����
	GLProgram* shader;//��Ⱦ�õ���ɫ��

	//----���ӳ�----
	std::vector<Particle> particles;

	//----��������----
	RFloat cumulativeTime{ 0.0f };//������û�����������ӵ��ۼ�ʱ��,��λms
	RInt lastUsedParticle{ 0 };//����Ѱ��û�õ�����
	int latencyTime{ -1 };//���ӷ���ȴ�ʱ��,��λms

	//----�������ɺ͸��º���----
	std::function<void(CParticle*, Particle&)> emissionFunc;//�������ӵĺ���
	std::function<void(CParticle*, Particle&, DWORD)> updateFunc;//�������ӵĺ���
};