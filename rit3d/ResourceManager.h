#pragma once
#include "RCommon.h"

class Mesh;
class Material;
class Texture;
class GLProgram;
class RGameObject;
class RScene;
class CRender;

class ResourceManager
{
public:
	static ResourceManager *Instance();
private:
	ResourceManager();
	virtual ~ResourceManager();

	static ResourceManager *m_instance;

	//�����
	std::map<RString, Mesh*> meshPool;
	//���ʳ�
	std::map<RString, Material*> materialPool;
	//�����
	std::map<RString, Texture*> texturePool;
	//��ɫ����
	std::map<RString, GLProgram*> shaderPool;

	//����vertices��indices����normals
	void _calcNormal(RFloat* vs, RInt vSize, RUInt* id, RInt iSize, RFloat* nm);
	//����vertices��indices����tangents
	void _calcTangent(RFloat* vs, RInt vSize, RUInt* id, RInt iSize, RFloat* uv, RFloat* tg);
	//����ģ��ʱ����ڵ�
	void _processNode(aiNode* node, const aiScene* scene, CRender* render, RString modelDir);
	//����ģ��ʱ��������
	void _processMesh(aiMesh* mesh, const aiScene* scene, CRender* render, RString modelDir);
	//����ģ�͵ò�������
	void _loadMaterialTexture(Material* mat, aiMaterial* aiMat, RString modelDir);
public:
	//����������
	Mesh* createMesh(const RString& _name, RFloat* verArray, RInt verSize, RUInt* indArray, RInt indSize);
	//���������Ƴ�������Դ
	void deleteMesh(const RString& _name);
	//�������ƻ�ȡ������Դ
	Mesh* getMesh(const RString& _name);

	//�����²���
	Material* createMaterial(const RString& _name);
	//���������Ƴ�������Դ
	void deleteMaterial(const RString& _name);
	//�������ƻ�ȡ������Դ
	Material* getMaterial(const RString& _name);

	//����������
	Texture* createTexture(const RString& imagePath);
	//���������Ƴ�������Դ
	void deleteTexture(const RString& _name);
	//�������ƻ�ȡ������Դ
	Texture* getTexture(const RString& _name);

	//��������ɫ��
	GLProgram* createShader(const RString& _name, const RString& vertexPath, const RString& fragmentPath, const RString& defines, const RString& geometryPath = "");
	//���������Ƴ���ɫ����Դ
	void deleteShader(const RString& _name);
	//�������ƻ�ȡ��ɫ����Դ
	GLProgram* getShader(const RString& _name);

	//����Ĭ��������Դ
	void createDefaultMesh();
	//����Ĭ�ϲ�����Դ
	void createDefaultMaterial();
	//����Ĭ��shader
	void createDefaultShader();

	//�������������Դ
	void clearMesh();
	//������в�����Դ
	void clearMaterial();
	//�������������Դ
	void clearTexture();
	//�������shader
	void clearShader();
	//���������Դ
	void clearAll();

	//����ģ��
	RGameObject* loadModel(RString path, RScene* sce);
};

