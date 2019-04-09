#pragma once

#include "RCommon.h"
#include "Object.h"
#include "CLight.h"

class RGameObject;
class CCamera;

class RScene : public Object {
public:
	//��������
	static RScene* CreateScene(RString name = DEFAULT_SCENE_NAME);

private:
	RScene(RString name);
	virtual ~RScene();

	std::list<RGameObject*> m_GameObjectList;//�����ж����б�
	RBool m_active{ true };//�����Ƿ񼤻� 
	RString m_name;//��������

	RUInt m_layer{ LAYER::Default }; //ͼ��

public:
	//��������
	void destroy();
	
	//�������Ʋ���
	RString getName() const;
	void setName(RString name);

	//����״̬����
	RBool isActive() const;
	void setActive(RBool value);

	//ͼ�����
	RUInt getLayer() const;
	void setLayer(RUInt l);

	//�����������Ϸ���󵽳�����
	RGameObject* addGameObject(RString n = "UnName", RString t = "UnTag", LAYER l = LAYER::Default);
	//��ģ���ļ��м�����Ϸ���󵽳�����
	RGameObject* loadGameObject(RString _path, RString _n = "UnName", RString _t = "UnTag", LAYER _l = LAYER::Default);
	//ɾ����Ϸ����
	void removeGameObject(RGameObject* pgb);
	//������Ϸ����
	RGameObject* findGameObjectWithName(RString name);
	RGameObject* findGameObjectWithTag(RString tag);
	std::list<RGameObject*> findGameObjectsWithTag(RString tag);
	std::list<RGameObject*> getAllGameObjects();
	//�����Ƿ������Ϸ����
	RBool hasGameObject(RGameObject* pgb);
	//��������Ϸ��������
	RUInt getGameObjectCount();
	//��ȡ��Ϸ�����б�
	std::list<RGameObject*> getGameObjectList() const;

private:
	//�ݹ�ɾ����Ϸ����
	void _removeGameObject(RGameObject* pgb);
};