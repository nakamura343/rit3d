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

//���ڴ�С�ı�ʱִ��
void BaseBehavior::onChangeSize(int _w, int _h) {
	
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

