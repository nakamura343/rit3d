#include "pch.h"
#include "CTransform.h"
#include "RGameObject.h"


CTransform::CTransform() {
	m_type = COMPTYPE::TRANFORM;
}


CTransform::~CTransform() {

}

CTransform* CTransform::CreateInstance() {
	return new CTransform();
}

//���ÿ���״̬
void CTransform::setEnabled(RBool value) {
	//ǿ�ƿ��ã����δ˷���
}

//���ø�����
CTransform* CTransform::getParent() const {
	return parent;
}
RBool CTransform::setParent(CTransform* p) {
	if (parent == p) {
		return true;
	}
	else {
		if (p == nullptr || p->gameObject->getScene() == gameObject->getScene()) {
			parent = p;
			_setDirty();//ȫ��ģ�;������
			return true;
		}
		else {
			return false;
		}
	}
}

//�ֲ���ȡ������Ϣ
glm::vec3 CTransform::getLocalPosition() const {
	return m_localPosition;
}
glm::vec3 CTransform::getLocalAngle() const {
	return m_localAngle;
}
glm::vec3 CTransform::getLocalScale() const {
	return m_localScale;
}
glm::vec3 CTransform::getLocalUpDir() const {
	return m_localUpDir;
}
glm::vec3 CTransform::getLocalFrontDir() const {
	return m_localFrontDir;
}

//�ֲ����ü�����Ϣ
void CTransform::setLocalPosition(float x, float y, float z) {
	if (m_localPosition.x == x && m_localPosition.y == y && m_localPosition.z == z) {
		return;
	}
	m_localPosition.x = x, m_localPosition.y = y, m_localPosition.z = z;
	_setLocalDirty();
	m_viewDirty = true;
}
void CTransform::setLocalAngle(float x, float y, float z) {
	if (m_localAngle.x == x && m_localAngle.y == y && m_localAngle.z == z) {
		return;
	}
	m_localAngle.x = x, m_localAngle.y = y, m_localAngle.z = z;
	_setLocalDirty();
	m_viewDirty = true;
}
void CTransform::setLocalScale(float x, float y, float z) {
	if (m_localScale.x == x && m_localScale.y == y && m_localScale.z == z) {
		return;
	}
	m_localScale.x = x, m_localScale.y = y, m_localScale.z = z;
	_setLocalDirty();
}
void CTransform::setLocalUpDir(float x, float y, float z) {
	if (m_localUpDir.x == x && m_localUpDir.y == y && m_localUpDir.z == z) {
		return;
	}
	m_localUpDir.x = x, m_localUpDir.y = y, m_localUpDir.z = z;
	m_localUpDir = glm::normalize(m_localUpDir);
	_setLocalDirty();
	m_viewDirty = true;
}
void CTransform::setLocalFrontDir(float x, float y, float z) {
	if (m_localFrontDir.x == x && m_localFrontDir.y == y && m_localFrontDir.z == z) {
		return;
	}
	m_localFrontDir.x = x, m_localFrontDir.y = y, m_localFrontDir.z = z;
	m_localFrontDir = glm::normalize(m_localFrontDir);
	_setLocalDirty();
	m_viewDirty = true;
}

//ȫ�ֻ�ȡ������Ϣ
glm::vec3 CTransform::getPosition() {
	//todo
	return m_localPosition;
}
glm::vec3 CTransform::getAngle() {
	//todo
	return m_localAngle;
}
glm::vec3 CTransform::getScale() {
	//todo
	return m_localScale;
}

//�ֲ���ȡģ�;���
glm::mat4 CTransform::getLocalModelMatrix() {
	//�����ţ�����תY��X��Z����ƽ��
	if (m_localModelDirty) {
		//λ��
		m_localModelMatrix = glm::translate(m_localModelMatrix, m_localPosition);
		//m_localModelMatrix = glm::rotate(m_localModelMatrix, glm::radians(m_localAngle.z), glm::vec3(0.0f, 0.0f, 1.0f));
		//m_localModelMatrix = glm::rotate(m_localModelMatrix, glm::radians(m_localAngle.x), glm::vec3(1.0f, 0.0f, 0.0f));
		//m_localModelMatrix = glm::rotate(m_localModelMatrix, glm::radians(m_localAngle.y), glm::vec3(0.0f, 1.0f, 0.0f));
		//��ת
		glm::vec3 right = glm::normalize(glm::cross(m_localUpDir, m_localFrontDir));
		glm::vec3 up = glm::normalize(glm::cross(m_localFrontDir, right));
		glm::vec3 front = m_localFrontDir;

		glm::mat4 trans(
			right.x, right.y, right.z, 0.0f,
			up.x, up.y, up.z, 0.0f,
			front.x, front.y, front.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		m_localModelMatrix = m_localModelMatrix * trans;
		//����
		m_localModelMatrix = glm::scale(m_localModelMatrix, m_localScale);

		m_localModelDirty = false;
	}
	return m_localModelMatrix;
}
//ȫ�ֻ�ȡģ�;���
glm::mat4 CTransform::getModelMatrix() {
	if (m_modelDirty) {
		getLocalModelMatrix();
		if (parent != nullptr) {
			m_modelMatrix = parent->getModelMatrix() * m_localModelMatrix;
		}
		else {
			m_modelMatrix = m_localModelMatrix;
		}
		m_modelDirty = false;
	}
	return m_modelMatrix;
}

//�ֲ�ģ�;������
void CTransform::_setLocalDirty() {
	//����ֲ�����
	m_localModelDirty = true;
	//����ȫ�ֱ���
	for (auto it : children) {
		it->_setDirty();
	}
}
//ȫ��ģ�;������
void CTransform::_setDirty() {
	//����ȫ�ֱ���
	m_modelDirty = true;
	//����ȫ�ֱ���
	for (auto it : children) {
		it->_setDirty();
	}
}

//��ȡ��ͼ����
glm::mat4 CTransform::getViewMatrrix() {
	if (m_viewDirty) {
		m_viewMatrix = glm::lookAt(m_localPosition, m_localPosition + m_localFrontDir, m_localUpDir);
		m_viewDirty = false;
	}
	return m_viewMatrix;
}
