#pragma once
#include "RCommon.h"

class RGameObject;
class BaseBehavior {
public:
	BaseBehavior();
	virtual ~BaseBehavior();

	//������������һִ֡��
	virtual void onStart();
	
	//ÿִ֡��
	virtual void onUpdate();

	//ÿִ֡�У���onUpdate֮��
	virtual void onLateUpdate();

	//��ײʱִ��
	virtual void onCollide();

	void update();

	void lateUpdate();

	RGameObject* gameObject;

private:
	RBool m_started{ false };
};