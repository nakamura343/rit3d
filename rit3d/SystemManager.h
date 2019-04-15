#pragma once

#include "RCommon.h"
#include "ISystem.h"
#include "RTimer.h"

/*
 * ϵͳ��������
 */
class SystemManager {
public:
	static SystemManager *Instance();
private:
	SystemManager();
	virtual ~SystemManager();

	static SystemManager *m_instance;

	//��ע�������ϵͳ��ʵ��
	std::list<ISystem*> m_systemList;

	//��¼����ϵͳ������ʱ��
	std::map<SYSTEMTYPE, DWORD> m_elapsedTime;

	RTimer clock_display{ 1000, 1000 };

	//ע�����ϵͳ�Ĵ���������ϵͳֻ��ͨ��������������������ֱ��new
	void registSystemCreateFunc();

	//ע���������Ĵ������������ֻ��ͨ��������������������ֱ��new
	void registCompCreateFunc();

	//��ʼ����Ҫ�ĵ������
	void registSingltonComp();
public:
	//Ϊ����ע��һ���ƶ���ϵͳ
	void registSystem(SYSTEMTYPE type, RInt od);
	//ϵͳ�������
	void update();
	//�ӳ�����ע���ȫ��ϵͳ�л�ȡһ��ָ����ϵͳ
	ISystem* getSystem(SYSTEMTYPE type);
	//�ж�ʱ���Ѿ�ע��ĳ��ϵͳ
	RBool hasSystem(SYSTEMTYPE type);
	//���ڴ�С�仯ʱ�ص�����
	void onChangeSize(int _w, int _h);
	//����µ����ʱ����
	void onAddComponent(COMPTYPE type, IComponent* pComp);
	//�Ƴ����ʱ����
	void onRemoveComponent(COMPTYPE type, IComponent* pComp);

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

	//������ײ������
	void setCollisionDetectionStrategy(int _cdt);
};