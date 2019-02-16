#pragma once
#include "RCommon.h"
#include "ISystem.h"

class CCamera;
class CRender;
class CLight;
class CTransform;
class Material;
class RScene;
class RFramebuffer {
public:
	RFramebuffer() {
		glGenFramebuffers(1, &fbo);
		glGenTextures(1, &colorTex);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glBindTexture(GL_TEXTURE_2D, colorTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, DEFAULT_WIDTH, DEFAULT_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTex, 0);
	}
	~RFramebuffer() {
		glDeleteFramebuffers(1, &fbo);
		glDeleteTextures(1, &colorTex);
	}
	RUInt fbo;
	RUInt colorTex;
};

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
	void _preRender(CCamera* camera, RScene* pSce);
	//����Ⱦ
	void _mainRender(CCamera* camera, RScene* pSce);
	//����Ⱦ
	void _postRender(CCamera* camera);
	//������Ⱦ����
	void _render();

	//����uniform����
	void _updateUniforms(CRender* pRender, CCamera* camera, CTransform* tran, std::list<CLight*> lights);

	//���¹�Դ��ص�uniform����
	void _updateLightsUniforms(Material* pMat, std::list<CLight*> lights);

	//vao���󹩺���ʹ��
	RUInt m_rectVAO;

	//texture������
	RUInt m_texCounter{ 0 };
	//texture������
	RUInt _allocTexture();
	//texture������״̬����
	void _resetTexAlloc();

	//framebuffer��
	std::vector<RFramebuffer*> m_framebufferPool;
	//ȡ��һ��framebuffer
	RFramebuffer* _popFramebuffer();
	//�����framebuffer���·���buffer��
	void _pushFramebuffer(RFramebuffer* pf);
};