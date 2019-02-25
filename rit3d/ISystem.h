#pragma once

#include "RCommon.h"

/*
 * ȫ��ϵͳ�Ļ��࣬����ϵͳ����̳��ڴ��࣬��ʵ�����еĴ��麯��
 * ����ϵͳ�࣬���뺬���Լ��ľ�̬��������������systemmanager��ע��
 */
class ISystem {
public:
	ISystem(RInt od);
	virtual ~ISystem();

	RInt order{ -1 };//ϵͳִ��˳��

	//����ϵͳʵ��������ϵͳʵ��ͨ���˷�������
	static ISystem* CreateSystem(SYSTEMTYPE type, RInt od);

	//�������ϵͳ�Ĵ�������������ʵ�ַ������
	static std::map<SYSTEMTYPE, std::function<ISystem*(RUInt)>> systemMap;

	//������Ҫʵ��static CreateInstance()����

protected:
	RBool enabled{ true };//ϵͳ�Ƿ񱻼���

	RBool m_started{ false };//ϵͳ�Ƿ���

	SYSTEMTYPE m_type;

public:
	//��ȡϵͳ����
	SYSTEMTYPE getType() const;

	//��ʼ��ϵͳ
	void initSystem();

	//ж��ϵͳ
	void uninitSystem();

	//ϵͳ����
	void update();

	//ϵͳ����2
	void lateUpdate();

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

	//ϵͳ��ʼ��ʱ����
	virtual void onAwake() = 0;

	//ϵͳ������ʱ����
	virtual void onEnable() = 0;

	//ϵͳ��ʼ����ʱ����
	virtual void onStart() = 0;

	//ʵ�屻��ӵ�ϵͳʱ����
	virtual void onAddGameObject() = 0;

	//�����ӵ�ʵ��ʱ����
	virtual void onAddComponent() = 0;

	//�����ʵ���Ƴ�ʱ����
	virtual void onRemoveComponent() = 0;

	//ʵ���ϵͳ���Ƴ�ʱ����
	virtual void onRemoveGameObject() = 0;

	//ϵͳ����ʱ����
	virtual void onUpdate() = 0;

	//ϵͳ����ʱonUpdate֮�����
	virtual void onLateUpdate() = 0;

	//ϵͳ������ʱ����
	virtual void onDisable() = 0;

	//ϵͳ��ע��ʱ����
	virtual void onDestroy() = 0;

	//����ϵͳ�Ƿ񱻼���
	RBool isEnabled() const;

	void setEnable(RBool value);

	RBool isStarted() const;

	void setStarted(RBool value);

private:

};


class StartSystem : public ISystem {
private:
	StartSystem(RInt od);
	virtual ~StartSystem();
public:
	static StartSystem* CreateInstance(RInt);
	
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