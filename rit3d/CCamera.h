#pragma once
#include "RCommon.h"
#include "IComponent.h"

struct Viewport {
	int x;
	int y;
	int w;
	int h;
};

//��Ⱦ��ʽ
enum RENDERMODEL {
	FORWARD = 0,
	DEFER,
};

//�������
typedef enum {
	ORTHO = 0,
	PERSPECTIVE = 1,
} CAMERATYPE;

class CCamera : public IComponent
{
private:
	CCamera();
	virtual ~CCamera();

	//��׶��
	RFloat m_near{ 0.1f };
	RFloat m_far{ 100.0f };
	RFloat m_asp{ 800.0f / 600.0f };
	RFloat m_fov{ 45.0f };
	RFloat m_size{ 100.0f };

	CAMERATYPE m_cameraType{ CAMERATYPE::PERSPECTIVE };

	glm::mat4 m_viewMatrix{ 1.0f };
	glm::mat4 m_projMatrix{ 1.0f };

	RBool m_projDirty{ true };

	Viewport m_viewport{ 0, 0, 800, 600 };

	//ͼ��
	RUInt m_cullMask{ LAYER::Default };
	//��ȾĿ��
	RUInt m_framebuffer;//֡���壬Ϊ�����ṩ�ӿ�
	RUInt m_colorTexs[2];//����֡�����ϵ�����

	//HDR����
	RFloat m_exposure{ 1.0f };//�ع����
	RFloat m_bloom{ 0.0f };//������ֵ

	//��Ⱦ��ʽ��������Ⱦ���ӳ���Ⱦ
	RENDERMODEL m_renderModel{ RENDERMODEL::FORWARD };
	RUInt m_gBuffer;//�ӳ���Ⱦ�õ���framebuffer
	RUInt m_gTextures[3];//�ӳ���Ⱦ�õ������� λ�� ���� ��ɫ
	RUInt m_rboDepth;//�ӳ���Ⱦ�õ�����Ȼ���

public:
	RUInt getCullMask() const;
	void setCullMask(RUInt _mask);

	RBool clearColor{ true };//�����Ȼ���
	RBool clearDepth{ true };//�����ɫ����

	glm::vec4 backgroundColor{ 0.0f, 0.0f, 0.0f, 1.0f };//����ɫ

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

	RFloat getExposure() const;
	void setExposure(RFloat _e);

	RFloat getBloom() const;
	void setBloom(RFloat _b);

	//������Ⱦģʽ
	RENDERMODEL getRenderModel() const;
	void setRenderModel(RENDERMODEL _m);
	//��ȡgBuffer��gTexture
	RUInt getGBuffer() const;
	RUInt getGTexture(RInt ind) const;

	//������׶��
	void setOrthoFrustum(RFloat _fov, RFloat _asp, RFloat _near, RFloat _far);
	void setPerspFrustum(RFloat _size, RFloat _asp, RFloat _near, RFloat _far);

	//��ȡͶӰ����
	glm::mat4 getProjMatrix();
	//��ȡ��ͼ����
	glm::mat4 getViewMatrix();

	//��ȡ֡�������
	RUInt getFramebuffer();
	//��ȡ֡�����ϵ���ɫ�������
	RUInt getColorTex(RUInt ind);

	void setViewport(int _x, int _y, int _w, int _h);
	Viewport getViewport() const;

	static CCamera* CreateInstance();
};

