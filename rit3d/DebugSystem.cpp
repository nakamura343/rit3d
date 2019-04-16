#include "pch.h"
#include "DebugSystem.h"


DebugSystem::DebugSystem(RInt od) : ISystem(od) {
	m_type = DEBUGSYSTEM;
}


DebugSystem::~DebugSystem() {

}

DebugSystem* DebugSystem::CreateInstance(RInt od) {
	return new DebugSystem(od);
}

//ϵͳ��ʼ��ʱ����
void DebugSystem::onAwake() {

}

//ϵͳ������ʱ����
void DebugSystem::onEnable() {

}

//ϵͳ��ʼ����ʱ����
void DebugSystem::onStart() {

}

//ʵ�屻��ӵ�ϵͳʱ����
void DebugSystem::onAddGameObject() {

}

//�����ӵ�ʵ��ʱ����
void DebugSystem::onAddComponent(COMPTYPE type, IComponent* pComp) {

}

//�����ʵ���Ƴ�ʱ����
void DebugSystem::onRemoveComponent(COMPTYPE type, IComponent* pComp) {

}

//ʵ���ϵͳ���Ƴ�ʱ����
void DebugSystem::onRemoveGameObject() {

}

//ϵͳ����ʱ����
void DebugSystem::onUpdate(DWORD deltaT) {
	m_fps.update();
}

//ϵͳ����ʱonUpdate֮�����
void DebugSystem::onLateUpdate() {

}

//ϵͳ������ʱ����
void DebugSystem::onDisable() {

}

//ϵͳ��ע��ʱ����
void DebugSystem::onDestroy() {

}
