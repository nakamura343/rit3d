#include "pch.h"
#include "ParticleSystem.h"
#include "CParticle.h"
#include "RGameObject.h"
#include "CTransform.h"
#include "RMath.h"
#include "GLProgram.h"
#include "CCamera.h"
#include "SCLightCameraCollecter.h"

ParticleSystem::ParticleSystem(RInt od) : ISystem(od) {
	m_type = PARTICLESYSTEM;
}
ParticleSystem::~ParticleSystem() {

}

ParticleSystem* ParticleSystem::CreateInstance(RInt od) {
	return new ParticleSystem(od);
}

//ϵͳ��ʼ��ʱ����
void ParticleSystem::onAwake() {
	RFloat vertices[] = {
		0.0f, 0.0f, 0.0f
	};
	//����attay buffer
	RUInt vbo;
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &vbo);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float), vertices, GL_STATIC_DRAW);
	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

//ϵͳ������ʱ����
void ParticleSystem::onEnable() {

}

//ϵͳ��ʼ����ʱ����
void ParticleSystem::onStart() {

}

//ʵ�屻��ӵ�ϵͳʱ����
void ParticleSystem::onAddGameObject() {

}

//�����ӵ�ʵ��ʱ����
void ParticleSystem::onAddComponent(COMPTYPE type, IComponent* pComp) {
	if (type == COMPTYPE::PARTICLE) {
		addParticle((CParticle*)pComp);
	}
}

//�����ʵ���Ƴ�ʱ����
void ParticleSystem::onRemoveComponent(COMPTYPE type, IComponent* pComp) {
	if (type == COMPTYPE::PARTICLE) {
		removeParticle((CParticle*)pComp);
	}
}

//ʵ���ϵͳ���Ƴ�ʱ����
void ParticleSystem::onRemoveGameObject() {

}

//ϵͳ����ʱ����
void ParticleSystem::onUpdate(DWORD deltaT) {
	_updateParticles(deltaT);
	_drawParticles();
}

//ϵͳ����ʱonUpdate֮�����
void ParticleSystem::onLateUpdate() {

}

//ϵͳ������ʱ����
void ParticleSystem::onDisable() {

}

//ϵͳ��ע��ʱ����
void ParticleSystem::onDestroy() {

}

void ParticleSystem::addParticle(CParticle* _b) {
	std::vector<CParticle*>::iterator iter;
	iter = std::find(m_particlePool.begin(), m_particlePool.end(), _b);
	if (iter == m_particlePool.end()) {
		m_particlePool.push_back(_b);
	}
}

void ParticleSystem::removeParticle(CParticle* _b) {
	std::vector<CParticle*>::iterator iter;
	iter = std::find(m_particlePool.begin(), m_particlePool.end(), _b);
	if (iter != m_particlePool.end()) {
		m_particlePool.erase(iter);
	}
}

//����������Ϣ
void ParticleSystem::_updateParticles(DWORD deltaT) {
	//����������Ϣ
	for (auto cp : m_particlePool) {
		for (auto& particle : cp->particles) {
			if (particle.life > 0.0f) {
				particle.life -= deltaT / 1000.0f;
				particle.position += particle.velocity * (cp->startSpeed * deltaT / 1000.0f);
			}
		}

		//�����µ�����
		//����������������
		RInt addNums = static_cast<int>((cp->cumulativeTime + deltaT) / 1000.0f * cp->rateOverTime);
		cp->cumulativeTime = cp->cumulativeTime + deltaT - addNums / cp->rateOverTime * 1000.0f;
		for (int i = 0; i < addNums; i++) {
			int j = _findUnusedParticle(cp);
			if (j == -1) {
				Particle par;
				par.life = cp->lifeTime;
				par.position = glm::vec3(0.0f, 0.0f, 0.0f);
				par.velocity = glmp::randomVec3();
				cp->particles.push_back(par);
			}
			else {
				cp->particles[j].life = cp->lifeTime;
				cp->particles[j].position = glm::vec3(0.0f, 0.0f, 0.0f);
				cp->particles[j].velocity = glmp::randomVec3();
			}
		}
	}
}
//��Ⱦ����
void ParticleSystem::_drawParticles() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glBindVertexArray(m_VAO);
	std::list<CCamera*> cameraList = SCLightCameraCollecter::Instance()->getCameraList();
	for (auto camera : cameraList) {
		for (auto cp : m_particlePool) {
			cp->shader->use();
			//texture
			cp->spirit->use(1);
			cp->shader->setInt("uSpirit", 1);
			cp->shader->setMat4("uModel", cp->gameObject->transform->getModelMatrix());
			cp->shader->setMat4("uView", camera->getViewMatrix());
			cp->shader->setMat4("uProjection", camera->getProjMatrix());
			for (auto par : cp->particles) {
				if (par.life > 0.0f) {
					cp->shader->setVec3("uOffset", par.position);
					glDrawArrays(GL_POINTS, 0, 1);
				}
			}
		}
	}
	glBindVertexArray(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_BLEND);
}

//Ѱ��һ��û�õ�����
RInt ParticleSystem::_findUnusedParticle(CParticle* cp) {
	for (RInt j = cp->lastUsedParticle; j < (int)cp->particles.size(); j++) {
		if (cp->particles[j].life <= 0.0f) {
			cp->lastUsedParticle = j;
			return j;
		}
	}
	for (RInt j = 0; j < cp->lastUsedParticle; j++) {
		if (cp->particles[j].life <= 0.0f) {
			cp->lastUsedParticle = j;
			return j;
		}
	}
	return -1;
}
