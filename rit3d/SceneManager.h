#pragma once

#include "RCommon.h"

class RScene;
class SceneManager
{
public:
	static SceneManager *Instance();
private:
	SceneManager();
	virtual ~SceneManager();

	static SceneManager *m_instance;

	//��ע�������ϵͳ��ʵ��
	std::list<RScene*> m_sceneList;

public:
	RScene* createScene(RString name = DEFAULT_SCENE_NAME);

	RScene* getSceneByName(RString name);

	void destroySceneByName(RString name);

	std::list<RScene*> getAllScene();

	RUInt getSceneCount();
};

