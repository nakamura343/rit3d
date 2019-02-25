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

//���ڴ�С�ı�ʱִ��
void BehaviorSystem::onChangeSize(int _w, int _h) {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onChangeSize(_w, _h);
	}
}

//����¼�
void BehaviorSystem::onLeftButtonDown() {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onLeftButtonDown();
	}
}
void BehaviorSystem::onLeftButtonUp() {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onLeftButtonUp();
	}
}
void BehaviorSystem::onRightButtonDown() {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onRightButtonDown();
	}
}
void BehaviorSystem::onRightButtonUp() {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onRightButtonUp();
	}
}
void BehaviorSystem::onMouseMove(double _x, double _y) {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onMouseMove(_x, _y);
	}
}
void BehaviorSystem::onScroll(double _x, double _y) {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onScroll(_x, _y);
	}
}
//�����¼�
void BehaviorSystem::onKeyDown(int key) {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onKeyDown(key);
	}
}
void BehaviorSystem::onKeyKeep(int key) {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onKeyKeep(key);
	}
}
void BehaviorSystem::onKeyUp(int key) {
	for (auto iter : m_behaviorPool) {
		iter->getBehavior()->onKeyUp(key);
	}
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
