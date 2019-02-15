#include "pch.h"
#include "Application.h"
#include "RWindow.h"
#include "SystemManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GLProgram.h"
#include "CPostProcess.h"
#include "CSkybox.h"

Application::Application() {
};

Application* Application::m_instance = nullptr;

Application* Application::Instance() {
	if (nullptr == m_instance) {
		m_instance = new Application();
	}
	return m_instance;
}

//�������
void Application::runRit3d() {
	if (m_isRunning) {
		return;
	}
	//����汾��Ϣ
	cout << "current version: " << m_version << endl;
	//��������
	m_window = new RWindow();
	//if (m_window == nullptr || m_window->getWindowContext() == nullptr) {
	//	cout << "application startup failed" << endl;
	//	return;
	//}

	GLFWwindow* wd = m_window->getWindowContext();

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		cout << "application startup failed" << endl;
		return;
	}

	//�����ʼ��
	_initApp();
	//��Ϸ��ڣ�Ԥ�༭��
	m_gameEntry();

	m_isRunning = true;
	cout << "application startup succeed" << endl;

	//��ѭ��
	while (!m_window->RWindowShouldClose())
	{
		//��Ⱦ�߼�
		_updateApp();

		//swap buffers
		m_window->swapBuffer();
		//poll IO events(keys pressed / released, mouse moved etc.)
		m_window->pollEvents();
	}
	//ɾ��VAO,VBO

	m_window->destroy();
	m_isRunning = false;
	return;
}

//��ʾfps
void Application::showFPS() {
	m_fps.show();
}
//����fps
void Application::hideFPS() {
	m_fps.hide();
}

//�����ʼ��
void Application::_initApp() {
	//��ʼ��ϵͳ������
	systemMng = SystemManager::Instance();
	//��ʼ������������
	sceneMng = SceneManager::Instance();
	//��ʼ����Դ������
	resourceMng = ResourceManager::Instance();
	//����Ĭ����Դ
	resourceMng->createDefaultMesh();
	resourceMng->createDefaultMaterial();
	resourceMng->createDefaultShader();
	//ע���Ҫϵͳ
	systemMng->registSystem(STARTSYSTEM, 1);
	systemMng->registSystem(RENDERSYSTEM, 2);
}
//��������
void Application::_updateApp() {
	if (m_fps.isShowed()) {
		m_fps.update();
	}
	systemMng->update();
}

//������Ϸ��ں���
void Application::setGameEntry(std::function<void()> _gameEntry) {
	m_gameEntry = _gameEntry;
}
