#include "pch.h"
#include "BaseBehavior.h"

BaseBehavior::BaseBehavior() {

}
BaseBehavior::~BaseBehavior() {

}

//������������һִ֡��
void BaseBehavior::onStart() {

}

//ÿִ֡��
void BaseBehavior::onUpdate() {

}

//ÿִ֡�У���onUpdate֮��
void BaseBehavior::onLateUpdate() {

}

//��ײʱִ��
void BaseBehavior::onCollide() {

}

void BaseBehavior::update() {
	if (!m_started) {
		onStart();
		m_started = true;
	}
	onUpdate();
}
void BaseBehavior::lateUpdate() {
	onLateUpdate();
}

