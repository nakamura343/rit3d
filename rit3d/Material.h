#pragma once
#include "RCommon.h"
#include "GLProgram.h"
#include "Texture.h"

class RUniform {
public:
	GLint location;
	GLenum type;
	RString name;
};

class Material {
public:
	static Material* Create(RString _name);
	static void Destroy(Material* _mat);
private:
	Material(RString _name);
	~Material();

	RString m_name;//��������
	glm::vec3 m_color{ 1.0f,1.0f,1.0f };//��������ɫ
	glm::vec3 m_ambient{ 1.0f,1.0f,1.0f };//���ʻ�������ɫ
	glm::vec3 m_diffuse{ 1.0f,1.0f,1.0f };//������������ɫ
	glm::vec3 m_specular{ 1.0f,1.0f,1.0f };//���ʾ��淴����ɫ
	RFloat m_shininess{ 32.0 };//���ʾ��淴��߹�ϵ��
	std::vector<Texture*> m_texList;//�����б�
	RBool m_useLight{ true };//�Ƿ�ʹ�õƹ�Ч��

	RString m_shaderName{ "" };//shader������
	GLProgram* m_shader{ nullptr };//shader����

	std::map<RString, RString> m_defines;//shader���õ��ĺ궨��

	RBool m_shaderDirty{ true };//shader����

	void _destroy();

public:
	//shader��ز���
	GLProgram* getShader();
	RString getShaderName() const;
	void setShader(RString _shader);

	//����define
	void addDefine(RString _key, RString _value);

	glm::vec3 getColor() const;
	void setColor(RFloat r, RFloat g, RFloat b);

	glm::vec3 getAmbient() const;
	void setAmbient(RFloat r, RFloat g, RFloat b);

	glm::vec3 getDiffuse() const;
	void setDiffuse(RFloat r, RFloat g, RFloat b);

	glm::vec3 getSpecular() const;
	void setSpecular(RFloat r, RFloat g, RFloat b);

	RFloat getShininess() const;
	void setShininess(RFloat s);

	void addTexture(Texture* _tex);
	void removeTexture(Texture* _tex);
	void clearTexture();
	Texture* getTexture(RUInt i);
	RUInt getTexNum() const;

	RBool isUseLight() const;
	void useLight();
	void closeLight();
};