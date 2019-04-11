#pragma once
#include "RCommon.h"
#include "Object.h"

//�������
typedef enum {
	TRANFORM = 0,
	//��Ⱦ������
	MESH,
	RENDER,
	CAMERA,
	LIGHT,
	POSTPROCESS,
	SKYBOX,
	//�ű�������
	BEHAVIOR,
	//����������
	SPHERECOLLIDER,
	BOXCOLLIDER,

	//�������
	LIGHTCAMERACOLLECTER,
} COMPTYPE;

class RGameObject;
class IComponent : public Object {
public:
	IComponent();
	virtual ~IComponent();

	//����ϵͳʵ��������ϵͳʵ��ͨ���˷�������
	static IComponent* CreateComponent(COMPTYPE type);

	//�����������Ĵ�������������ʵ�ַ������
	static std::map<COMPTYPE, std::function<IComponent*()>> compMap;

	RGameObject* gameObject{ nullptr };//�����ʵ��

protected:
	RBool m_enabled{ true };//����Ƿ��Ծ

	RBool m_allowMultiple{ false };//�Ƿ�������ͬһʵ������Ӷ���������ʵ��

	RBool m_isSingleton{ false };//�Ƿ��ǵ������

	COMPTYPE m_type;

public:
	//��ȡϵͳ����
	COMPTYPE getType() const;

	//�Ƿ�������ͬһʵ������Ӷ���������ʵ��
	RBool allowMultiple() const;

	//�Ƿ��ǵ������
	RBool isSingleton() const;

	//�Ƿ����
	RBool isEnabled() const;
	//���ÿ���״̬
	void setEnabled(RBool value);
	//�Ƿ񼤻��ҿ���
	RBool isActiveAndEnabled() const;
};

