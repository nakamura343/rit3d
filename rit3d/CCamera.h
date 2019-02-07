#pragma once
#include "RCommon.h"
#include "IComponent.h"

class CCamera : public IComponent
{
private:
	CCamera();
	virtual ~CCamera();

	RFloat m_near{ 0.1f };
	RFloat m_far{ 100.0f };
	RFloat m_asp{ 800.0f / 600.0f };
	RFloat m_fov{ 45.0f };
	RFloat m_size{ 100.0f };

	CAMERATYPE m_cameraType{ CAMERATYPE::PERSPECTIVE };

	glm::mat4 m_viewMatrix{ 1.0f };
	glm::mat4 m_projMatrix{ 1.0f };

	RBool m_projDirty{ true };

public:
	RBool clearColor{ true };//�����Ȼ���
	RBool clearDepth{ true };//�����ɫ����

	glm::vec4 backgroundColor{ 0.2f, 0.3f, 0.3f, 1.0f };//����ɫ

	RUInt order;

	CAMERATYPE getCameraType() const;
	void setCameraType(CAMERATYPE type);

	RFloat getNear() const;
	void setNear(RFloat _n);

	RFloat getFar() const;
	void setFar(RFloat _f);

	RFloat getAsp() const;
	void setAsp(RFloat _a);

	RFloat getFov() const;
	void setFov(RFloat _f);

	RFloat getSize() const;
	void setSize(RFloat _s);

	//������׶��
	void setOrthoFrustum(RFloat _fov, RFloat _asp, RFloat _near, RFloat _far);
	void setPerspFrustum(RFloat _size, RFloat _asp, RFloat _near, RFloat _far);

	//��ȡͶӰ����
	glm::mat4 getProjMatrix();
	//��ȡ��ͼ����
	glm::mat4 getViewMatrix();

	static CCamera* CreateInstance();
};

