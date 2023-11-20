#pragma once

#include "EHEntity.h"
class Obj;
class CCollider;

class Layer
	: public Entity
{
private:
	vector<Obj*> 		m_vecObjects;
	vector<CCollider*>	m_vecCollider;

public:
	void begin();
	void tick(float _DT);
	void finaltick(float _DT);
	void render(HDC _dc);

	void clear() { m_vecCollider.clear(); }
	void AddObject(Obj* _Object) { m_vecObjects.push_back(_Object); }
	void RegisterCollider(CCollider* _Collider) { m_vecCollider.push_back(_Collider); }

	const vector<Obj*>& GetObjects() { return  m_vecObjects; }

	const vector<CCollider*>& GetColliders() { return m_vecCollider; }

	void DeleteAllObjects();


public:
	CLONE_DISABLE(Layer);
	Layer();
	Layer(const Layer& _Origin) = delete;
	~Layer();

	friend class CLevel;
	friend class CUIMgr;
};

