#pragma once
#include "RCommon.h"
#include "ISystem.h"

class CCollider;
class CollideSystem : public ISystem {
private:
	CollideSystem(RInt od);
	virtual ~CollideSystem();

	std::vector<CCollider*> m_colliderPool;
public:
	static CollideSystem* CreateInstance(RInt od);

	//ϵͳ��ʼ��ʱ����
	virtual void onAwake();

	//ϵͳ������ʱ����
	virtual void onEnable();

	//ϵͳ��ʼ����ʱ����
	virtual void onStart();

	//ʵ�屻��ӵ�ϵͳʱ����
	virtual void onAddGameObject();

	//�����ӵ�ʵ��ʱ����
	virtual void onAddComponent();

	//�����ʵ���Ƴ�ʱ����
	virtual void onRemoveComponent();

	//ʵ���ϵͳ���Ƴ�ʱ����
	virtual void onRemoveGameObject();

	//ϵͳ����ʱ����
	virtual void onUpdate();

	//ϵͳ����ʱonUpdate֮�����
	virtual void onLateUpdate();

	//ϵͳ������ʱ����
	virtual void onDisable();

	//ϵͳ��ע��ʱ����
	virtual void onDestroy();
};

