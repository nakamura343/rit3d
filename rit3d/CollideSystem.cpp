#include "pch.h"
#include "CollideSystem.h"
#include "RGameObject.h"
#include "CTransform.h"
#include "RMath.h"

CollideSystem::CollideSystem(RInt od) : ISystem(od) {
	m_type = COLLIDESYSTEM;
}

CollideSystem::~CollideSystem() {

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
	static int counts_intersect1 = 0, counts_intersect2 = 0, counts_calc1 = 0, counts_calc2 = 0;
	int count_intersect1 = 0, count_intersect2 = 0, count_calc1 = 0, count_calc2 = 0;
	//����������ײ�������������ϵ�µļ�����Ϣ
	calcGeomInfoInWorld();
	std::vector<CCollider*>::size_type i, j;
	std::vector<CCollider*>::size_type l = m_colliderPool.size();
	for (i = 0; i < l; i++) {
		for (j = i + 1; j < l; j++) {
			count_calc1++;
			if (_intersectionTest(m_colliderPool[i]->wBV, m_colliderPool[j]->wBV)) {
				count_intersect1++;
			}
		}
	}

	//����BVH��
	_buildBVHTree();
	//ÿ����ײ�����BVH������ײ���
	for (i = 0; i < l; i++) {
		std::queue<BVHNode*> qNode;
		qNode.push(m_BHVTree);
		CCollider* sc = m_colliderPool[i];
		IBV* bv = sc->wBV;
		while (!qNode.empty()) {
			BVHNode* currNode = qNode.front();
			qNode.pop();
			//���ӽڵ�
			if (currNode->pLeft) {
				if (currNode->pLeft->nodeType == BVHNODETYPE::NODE) {
					//����Ҷ�ӽڵ�
					count_calc2++;
					if (_intersectionTest(bv, currNode->pLeft->bv)) {
						qNode.push(currNode->pLeft);
					}
				}
				else {
					//��Ҷ�ӽڵ�
					if (currNode->pLeft->pc == sc) {
						currNode->pLeft->active = false;
					}
					if (currNode->pLeft->active) {
						count_calc2++;
						if (_intersectionTest(bv, currNode->pLeft->bv)) {
							count_intersect2++;
						}
					}
				}
			}
			//���ӽ��
			if (currNode->pRight) {
				if (currNode->pRight->nodeType == BVHNODETYPE::NODE) {
					//����Ҷ�ӽڵ�
					count_calc2++;
					if (_intersectionTest(bv, currNode->pRight->bv)) {
						qNode.push(currNode->pRight);
					}
				}
				else {
					//��Ҷ�ӽڵ�
					if (currNode->pRight->pc == sc) {
						currNode->pRight->active = false;
					}
					if (currNode->pRight->active) {
						count_calc2++;
						if (_intersectionTest(bv, currNode->pRight->bv)) {
							count_intersect2++;
						}
					}
				}
			}
		}
	}

	if (count_intersect1 != counts_intersect1) {
		counts_intersect1 = count_intersect1;
		cout << "counts_intersect1:" << counts_intersect1 << endl;
	}
	if (count_intersect2 != counts_intersect2) {
		counts_intersect2 = count_intersect2;
		cout << "counts_intersect2:" << counts_intersect2 << endl;
	}
	if (count_calc1 != counts_calc1) {
		counts_calc1 = count_calc1;
		cout << "counts_calc1:" << counts_calc1 << endl;
	}
	if (count_calc2 != counts_calc2) {
		counts_calc2 = count_calc2;
		cout << "counts_calc2:" << counts_calc2 << endl;
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

//����������ײ�������������ϵ�µļ�����Ϣ
void CollideSystem::calcGeomInfoInWorld() {
	for (auto c : m_colliderPool) {
		CSphereCollider* sc = (CSphereCollider*)c;
		((SphereBV*)sc->wBV)->c = glm::vec3(sc->gameObject->transform->getModelMatrix() * glm::vec4(sc->center, 1.0f));
		((SphereBV*)sc->wBV)->r = glmp::max(sc->gameObject->transform->getScale()) * sc->radius;
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