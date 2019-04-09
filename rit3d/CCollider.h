#pragma once
#include "RCommon.h"
#include "IComponent.h"

class CSphereCollider : public IComponent {
private:
	CSphereCollider();
	virtual ~CSphereCollider();

public:
	static CSphereCollider* CreateInstance();

	glm::vec3 center{ 0.0f, 0.0f, 0.0f };//�ֲ�����ϵ����
	RFloat radius;//�뾶
};

