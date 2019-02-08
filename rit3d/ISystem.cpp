#include "pch.h"
#include "ISystem.h"

ISystem::ISystem(RInt od) {
	////������ֱ��newһ��ʵ������
	//if (!ISystem::CreateEnable) {
	//	cout << "Create an instance of a system is not allowed!" << endl;
	//}
	//ISystem::CreateEnable = false;

	this->order = od;
}
ISystem::~ISystem() {
	
}

//RBool ISystem::CreateEnable = false;
//�������ϵͳ�Ĵ�������������ʵ�ַ������
std::map<SYSTEMTYPE, std::function<ISystem*(RUInt)>> ISystem::systemMap;

//����ϵͳʵ��������ϵͳʵ��ͨ���˷�������
ISystem* ISystem::CreateSystem(SYSTEMTYPE type, RInt od) {
	ISystem* st = ISystem::systemMap[type](od);
	return st;
}

//��ʼ��ϵͳ
void ISystem::initSystem() {
	onAwake();
}

//ж��ϵͳ
void ISystem::uninitSystem() {

}

//ϵͳ����
void ISystem::update() {
	this->onUpdate();
}

//ϵͳ����2
void ISystem::lateUpdate() {
	this->onLateUpdate();
}

//����ϵͳ�Ƿ񱻼���
RBool ISystem::isEnabled() const {
	return enabled;
}

void ISystem::setEnable(RBool value) {
	if (enabled == value) {
		return;
	}

	enabled = value;

	if (enabled) {
		onEnable();
	}
	else {
		onDisable();
	}
}

//��ȡϵͳ����
SYSTEMTYPE ISystem::getType() const {
	return m_type;
}

RBool ISystem::isStarted() const {
	return m_started;
}

void ISystem::setStarted(RBool value) {
	m_started = value;
}
