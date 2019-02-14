#include "pch.h"
#include "Texture.h"

Texture* Texture::Create(RString imagePath) {
	return new Texture(imagePath);
}
void Texture::Destroy(Texture* _tex) {
	delete _tex;
	_tex = nullptr;
}

Texture::Texture(RString imagePath) {
	//��������
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	//���û��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	//���ز���������
	RInt width, height, nrChannels;
	RUChar* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1) {
			format = GL_RED;
		}
		else if (nrChannels == 3) {
			format = GL_RGB;
		}
		else if (nrChannels == 4) {
			format = GL_RGBA;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
}

Texture::~Texture() {
	_destroy();
}

GLTexture Texture::getTexture() const {
	return m_texture;
}

//ʹ�ø�texture
void Texture::use(RUInt unitId) const {
	//0x84c0 ���� GL_TEXTURE0
	glActiveTexture(0x84C0 + unitId);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::_destroy() {

}