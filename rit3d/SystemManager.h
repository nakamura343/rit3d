#pragma once

#include "RCommon.h"
#include "ISystem.h"
#include "RenderSystem.h"

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

	//ע�����ϵͳ�Ĵ���������ϵͳֻ��ͨ��������������������ֱ��new
	void registSystemCreateFunc();

	//ע���������Ĵ������������ֻ��ͨ��������������������ֱ��new
	void registCompCreateFunc();
public:
	//Ϊ����ע��һ���ƶ���ϵͳ
	void registSystem(SYSTEMTYPE type, RInt od);
	//ϵͳ�������
	void update();
	//�ӳ�����ע���ȫ��ϵͳ�л�ȡһ��ָ����ϵͳ
	ISystem* getSystem(SYSTEMTYPE type);
	//�ж�ʱ���Ѿ�ע��ĳ��ϵͳ
	RBool hasSystem(SYSTEMTYPE type);
};