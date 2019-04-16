#pragma once
#include "RCommon.h"
#include "IComponent.h"
#include "Texture.h"
#include "GLProgram.h"

enum EMISSIONSHAP {
	ES_SHPERE,
	ES_DIR,
	ES_CONE,
	ES_PLAN,
};

struct Particle {
	glm::vec3 position;
	glm::vec3 velocity;
	RFloat life;

	Particle() : position(0.0f), velocity(0.0f), life(0.0f) {}
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
	RFloat lifeTime{ 1.0f };//���Ӵ��ʱ��
	RFloat startSize{ 1.0f };//����ʱ���Ӵ�С
	RFloat rateOverTime{ 5.0f };//��λʱ���������ӵ�����
	EMISSIONSHAP emissionShap{ ES_SHPERE };//����������

	//----��Ⱦ���----
	Texture* spirit;//���ӵ�����
	GLProgram* shader;//��Ⱦ�õ���ɫ��

	//----���ӳ�----
	std::vector<Particle> particles;

	//----��������----
	RFloat cumulativeTime{ 0.0f };//������û�����������ӵ��ۼ�ʱ��,��λms
	RInt lastUsedParticle{ 0 };//����Ѱ��û�õ�����
};