#pragma once
#include "RCommon.h"
#include "IComponent.h"

class CLight : public IComponent {

private:
	CLight();
	virtual ~CLight();

	//--��������
	//��ɫ
	glm::vec3 m_color{ 1.0f, 1.0f, 1.0f };
	//ambientǿ��
	RFloat m_ambientInt{ 0.1f };
	//diffuseǿ��
	RFloat m_diffuseInt{ 0.5f };
	//specularǿ��
	RFloat m_specularInt{ 1.0f };
	//�Ƿ�Ͷ����Ӱ
	RBool m_castShadow{ false };
	//��Դ����
	LIGHTTYPE m_lightType{ LIGHTTYPE::DIRECTION };

	//--ƽ�й�����

	//--���Դ����
	//���þ���
	RFloat m_distance{ 50.0f };
	//˥��ϵ��
	RFloat m_kc{ 1.0f };   //������
	RFloat m_kl{ 0.09f };  //������
	RFloat m_kq{ 0.032f }; //������
	//--�۹������
	//׶��(����)
	RFloat m_cutInner{ cos(15.0f / 57.3f) };//��׶��
	RFloat m_cutOuter{ cos(25.0f / 57.3f) };//��׶��

	//--��Ӱ���
	RUInt m_depthMapFBO;//shadow map��framebuffer
	RUInt m_depthMap;//��������ͼ������

	RFloat m_near_s{ 0.1f };
	RFloat m_far_s{ 5.0f };
	RFloat m_asp_s{ 800.0f / 600.0f };
	RFloat m_fov_s{ 45.0f };
	RFloat m_size_s{ 10.0f };

	RBool m_projDirty{ true };

	glm::mat4 m_viewMatrix{ 1.0f };
	glm::mat4 m_projMatrix{ 1.0f };

public:
	//��������
	glm::vec3 getColor() const;
	void setColor(RFloat r, RFloat g, RFloat b);
	void setColor(glm::vec3 _color);

	void setIntensity(RFloat amb, RFloat dif, RFloat spe);
	RFloat getAmbInt() const;
	RFloat getDifInt() const;
	RFloat getSpeInt() const;

	RBool isCastShadow() const;
	void castShadow(RBool _cast);

	LIGHTTYPE getLightType() const;
	void setLightType(LIGHTTYPE _type);

	//���Դ���

	void setAttenuation(RFloat dis, RFloat _kc, RFloat _kl, RFloat _kq);
	RFloat getKc() const;
	RFloat getKl() const;
	RFloat getKq() const;

	//�۹�����
	void setCutOff(RFloat inner, RFloat outer);
	RFloat getCutInner() const;
	RFloat getCutOuter() const;

	//--��Ӱ
	RUInt getFramebuffer() const;
	RUInt getDepthMap() const;

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
	void setOrthoFrustum(RFloat fov, RFloat asp, RFloat near, RFloat far);
	void setPerspFrustum(RFloat size, RFloat asp, RFloat near, RFloat far);

	//��ȡ��ͼͶӰ����
	glm::mat4 getLightSpaceMatrix();

private:
	//��ȡͶӰ����
	glm::mat4 _getProjMatrix();
	//��ȡ��ͼ����
	glm::mat4 _getViewMatrix();

public:

	static CLight* CreateInstance();

};

