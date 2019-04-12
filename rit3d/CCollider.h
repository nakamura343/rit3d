#pragma once
#include "RCommon.h"
#include "IComponent.h"

//��Χ������
typedef enum {
	SPHEREBV = 0,
	BOXBV,
} BVTYPE;

//interface of bounding volume
class IBV {
public:
	BVTYPE type;
	IBV() {}
};

//sphere bounding volume
class SphereBV : public IBV {
public:
	glm::vec3 c{ 0.0f, 0.0f, 0.0f };
	RFloat r{ 0.0f };

	SphereBV() {
		type = BVTYPE::SPHEREBV;
	}
};

//��ײ�齨����
class CCollider : public IComponent {
public:
	CCollider();
	virtual ~CCollider();

	//��������ϵ�µ���ײ�У������ڲ������õ����ݽṹ�����ⲻ�ɼ�������ɼ���ֻ����������ԡ�
	IBV* wBV{ nullptr };
};

//����ײ���
class CSphereCollider : public CCollider {
private:
	CSphereCollider();
	virtual ~CSphereCollider();

public:
	static CSphereCollider* CreateInstance();

	glm::vec3 center{ 0.0f, 0.0f, 0.0f };//�ֲ�����ϵ����
	RFloat radius{ 0.5f };//�ֲ�����ϵ�뾶
};

//��������ײ���
class CBoxCollider : public CCollider {
private:
	CBoxCollider();
	virtual ~CBoxCollider();

public:
	static CBoxCollider* CreateInstance();

	glm::vec3 center{ 0.0f, 0.0f, 0.0f };//�ֲ�����ϵ����
};

