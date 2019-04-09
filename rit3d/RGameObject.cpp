#include "pch.h"
#include "RGameObject.h"
#include "RScene.h"
#include "CTransform.h"
#include "Application.h"
#include "SystemManager.h"
#include "BehaviorSystem.h"


RGameObject::RGameObject(RScene* s, RString n, RString t, LAYER l) :
	m_sce(s), name(n), tag(t), m_layer(l) {
	IComponent* pComp = addComponent(COMPTYPE::TRANFORM);
	transform = (CTransform*)pComp;
}


RGameObject::~RGameObject() {
	_destroy();
}

//���ٶ���
void RGameObject::_destroy() {
	//�ͷ���������Ŀռ�
	removeAllComponent();
}

//��ȡͼ��
LAYER RGameObject::getLayer() const {
	return m_layer;
}
//����ͼ��
void RGameObject::setLayer(LAYER _layer) {
	m_layer = _layer;
}

//������
IComponent* RGameObject::addComponent(COMPTYPE type) {
	if (m_compMap.find(type) != m_compMap.end()) {
		return m_compMap[type];
	}
	IComponent* pComp = IComponent::CreateComponent(type);
	pComp->gameObject = this;

	//std::pair<std::map<COMPTYPE, IComponent*>::iterator, bool> Insert_Pair;
	//Insert_Pair = 

	m_compMap.insert(std::map<COMPTYPE, IComponent*>::value_type(type, pComp));

	Application::Instance()->systemMng->onAddComponent(type, pComp);

	return pComp;
}

//�Ƴ�һ���ض����
void RGameObject::removeComponent(COMPTYPE type) {
	auto iter = m_compMap.find(type);
	if (iter != m_compMap.end()) {
		Application::Instance()->systemMng->onRemoveComponent(type, iter->second);
		SafeDelete(iter->second);
		m_compMap.erase(iter);
	}
}

//�Ƴ������ض����
void RGameObject::removeComponents(COMPTYPE type) {
	removeComponent(type);
}

//�Ƴ��������
void RGameObject::removeAllComponent() {
	for (auto iter = m_compMap.begin(); iter != m_compMap.end(); iter++) {
		removeComponent(iter->first);
	}
	m_compMap.clear();
}

//��ȡһ���ض����
IComponent* RGameObject::getComponent(COMPTYPE type) {
	auto iter = m_compMap.find(type);
	if (iter != m_compMap.end()) {
		return iter->second;
	}
	return nullptr;
}

//��ȡ�����ض����
std::list<IComponent*> RGameObject::getComponents(COMPTYPE type) {
	std::list<IComponent*> l;
	return l;
}

//��ȡ�������
std::list<IComponent*> RGameObject::getAllComponent() {
	std::list<IComponent*> l;
	return l;
}

//�Ƿ񼤻�������Լ��Ƿ񼤻��Ҫ���汲�Ƿ񼤻�
RBool RGameObject::isActive() {
	if (m_activeDirty) {
		CTransform* parent = transform->parent;

		//�������û�м���ӱ��ض�û�м���
		if (parent == nullptr || parent->gameObject->isActive()) {
			m_active = m_activeSelf;
		}
		else {
			m_active = false;
		}

		m_activeDirty = false;
	}

	return m_active;
}

//��ȡ������״̬
RBool RGameObject::getActiveSelf() const {
	return m_activeSelf;
}

//���ü���״̬�����������Լ��ļ���״̬
void RGameObject::setActiveSelf(RBool value) {
	if (m_activeSelf == value) {
		return;
	}

	CTransform* parent = transform->parent;
	if (parent == nullptr || parent->gameObject->isActive()) {
		m_activeSelf = value;
	}
	else {
		m_activeSelf = value;
	}
}

//����״̬����
void RGameObject::_setActiveDirty() {
	m_activeDirty = true;

	for (auto it : transform->children) {
		it->gameObject->_setActiveDirty();
	}
}

//��ȡ������������
RScene* RGameObject::getScene() const {
	return m_sce;
}

