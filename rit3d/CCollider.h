#pragma once
#include "RCommon.h"
#include "IComponent.h"

class CCollider : public IComponent {
public:
	CCollider();
	virtual ~CCollider();
};

class CSphereCollider : public CCollider {
private:
	CSphereCollider();
	virtual ~CSphereCollider();

public:
	static CSphereCollider* CreateInstance();

	glm::vec3 center{ 0.0f, 0.0f, 0.0f };//�ֲ�����ϵ����
	RFloat radius{ 0.5f };//�뾶
};

class CBoxCollider : public CCollider {
private:
	CBoxCollider();
	virtual ~CBoxCollider();

public:
	static CBoxCollider* CreateInstance();

	glm::vec3 center{ 0.0f, 0.0f, 0.0f };//�ֲ�����ϵ����
};

