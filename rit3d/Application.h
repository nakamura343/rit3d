#pragma once

#include "RCommon.h"
#include "fps.h"

class SystemManager;
class SceneManager;
class ResourceManager;
class RWindow;
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
	void runRit3d(RString _title = "Rit3D", int _w = DEFAULT_WIDTH, int _h = DEFAULT_HEIGHT);
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
	//���ڴ�С�仯ʱ�ص�����
	static void _framebuffer_size_callback(GLFWwindow* window, int w, int h);
	//��갴���ص�����
	static void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	//���λ�ûص�
	static void _cursor_position_callback(GLFWwindow* window, double x, double y);
	//�����ֻص�
	static void _scroll_callback(GLFWwindow* window, double x, double y);
	//���̰����ص�
	static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};


