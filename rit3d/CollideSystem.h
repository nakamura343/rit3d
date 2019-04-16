#pragma once
#include "RCommon.h"
#include "ISystem.h"
#include "CCollider.h"

//��ײ������ Collision detection strategy
enum CDT {
	TRAVERSAL = 1,//����������
	BVH = 2,//��ΰ�Χ��
	OCTREE = 4,//�˲���
	BST = 8,//���ֿռ仮����
};

//BVH���ڵ����ͣ�Ҷ�ӽڵ�ͷ�Ҷ�ӽڵ�
enum BVHNODETYPE {
	NODE,
	LEAF,
};

//Octree�ڵ�
class OctreeNode {
public:
	glm::vec3 center;
	RFloat halfWidth;
	OctreeNode* pChild[8]{ nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	std::list<CCollider*> cList;
};

const int MAX_OCTREE_DEPTH = 5;

//BVH���ڵ�
class BVHNode {
public:
	BVHNode() {};
	~BVHNode() {
		if (bv) {
			SafeDelete(bv);
		}
	};
	IBV* bv;//�ڵ��Ӧ�İ�Χ��,�����ڵ�ʱ����������newһ��bv���������ܰ���ײ����е�IBVָ��ֱ�Ӹ�ֵ
	BVHNODETYPE nodeType;//�ڵ�����
	int nums;//��������ײ���������
	CCollider* pc;//�ڵ�����Ӧ����ײ���
	RBool active;//�ڵ��Ƿ��Ծ���Ƿ���Ҫ������ײ��⣩
	BVHNode* pLeft;
	BVHNode* pRight;
	int offset{ -1 };
};

class CollideSystem : public ISystem {
private:
	CollideSystem(RInt od);
	virtual ~CollideSystem();

	std::vector<CCollider*> m_colliderPool;
	std::function<RBool(IBV*, IBV*)> m_intersectionMethod[2][2];
	int m_cdt{ CDT::TRAVERSAL };
	int m_cc1, m_ci1, m_cc2, m_ci2, m_cc3, m_ci3;
public:
	static CollideSystem* CreateInstance(RInt od);

	//ϵͳ��ʼ��ʱ����
	virtual void onAwake();

	//ϵͳ������ʱ����
	virtual void onEnable();

	//ϵͳ��ʼ����ʱ����
	virtual void onStart();

	//ʵ�屻��ӵ�ϵͳʱ����
	virtual void onAddGameObject();

	//�����ӵ�ʵ��ʱ����
	virtual void onAddComponent(COMPTYPE type, IComponent* pComp);

	//�����ʵ���Ƴ�ʱ����
	virtual void onRemoveComponent(COMPTYPE type, IComponent* pComp);

	//ʵ���ϵͳ���Ƴ�ʱ����
	virtual void onRemoveGameObject();

	//ϵͳ����ʱ����
	virtual void onUpdate();

	//ϵͳ����ʱonUpdate֮�����
	virtual void onLateUpdate();

	//ϵͳ������ʱ����
	virtual void onDisable();

	//ϵͳ��ע��ʱ����
	virtual void onDestroy();

	//������ײ������
	void setCollisionDetectionStrategy(int _cdt);

private:
	//�ཻ���
	RBool _intersectionTest(IBV* _bv1, IBV* _bv2);
	static RBool _intersectionTest_sphere2sphere(IBV* _bv1, IBV* _bv2);
	static RBool _intersectionTest_sphere2box(IBV* _bv1, IBV* _bv2);
	static RBool _intersectionTest_box2sphere(IBV* _bv1, IBV* _bv2);
	static RBool _intersectionTest_box2box(IBV* _bv1, IBV* _bv2);

	//����������ײ�������������ϵ�µļ�����Ϣ
	void calcGeomInfoInWorld();

	//----����BVH��-----
	//BVH��
	BVHNode* m_BHVTree{ nullptr };
	std::vector<BVHNode*> m_BHVArray;

	//����BVH��
	void _buildBVHTree();
	void _buildBVHTreeCore(BVHNode** tree, int start, int end);
	void _tree2array();
	//ɾ��BVH��
	void _deleteBVHTree(BVHNode* pNode);
	//����m_colliderPool��start��end��ײ������ܰ�Χ��,������һ���ָ���ķ���
	IBV* _computeBoundingVolumn(int start, int end, glm::vec3& separating_axis);
	//���ֽڵ�
	int _partition(int start, int end, glm::vec3 dir, glm::vec3 point);

	//----���ڰ˲���-----
	RInt m_octreeDepth{ 2 };//�����
	OctreeNode* m_octree{ nullptr };//�˲���

	//����octree
	void _buildOctree();
	OctreeNode* _buildOctreeCore(glm::vec3 center, RFloat halfWidth, int stopDepth);
	//��octree�в�����ײ���
	void _insertCollider(OctreeNode* pTree, CCollider* pC);
	//ɾ��octree
	void _deleteOctree(OctreeNode* pNode);
	//octree�ж�����ײ���
	void _testAllCollisionsInOctree(OctreeNode* pTree);

	//----����----
	//std::map<CCollider*, std::map<CCollider*, RBool>> m_cache;
};

