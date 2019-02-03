#include "pch.h"
#include "IComponent.h"
#include "RGameObject.h"


IComponent::IComponent() {

}


IComponent::~IComponent() {

}

//�����������Ĵ�������������ʵ�ַ������
std::map<COMPTYPE, std::function<IComponent*()>> IComponent::compMap;

//����ϵͳʵ��������ϵͳʵ��ͨ���˷�������
IComponent* IComponent::CreateComponent(COMPTYPE type) {
	IComponent* comp = compMap[type]();
	return comp;
}

//��ȡϵͳ����
COMPTYPE IComponent::getType() const {
	return m_type;
}

//�Ƿ�������ͬһʵ������Ӷ���������ʵ��
RBool IComponent::allowMultiple() const {
	return m_allowMultiple;
}

//�Ƿ����
RBool IComponent::isEnabled() const {
	return m_enabled;
}
//���ÿ���״̬
void IComponent::setEnabled(RBool value) {
	if (m_enabled == value) {
		return;
	}

	m_enabled = value;
}
//�Ƿ񼤻��ҿ���
RBool IComponent::isActiveAndEnabled() const {
	return m_enabled && gameObject->isActive();
}
