#pragma once
#include "RCommon.h"

class Texture {
public:
	static Texture* Create(RString imagePath);
	static void Destroy(Texture* _tex);

private:
	Texture(RString imagePath);
	~Texture();

	GLTexture m_texture{ 0 };

	void _destroy();
public:
	//��ȡgltexture�����id
	GLTexture getTexture() const;
	//ʹ�ø�texture
	void use(RUInt unitId) const;
};