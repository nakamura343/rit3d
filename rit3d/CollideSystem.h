#pragma once
#include "RCommon.h"
#include "ISystem.h"
#include "CCollider.h"

//BVH���ڵ����ͣ�Ҷ�ӽڵ�ͷ�Ҷ�ӽڵ�
enum BVHNODETYPE {
	NODE,
	LEAF,
};
//sphere bounding volume
struct BV {
	glm::vec3 center;
	RFloat radius;
};
//BVH���ڵ�
struct BVHNode {
	BV bv;//�ڵ��Ӧ�İ�Χ��
	BVHNODETYPE nodeType;//�ڵ�����
	int nums;//��������ײ���������
	CCollider* pc;//�ڵ�����Ӧ����ײ���
	RBool active;//�ڵ��Ƿ��Ծ���Ƿ���Ҫ������ײ��⣩
	BVHNode* pLeft;
	BVHNode* pRight;
};

class CollideSystem : public ISystem {
private:
	CollideSystem(RInt od);
	virtual ~CollideSystem();

	std::vector<CCollider*> m_colliderPool;
	std::function<RBool(CCollider*, CCollider*)> m_intersectionMethod[2][2];
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

private:
	//�ཻ���
	RBool _intersectionTest(CCollider* c1, CCollider* c2);
	static RBool _intersectionTest_sphere2sphere(CCollider* c1, CCollider* c2);
	static RBool _intersectionTest_sphere2box(CCollider* c1, CCollider* c2);
	static RBool _intersectionTest_box2sphere(CCollider* c1, CCollider* c2);
	static RBool _intersectionTest_box2box(CCollider* c1, CCollider* c2);

	//����������ײ�������������ϵ�µļ�����Ϣ
	void calcGeomInfoInWorld();

	//----����BVH��-----
	//BVH��
	BVHNode* m_BHVTree{ nullptr };
	//����BVH��
	void _buildBVHTree();
	void _buildBVHTreeCore(BVHNode** tree, int start, int end);
	//ɾ��BVH��
	void _deleteBVHTree(BVHNode* pNode);
	//����m_colliderPool��start��end��ײ������ܰ�Χ��,������һ���ָ���ķ���
	BV _computeBoundingVolumn(int start, int end, glm::vec3& separating_axis);
	//���ֽڵ�
	int _partition(int start, int end, glm::vec3 dir, glm::vec3 point);
};

