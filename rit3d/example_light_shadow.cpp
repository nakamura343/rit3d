#include "pch.h"
#include <iostream>
#include "declare.h"
#include <time.h>

class CameraScript : public BaseBehavior {
private:
	glm::vec3 lastPos;
	DWORD lastTime;
	bool isKeyDown{ false };
	bool isLeftButtonDown{ false };
	float lastX;
	float lastY;
public:
	float speed = 1.0f;//世界坐标单位长度/每秒
	float rotateSpeed = 1.0f / 100.0f * 0.3f;//弧度/100像素
	virtual void onChangeSize(int _w, int _h) {
		CCamera* camera = (CCamera*)gameObject->getComponent(COMPTYPE::CAMERA);
		if (camera != nullptr) {
			camera->setViewport(0, 0, _w, _h);
		}
	}
	virtual void onLeftButtonDown() {
		isLeftButtonDown = true;
	}
	virtual void onLeftButtonUp() {
		isLeftButtonDown = false;
	}
	virtual void onMouseMove(double _x, double _y) {
		if (isLeftButtonDown) {
			float deltaX = (lastX - static_cast<float>(_x)) * rotateSpeed;
			float deltaY = (lastY - static_cast<float>(_y)) * rotateSpeed;

			glm::vec3 front = gameObject->transform->getLocalFrontDir();
			glm::vec3 up = gameObject->transform->getLocalUpDir();
			glm::vec3 right = gameObject->transform->getLocalRightDir();

			front = front * cos(deltaY) + up * sin(deltaY);
			front = front * cos(deltaX) + right * sin(deltaX);
			gameObject->transform->setLocalFrontDir(front.x, front.y, front.z);

			lastX = static_cast<float>(_x);
			lastY = static_cast<float>(_y);
		}
		else {
			lastX = static_cast<float>(_x);
			lastY = static_cast<float>(_y);
		}
	}
	virtual void onScroll(double _x, double _y) {

	}
	virtual void onKeyDown(int key) {
	}
	virtual void onKeyKeep(int key) {
		if (!isKeyDown) {
			lastTime = ::GetTickCount();
			isKeyDown = true;
		}
		if (key == GLFW_KEY_W) {
			lastPos = gameObject->transform->getLocalPosition();
			DWORD now = ::GetTickCount();
			DWORD deltaTime = now - lastTime;
			lastTime = now;
			float deltaZ = deltaTime / 1000.0f * speed;
			glm::vec3 newPos = lastPos + deltaZ * gameObject->transform->getLocalFrontDir();
			gameObject->transform->setLocalPosition(newPos.x, newPos.y, newPos.z);
		}
		else if (key == GLFW_KEY_S) {
			lastPos = gameObject->transform->getLocalPosition();
			DWORD now = ::GetTickCount();
			DWORD deltaTime = now - lastTime;
			lastTime = now;
			float deltaZ = deltaTime / 1000.0f * speed;
			glm::vec3 newPos = lastPos - deltaZ * gameObject->transform->getLocalFrontDir();
			gameObject->transform->setLocalPosition(newPos.x, newPos.y, newPos.z);
		}
		else if (key == GLFW_KEY_A) {
			lastPos = gameObject->transform->getLocalPosition();
			DWORD now = ::GetTickCount();
			DWORD deltaTime = now - lastTime;
			lastTime = now;
			float deltaZ = deltaTime / 1000.0f * speed;
			glm::vec3 newPos = lastPos + deltaZ * gameObject->transform->getLocalRightDir();
			gameObject->transform->setLocalPosition(newPos.x, newPos.y, newPos.z);
		}
		else if (key == GLFW_KEY_D) {
			lastPos = gameObject->transform->getLocalPosition();
			DWORD now = ::GetTickCount();
			DWORD deltaTime = now - lastTime;
			lastTime = now;
			float deltaZ = deltaTime / 1000.0f * speed;
			glm::vec3 newPos = lastPos - deltaZ * gameObject->transform->getLocalRightDir();
			gameObject->transform->setLocalPosition(newPos.x, newPos.y, newPos.z);
		}
	}
	virtual void onKeyUp(int key) {
		isKeyDown = false;
	}
};
class TestScript : public BaseBehavior {

private:
	DWORD startTime;
	float speed{ 1.0f };
public:
	virtual void onStart() {
		startTime = ::GetTickCount();
	}
	virtual void onUpdate() {
		DWORD delta = ::GetTickCount() - startTime;
		float angle = (float)delta / 1000.0f * speed;
		gameObject->transform->setLocalFrontDir(sin(angle), 0.0f, cos(angle));
	}
	virtual void onLateUpdate() {
		//cout << "lateUpdate!" << endl;
	}
};
class RandomMove : public BaseBehavior {

private:
	DWORD startTime;
	float speed{ 0.8f };
public:
	virtual void onStart() {
		startTime = ::GetTickCount();
	}
	virtual void onUpdate() {
		DWORD delta = ::GetTickCount() - startTime;
		float dx = (rand() / (float)RAND_MAX - 0.5f) * speed;
		float dy = (rand() / (float)RAND_MAX - 0.5f) * speed;
		float dz = (rand() / (float)RAND_MAX - 0.5f) * speed;
		glm::vec3 oldPos = gameObject->transform->getLocalPosition();
		gameObject->transform->setLocalPosition(oldPos.x + dx, oldPos.y + dy, oldPos.y + dy);
	}
	virtual void onLateUpdate() {
		//cout << "lateUpdate!" << endl;
	}
};

/**
 *光照和阴影
 */
void example_light_shadow_1() {
	cout << "light and shadow" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	//纹理和材质
	Texture* tex1 = app->resourceMng->createTexture("resources/textures/container.jpg");
	Material* mat = app->resourceMng->createMaterial("mat1");
	mat->addTexture(tex1);
	mat->setShader("phong");

	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->setShader("phong");
	mat2->setColor(1.0f, 1.0f, 1.0f);

	//平面
	RGameObject* plane = pSce->addGameObject();
	plane->transform->setLocalScale(0.7f, 1.0f, 0.7f);
	CRender* planerender = (CRender*)plane->addComponent(RENDER);
	planerender->addMesh(app->resourceMng->getMesh("plane"));
	planerender->addMaterial(mat2);
	planerender->recieveShadow(true);
	//立方体
	RGameObject* cube = pSce->addGameObject();
	cube->transform->setLocalPosition(0.0f, 0.5f, 0.0f);
	cube->transform->setLocalScale(0.7f, 0.7f, 0.7f);
	cube->transform->setLocalFrontDir(0.2f, 0.0f, 0.9f);
	CRender* cuberender = (CRender*)cube->addComponent(RENDER);
	cuberender->addMesh(app->resourceMng->getMesh("cube"));
	cuberender->addMaterial(mat2);
	cuberender->castShadow(true);
	//球
	RGameObject* sphere = pSce->addGameObject();
	sphere->transform->setLocalPosition(-1.0f, 0.5f, 0.5f);
	sphere->transform->setLocalScale(0.7f, 0.7f, 0.7f);
	sphere->transform->setLocalFrontDir(1.0f, 0.0f, 0.0f);
	CRender* sphererender = (CRender*)sphere->addComponent(RENDER);
	sphererender->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender->addMaterial(mat2);
	sphererender->castShadow(true);

	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 4.0f, 6.0f);
	CO->transform->setLocalFrontDir(0.0f, -2.0f, -3.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());

	//平行光
	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, 0.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->castShadow(true);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);

	//点光源
	RGameObject* LO1 = pSce->addGameObject();
	LO1->transform->setLocalPosition(0.0f, 2.0f, 0.0f);
	LO1->transform->setLocalFrontDir(1.0f, -0.5f, 0.0f);
	LO1->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light1 = (CLight*)LO1->addComponent(COMPTYPE::LIGHT);
	light1->castShadow(true);
	light1->setIntensity(0.1f, 1.0f, 1.0f);
	light1->setColor(1.0f, 1.0f, 1.0f);
	light1->setLightType(LIGHTTYPE::LPOINT);

	//聚光灯
	RGameObject* LO2 = pSce->addGameObject();
	LO2->transform->setLocalPosition(2.0f, 3.0f, -1.0f);
	LO2->transform->setLocalFrontDir(-2.0f, -2.5f, 1.0f);
	LO2->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light2 = (CLight*)LO2->addComponent(COMPTYPE::LIGHT);
	light2->castShadow(true);
	light2->setIntensity(0.1f, 1.0f, 1.0f);
	light2->setColor(1.0f, 0.0f, 0.0f);
	light2->setCutOff(10, 15);
	light2->setLightType(LIGHTTYPE::SPOT);
}

/**
 *泛光
 */
void example_light_shadow_2() {
	cout << "bloom" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	//纹理和材质
	Material* mat = app->resourceMng->createMaterial("mat");
	mat->setShader("phong");
	mat->setColor(1.0f, 1.0f, 1.0f);

	Material* mat1 = app->resourceMng->createMaterial("mat1");
	mat1->setShader("simple");
	mat1->setColor(10.0f, 10.0f, 10.0f);
	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->setShader("simple");
	mat2->setColor(10.0f, 0.0f, 0.0f);

	//球
	RGameObject* sphere = pSce->addGameObject();
	sphere->transform->setLocalPosition(0.0f, 0.0f, 0.0f);
	sphere->transform->setLocalScale(1.0f, 1.0f, 1.0f);
	sphere->transform->setLocalFrontDir(1.0f, 0.0f, 0.0f);
	CRender* sphererender = (CRender*)sphere->addComponent(RENDER);
	sphererender->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender->addMaterial(mat);
	sphererender->castShadow(true);

	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 4.0f, 6.0f);
	CO->transform->setLocalFrontDir(0.0f, -2.0f, -3.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setBloom(2.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());


	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, 0.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->castShadow(true);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);

	RGameObject* LO1 = pSce->addGameObject();
	LO1->transform->setLocalPosition(0.0f, 2.0f, 0.0f);
	LO1->transform->setLocalFrontDir(1.0f, -0.5f, 0.0f);
	LO1->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	LO1->transform->setLocalScale(0.2f, 0.2f, 0.2f);
	CLight* light1 = (CLight*)LO1->addComponent(COMPTYPE::LIGHT);
	light1->castShadow(true);
	light1->setIntensity(0.1f, 1.0f, 1.0f);
	light1->setColor(1.0f, 1.0f, 1.0f);
	light1->setLightType(LIGHTTYPE::LPOINT);
	CRender* lo1render = (CRender*)LO1->addComponent(RENDER);
	lo1render->addMesh(app->resourceMng->getMesh("sphere"));
	lo1render->addMaterial(mat1);

	RGameObject* LO2 = pSce->addGameObject();
	LO2->transform->setLocalPosition(1.6f, 2.4f, -0.8f);
	LO2->transform->setLocalFrontDir(-2.0f, -2.5f, 1.0f);
	LO2->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	LO2->transform->setLocalScale(0.2f, 0.2f, 0.2f);
	CLight* light2 = (CLight*)LO2->addComponent(COMPTYPE::LIGHT);
	light2->castShadow(true);
	light2->setIntensity(0.1f, 1.0f, 1.0f);
	light2->setColor(1.0f, 0.0f, 0.0f);
	light2->setCutOff(10, 15);
	light2->setLightType(LIGHTTYPE::SPOT);
	CRender* lo2render = (CRender*)LO2->addComponent(RENDER);
	lo2render->addMesh(app->resourceMng->getMesh("sphere"));
	lo2render->addMaterial(mat2);
}

/**
 *pbr材质
 */
void example_light_shadow_3() {
	cout << "pbr" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	//创建纹理
	Texture* tex0 = app->resourceMng->createTexture("resources/textures/rustediron2_basecolor.png");
	Texture* tex1 = app->resourceMng->createTexture("resources/textures/rustediron2_metallic.png");
	Texture* tex2 = app->resourceMng->createTexture("resources/textures/rustediron2_roughness.png");
	Texture* tex3 = app->resourceMng->createTexture("resources/textures/brickwall.jpg");
	Texture* tex4 = app->resourceMng->createTexture("resources/textures/brickwall_normal.jpg");
	Texture* tex5 = app->resourceMng->createTexture("resources/textures/copper-rock1-alb.png");
	Texture* tex6 = app->resourceMng->createTexture("resources/textures/copper-rock1-metal.png");
	Texture* tex7 = app->resourceMng->createTexture("resources/textures/copper-rock1-rough.png");
	Texture* tex8 = app->resourceMng->createTexture("resources/textures/copper-rock1-normal.png");
	Texture* tex9 = app->resourceMng->createTexture("resources/textures/copper-rock1-ao.png");
	Texture* tex10 = app->resourceMng->createTexture("resources/textures/greasy-pan-2-albedo.png");
	Texture* tex11 = app->resourceMng->createTexture("resources/textures/greasy-pan-2-metal.png");
	Texture* tex12 = app->resourceMng->createTexture("resources/textures/greasy-pan-2-roughness.png");
	Texture* tex13 = app->resourceMng->createTexture("resources/textures/greasy-pan-2-normal.png");
	Texture* tex14 = app->resourceMng->createTexture("resources/textures/chipped-paint-metal-albedo.png");
	Texture* tex15 = app->resourceMng->createTexture("resources/textures/chipped-paint-metal-metal.png");
	Texture* tex16 = app->resourceMng->createTexture("resources/textures/chipped-paint-metal-rough2.png");
	Texture* tex17 = app->resourceMng->createTexture("resources/textures/chipped-paint-metal-normal-dx.png");
	Texture* tex18 = app->resourceMng->createTexture("resources/textures/chipped-paint-ao.png");
	Texture* tex19 = app->resourceMng->createTexture("resources/textures/streakedmetal-albedo.png");
	Texture* tex20 = app->resourceMng->createTexture("resources/textures/streakedmetal-metalness.png");
	Texture* tex21 = app->resourceMng->createTexture("resources/textures/streakedmetal-roughness.png");

	//创建材质
	Material* mat1 = app->resourceMng->createMaterial("mat1");
	mat1->setShader("pbr");
	mat1->setColor(0.5, 0.0f, 0.0);
	mat1->addTexture(tex0);
	mat1->addTexture(tex1);
	mat1->addTexture(tex2);

	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->addTexture(tex3);
	mat2->setShader("pbr");
	mat2->setNormalMap(tex4);
	mat2->setMetallic(0.0f);
	mat2->setRoughness(0.8f);

	Material* mat3 = app->resourceMng->createMaterial("mat3");
	mat3->setShader("pbr");
	mat3->addTexture(tex5);
	mat3->addTexture(tex6);
	mat3->addTexture(tex7);
	mat3->addTexture(tex9);
	mat3->setNormalMap(tex8);

	Material* mat4 = app->resourceMng->createMaterial("mat4");
	mat4->setShader("pbr");
	mat4->addTexture(tex10);
	mat4->addTexture(tex11);
	mat4->addTexture(tex12);
	mat4->setNormalMap(tex13);

	Material* mat5 = app->resourceMng->createMaterial("mat5");
	mat5->setShader("pbr");
	mat5->addTexture(tex14);
	mat5->addTexture(tex15);
	mat5->addTexture(tex16);
	mat5->addTexture(tex18);
	mat5->setNormalMap(tex17);

	Material* mat6 = app->resourceMng->createMaterial("mat6");
	mat6->setShader("pbr");
	mat6->addTexture(tex19);
	mat6->addTexture(tex20);
	mat6->addTexture(tex21);

	//球1：生锈铁球
	RGameObject* sphere1 = pSce->addGameObject();
	sphere1->transform->setLocalPosition(-1.5f, 1.0f, 0.0f);
	CRender* sphererender1 = (CRender*)sphere1->addComponent(RENDER);
	sphererender1->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender1->addMaterial(mat1);
	sphererender1->castShadow(false);
	CBehavior* sphereBehavior1 = (CBehavior*)sphere1->addComponent(BEHAVIOR);
	sphereBehavior1->setBehavior(new TestScript());

	//球2：砖墙贴图
	RGameObject* sphere2 = pSce->addGameObject();
	sphere2->transform->setLocalPosition(-.0f, 1.0f, 0.0f);
	CRender* sphererender2 = (CRender*)sphere2->addComponent(RENDER);
	sphererender2->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender2->addMaterial(mat2);
	sphererender2->castShadow(false);
	CBehavior* sphereBehavior2 = (CBehavior*)sphere2->addComponent(BEHAVIOR);
	sphereBehavior2->setBehavior(new TestScript());

	//球3：金属石头
	RGameObject* sphere3 = pSce->addGameObject();
	sphere3->transform->setLocalPosition(1.5f, 1.0f, 0.0f);
	CRender* sphererender3 = (CRender*)sphere3->addComponent(RENDER);
	sphererender3->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender3->addMaterial(mat3);
	sphererender3->castShadow(false);
	CBehavior* sphereBehavior3 = (CBehavior*)sphere3->addComponent(BEHAVIOR);
	sphereBehavior3->setBehavior(new TestScript());

	//球4
	RGameObject* sphere4 = pSce->addGameObject();
	sphere4->transform->setLocalPosition(-1.5f, -1.0f, 0.0f);
	CRender* sphererender4 = (CRender*)sphere4->addComponent(RENDER);
	sphererender4->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender4->addMaterial(mat4);
	sphererender4->castShadow(false);
	CBehavior* sphereBehavior4 = (CBehavior*)sphere4->addComponent(BEHAVIOR);
	sphereBehavior4->setBehavior(new TestScript());

	//球5
	RGameObject* sphere5 = pSce->addGameObject();
	sphere5->transform->setLocalPosition(0.0f, -1.0f, 0.0f);
	CRender* sphererender5 = (CRender*)sphere5->addComponent(RENDER);
	sphererender5->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender5->addMaterial(mat5);
	sphererender5->castShadow(false);
	CBehavior* sphereBehavior5 = (CBehavior*)sphere5->addComponent(BEHAVIOR);
	sphereBehavior5->setBehavior(new TestScript());

	//球6
	RGameObject* sphere6 = pSce->addGameObject();
	sphere6->transform->setLocalPosition(1.5f, -1.0f, 0.0f);
	CRender* sphererender6 = (CRender*)sphere6->addComponent(RENDER);
	sphererender6->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender6->addMaterial(mat6);
	sphererender6->castShadow(false);
	CBehavior* sphereBehavior6 = (CBehavior*)sphere6->addComponent(BEHAVIOR);
	sphereBehavior6->setBehavior(new TestScript());



	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 0.0f, 5.0f);
	CO->transform->setLocalFrontDir(0.0f, 0.0f, -1.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->backgroundColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());

	//四个点光源
	RGameObject* LO1 = pSce->addGameObject();
	LO1->transform->setLocalPosition(-5.0, 5.0f, 5.0f);
	CLight* light1 = (CLight*)LO1->addComponent(COMPTYPE::LIGHT);
	light1->castShadow(false);
	light1->setColor(300.0f, 300.0f, 300.0f);
	light1->setLightType(LIGHTTYPE::LPOINT);

	RGameObject* LO2 = pSce->addGameObject();
	LO2->transform->setLocalPosition(5.0, 5.0f, 5.0f);
	CLight* light2 = (CLight*)LO2->addComponent(COMPTYPE::LIGHT);
	light2->castShadow(false);
	light2->setColor(300.0f, 300.0f, 300.0f);
	light2->setLightType(LIGHTTYPE::LPOINT);

	RGameObject* LO3 = pSce->addGameObject();
	LO3->transform->setLocalPosition(-5.0, -5.0f, 5.0f);
	CLight* light3 = (CLight*)LO3->addComponent(COMPTYPE::LIGHT);
	light3->castShadow(false);
	light3->setColor(300.0f, 300.0f, 300.0f);
	light3->setLightType(LIGHTTYPE::LPOINT);
}

/**
 *法线贴图
 */
void example_light_shadow_4() {
	cout << "normal map" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	//纹理和材质
	Texture* tex1 = app->resourceMng->createTexture("resources/textures/brickwall.jpg");
	Texture* tex2 = app->resourceMng->createTexture("resources/textures/brickwall_normal.jpg");
	Material* mat = app->resourceMng->createMaterial("mat1");
	mat->addTexture(tex1);
	mat->setShader("pbr");
	mat->setNormalMap(tex2);
	mat->setMetallic(0.0f);
	mat->setRoughness(0.8f);

	Material* mat1 = app->resourceMng->createMaterial("mat2");
	mat1->addTexture(tex1);
	mat1->setShader("pbr");
	mat1->setMetallic(0.0f);
	mat1->setRoughness(0.8f);

	//平面
	RGameObject* plane1 = pSce->addGameObject();
	plane1->transform->setLocalPosition(-3.0f, 0.0f, 0.0);
	plane1->transform->setLocalScale(0.5f, 1.0f, 0.5f);
	plane1->transform->setLocalUpDir(0.0f, 0.0f, 1.0f);
	plane1->transform->setLocalFrontDir(0.0f, -1.0f, 0.0f);
	CRender* planerender1 = (CRender*)plane1->addComponent(RENDER);
	planerender1->addMesh(app->resourceMng->getMesh("plane"));
	planerender1->addMaterial(mat);

	RGameObject* plane2 = pSce->addGameObject();
	plane2->transform->setLocalPosition(3.0f, 0.0f, 0.0);
	plane2->transform->setLocalScale(0.5f, 1.0f, 0.5f);
	plane2->transform->setLocalUpDir(0.0f, 0.0f, 1.0f);
	plane2->transform->setLocalFrontDir(0.0f, -1.0f, 0.0f);
	CRender* planerender2 = (CRender*)plane2->addComponent(RENDER);
	planerender2->addMesh(app->resourceMng->getMesh("plane"));
	planerender2->addMaterial(mat1);

	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 0.0f, 10.0f);
	CO->transform->setLocalFrontDir(0.0f, 0.0f, -3.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());

	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, -1.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->castShadow(false);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);

	RGameObject* LO1 = pSce->addGameObject();
	LO1->transform->setLocalPosition(0.0f, 2.0f, 2.0f);
	LO1->transform->setLocalFrontDir(1.0f, -0.5f, 0.0f);
	LO1->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light1 = (CLight*)LO1->addComponent(COMPTYPE::LIGHT);
	light1->castShadow(false);
	light1->setIntensity(0.1f, 1.0f, 1.0f);
	light1->setColor(300.0f, 300.0f, 300.0f);
	light1->setLightType(LIGHTTYPE::LPOINT);
}

/**
 *后期处理
 */
void example_light_shadow_5() {
	cout << "post process" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	//纹理和材质
	Texture* tex1 = app->resourceMng->createTexture("resources/textures/container.jpg");
	Material* mat = app->resourceMng->createMaterial("mat1");
	mat->addTexture(tex1);
	mat->setShader("phong");

	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->setShader("phong");
	mat2->setColor(1.0f, 1.0f, 1.0f);

	//平面
	RGameObject* plane = pSce->addGameObject();
	plane->transform->setLocalScale(0.7f, 1.0f, 0.7f);
	CRender* planerender = (CRender*)plane->addComponent(RENDER);
	planerender->addMesh(app->resourceMng->getMesh("plane"));
	planerender->addMaterial(mat2);
	planerender->recieveShadow(true);
	//立方体
	RGameObject* cube = pSce->addGameObject();
	cube->transform->setLocalPosition(0.0f, 0.5f, 0.0f);
	cube->transform->setLocalScale(0.7f, 0.7f, 0.7f);
	cube->transform->setLocalFrontDir(0.2f, 0.0f, 0.9f);
	CRender* cuberender = (CRender*)cube->addComponent(RENDER);
	cuberender->addMesh(app->resourceMng->getMesh("cube"));
	cuberender->addMaterial(mat2);
	cuberender->castShadow(true);
	//球
	RGameObject* sphere = pSce->addGameObject();
	sphere->transform->setLocalPosition(-1.0f, 0.5f, 0.5f);
	sphere->transform->setLocalScale(0.7f, 0.7f, 0.7f);
	sphere->transform->setLocalFrontDir(1.0f, 0.0f, 0.0f);
	CRender* sphererender = (CRender*)sphere->addComponent(RENDER);
	sphererender->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender->addMaterial(mat2);
	sphererender->castShadow(true);

	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 4.0f, 6.0f);
	CO->transform->setLocalFrontDir(0.0f, -2.0f, -3.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());

	CPostProcess* post = (CPostProcess*)CO->addComponent(COMPTYPE::POSTPROCESS);
	//post->setShaderPath("sharpen");
	//post->setShaderPath("blur");
	//post->setShaderPath("edgedetection");
	post->setShaderPath("grayscale");
	//post->setShaderPath("inversion");

	//平行光
	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, 0.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->castShadow(true);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);

	//点光源
	RGameObject* LO1 = pSce->addGameObject();
	LO1->transform->setLocalPosition(0.0f, 2.0f, 0.0f);
	LO1->transform->setLocalFrontDir(1.0f, -0.5f, 0.0f);
	LO1->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light1 = (CLight*)LO1->addComponent(COMPTYPE::LIGHT);
	light1->castShadow(true);
	light1->setIntensity(0.1f, 1.0f, 1.0f);
	light1->setColor(1.0f, 1.0f, 1.0f);
	light1->setLightType(LIGHTTYPE::LPOINT);

	//聚光灯
	RGameObject* LO2 = pSce->addGameObject();
	LO2->transform->setLocalPosition(2.0f, 3.0f, -1.0f);
	LO2->transform->setLocalFrontDir(-2.0f, -2.5f, 1.0f);
	LO2->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light2 = (CLight*)LO2->addComponent(COMPTYPE::LIGHT);
	light2->castShadow(true);
	light2->setIntensity(0.1f, 1.0f, 1.0f);
	light2->setColor(1.0f, 0.0f, 0.0f);
	light2->setCutOff(10, 15);
	light2->setLightType(LIGHTTYPE::SPOT);
}

/**
 *延迟渲染
 */
void example_light_shadow_6() {
	cout << "light and shadow" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	//纹理和材质
	Texture* tex1 = app->resourceMng->createTexture("resources/textures/container.jpg");
	Material* mat = app->resourceMng->createMaterial("mat1");
	mat->addTexture(tex1);
	mat->setShader("phong");

	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->setShader("phong");
	mat2->setColor(1.0f, 1.0f, 1.0f);

	//平面
	RGameObject* plane = pSce->addGameObject();
	plane->transform->setLocalScale(0.7f, 1.0f, 0.7f);
	CRender* planerender = (CRender*)plane->addComponent(RENDER);
	planerender->addMesh(app->resourceMng->getMesh("plane"));
	planerender->addMaterial(mat2);
	planerender->recieveShadow(true);
	//立方体
	RGameObject* cube = pSce->addGameObject();
	cube->transform->setLocalPosition(0.0f, 0.5f, 0.0f);
	cube->transform->setLocalScale(0.7f, 0.7f, 0.7f);
	cube->transform->setLocalFrontDir(0.2f, 0.0f, 0.9f);
	CRender* cuberender = (CRender*)cube->addComponent(RENDER);
	cuberender->addMesh(app->resourceMng->getMesh("cube"));
	cuberender->addMaterial(mat2);
	cuberender->castShadow(true);
	//球
	RGameObject* sphere = pSce->addGameObject();
	sphere->transform->setLocalPosition(-1.0f, 0.5f, 0.5f);
	sphere->transform->setLocalScale(0.7f, 0.7f, 0.7f);
	sphere->transform->setLocalFrontDir(1.0f, 0.0f, 0.0f);
	CRender* sphererender = (CRender*)sphere->addComponent(RENDER);
	sphererender->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender->addMaterial(mat2);
	sphererender->castShadow(true);

	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 4.0f, 6.0f);
	CO->transform->setLocalFrontDir(0.0f, -2.0f, -3.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());
	cam->setRenderModel(RENDERMODEL::DEFER);

	//平行光
	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, 0.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->castShadow(true);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);

	//点光源
	RGameObject* LO1 = pSce->addGameObject();
	LO1->transform->setLocalPosition(0.0f, 2.0f, 0.0f);
	LO1->transform->setLocalFrontDir(1.0f, -0.5f, 0.0f);
	LO1->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light1 = (CLight*)LO1->addComponent(COMPTYPE::LIGHT);
	light1->castShadow(true);
	light1->setIntensity(0.1f, 1.0f, 1.0f);
	light1->setColor(1.0f, 1.0f, 1.0f);
	light1->setLightType(LIGHTTYPE::LPOINT);

	//聚光灯
	RGameObject* LO2 = pSce->addGameObject();
	LO2->transform->setLocalPosition(2.0f, 3.0f, -1.0f);
	LO2->transform->setLocalFrontDir(-2.0f, -2.5f, 1.0f);
	LO2->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light2 = (CLight*)LO2->addComponent(COMPTYPE::LIGHT);
	light2->castShadow(false);
	light2->setIntensity(0.1f, 1.0f, 1.0f);
	light2->setColor(1.0f, 0.0f, 0.0f);
	light2->setCutOff(10, 15);
	light2->setLightType(LIGHTTYPE::SPOT);
}
/**
 *天空盒
 */
void example_skybox_1() {
	cout << "skybox" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	//纹理和材质
	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->setShader("environment");
	mat2->setColor(1.0f, 1.0f, 1.0f);

	//球
	RGameObject* sphere = pSce->addGameObject();
	sphere->transform->setLocalPosition(0.0f, 0.0f, 0.0f);
	sphere->transform->setLocalScale(1.0f, 1.0f, 1.0f);
	sphere->transform->setLocalFrontDir(1.0f, 0.0f, 0.0f);
	CRender* sphererender = (CRender*)sphere->addComponent(RENDER);
	sphererender->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender->addMaterial(mat2);
	sphererender->castShadow(true);

	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 0.0f, 5.0f);
	CO->transform->setLocalFrontDir(0.0f, 0.0f, -1.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());

	//CBehavior* coBehavior = (CBehavior*)CO->addComponent(BEHAVIOR);
	//coBehavior->setBehavior(new TestScript());

	CSkybox* skybox = (CSkybox*)CO->addComponent(COMPTYPE::SKYBOX);
	std::vector<RString> path;
	path.push_back("resources/skybox/darkskies_ft.tga");
	path.push_back("resources/skybox/darkskies_bk.tga");
	path.push_back("resources/skybox/darkskies_up.tga");
	path.push_back("resources/skybox/darkskies_dn.tga");
	path.push_back("resources/skybox/darkskies_rt.tga");
	path.push_back("resources/skybox/darkskies_lf.tga");
	skybox->setTextures(path);

	//平行光
	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, 0.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->castShadow(true);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);

	//点光源
	RGameObject* LO1 = pSce->addGameObject();
	LO1->transform->setLocalPosition(0.0f, 2.0f, 0.0f);
	LO1->transform->setLocalFrontDir(1.0f, -0.5f, 0.0f);
	LO1->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light1 = (CLight*)LO1->addComponent(COMPTYPE::LIGHT);
	light1->castShadow(true);
	light1->setIntensity(0.1f, 1.0f, 1.0f);
	light1->setColor(1.0f, 1.0f, 1.0f);
	light1->setLightType(LIGHTTYPE::LPOINT);

	//聚光灯
	RGameObject* LO2 = pSce->addGameObject();
	LO2->transform->setLocalPosition(2.0f, 3.0f, -1.0f);
	LO2->transform->setLocalFrontDir(-2.0f, -2.5f, 1.0f);
	LO2->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light2 = (CLight*)LO2->addComponent(COMPTYPE::LIGHT);
	light2->castShadow(true);
	light2->setIntensity(0.1f, 1.0f, 1.0f);
	light2->setColor(1.0f, 0.0f, 0.0f);
	light2->setCutOff(10, 15);
	light2->setLightType(LIGHTTYPE::SPOT);
}
/**
 *模型加载
 */
void example_model_load_1() {
	cout << "load model" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	//obj模型
	RGameObject* nunosuit = pSce->loadGameObject("resources/nanosuit/nanosuit.obj");
	nunosuit->transform->setLocalPosition(0.0f, -4.0f, 0.0f);
	nunosuit->transform->setLocalScale(0.5f, 0.5f, 0.5f);
	CRender* nunosuitrender = (CRender*)nunosuit->getComponent(RENDER);
	CBehavior* nunosuitBehavior1 = (CBehavior*)nunosuit->addComponent(BEHAVIOR);
	nunosuitBehavior1->setBehavior(new TestScript());

	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 0.0f, 20.0f);
	CO->transform->setLocalFrontDir(0.0f, 0.0f, -1.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());

	//平行光
	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, 0.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->castShadow(true);
	light->setColor(5.0f, 5.0f, 5.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);

	////点光源
	//RGameObject* LO1 = pSce->addGameObject();
	//LO1->transform->setLocalPosition(0.0f, 2.0f, 0.0f);
	//LO1->transform->setLocalFrontDir(1.0f, -0.5f, 0.0f);
	//LO1->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	//CLight* light1 = (CLight*)LO1->addComponent(COMPTYPE::LIGHT);
	//light1->castShadow(true);
	//light1->setIntensity(0.1f, 1.0f, 1.0f);
	//light1->setColor(1.0f, 1.0f, 1.0f);
	//light1->setLightType(LIGHTTYPE::LPOINT);

	////聚光灯
	//RGameObject* LO2 = pSce->addGameObject();
	//LO2->transform->setLocalPosition(2.0f, 3.0f, -1.0f);
	//LO2->transform->setLocalFrontDir(-2.0f, -2.5f, 1.0f);
	//LO2->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	//CLight* light2 = (CLight*)LO2->addComponent(COMPTYPE::LIGHT);
	//light2->castShadow(true);
	//light2->setIntensity(0.1f, 1.0f, 1.0f);
	//light2->setColor(1.0f, 0.0f, 0.0f);
	//light2->setCutOff(10, 15);
	//light2->setLightType(LIGHTTYPE::SPOT);
}

/**
 *碰撞检测
 */
void example_collide_1() {
	cout << "collide test" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();
	app->setCollisionDetectionStrategy(4);

	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->setShader("phong");
	mat2->setColor(1.0f, 1.0f, 1.0f);

	//球1
	RGameObject* sphere1 = pSce->addGameObject();
	sphere1->transform->setLocalPosition(-1.0f, 0.5f, 0.5f);
	sphere1->transform->setLocalScale(1.0f, 1.0f, 1.0f);
	CRender* sphererender1 = (CRender*)sphere1->addComponent(RENDER);
	sphererender1->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender1->addMaterial(mat2);
	CSphereCollider* coll1 = (CSphereCollider*)sphere1->addComponent(SPHERECOLLIDER);
	//球2
	RGameObject* sphere2 = pSce->addGameObject();
	sphere2->transform->setLocalPosition(0.3f, 0.5f, 0.5f);
	sphere2->transform->setLocalScale(2.0f, 1.0f, 1.0f);
	CRender* sphererender2 = (CRender*)sphere2->addComponent(RENDER);
	sphererender2->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender2->addMaterial(mat2);
	CSphereCollider* coll2 = (CSphereCollider*)sphere2->addComponent(SPHERECOLLIDER);

	for (int i = 0; i <200; i++) {
		RGameObject* sphere = pSce->addGameObject();
		RFloat x = (float)rand() / (float)RAND_MAX * 5.0f - 2.5f;
		RFloat y = (float)rand() / (float)RAND_MAX * 5.0f - 2.5f;
		RFloat z = (float)rand() / (float)RAND_MAX * 5.0f - 2.5f;
		sphere->transform->setLocalPosition(x, y, z);
		sphere->transform->setLocalScale(0.5f, 0.5f, 0.5f);
		CRender* sphererender = (CRender*)sphere->addComponent(RENDER);
		sphererender->addMesh(app->resourceMng->getMesh("sphere"));
		sphererender->addMaterial(mat2);
		CSphereCollider* coll = (CSphereCollider*)sphere->addComponent(SPHERECOLLIDER);
		if (i >= 190) {
			CBehavior* sphereBehavior = (CBehavior*)sphere->addComponent(BEHAVIOR);
			sphereBehavior->setBehavior(new RandomMove());
		}
	}

	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 0.0f, 6.0f);
	CO->transform->setLocalFrontDir(0.0f, 0.0f, -3.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());

	//平行光
	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, 0.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);
}

/**
 *粒子
 */
void example_particle_1() {
	cout << "particle" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	Texture* texs[3] = { app->resourceMng->createTexture("resources/textures/particle1.png"),
		app->resourceMng->createTexture("resources/textures/particle2.png"),
		app->resourceMng->createTexture("resources/textures/particle3.png") };
	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->setShader("phong");
	mat2->setColor(1.0f, 1.0f, 1.0f);
	//粒子
	for (int i = 0; i < 3; i++) {
		RGameObject* sphere1 = pSce->addGameObject();
		RFloat rx = rand() / (float)RAND_MAX * 6.0f - 3.0f;
		RFloat ry = rand() / (float)RAND_MAX * 2.0f + 1.0f;
		sphere1->transform->setLocalPosition(rx, ry, -4.0f);
		CParticle* par1 = (CParticle*)sphere1->addComponent(PARTICLE);
		par1->spirit = texs[i];
		par1->shader = Application::Instance()->resourceMng->getShader("particle_simple");
		par1->emissionFunc = [](CParticle* cp, Particle& par) -> void {
			par.position = glm::vec3(0.0f, 0.0f, 0.0f);
			par.velocity = glmp::randomVec3() * cp->startSpeed;
			par.size = cp->startSize;
			par.brightness = 0.5f;
		};
		par1->updateFunc = [](CParticle* cp, Particle& par, DWORD deltaT) -> void {
			par.velocity += cp->accelerat * (deltaT / 1000.0f);
			par.velocity += par.velocity * (-0.4f * deltaT / 1000.0f);
			par.position += par.velocity * (deltaT / 1000.0f);
			par.size += (cp->endSize - cp->startSize) * (deltaT / 1000.0f / cp->lifeTime);
			if (par.life <= cp->lifeTime / 4.0f) {
				par.brightness = 4.0f / cp->lifeTime * par.life;
			}
			else {
				par.brightness = -0.67f / cp->lifeTime * par.life + 1.17f;
			}
		};
		par1->emissionType = ET_PILSING;
		par1->rateOnce = 50;
		par1->lifeTime = 1.8f;
		par1->duration = 2.0f;
		par1->accelerat = glm::vec3(0.0f, -0.8f, 0.0f);
		par1->startSpeed = 2.0f;
		//par1->loop = false;
	}
	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 0.0f, 6.0f);
	CO->transform->setLocalFrontDir(0.0f, 0.0f, -3.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	CBehavior* cameraBehavior1 = (CBehavior*)CO->addComponent(BEHAVIOR);
	cameraBehavior1->setBehavior(new CameraScript());

	//平行光
	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(-1.0f, -0.5f, 0.0f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);
}

/**
 *毛发
 */
void example_hair_1() {
	cout << "hair" << endl;
	Application* app = Application::Instance();
	RScene* pSce = app->sceneMng->createScene();

	Material* mat2 = app->resourceMng->createMaterial("mat2");
	mat2->setShader("phong");
	mat2->setColor(1.0f, 1.0f, 1.0f);
	//球1
	RGameObject* sphere1 = pSce->addGameObject();
	sphere1->transform->setLocalPosition(0.0f, 2.0f, 0.0f);
	sphere1->transform->setLocalScale(1.0f, 1.0f, 1.0f);
	CRender* sphererender1 = (CRender*)sphere1->addComponent(RENDER);
	sphererender1->addMesh(app->resourceMng->getMesh("sphere"));
	sphererender1->addMaterial(mat2);
	CHair* hair = (CHair*)sphere1->addComponent(HAIR);
	hair->shader = Application::Instance()->resourceMng->getShader("hair");
	hair->d = 0.9f;
	hair->a = glm::vec3(0.0f, -9.8f, 0.0f);
	CBehavior* sphereBehavior1 = (CBehavior*)sphere1->addComponent(BEHAVIOR);
	sphereBehavior1->setBehavior(new CameraScript());
	//相机
	RGameObject* CO = pSce->addGameObject();
	CO->transform->setLocalPosition(0.0f, 0.0f, 10.0f);
	CO->transform->setLocalFrontDir(0.0f, 0.0f, -3.0f);
	CO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CCamera* cam = (CCamera*)CO->addComponent(COMPTYPE::CAMERA);
	cam->setCameraType(CAMERATYPE::PERSPECTIVE);
	cam->setPerspFrustum(45.0f, 8.0f / 6.0f, 0.1f, 100.0f);
	cam->setViewport(0, 0, 1000, 800);
	cam->backgroundColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

	//平行光
	RGameObject* LO = pSce->addGameObject();
	LO->transform->setLocalPosition(3.0f, 1.5f, 0.0f);
	LO->transform->setLocalFrontDir(0.0f, -1.0f, -0.4f);
	LO->transform->setLocalUpDir(0.0f, 1.0f, 0.0f);
	CLight* light = (CLight*)LO->addComponent(COMPTYPE::LIGHT);
	light->setColor(1.0f, 1.0f, 1.0f);
	light->setLightType(LIGHTTYPE::DIRECTION);
	light->setEnabled(true);
}