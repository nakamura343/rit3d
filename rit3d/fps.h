#pragma once
#include "RCommon.h"
#include "RTimer.h"

class FPS {
public:
	FPS();
	~FPS();
private:
	//�Ƿ���ʾ
	RBool m_isShow{ false };
	//��ʱ��
	RTimer m_timer{ 3000, 1000 };
	//����
	RUInt m_count{ 0 };
public:
	void update();
	void show();
	void hide();
	RBool isShowed() const;
};