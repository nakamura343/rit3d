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
	
}//����¼�
void BaseBehavior::onLeftButtonDown() {}
void BaseBehavior::onLeftButtonUp() {}
void BaseBehavior::onRightButtonDown() {}
void BaseBehavior::onRightButtonUp() {}
void BaseBehavior::onMouseMove(double _x, double _y) {}
void BaseBehavior::onScroll(double _x, double _y) {}
//�����¼�
void BaseBehavior::onKeyDown(int key) {}
void BaseBehavior::onKeyKeep(int key) {}
void BaseBehavior::onKeyUp(int key) {}


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

