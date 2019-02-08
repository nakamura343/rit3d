#include "pch.h"
#include "SystemManager.h"
#include "IComponent.h"
#include "CTransform.h"
#include "CRender.h"
#include "CCamera.h"
#include "CLight.h"
#include "CPostProcess.h"

/*
 * ϵͳ��������
 */
SystemManager::SystemManager() {
	//ע��ϵͳ��������
	registSystemCreateFunc();
	//ע�������������
	registCompCreateFunc();
	//���ϵͳ�б�
	m_systemList.clear();
};
SystemManager::~SystemManager() {};

SystemManager* SystemManager::m_instance = nullptr;

SystemManager* SystemManager::Instance() {
	if (nullptr == m_instance) {
		m_instance = new SystemManager();
	}
	return m_instance;
}

//ע�����ϵͳ�Ĵ���������ϵͳֻ��ͨ��������������������ֱ��new
void SystemManager::registSystemCreateFunc() {
	ISystem::systemMap.clear();
	ISystem::systemMap[STARTSYSTEM] = StartSystem::CreateInstance;
	ISystem::systemMap[RENDERSYSTEM] = RenderSystem::CreateInstance;
}

//ע���������Ĵ������������ֻ��ͨ��������������������ֱ��new
void SystemManager::registCompCreateFunc() {
	IComponent::compMap.clear();
	IComponent::compMap[TRANFORM] = CTransform::CreateInstance;
	IComponent::compMap[RENDER] = CRender::CreateInstance;
	IComponent::compMap[CAMERA] = CCamera::CreateInstance;
	IComponent::compMap[LIGHT] = CLight::CreateInstance;
	IComponent::compMap[POSTPROCESS] = CPostProcess::CreateInstance;
}

//Ϊ����ע��һ���ƶ���ϵͳ
void SystemManager::registSystem(SYSTEMTYPE type, RInt od) {
	if (hasSystem(type)) {
		cout << "system has been registed!" << endl;
		return;
	}
	ISystem* st = ISystem::CreateSystem(type, od);
	//����od���뵽�ƶ�λ��
	std::list<ISystem*>::iterator it = m_systemList.begin();
	for (; it != m_systemList.end(); it++) {
		auto pItem = *it;
		if (pItem->order > od) {
			m_systemList.insert(it, st);
			break;
		}
	}
	if (it == m_systemList.end()) {
		m_systemList.push_back(st);
	}

	st->initSystem();
}

//ϵͳ�������
void SystemManager::update() {
	//onStart()
	for (auto st : m_systemList) {
		if (st->isEnabled() && !st->isStarted()) {
			st->setStarted(true);
			st->onStart();
		}
	}
	//update
	for (auto st : m_systemList) {
		if (st->isEnabled()) {
			st->update();
		}
	}
	//lateUpdate
	for (auto st : m_systemList) {
		if (st->isEnabled()) {
			st->lateUpdate();
		}
	}
}

//�ж�ʱ���Ѿ�ע��ĳ��ϵͳ
RBool SystemManager::hasSystem(SYSTEMTYPE type) {
	for (auto it : m_systemList) {
		if (it->getType() == type) {
			return true;
		}
	}
	return false;
}

//�ӳ�����ע���ȫ��ϵͳ�л�ȡһ��ָ����ϵͳ
ISystem* SystemManager::getSystem(SYSTEMTYPE type) {
	for (auto it : m_systemList) {
		if (it->getType() == type) {
			return it;
		}
	}
	return nullptr;
}