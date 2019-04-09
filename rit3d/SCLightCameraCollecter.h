#pragma once
#include "ISingletonComponent.h"
#include "CLight.h"
#include "CCamera.h"

/**
 *�ƹ�����ռ����
 */
class SCLightCameraCollecter : public ISingletonComponent {
private:
	SCLightCameraCollecter();
	virtual ~SCLightCameraCollecter();
	static SCLightCameraCollecter *m_instance;

	std::list<CLight*> m_lightList;
	std::list<CCamera*> m_cameraList;

	RUInt m_dirLightNum{ 0 };//ƽ�й�����
	RUInt m_poiLightNum{ 0 };//���Դ����
	RUInt m_spoLightNum{ 0 };//�۹������

public:
	static SCLightCameraCollecter* Instance();

	//���������
	void addCamera(CCamera* camera);
	//�Ƴ�������
	void removeCamera(CCamera* camera);
	//��ȡ����б�
	std::list<CCamera*> getCameraList() const;

	//��ӵƹ����
	void addLight(CLight* light);
	//�Ƴ��ƹ����
	void removeLight(CLight* light);
	//��ȡ�ƹ��б�
	std::list<CLight*> getLightList() const;
	//��ȡ��Դ����
	RUInt getLightNum(LIGHTTYPE _type) const;
	//������Դ����
	void resetLightNum(LIGHTTYPE _type, RInt delta);
};

