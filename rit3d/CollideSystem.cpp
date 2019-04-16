#include "pch.h"
#include "CollideSystem.h"
#include "RGameObject.h"
#include "CTransform.h"
#include "RMath.h"

CollideSystem::CollideSystem(RInt od) : ISystem(od) {
	m_type = COLLIDESYSTEM;
}

CollideSystem::~CollideSystem() {
	_deleteBVHTree(m_BHVTree);
	_deleteOctree(m_octree);
}

CollideSystem* CollideSystem::CreateInstance(RInt od) {
	return new CollideSystem(od);
}

//ϵͳ��ʼ��ʱ����
void CollideSystem::onAwake() {
	//0-sphere,1-box
	m_intersectionMethod[0][0] = _intersectionTest_sphere2sphere;
	m_intersectionMethod[0][1] = _intersectionTest_sphere2box;
	m_intersectionMethod[1][0] = _intersectionTest_box2sphere;
	m_intersectionMethod[1][1] = _intersectionTest_box2box;
}

//ϵͳ������ʱ����
void CollideSystem::onEnable() {

}

//ϵͳ��ʼ����ʱ����
void CollideSystem::onStart() {

}

//ʵ�屻��ӵ�ϵͳʱ����
void CollideSystem::onAddGameObject() {

}

//�����ӵ�ʵ��ʱ����
void CollideSystem::onAddComponent(COMPTYPE type, IComponent* pComp) {
	if (type == COMPTYPE::SPHERECOLLIDER || type == COMPTYPE::BOXCOLLIDER) {
		std::vector<CCollider*>::iterator iter;
		iter = std::find(m_colliderPool.begin(), m_colliderPool.end(), (CCollider*)pComp);
		if (iter == m_colliderPool.end()) {
			m_colliderPool.push_back((CCollider*)pComp);
		}
	}
}

//�����ʵ���Ƴ�ʱ����
void CollideSystem::onRemoveComponent(COMPTYPE type, IComponent* pComp) {
	if (type == COMPTYPE::SPHERECOLLIDER || type == COMPTYPE::BOXCOLLIDER) {
		std::vector<CCollider*>::iterator iter;
		iter = std::find(m_colliderPool.begin(), m_colliderPool.end(), (CCollider*)pComp);
		if (iter != m_colliderPool.end()) {
			m_colliderPool.erase(iter);
		}
	}
}

//ʵ���ϵͳ���Ƴ�ʱ����
void CollideSystem::onRemoveGameObject() {

}

//ϵͳ����ʱ����
void CollideSystem::onUpdate() {
	//����������ײ�������������ϵ�µļ�����Ϣ
	calcGeomInfoInWorld();
	if(m_cdt & CDT::TRAVERSAL) {
		m_cc1 = m_ci1 = 0;
		std::vector<CCollider*>::size_type i, j;
		std::vector<CCollider*>::size_type l = m_colliderPool.size();
		for (i = 0; i < l; i++) {
			for (j = i + 1; j < l; j++) {
				m_cc1++;
				if (_intersectionTest(m_colliderPool[i]->wBV, m_colliderPool[j]->wBV)) {
					m_ci1++;
				}
			}
		}
	}
	if(m_cdt & CDT::BVH) {
		m_cc2 = m_ci2 = 0;
		std::vector<CCollider*>::size_type i;
		std::vector<CCollider*>::size_type l = m_colliderPool.size();
		//����BVH��
		_buildBVHTree();
		//ÿ����ײ�����BVH������ײ���
		for (i = 0; i < l; i++) {
			CCollider* sc = m_colliderPool[i];
			IBV* bv = sc->wBV;
			std::vector<BVHNode*>::size_type k = 1;
			while (k < m_BHVArray.size()) {
				BVHNode* curr = m_BHVArray[k];
				if (curr->nodeType == BVHNODETYPE::LEAF) {
					//��Ҷ�ӽڵ�
					if (curr->pc == sc) {
						curr->active = false;
					}
					if (curr->active) {
						m_cc2++;
						if (_intersectionTest(bv, curr->bv)) {
							m_ci2++;
						}
					}
				}
				else {
					//����Ҷ�ӽڵ�
					m_cc2++;
					if (!_intersectionTest(bv, curr->bv)) {
						while (curr->nodeType == BVHNODETYPE::NODE) {
							k = curr->offset;
							curr = m_BHVArray[k];
						}
					}
				}
				k++;
			}

		}
	}

	if (m_cdt & CDT::OCTREE) {
		m_cc3 = m_ci3 = 0;
		//����Octree
		_buildOctree();
		//���ж������ײ���
		_testAllCollisionsInOctree(m_octree);
	}

	if (m_cdt & CDT::BST) {

	}
}

//ϵͳ����ʱonUpdate֮�����
void CollideSystem::onLateUpdate() {

}

//ϵͳ������ʱ����
void CollideSystem::onDisable() {

}

//ϵͳ��ע��ʱ����
void CollideSystem::onDestroy() {

}

//������ײ������
void CollideSystem::setCollisionDetectionStrategy(int _cdt) {
	if (m_cdt == _cdt) return;
	m_cdt = _cdt;
}

//����������ײ�������������ϵ�µļ�����Ϣ
void CollideSystem::calcGeomInfoInWorld() {
	for (auto c : m_colliderPool) {
		CSphereCollider* sc = (CSphereCollider*)c;
		glm::vec3 cw = glm::vec3(sc->gameObject->transform->getModelMatrix() * glm::vec4(sc->center, 1.0f));
		RFloat rw = glmp::max(sc->gameObject->transform->getScale()) * sc->radius;
		if (sc->wBV && ((SphereBV*)sc->wBV)->c == cw && ((SphereBV*)sc->wBV)->r == rw) {
			sc->dirty = false;
		}
		else {
			((SphereBV*)sc->wBV)->c = cw;
			((SphereBV*)sc->wBV)->r = rw;
			sc->dirty = true;
		}
	}
}

//�ཻ���
RBool CollideSystem::_intersectionTest(IBV* _bv1, IBV* _bv2) {
	return m_intersectionMethod[_bv1->type][_bv2->type](_bv1, _bv2);
}

//�ཻ��⣬�����
RBool CollideSystem::_intersectionTest_sphere2sphere(IBV* _bv1, IBV* _bv2) {
	SphereBV* bv1 = (SphereBV*)_bv1;
	SphereBV* bv2 = (SphereBV*)_bv2;
	glm::vec3 d = bv1->c - bv2->c;
	RFloat dis2 = glm::dot(d, d);
	return dis2 <= (bv1->r + bv2->r) * (bv1->r + bv2->r);
}

//�ཻ��⣬���������
RBool CollideSystem::_intersectionTest_sphere2box(IBV* _bv1, IBV* _bv2) {
	return true;
}

//�ཻ��⣬���������
RBool CollideSystem::_intersectionTest_box2sphere(IBV* _bv1, IBV* _bv2) {
	return _intersectionTest_sphere2box(_bv2, _bv1);
}

//�ཻ��⣬�������������
RBool CollideSystem::_intersectionTest_box2box(IBV* _bv1, IBV* _bv2) {
	return true;
}

//����BVH��
void CollideSystem::_buildBVHTree() {
	//ɾ��ԭ����BVHTree
	_deleteBVHTree(m_BHVTree);
	_buildBVHTreeCore(&m_BHVTree, 0, m_colliderPool.size() - 1);
	_tree2array();
}
void CollideSystem::_buildBVHTreeCore(BVHNode** tree, int start, int end) {
	int nums = end - start + 1;
	if (nums <= 0) return;//û�нڵ�ʱ�˳�
	BVHNode* pNode = new BVHNode;
	*tree = pNode;
	glm::vec3 separatDir(0.0f, 0.0f, 0.0f);
	pNode->bv = _computeBoundingVolumn(start, end, separatDir);
	pNode->nums = nums;
	pNode->active = true;

	if (1 == nums) {
		//ֻʣһ���ڵ�ʱ����ΪҶ�ӽڵ㣬����¼��Ӧ����ײ���
		pNode->nodeType = BVHNODETYPE::LEAF;
		pNode->pc = m_colliderPool[start];
		pNode->pLeft = nullptr;
		pNode->pRight = nullptr;
	}
	else {
		//ʣ����ڵ�ʱ��������
		pNode->nodeType = BVHNODETYPE::NODE;
		int k = _partition(start, end, separatDir, ((SphereBV*)pNode->bv)->c);
		_buildBVHTreeCore(&(pNode->pLeft), start, k);
		_buildBVHTreeCore(&(pNode->pRight), k + 1, end);
	}
}
void CollideSystem::_tree2array() {
	m_BHVArray.clear();
	std::stack<BVHNode*> s;
	BVHNode* p = m_BHVTree;
	while (p != nullptr || !s.empty()) {
		if (p != nullptr) {
			m_BHVArray.push_back(p);
			s.push(p);
			p = p->pLeft;
		}
		else {
			p = s.top();
			s.pop();
			if (p->nodeType == BVHNODETYPE::NODE) {
				p->offset = m_BHVArray.size();
			}
			p = p->pRight;
		}
	}
}

//ɾ��BVH��
void CollideSystem::_deleteBVHTree(BVHNode* pNode) {
	if (nullptr == pNode) return;
	_deleteBVHTree(pNode->pLeft);
	_deleteBVHTree(pNode->pRight);
	SafeDelete(pNode);
}

//����m_colliderPool��start��end��ײ������ܰ�Χ��
IBV* CollideSystem::_computeBoundingVolumn(int start, int end, glm::vec3& separating_axis) {
	SphereBV* bv = new SphereBV;
	if (start == end) {
		//ֻ��һ���ڵ�
		CCollider* collider = m_colliderPool[start];
		bv->c = ((SphereBV*)collider->wBV)->c;
		bv->r = ((SphereBV*)collider->wBV)->r;
	}
	else {
		//�ж���ڵ�
		//����sphere��Χ�е�Բ�ĵļ������ĵ�ΪԲ��
		bv->c = glm::vec3(0.0f, 0.0f, 0.0f);
		bv->r = 0.0f;
		for (int i = start; i <= end; i++) {
			CCollider* collider = m_colliderPool[i];
			bv->c += ((SphereBV*)collider->wBV)->c;
		}
		bv->c /= (end - start + 1.0f);
		for (int i = start; i <= end; i++) {
			CCollider* collider = m_colliderPool[i];
			RFloat nr = glm::length(bv->c - ((SphereBV*)collider->wBV)->c) + ((SphereBV*)collider->wBV)->r;
			if (nr > bv->r) {
				bv->r = nr;
				separating_axis = ((SphereBV*)collider->wBV)->c - bv->c;
			}
		}
	}
	return bv;
}

//���ֽڵ�
int CollideSystem::_partition(int start, int end, glm::vec3 dir, glm::vec3 point) {
	int i = start, j = end;
	if (j - i < 2) return i;
	while (i < j) {
		while (glm::dot(((SphereBV*)m_colliderPool[i]->wBV)->c - point, dir) >= 0.0f && i < end) {
			i++;
		}
		while (glm::dot(((SphereBV*)m_colliderPool[j]->wBV)->c - point, dir) < 0.0f && j > start) {
			j--;
		}
		if (i < j) {
			CCollider* temp = m_colliderPool[i];
			m_colliderPool[i] = m_colliderPool[j];
			m_colliderPool[j] = temp;
		}
	}
	return j;
}

//����octree
void CollideSystem::_buildOctree() {
	//���ԭ�е���
	//_deleteOctree(m_octree);
	//���octreeΪ�գ�����һ��octree
	int l = m_colliderPool.size();
	if (l == 0) return;
	if (nullptr == m_octree) {
		//����octree���ڵ�����ĺͰ뾶
		glm::vec3 c = glm::vec3(0.0f, 0.0f, 0.0f);//���ڵ�����
		RFloat hw = 0.0f;//���ڵ��������ȵ�һ��
		for (int i = 0; i < l; i++) {
			c += ((SphereBV*)m_colliderPool[i]->wBV)->c;
		}
		c /= l;
		for (int i = 0; i < l; i++) {
			CCollider* collider = m_colliderPool[i];
			glm::vec3 deltaC = glm::abs(c - ((SphereBV*)collider->wBV)->c) + ((SphereBV*)collider->wBV)->r;
			RFloat nhw = glmp::max(deltaC);
			if (nhw > hw) hw = nhw;
		}
		//��ʼ��һ��ָ����ȵ�octree
		m_octree = _buildOctreeCore(c, hw, m_octreeDepth);
	}

	//��octree�в�����ײ���
	for (int i = 0; i < l; i++) {
		if (m_colliderPool[i]->dirty) {
			_insertCollider(m_octree, m_colliderPool[i]);
		}
	}
}

OctreeNode* CollideSystem::_buildOctreeCore(glm::vec3 center, RFloat halfWidth, int stopDepth) {
	if (stopDepth <= 0) return nullptr;

	OctreeNode* pNode = new OctreeNode;
	pNode->center = center;
	pNode->halfWidth = halfWidth;

	glm::vec3 offset;
	RFloat step = halfWidth * 0.5f;
	for (int i = 0; i < 8; i++) {
		offset.x = ((i & 1) ? step : -step);
		offset.y = ((i & 2) ? step : -step);
		offset.z = ((i & 4) ? step : -step);
		pNode->pChild[i] = _buildOctreeCore(center + offset, step, stopDepth - 1);
	}
	/*
	���޺�   i(2)   i(10)
	I       111    7
	II      011    3
	III     010    2
	IV      110    6
	V       101    5
	VI      001    1
	VII     000    0
	VIII    100    4
	*/
	return pNode;
}

//��octree�в�����ײ���
void CollideSystem::_insertCollider(OctreeNode* pTree, CCollider* pC) {
	RInt index = 0;//���ޱ�ʶ
	RBool straddle = false;//�Ƿ�ͬʱ�����ӹ����ཻ
	for (int i = 0; i < 3; i++) {
		float delta = ((SphereBV*)pC->wBV)->c[i] - pTree->center[i];
		if (abs(delta) < ((SphereBV*)pC->wBV)->r) {
			straddle = true;
			break;
		}
		if (delta > 0.0f) {
			index |= (1 << i);
		}
	}
	if (!straddle && pTree->pChild[index]) {
		//��ͬʱ�����ӹ����ཻ��ͬʱ�����ӹ��ޣ����뵽�ӹ�����
		_insertCollider(pTree->pChild[index], pC);
	}
	else {
		//����(ͬʱ�����ӹ����ཻ���򲻴����ӹ���)�����뵽��ǰ�ڵ���
		if (pC->paNode != pTree) {
			if (pC->paNode) {
				//��ԭ�����Ƴ�
				pC->paNode->cList.remove(pC);
			}
			pTree->cList.push_back(pC);
			pC->paNode = pTree;
		}
	}
}

//ɾ��octree
void CollideSystem::_deleteOctree(OctreeNode* pNode) {
	if (nullptr == pNode) return;
	for (int i = 0; i < 8; i++) {
		_deleteOctree(pNode->pChild[i]);
	}
	SafeDelete(pNode);
}

//octree�ж�����ײ���
void CollideSystem::_testAllCollisionsInOctree(OctreeNode* pTree) {
	//����Ҫ�ͱ��ڵ��еĶ�����ײ��⣬��Ҫ���������Ƚ���е����ж�����ײ���
	static OctreeNode* ancestorStack[MAX_OCTREE_DEPTH];
	static int depth = 0;
	ancestorStack[depth++] = pTree;
	for (int n = 0; n < depth; n++) {
		for (auto pC1 : pTree->cList) {
			for (auto pC2 : ancestorStack[n]->cList) {
				if (pC1 == pC2) break;
				m_cc3++;
				if (_intersectionTest(pC1->wBV, pC2->wBV)) {
					m_ci3++;
				}
			}
		}
	}

	//��������
	for (int i = 0; i < 8; i++) {
		if (pTree->pChild[i])
			_testAllCollisionsInOctree(pTree->pChild[i]);
	}

	depth--;
}