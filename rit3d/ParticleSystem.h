#pragma once
#include "RCommon.h"
#include "ISystem.h"

class CParticle;
class CCamera;
class ParticleSystem : public ISystem {
private:
	ParticleSystem(RInt od);
	virtual ~ParticleSystem();

	std::vector<CParticle*> m_particlePool;

	RUInt m_VAO;
public:
	void addParticle(CParticle* _b);
	void removeParticle(CParticle* _b);
	static ParticleSystem* CreateInstance(RInt);

	//ϵͳ��ʼ��ʱ����
	virtual void onAwake();

	//ϵͳ������ʱ����
	virtual void onEnable();

	//ϵͳ��ʼ����ʱ����
	virtual void onStart();

	//ʵ�屻��ӵ�ϵͳʱ����
	virtual void onAddGameObject();

	//�����ӵ�ʵ��ʱ����
	virtual void onAddComponent(COMPTYPE type, IComponent* pComp);

	//�����ʵ���Ƴ�ʱ����
	virtual void onRemoveComponent(COMPTYPE type, IComponent* pComp);

	//ʵ���ϵͳ���Ƴ�ʱ����
	virtual void onRemoveGameObject();

	//ϵͳ����ʱ����
	virtual void onUpdate(DWORD deltaT);

	//ϵͳ����ʱonUpdate֮�����
	virtual void onLateUpdate();

	//ϵͳ������ʱ����
	virtual void onDisable();

	//ϵͳ��ע��ʱ����
	virtual void onDestroy();

private:
	//����������Ϣ
	void _updateParticles(DWORD deltaT);
	//��Ⱦ����
	void _drawParticles();
	//Ѱ��һ��û�õ�����
	RInt _findUnusedParticle(CParticle* cp);
};