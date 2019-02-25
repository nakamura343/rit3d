#pragma once
#include "RCommon.h"
#include "ISystem.h"

class CBehavior;
class BehaviorSystem : public ISystem {
private:
	BehaviorSystem(RInt od);
	virtual ~BehaviorSystem();

	std::vector<CBehavior*> m_behaviorPool;
public:
	void addBehavior(CBehavior* _b);
	void removeBehavior(CBehavior* _b);
	static BehaviorSystem* CreateInstance(RInt);

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

	//���ڴ�С�ı�ʱִ��
	virtual void onChangeSize(int _w, int _h);
	//����¼�
	virtual void onLeftButtonDown();
	virtual void onLeftButtonUp();
	virtual void onRightButtonDown();
	virtual void onRightButtonUp();
	virtual void onMouseMove(double _x, double _y);
	virtual void onScroll(double _x, double _y);
	//�����¼�
	virtual void onKeyDown(int key);
	virtual void onKeyKeep(int key);
	virtual void onKeyUp(int key);
};