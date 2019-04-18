#pragma once
#include "RCommon.h"
#include "ISystem.h"
#include "CHair.h"

class HairSystem : public ISystem {
private:
	HairSystem(RInt od);
	virtual ~HairSystem();

	std::vector<CHair*> m_hairPool;

public:
	void addHair(CHair* _b);
	void removeHair(CHair* _b);
	static HairSystem* CreateInstance(RInt);

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
	//����ͷ������
	void _updateHair(DWORD deltaT);

	//����ͷ��
	void _drawHair();

	//ͷ������ײ���
	void _collideHair(CHair* ch, glm::vec3& point);

	//�ڵ����ݴӾֲ�����ϵת������������ϵ
	void _transform(CHair* ch);
};