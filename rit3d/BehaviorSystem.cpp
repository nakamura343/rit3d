#include "pch.h"
#include "BehaviorSystem.h"
#include "CBehavior.h"
#include "BaseBehavior.h"

BehaviorSystem::BehaviorSystem(RInt od) : ISystem(od) {
	m_type = BEHAVIORSYSTEM;
}
BehaviorSystem::~BehaviorSystem() {

}

BehaviorSystem* BehaviorSystem::CreateInstance(RInt od) {
	return new BehaviorSystem(od);
}

//ϵͳ��ʼ��ʱ����
void BehaviorSystem::onAwake() {

}

//ϵͳ������ʱ����
void BehaviorSystem::onEnable() {

}

//ϵͳ��ʼ����ʱ����
void BehaviorSystem::onStart() {

}

//ʵ�屻��ӵ�ϵͳʱ����
void BehaviorSystem::onAddGameObject() {

}

//�����ӵ�ʵ��ʱ����
void BehaviorSystem::onAddComponent() {

}

//�����ʵ���Ƴ�ʱ����
void BehaviorSystem::onRemoveComponent() {

}

//ʵ���ϵͳ���Ƴ�ʱ����
void BehaviorSystem::onRemoveGameObject() {

}

//ϵͳ����ʱ����
void BehaviorSystem::onUpdate() {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->update();
	}
}

//ϵͳ����ʱonUpdate֮�����
void BehaviorSystem::onLateUpdate() {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->lateUpdate();
	}
}

//ϵͳ������ʱ����
void BehaviorSystem::onDisable() {

}

//ϵͳ��ע��ʱ����
void BehaviorSystem::onDestroy() {

}

void BehaviorSystem::addBehavior(CBehavior* _b) {
	std::vector<CBehavior*>::iterator iter;
	iter = std::find(m_behaviorPool.begin(), m_behaviorPool.end(), _b);
	if (iter == m_behaviorPool.end()) {
		m_behaviorPool.push_back(_b);
	}
}

void BehaviorSystem::removeBehavior(CBehavior* _b) {
	std::vector<CBehavior*>::iterator iter;
	iter = std::find(m_behaviorPool.begin(), m_behaviorPool.end(), _b);
	if (iter != m_behaviorPool.end()) {
		m_behaviorPool.erase(iter);
	}
}