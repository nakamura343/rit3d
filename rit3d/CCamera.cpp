#include "pch.h"
#include "CCamera.h"
#include "RGameObject.h"


CCamera::CCamera() {
	m_type = COMPTYPE::CAMERA;

	//����framebuffer
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	//��������
	glGenTextures(2, m_colorTexs);
	for (RUInt i = 0; i < 2; i++) {
		glBindTexture(GL_TEXTURE_2D, m_colorTexs[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, DEFAULT_WIDTH * 2, DEFAULT_HEIGHT * 2, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);

		//�����ӵ���ǰ�󶨵�֡�������
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_colorTexs[i], 0);
	}

	//������Ⱦ���������Ϊ��Ȼ����ģ�建��
	RUInt rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, DEFAULT_WIDTH * 2, DEFAULT_HEIGHT * 2);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	//��ӡ������Ϣ
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	//�ָ�Ĭ��framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


CCamera::~CCamera() {
	glDeleteFramebuffers(1, &m_framebuffer);
	glDeleteTextures(2, m_colorTexs);
}

CCamera* CCamera::CreateInstance() {
	return new CCamera();
};

RUInt CCamera::getCullMask() const {
	return m_cullMask;
}
void CCamera::setCullMask(RUInt _mask) {
	m_cullMask = _mask;
}

CAMERATYPE CCamera::getCameraType() const {
	return m_cameraType;
}
void CCamera::setCameraType(CAMERATYPE type) {
	if (m_cameraType != type) {
		m_cameraType = type;
		m_projDirty = true;
	}
}

//������׶��
RFloat CCamera::getNear() const {
	return m_near;
}
void CCamera::setNear(RFloat _n) {
	if (m_near != _n) {
		m_near = _n;
		m_projDirty = true;
	}
}

RFloat CCamera::getFar() const {
	return m_far;
}
void CCamera::setFar(RFloat _f) {
	if (m_far != _f) {
		m_far = _f;
		m_projDirty = true;
	}
}

RFloat CCamera::getAsp() const {
	return m_asp;
}
void CCamera::setAsp(RFloat _a) {
	if (m_asp != _a) {
		m_asp = _a;
		m_projDirty = true;
	}
}

RFloat CCamera::getFov() const {
	return m_fov;
}
void CCamera::setFov(RFloat _f) {
	if (m_fov != _f) {
		m_fov = _f;
		m_projDirty = true;
	}
}

RFloat CCamera::getSize() const {
	return m_size;
}
void CCamera::setSize(RFloat _s) {
	if (m_size != _s) {
		m_size = _s;
		m_projDirty = true;
	}
}

void CCamera::setOrthoFrustum(RFloat _fov, RFloat _asp, RFloat _near, RFloat _far) {
	if (m_fov != _fov || m_asp != _asp || m_near != _near || m_far != _far) {
		m_fov = _fov;
		m_asp = _asp;
		m_near = _near;
		m_far = _far;
		m_projDirty = true;
	}
}
void CCamera::setPerspFrustum(RFloat _size, RFloat _asp, RFloat _near, RFloat _far) {
	if (m_size != _size || m_asp != _asp || m_near != _near || m_far != _far) {
		m_size = _size;
		m_asp = _asp;
		m_near = _near;
		m_far = _far;
		m_projDirty = true;
	}
}

//��ȡ֡�������
RUInt CCamera::getFramebuffer() {
	return m_framebuffer;
}
//��ȡ֡�����ϵ���ɫ�������
RUInt CCamera::getColorTex(RUInt ind) {
	return m_colorTexs[ind];
}

RFloat CCamera::getExposure() const {
	return m_exposure;
}
void CCamera::setExposure(RFloat _e) {
	m_exposure = _e;
}

RFloat CCamera::getBloom() const {
	return m_bloom;
}
void CCamera::setBloom(RFloat _b) {
	m_bloom = _b;
}

//��ȡͶӰ����
glm::mat4 CCamera::getProjMatrix() {
	if (m_projDirty) {
		if (m_cameraType == CAMERATYPE::ORTHO) {
			float hw = m_size / 2;
			float hh = hw / m_asp;
			m_projMatrix = glm::ortho(-hw, hw, -hh, hh, m_near, m_far);
		}
		else if (m_cameraType == CAMERATYPE::PERSPECTIVE) {
			m_projMatrix = glm::perspective(glm::radians(m_fov), m_asp, m_near, m_far);
		}
		else {

		}
	}
	return m_projMatrix;
}

//��ȡ��ͼ����
glm::mat4 CCamera::getViewMatrix() {
	return gameObject->transform->getViewMatrix();
}
