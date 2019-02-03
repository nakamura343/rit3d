#pragma once

#include "RCommon.h"
#include "RGameObject.h"
#include "CCamera.h"
#include "CLight.h"

class RScene {
public:
	//��������
	static RScene* CreateScene(RString name = DEFAULT_SCENE_NAME);

private:
	RScene(RString name);
	virtual ~RScene();

	std::list<RGameObject*> m_GameObjectList;//�����ж����б�
	std::list<CCamera*> m_cameraList;//����б�
	std::list<CLight*> m_lightList;//��Դ�б�
	RUInt m_dirLightNum{ 0 };//ƽ�й�����
	RUInt m_poiLightNum{ 0 };//���Դ����
	RUInt m_spoLightNum{ 0 };//�۹������
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

	//���������
	void addCamera(CCamera* camera);
	//�Ƴ�������
	void removeCamera(CCamera* camera);
	//��ȡ����б�
	std::list<CCamera*> getCameraList() const;

	//��ӵƹ����
	void addLight(CLight* light);
	//�Ƴ��ƹ����
	void removeLight(CLight* light);
	//��ȡ�ƹ��б�
	std::list<CLight*> getLightList() const;
	//��ȡ��Դ����
	RUInt getLightNum(LIGHTTYPE _type) const;
	//������Դ����
	void resetLightNum(LIGHTTYPE _type, RInt delta);

private:
	//�ݹ�ɾ����Ϸ����
	void _removeGameObject(RGameObject* pgb);
};