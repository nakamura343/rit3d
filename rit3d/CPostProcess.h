#pragma once
#include "RCommon.h"
#include "IComponent.h"

class GLProgram;
//ֻ�мӵ����������Ķ����²�����
//��Ҫ�û��Լ�дshader������shader·��
class CPostProcess : public IComponent {
private:
	CPostProcess();
	virtual ~CPostProcess();

	RString m_shaderPath{ "postProcess" };//û��.frag��׺

	GLProgram* m_shader;

public:
	//����shader·��
	RString getShaderPath() const;
	void setShaderPath(const RString& _path);

	GLProgram* getShader() const;

	static CPostProcess* CreateInstance();
};
