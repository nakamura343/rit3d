#pragma once

#include "RCommon.h"
#include "RWindow.h"
#include "SystemManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CRender.h"
#include "fps.h"
#include "CPostProcess.h"
#include "CSkybox.h"

/*
 * Ӧ�õ�����
 */
class Application {
public:
	static Application *Instance();
private:
	Application();
	virtual ~Application() {};

private:
	static Application *m_instance;

	const RString m_version = "0.0.1";

	RBool m_isRunning{ false };

	RWindow* m_window{ nullptr };

	//��Ϸ��ں���������ѭ��ǰ��Ԥ�༭����Ϸ��������Ҫʵ�ִ˺���
	std::function<void()> m_gameEntry;

	//fps����
	FPS m_fps;

public:
	//ϵͳ������
	SystemManager* systemMng{ nullptr };
	//����������
	SceneManager* sceneMng{ nullptr };
	//��Դ������
	ResourceManager* resourceMng{ nullptr };
	//�������
	void runRit3d();
	//������Ϸ��ں���
	void setGameEntry(std::function<void()> _gameEntry);
	//��ʾfps
	void showFPS();
	//����fps
	void hideFPS();
private:
	//�����ʼ��
	void _initApp();
	//��������
	void _updateApp();
};


