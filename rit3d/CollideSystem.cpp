#include "pch.h"
#include "CollideSystem.h"
#include "CCollider.h"

CollideSystem::CollideSystem(RInt od) : ISystem(od) {
	m_type = COLLIDESYSTEM;
}

CollideSystem::~CollideSystem() {

}

CollideSystem* CollideSystem::CreateInstance(RInt od) {
	return new CollideSystem(od);
}

//ϵͳ��ʼ��ʱ����
void CollideSystem::onAwake() {

}

//ϵͳ������ʱ����
void CollideSystem::onEnable() {

}

//ϵͳ��ʼ����ʱ����
void CollideSystem::onStart() {

}

//ʵ�屻��ӵ�ϵͳʱ����
void CollideSystem::onAddGameObject() {

}

//�����ӵ�ʵ��ʱ����
void CollideSystem::onAddComponent(COMPTYPE type, IComponent* pComp) {

}

//�����ʵ���Ƴ�ʱ����
void CollideSystem::onRemoveComponent(COMPTYPE type, IComponent* pComp) {

}

//ʵ���ϵͳ���Ƴ�ʱ����
void CollideSystem::onRemoveGameObject() {

}

//ϵͳ����ʱ����
void CollideSystem::onUpdate() {

}

//ϵͳ����ʱonUpdate֮�����
void CollideSystem::onLateUpdate() {

}

//ϵͳ������ʱ����
void CollideSystem::onDisable() {

}

//ϵͳ��ע��ʱ����
void CollideSystem::onDestroy() {

}