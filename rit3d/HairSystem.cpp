#include "pch.h"
#include "HairSystem.h"
#include "SCLightCameraCollecter.h"
#include "RGameObject.h"
#include "CTransform.h"

HairSystem::HairSystem(RInt od) : ISystem(od) {
	m_type = HAIRSYSTEM;
}

HairSystem::~HairSystem() {

}

void HairSystem::addHair(CHair* _b) {
	std::vector<CHair*>::iterator iter;
	iter = std::find(m_hairPool.begin(), m_hairPool.end(), _b);
	if (iter == m_hairPool.end()) {
		m_hairPool.push_back(_b);
	}
}

void HairSystem::removeHair(CHair* _b) {
	std::vector<CHair*>::iterator iter;
	iter = std::find(m_hairPool.begin(), m_hairPool.end(), _b);
	if (iter != m_hairPool.end()) {
		m_hairPool.erase(iter);
	}
}

HairSystem* HairSystem::CreateInstance(RInt od) {
	return new HairSystem(od);
}

//ϵͳ��ʼ��ʱ����
void HairSystem::onAwake() {

}

//ϵͳ������ʱ����
void HairSystem::onEnable() {

}

//ϵͳ��ʼ����ʱ����
void HairSystem::onStart() {

}

//ʵ�屻��ӵ�ϵͳʱ����
void HairSystem::onAddGameObject() {

}

//�����ӵ�ʵ��ʱ����
void HairSystem::onAddComponent(COMPTYPE type, IComponent* pComp) {
	if (type == COMPTYPE::HAIR) {
		addHair((CHair*)pComp);
		_transform((CHair*)pComp);
	}
}

//�����ʵ���Ƴ�ʱ����
void HairSystem::onRemoveComponent(COMPTYPE type, IComponent* pComp) {
	if (type == COMPTYPE::HAIR) {
		removeHair((CHair*)pComp);
	}
}

//ʵ���ϵͳ���Ƴ�ʱ����
void HairSystem::onRemoveGameObject() {

}

//ϵͳ����ʱ����
void HairSystem::onUpdate(DWORD deltaT) {
	_updateHair(deltaT);
	_drawHair();
}

void HairSystem::_updateHair(DWORD deltaT) {
	RFloat dt = static_cast<RFloat>(deltaT) / 1000.0f;
	//cout << dt << endl;
	if (dt > 1.0f / 60.0f) {
		dt = 1.0f / 60.0f;
	}
	for (auto hair : m_hairPool) {
		glm::mat4 mMat = hair->gameObject->transform->getModelMatrix();
		//verlet��ֵ���ֻ�ȡ�µ�λ��
		for (auto& node : hair->m_nodes) {
			glm::vec3 p2 = node.p1 + hair->d * (node.p1 - node.p0) + hair->a * dt * dt;
			//��״̬ȡ����״̬
			node.p0 = node.p1;
			node.p1 = p2;
		}
		//��ÿ����˿�ɳڷ�����Լ�����
		for (auto strand : hair->m_strands) {
			//�ɳڷ�����
			for (int i = 0; i < 10; i++) {
				//��ÿ���ڵ�Ĵ���
				for (int index = strand.nodeStart; index < strand.nodeEnd; index++) {
					HairNode& na = hair->m_nodes[index];
					HairNode& nb = hair->m_nodes[index + 1];
					//��ײ���;���
					_collideHair(hair, nb.p1);
					//����Լ��
					glm::vec3 a2b = nb.p1 - na.p1;
					float l = glm::length(a2b);
					float factor = (l - nb.maxLength) / (2.0f * l);
					na.p1 = na.p1 + a2b * factor;
					nb.p1 = nb.p1 - a2b * factor;
				}
				hair->m_nodes[strand.nodeStart].p1 = glm::vec3(mMat * glm::vec4(strand.rootP, 1.0f));
			}
		}
		//���»�������
		int l = hair->m_drawData.size();
		for (int i = 0; i < l; i++) {
			hair->m_drawData[i] = hair->m_nodes[i].p1;
		}
	}
}
void HairSystem::_drawHair() {
	std::list<CCamera*> cameraList = SCLightCameraCollecter::Instance()->getCameraList();
	for (auto camera : cameraList) {
		for (auto hair : m_hairPool) {
			glBindVertexArray(hair->m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, hair->m_VBO);
			glBufferData(GL_ARRAY_BUFFER, 3 * hair->m_drawData.size() * sizeof(float), &(hair->m_drawData[0]), GL_STREAM_DRAW);
			hair->shader->use();
			hair->shader->setMat4("uModel", hair->gameObject->transform->getModelMatrix());
			hair->shader->setMat4("uView", camera->getViewMatrix());
			hair->shader->setMat4("uProjection", camera->getProjMatrix());
			for (int i = 0; i < static_cast<int>(hair->m_strands.size()); i++) {
				glDrawArrays(GL_LINE_STRIP, i * hair->nodeInStrand, hair->nodeInStrand);
			}
		}
		glBindVertexArray(0);
	}
}

//ϵͳ����ʱonUpdate֮�����
void HairSystem::onLateUpdate() {

}

//ϵͳ������ʱ����
void HairSystem::onDisable() {

}

void HairSystem::onDestroy() {

}

//ͷ������ײ���
void HairSystem::_collideHair(CHair* ch, glm::vec3& point) {
	glm::vec3 dir = point - ch->center;
	float l = glm::length(dir);
	if (l < ch->raduis) {
		point = ch->center + ch->raduis / l * dir;
	}
}

//�ڵ����ݴӾֲ�����ϵת������������ϵ
void HairSystem::_transform(CHair* ch) {
	glm::mat4 mMat = ch->gameObject->transform->getModelMatrix();
	int l = ch->m_nodes.size();
	for (int i = 0; i < l; i++) {
		ch->m_nodes[i].p0 = ch->m_nodes[i].p1 = glm::vec3(mMat * glm::vec4(ch->m_nodes[i].p1, 1.0f));
	}
	ch->center = glm::vec3(mMat * glm::vec4(ch->center, 1.0f));
}