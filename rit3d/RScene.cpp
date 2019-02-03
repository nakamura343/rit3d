#include "pch.h"
#include "RScene.h"

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

//���������
void RScene::addCamera(CCamera* camera) {
	std::list<CCamera*>::iterator iter;
	iter = std::find(m_cameraList.begin(), m_cameraList.end(), camera);
	if (iter != m_cameraList.end()) {
		return;
	}
	m_cameraList.push_back(camera);
}
//�Ƴ�������
void RScene::removeCamera(CCamera* camera) {
	std::list<CCamera*>::iterator iter;
	iter = std::find(m_cameraList.begin(), m_cameraList.end(), camera);
	if (iter == m_cameraList.end()) {
		return;
	}
	m_cameraList.remove(camera);
}
//��ȡ����б�
std::list<CCamera*> RScene::getCameraList() const {
	return m_cameraList;
}

//��ӵƹ����
void RScene::addLight(CLight* light) {
	std::list<CLight*>::iterator iter;
	iter = std::find(m_lightList.begin(), m_lightList.end(), light);
	if (iter != m_lightList.end()) {
		return;
	}
	m_lightList.push_back(light);
	LIGHTTYPE t = light->getLightType();
	switch (t)
	{
	case LIGHTTYPE::DIRECTION:
		m_dirLightNum++;
		break;
	case LIGHTTYPE::POINT:
		m_poiLightNum++;
		break;
	case LIGHTTYPE::SPOT:
		m_spoLightNum++;
		break;
	default:
		break;
	}
}
//�Ƴ��ƹ����
void RScene::removeLight(CLight* light) {
	std::list<CLight*>::iterator iter;
	iter = std::find(m_lightList.begin(), m_lightList.end(), light);
	if (iter == m_lightList.end()) {
		return;
	}
	m_lightList.remove(light);
	LIGHTTYPE t = light->getLightType();
	switch (t)
	{
	case LIGHTTYPE::DIRECTION:
		m_dirLightNum--;
		break;
	case LIGHTTYPE::POINT:
		m_poiLightNum--;
		break;
	case LIGHTTYPE::SPOT:
		m_spoLightNum--;
		break;
	default:
		break;
	}
}
//��ȡ�ƹ��б�
std::list<CLight*> RScene::getLightList() const {
	return m_lightList;
}
//��ȡ��Դ����
RUInt RScene::getLightNum(LIGHTTYPE _type) const {
	switch (_type)
	{
	case LIGHTTYPE::DIRECTION:
		return m_dirLightNum;
	case LIGHTTYPE::POINT:
		return m_poiLightNum;
	case LIGHTTYPE::SPOT:
		return m_spoLightNum;
	default:
		return 0;
	}
}

//������Դ����
void RScene::resetLightNum(LIGHTTYPE _type, RInt delta) {
	switch (_type)
	{
	case LIGHTTYPE::DIRECTION:
		m_dirLightNum += delta;
		break;
	case LIGHTTYPE::POINT:
		m_poiLightNum += delta;
		break;
	case LIGHTTYPE::SPOT:
		m_spoLightNum += delta;
		break;
	default:
		break;
	}
}
