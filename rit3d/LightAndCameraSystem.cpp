#include "pch.h"
#include "LightAndCameraSystem.h"
#include "SCLightCameraCollecter.h"

LightAndCameraSystem::LightAndCameraSystem(RInt od) : ISystem(od) {
	m_type = LIGHTANDCAMERA;
}

LightAndCameraSystem::~LightAndCameraSystem() {

}

LightAndCameraSystem* LightAndCameraSystem::CreateInstance(RInt od) {
	return new LightAndCameraSystem(od);
}

//ϵͳ��ʼ��ʱ����
void LightAndCameraSystem::onAwake() {

}

//ϵͳ������ʱ����
void LightAndCameraSystem::onEnable() {

}

//ϵͳ��ʼ����ʱ����
void LightAndCameraSystem::onStart() {

}

//ʵ�屻��ӵ�ϵͳʱ����
void LightAndCameraSystem::onAddGameObject() {

}

//�����ӵ�ʵ��ʱ����
void LightAndCameraSystem::onAddComponent(COMPTYPE type, IComponent* pComp) {
	if (type == COMPTYPE::LIGHT) {
		SCLightCameraCollecter::Instance()->addLight((CLight*)pComp);
	}
	if (type == COMPTYPE::CAMERA) {
		SCLightCameraCollecter::Instance()->addCamera((CCamera*)pComp);
	}
}

//�����ʵ���Ƴ�ʱ����
void LightAndCameraSystem::onRemoveComponent(COMPTYPE type, IComponent* pComp) {
	if (type == COMPTYPE::LIGHT) {
		SCLightCameraCollecter::Instance()->removeLight((CLight*)pComp);
	}
	if (type == COMPTYPE::CAMERA) {
		SCLightCameraCollecter::Instance()->removeCamera((CCamera*)pComp);
	}
}

//ʵ���ϵͳ���Ƴ�ʱ����
void LightAndCameraSystem::onRemoveGameObject() {

}

//ϵͳ����ʱ����
void LightAndCameraSystem::onUpdate() {

}

//ϵͳ����ʱonUpdate֮�����
void LightAndCameraSystem::onLateUpdate() {

}

//ϵͳ������ʱ����
void LightAndCameraSystem::onDisable() {

}

//ϵͳ��ע��ʱ����
void LightAndCameraSystem::onDestroy() {

}
