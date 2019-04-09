#pragma once
#include "RCommon.h"
#include "IComponent.h"

//��������
typedef enum {
	NONE = 0,
	DIRECTION,
	LPOINT,
	SPOT,
} LIGHTTYPE;

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
	LIGHTTYPE m_lightType{ LIGHTTYPE::NONE };

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
	RFloat m_far_s{ 10.0f };
	RFloat m_asp_s{ 1.0f };
	RFloat m_fov_s{ 90.0f };
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

	//��дsetEnabled
	void setEnabled(RBool value);

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

	RFloat getFov() const;

	RFloat getSize() const;
	void setSize(RFloat _s);

	//������׶��
	void setOrthoFrustum(RFloat _size, RFloat _near, RFloat _far);
	void setPerspFrustum(RFloat _near, RFloat _far);

	//��ȡ��ͼͶӰ����
	glm::mat4 getLightSpaceMatrix();
	//��ȡ��ͼͶӰ����
	std::vector<glm::mat4> getLightSpaceMatrixs();

private:
	//��ȡͶӰ����
	glm::mat4 _getProjMatrix();
	//��ȡ��ͼ����(ƽ�й�)
	glm::mat4 _getViewMatrix();
	//��ȡ��ͼ����(���Դ)
	std::vector<glm::mat4> _getViewMatrixs();

public:

	static CLight* CreateInstance();

};

