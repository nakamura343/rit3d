#pragma once

#include "RCommon.h"
#include "IComponent.h"

class CTransform;
class RScene;
class RGameObject
{
public:
	RGameObject(RScene* s, RString n = "UnName", RString t = "UnTag", LAYER l = LAYER::Default);
	~RGameObject();

	RString name;//����
	RString tag;//���

	CTransform* transform;//�������

private:
	LAYER m_layer{ LAYER::Default };//����ͼ��
	RScene* m_sce;//��������

	RBool m_activeSelf{ true };//����ļ���״̬
	RBool m_active{ true };//�ڳ����е���ʵ����״̬
	RBool m_activeDirty{ false };//��Ǽ���״̬�Ƿ���ܸı�

	std::map<COMPTYPE, IComponent*> m_compMap;

public:
	//��ȡͼ��
	LAYER getLayer() const;
	//����ͼ��
	void setLayer(LAYER _layer);

	//������
	IComponent* addComponent(COMPTYPE type);

	//�Ƴ�һ���ض����
	void removeComponent(COMPTYPE type);

	//�Ƴ������ض����
	void removeComponents(COMPTYPE type);

	//�Ƴ��������
	void removeAllComponent();

	//��ȡһ���ض����
	IComponent* getComponent(COMPTYPE type);

	//��ȡ�����ض����
	std::list<IComponent*> getComponents(COMPTYPE type);

	//��ȡ�������
	std::list<IComponent*> getAllComponent();

	//�Ƿ񼤻�������Լ��Ƿ񼤻��Ҫ���汲�Ƿ񼤻�
	RBool isActive();

	//��ȡ������״̬
	RBool getActiveSelf() const;

	//���ü���״̬�����������Լ��ļ���״̬
	void setActiveSelf(RBool value);

	//����״̬����
	void _setActiveDirty();

	//��ȡ������������
	RScene* getScene() const;

private:
	//���ٶ���
	void _destroy();
};

