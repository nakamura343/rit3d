#pragma once
#include "RCommon.h"
#include "IComponent.h"
#include "GLProgram.h"

class CSkybox : public IComponent {
private:
	CSkybox();
	~CSkybox();

	RUInt m_boxVAO;//��պе�������vao����
	RUInt m_vbo;
	RUInt m_ebo;

	std::vector<RString> m_texName;//��������ǰ��

	RUInt m_cubeTexture;//��������ͼ����

	GLProgram* m_shader;//��Ⱦ��պ��õ���ɫ��

public:
	//������պ�������������ǰ��
	void setTextures(std::vector<RString> _path);

	//��ȡ��պ�vao
	RUInt getBoxVAO() const;

	//��ȡi��������ͼ����
	RUInt getBoxTexture() const;

	void setShader(const RString& _texName);

	GLProgram* getShader() const;

	static CSkybox* CreateInstance();
};