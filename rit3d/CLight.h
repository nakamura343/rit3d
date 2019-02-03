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
	RFloat m_cutInner{ 15.0f / 57.3f };//��׶��
	RFloat m_cutOuter{ 25.0f / 57.3f };//��׶��

public:
	glm::vec3 getColor() const;
	void setColor(RFloat r, RFloat g, RFloat b);
	void setColor(glm::vec3 _color);

	void setIntensity(RFloat amb, RFloat dif, RFloat spe);

	RBool isCastShadow() const;
	void castShadow(RBool _cast);

	LIGHTTYPE getLightType() const;
	void setLightType(LIGHTTYPE _type);

	void setAttenuation(RFloat dis, RFloat _kc, RFloat _kl, RFloat _kq);

	void setCutOff(RFloat inner, RFloat outer);

	RFloat getAmbInt() const;
	RFloat getDifInt() const;
	RFloat getSpeInt() const;

	static CLight* CreateInstance();
};

