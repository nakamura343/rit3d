#pragma once
#include "RCommon.h"
#include "IComponent.h"

class CTransform : public IComponent {
private:
	CTransform();
	virtual ~CTransform();

	//������Ϣ
	glm::vec3 m_localPosition{ 0.0f,0.0f,0.0f };  //�ֲ�����ϵ λ������
	glm::vec3 m_localAngle{ 0.0f,0.0f,0.0f };     //�ֲ�����ϵ ������ת�Ƕ�
	glm::vec3 m_localUpDir{ 0.0f, 1.0f, 0.0f };   //������(+y)
	glm::vec3 m_localFrontDir{ 0.0f, 0.0f, 1.0f };//ǰ����(+z)
	glm::vec3 m_localRightDir{ 1.0f, 0.0f, 0.0f };//������(+x)
	glm::vec3 m_localScale{ 1.0f, 1.0f,1.0f };    //�ֲ�����ϵ ����

	glm::mat4 m_modelMatrix{ 1.0f };              //ȫ��ģ�;���
	glm::mat4 m_localModelMatrix{ 1.0f };         //�ֲ�ģ�;���
	glm::mat4 m_viewMatrix{ 1.0f };               //��ͼ����

	RBool m_localModelDirty{ true };              //�ֲ�������Ϣ����
	RBool m_modelDirty{ true };                   //ȫ�ּ�����Ϣ����

	//����͵ƹ���ʱ�ǿ��Ƿ��ڳ����У�������Ƕ��
	RBool m_viewDirty{ true };                    //��ͼ�������
	//��Ե��Դ��Ӱ
	RBool m_viewsDirty{ true };
	std::vector<glm::mat4> m_viewsMatrix;

public:
	static CTransform* CreateInstance();

public:
	CTransform* parent;
	std::vector<CTransform*> children;

	//���ÿ���״̬
	void setEnabled(RBool value);

	//���ø�����
	CTransform* getParent() const;
	RBool setParent(CTransform* p);

	//�ֲ���ȡ������Ϣ
	glm::vec3 getLocalPosition() const;
	glm::vec3 getLocalAngle() const;
	glm::vec3 getLocalScale() const;
	glm::vec3 getLocalUpDir();
	glm::vec3 getLocalFrontDir();
	glm::vec3 getLocalRightDir();

	//�ֲ����ü�����Ϣ
	void setLocalPosition(float x, float y, float z);
	void setLocalAngle(float x, float y, float z);
	void setLocalScale(float x, float y, float z);
	void setLocalUpDir(float x, float y, float z);
	void setLocalFrontDir(float x, float y, float z);

	//ȫ�ֻ�ȡ������Ϣ
	glm::vec3 getPosition();
	glm::vec3 getAngle();
	glm::vec3 getScale();

	//�ֲ���ȡģ�;���
	glm::mat4 getLocalModelMatrix();
	//ȫ�ֻ�ȡģ�;���
	glm::mat4 getModelMatrix();
	//��ȡ��ͼ����
	glm::mat4 getViewMatrix();
	//��ȡ������ͼ������Ҫ��Ϊ�˵��Դ��Ӱ
	std::vector<glm::mat4> getViewMatrixs();

private:
	//�ֲ�ģ�;������
	void _setLocalDirty();
	//ȫ��ģ�;������
	void _setDirty();
};

