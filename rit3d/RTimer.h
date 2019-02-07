#pragma once
#include "RCommon.h"

class RTimer {
public:
	RTimer(DWORD _total, DWORD _interval);
	~RTimer();

private:
	DWORD m_timeStart{ ::GetTickCount() };//��ʼʱ��
	DWORD m_timeLast{ m_timeStart };//��һ�μ�ʱʱ��
	DWORD m_timeTotal{ 3000 };//�ܵĳ�ʱʱ��
	DWORD m_timeInterval{ 30 };//�������

public:
	DWORD getTimeStart() const;
	void reset();

	DWORD getTimeTotal() const;
	void setTimeTotal(DWORD _t);

	DWORD getTimeInterval() const;
	void setTimeInterval(DWORD _t);

	RBool isTotal() const;
	RBool isInterval();
};