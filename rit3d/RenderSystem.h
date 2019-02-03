#pragma once
#include "RCommon.h"
#include "ISystem.h"
#include "Material.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CLight.h"

class RenderSystem : public ISystem {
private:
	RenderSystem(RInt od);
	virtual ~RenderSystem();
public:
	static RenderSystem* CreateInstance(RInt);

	//ϵͳ��ʼ��ʱ����
	virtual void onAwake();

	//ϵͳ������ʱ����
	virtual void onEnable();

	//ϵͳ��ʼ����ʱ����
	virtual void onStart();

	//ʵ�屻��ӵ�ϵͳʱ����
	virtual void onAddGameObject();

	//�����ӵ�ʵ��ʱ����
	virtual void onAddComponent();

	//�����ʵ���Ƴ�ʱ����
	virtual void onRemoveComponent();

	//ʵ���ϵͳ���Ƴ�ʱ����
	virtual void onRemoveGameObject();

	//ϵͳ����ʱ����
	virtual void onUpdate();

	//ϵͳ����ʱonUpdate֮�����
	virtual void onLateUpdate();

	//ϵͳ������ʱ����
	virtual void onDisable();

	//ϵͳ��ע��ʱ����
	virtual void onDestroy();

private:
	//������Ⱦ����
	void _render();

	//����uniform����
	void _updateUniforms(Material* pMat, CCamera* camera, CTransform* tran, std::list<CLight*> lights);

	//���¹�Դ��ص�uniform����
	void _updateLightsUniforms(Material* pMat, std::list<CLight*> lights);
};