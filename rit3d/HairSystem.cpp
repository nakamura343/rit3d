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
		_transform((CHair*)pComp);//�������ϵͳ�����ʱ����������仯���˹��̲����棬Ҳ����˵��ʹ֮�����Ƴ����������Ҳ���ỹԭ
		_barycentric((CHair*)pComp);//������ֵ��������
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
		//���»������ݣ���Ҫ��3��Bezier�������
		_bezierCurve(hair);
		_interpolate(hair);
		_calcTangent(hair);
	}
}
void HairSystem::_drawHair() {
	std::list<CCamera*> cameraList = SCLightCameraCollecter::Instance()->getCameraList();
	std::list<CLight*> lightList = SCLightCameraCollecter::Instance()->getLightList();
	CLight* light = lightList.front();
	for (auto camera : cameraList) {
		for (auto hair : m_hairPool) {
			int num = (hair->nodeInStrand - 1) * (hair->interN + 1) + 1;
			glBindVertexArray(hair->m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, hair->m_VBO);
			glBufferData(GL_ARRAY_BUFFER, hair->m_dataSize * sizeof(float), &(hair->m_drawData[0]), GL_STREAM_DRAW);
			hair->shader->use();
			//hair->shader->setMat4("uModel", hair->gameObject->transform->getModelMatrix());
			hair->shader->setMat4("uView", camera->getViewMatrix());
			hair->shader->setMat4("uProjection", camera->getProjMatrix());
			hair->shader->setVec3("uLight.direction", light->gameObject->transform->getLocalFrontDir());
			hair->shader->setVec3("uLight.color", light->getColor());
			hair->shader->setFloat("uLight.ambInt", light->getAmbInt());
			hair->shader->setFloat("uLight.difInt", light->getDifInt());
			hair->shader->setFloat("uLight.speInt", light->getSpeInt());
			hair->shader->setFloat("uLight.castShadow", light->isCastShadow());
			hair->shader->setVec3("uViewPos", camera->gameObject->transform->getPosition());
			int count_strand = static_cast<int>(hair->m_dataSize / 6 / num);
			//int count_strand = static_cast<int>(hair->m_strands.size());
			for (int i = 0; i < count_strand; i++) {
				glDrawArrays(GL_LINE_STRIP, i * num, num);
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

//3��Bezier�������
void HairSystem::_bezierCurve(CHair* ch) {
	ch->m_pointer4Data = 0;
	RFloat a = 0.25f, b = 0.25f;//������Ƶ��õ���ϵ��
	int n = ch->interN;//��ֵ�����
	float dt = 1.0f / (n + 1);
	std::vector<HairStrand>& ms = ch->m_strands;
	//��ÿ����������bezier��ֵ
	for (auto s : ms) {
		std::vector<glm::vec3> cpa;//���Ƶ�A
		std::vector<glm::vec3> cpb;//���Ƶ�B
		//���ƿ��Ƶ�
		cpa.push_back(ch->m_nodes[s.nodeStart].p1 + a * (ch->m_nodes[s.nodeStart + 1].p1 - ch->m_nodes[s.nodeStart].p1));
		for (int i = s.nodeStart + 1; i < s.nodeEnd; i++) {
			glm::vec3 tan = ch->m_nodes[i + 1].p1 - ch->m_nodes[i - 1].p1;
			cpa.push_back(ch->m_nodes[i].p1 + a * tan);
			cpb.push_back(ch->m_nodes[i].p1 - b * tan);
		}
		cpb.push_back(ch->m_nodes[s.nodeEnd].p1 - b * (ch->m_nodes[s.nodeEnd].p1 - ch->m_nodes[s.nodeEnd - 1].p1));
		//��ֵ
		for (int i = s.nodeStart; i < s.nodeEnd; i++) {
			for (int j = 0; j <= n; j++) {
				float t = dt * j;
				glm::vec3 p = ch->m_nodes[i].p1 * (1.0f - t) * (1.0f - t) * (1.0f - t) +
					cpa[i - s.nodeStart] * 3.0f * t * (1 - t) * (1 - t) +
					cpb[i - s.nodeStart] * 3.0f * t * t * (1 - t) +
					ch->m_nodes[i + 1].p1 * t * t * t;
				ch->m_drawData[ch->m_pointer4Data++] = p.x;
				ch->m_drawData[ch->m_pointer4Data++] = p.y;
				ch->m_drawData[ch->m_pointer4Data++] = p.z;
				//�ճ����ߵ�λ��
				ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
				ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
				ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
			}
		}
		ch->m_drawData[ch->m_pointer4Data++] = ch->m_nodes[s.nodeEnd].p1.x;
		ch->m_drawData[ch->m_pointer4Data++] = ch->m_nodes[s.nodeEnd].p1.y;
		ch->m_drawData[ch->m_pointer4Data++] = ch->m_nodes[s.nodeEnd].p1.z;
		//�ճ����ߵ�λ��
		ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
		ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
		ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
	}
}

//������������
void HairSystem::_barycentric(CHair* ch) {
	ch->m_interCoord.clear();
	for (RUInt i = 0; i < ch->strandN; i++) {
		RFloat x = rand() / (RFloat)RAND_MAX;
		RFloat y = rand() / (RFloat)RAND_MAX;
		if (x + y > 1.0f) {
			if (x > y) {
				x = 1.0f - x;
			}
			else {
				y = 1.0f - y;
			}
		}
		RFloat z = 1.0f - x - y;
		ch->m_interCoord.push_back(glm::vec3(x, y, z));
	}
}

//��ֵ���е�ͷ��
void HairSystem::_interpolate(CHair* ch) {
	int faces = ch->scalp_i.size() / 3;//��ĸ���
	int nodes = (ch->nodeInStrand - 1) * (ch->interN + 1) + 1;//һ�������ϵĽڵ�����bezier��ֵ��
	for (int i = 0; i < faces; i++) {
		//������������������
		RUInt ip1 = ch->scalp_i[3 * i];
		RUInt ip2 = ch->scalp_i[3 * i + 1];
		RUInt ip3 = ch->scalp_i[3 * i + 2];
		//�����µķ���
		for (auto coord : ch->m_interCoord) {
			for (int j = 0; j < nodes; j++) {
				for (int k = 0; k < 3; k++) {
					RFloat p1k = ch->m_drawData[6 * (ip1 * nodes + j) + k];
					RFloat p2k = ch->m_drawData[6 * (ip2 * nodes + j) + k];
					RFloat p3k = ch->m_drawData[6 * (ip3 * nodes + j) + k];
					ch->m_drawData[ch->m_pointer4Data++] = p1k * coord.x + p2k * coord.y + p3k * coord.z;
				}
				//�ճ����ߵ�λ��
				ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
				ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
				ch->m_drawData[ch->m_pointer4Data++] = 0.0f;
			}
		}
	}
}

//������
void HairSystem::_calcTangent(CHair* ch) {
	//�����ﲻ����λ������shader�ﵥλ��
	int numNodes = (ch->nodeInStrand - 1) * (ch->interN + 1) + 1;//һ�������ϵĽڵ�����bezier��ֵ��
	int numStrand = ch->m_dataSize / 6 / numNodes;
	for (int j = 0; j < numStrand; j++) {
		//�����ϵ�һ���������012 345 678
		int p1 = 6 * (j * numNodes);//�׵�ַ
		ch->m_drawData[p1 + 3] = ch->m_drawData[p1 + 6] - ch->m_drawData[p1 + 0];
		ch->m_drawData[p1 + 4] = ch->m_drawData[p1 + 7] - ch->m_drawData[p1 + 1];
		ch->m_drawData[p1 + 5] = ch->m_drawData[p1 + 8] - ch->m_drawData[p1 + 2];
		//�����м�������
		for (int i = 1; i < numNodes - 1; i++) {
			int pi = 6 * (j * numNodes + i);
			ch->m_drawData[pi + 3] = ch->m_drawData[pi + 6] - ch->m_drawData[pi - 6];
			ch->m_drawData[pi + 4] = ch->m_drawData[pi + 7] - ch->m_drawData[pi - 5];
			ch->m_drawData[pi + 5] = ch->m_drawData[pi + 8] - ch->m_drawData[pi - 4];
		}
		//����ĩβ�������
		int pe = 6 * (j * numNodes + numNodes - 1);
		ch->m_drawData[pe + 3] = ch->m_drawData[pe + 0] - ch->m_drawData[pe - 6];
		ch->m_drawData[pe + 4] = ch->m_drawData[pe + 1] - ch->m_drawData[pe - 5];
		ch->m_drawData[pe + 5] = ch->m_drawData[pe + 2] - ch->m_drawData[pe - 4];
	}
}