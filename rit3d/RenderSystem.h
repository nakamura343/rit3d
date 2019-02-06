#pragma once
#include "RCommon.h"
#include "ISystem.h"
#include "Material.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CLight.h"
#include "RScene.h"
#include "CRender.h"

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
	//Ԥ��Ⱦ
	void _preRender(RScene* pSce);
	//����Ⱦ
	void _mainRender(CCamera* camera, RScene* pSce);
	//����Ⱦ
	void _postRender();
	//������Ⱦ����
	void _render();

	//����uniform����
	void _updateUniforms(CRender* pRender, CCamera* camera, CTransform* tran, std::list<CLight*> lights);

	//���¹�Դ��ص�uniform����
	void _updateLightsUniforms(Material* pMat, std::list<CLight*> lights);

	//texture������
	RUInt m_texCounter{ 0 };
	//texture������
	RUInt _allocTexture();
	//texture������״̬����
	void _resetTexAlloc();
};