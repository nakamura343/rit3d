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
void Application::runRit3d(RString _title, int _w, int _h) {
	if (m_isRunning) {
		return;
	}
	//����汾��Ϣ
	cout << "current version: " << m_version << endl;
	//��������
	m_window = new RWindow(_title, 0, 0, _w, _h);

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
	systemMng->registSystem(BEHAVIORSYSTEM, 2);
	systemMng->registSystem(RENDERSYSTEM, 3);

	//��ȡ���ڻ���
	GLFWwindow* wd = m_window->getWindowContext();
	glfwSetKeyCallback(wd, Application::_key_callback);
	glfwSetFramebufferSizeCallback(wd, Application::_framebuffer_size_callback);
	glfwSetMouseButtonCallback(wd, Application::_mouse_button_callback);
	glfwSetCursorPosCallback(wd, Application::_cursor_position_callback);
	glfwSetScrollCallback(wd, Application::_scroll_callback);
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

//���ڴ�С�仯ʱ�ص�����
void Application::_framebuffer_size_callback(GLFWwindow* window, int w, int h) {
	SystemManager::Instance()->onChangeSize(w, h);
}
//��갴���ص�����
void Application::_mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			//�������
			SystemManager::Instance()->onLeftButtonDown();
		}
		else if (action == GLFW_RELEASE) {
			//���̧��
			SystemManager::Instance()->onLeftButtonUp();
		}
		else {

		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			//�Ҽ�����
			SystemManager::Instance()->onRightButtonDown();
		}
		else if (action == GLFW_RELEASE) {
			//�Ҽ�̧��
			SystemManager::Instance()->onRightButtonUp();
		}
		else {

		}
	}
	else {

	}
}
//���λ�ûص�
void Application::_cursor_position_callback(GLFWwindow* window, double x, double y) {
	SystemManager::Instance()->onMouseMove(x, y);
}
//�����ֻص�
void Application::_scroll_callback(GLFWwindow* window, double x, double y) {
	SystemManager::Instance()->onScroll(x, y);
}
//���̰����ص�
void Application::_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (action)
	{
	case GLFW_PRESS:
		SystemManager::Instance()->onKeyDown(key);
		break;
	case GLFW_RELEASE:
		SystemManager::Instance()->onKeyUp(key);
		break;
	case GLFW_REPEAT:
		SystemManager::Instance()->onKeyKeep(key);
		break;
	default:
		break;
	}
}
