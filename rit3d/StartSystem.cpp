#include "pch.h"
#include "ISystem.h"

StartSystem::StartSystem(RInt od) : ISystem(od) {
	m_type = STARTSYSTEM;
}
StartSystem::~StartSystem() {

}

StartSystem* StartSystem::CreateInstance(RInt od) {
	return new StartSystem(od);
}

//ϵͳ��ʼ��ʱ����
void StartSystem::onAwake() {

}

//ϵͳ������ʱ����
void StartSystem::onEnable() {

}

//ϵͳ��ʼ����ʱ����
void StartSystem::onStart() {

}

//ʵ�屻��ӵ�ϵͳʱ����
void StartSystem::onAddGameObject() {

}

//�����ӵ�ʵ��ʱ����
void StartSystem::onAddComponent(COMPTYPE type, IComponent* pComp) {

}

//�����ʵ���Ƴ�ʱ����
void StartSystem::onRemoveComponent(COMPTYPE type, IComponent* pComp) {

}

//ʵ���ϵͳ���Ƴ�ʱ����
void StartSystem::onRemoveGameObject() {

}

//ϵͳ����ʱ����
void StartSystem::onUpdate(DWORD deltaT) {
	
}

//ϵͳ����ʱonUpdate֮�����
void StartSystem::onLateUpdate() {

}

//ϵͳ������ʱ����
void StartSystem::onDisable() {

}

//ϵͳ��ע��ʱ����
void StartSystem::onDestroy() {

}