#include "pch.h"
#include "RScene.h"
#include "RGameObject.h"
#include "CCamera.h"
#include "CLight.h"
#include "CTransform.h"
#include "Application.h"
#include "ResourceManager.h"

//��������
RScene* RScene::CreateScene(RString name) {
	RScene* scn = new RScene(name);
	return scn;
}

RScene::RScene(RString name) {
	m_name = name;
}
RScene::~RScene() {

}

//��������
void RScene::destroy() {
	//����������Ϸ����
	for (auto it : m_GameObjectList) {
		delete it;
		it = nullptr;
	}
	m_GameObjectList.clear();
	delete this;
}

//�������Ʋ���
RString RScene::getName() const {
	return m_name;
}
void RScene::setName(RString name) {
	m_name = name;
}

//����״̬����
RBool RScene::isActive() const {
	return m_active;
}
void RScene::setActive(RBool value) {
	m_active = value;
}

//ͼ�����
RUInt RScene::getLayer() const {
	return m_layer;
}
void RScene::setLayer(RUInt l) {
	m_layer = l;
}

//�����Ϸ����
RGameObject* RScene::addGameObject(RString n, RString t, LAYER l) {
	RGameObject* go = new RGameObject(this, n, t, l);
	m_GameObjectList.push_back(go);
	return go;
}
//��ģ���ļ��м�����Ϸ���󵽳�����
RGameObject* RScene::loadGameObject(RString _path, RString _n, RString _t, LAYER _l) {
	RGameObject* go = Application::Instance()->resourceMng->loadModel(_path, this);
	if (go != nullptr) {
		go->name = _n;
		go->tag = _t;
		go->setLayer(_l);
		m_GameObjectList.push_back(go);
	}
	return go;
}
//ɾ����Ϸ����
void RScene::removeGameObject(RGameObject* pgb) {
	if (hasGameObject(pgb)) {
		CTransform* parent = pgb->transform->parent;

		//�Ӹ��ڵ���ӽڵ�������ɾ���ö���
		if (parent != nullptr) {
			std::vector<CTransform*> children = parent->children;
			children.erase(std::remove(children.begin(), children.end(), pgb->transform), children.end());
		}

		_removeGameObject(pgb);
	}
}
//�ݹ�ɾ����Ϸ����
void RScene::_removeGameObject(RGameObject* pgb) {
	if (!pgb->transform->children.empty()) {
		for (auto it : pgb->transform->children) {
			_removeGameObject(it->gameObject);
		}
	}
	m_GameObjectList.remove(pgb);
	delete pgb;
	pgb = nullptr;
}

//������Ϸ����
RGameObject* RScene::findGameObjectWithName(RString name) {
	for (auto it : m_GameObjectList) {
		if (it->name == name) {
			return it;
		}
	}
	return nullptr;
}
RGameObject* RScene::findGameObjectWithTag(RString tag) {
	for (auto it : m_GameObjectList) {
		if (it->tag == tag) {
			return it;
		}
	}
	return nullptr;
}
std::list<RGameObject*> RScene::findGameObjectsWithTag(RString tag) {
	std::list<RGameObject*> nlist;
	for (auto it : m_GameObjectList) {
		if (it->tag == tag) {
			nlist.push_back(it);
		}
	}
	return nlist;
}
std::list<RGameObject*> RScene::getAllGameObjects() {
	return m_GameObjectList;
}

//�����Ƿ������Ϸ����
RBool RScene::hasGameObject(RGameObject* pgb) {
	for (auto it : m_GameObjectList) {
		if (it == pgb) {
			return true;
		}
	}
	return false;
}

//��������Ϸ��������
RUInt RScene::getGameObjectCount() {
	return m_GameObjectList.size();
}

std::list<RGameObject*> RScene::getGameObjectList() const {
	return m_GameObjectList;
}
