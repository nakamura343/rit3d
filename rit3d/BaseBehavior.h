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

	//���ڴ�С�ı�ʱִ��
	virtual void onChangeSize(int _w, int _h);
	//����¼�
	virtual void onLeftButtonDown();
	virtual void onLeftButtonUp();
	virtual void onRightButtonDown();
	virtual void onRightButtonUp();
	virtual void onMouseMove(double _x, double _y);
	virtual void onScroll(double _x, double _y);
	//�����¼�
	virtual void onKeyDown(int key);
	virtual void onKeyKeep(int key);
	virtual void onKeyUp(int key);

	void update();

	void lateUpdate();

	RGameObject* gameObject;

private:
	RBool m_started{ false };
};