#pragma once

#include "EHEntity.h"
#include "EHCamera.h"

#include "EHComponent.h"

class Obj
	: public Entity
{
private:
	Vec2				m_Pos;
	Vec2				m_Scale;
	vector<Component*>	m_vecComponent;
	int					m_iLayerIdx;


public:
	Vec2 GetPos() { return m_Pos; }
	//Vec2 GetRenderPos() { return Camera::GetInst()->GetRenderPos(m_Pos); }
	Vec2 GetScale() { return m_Scale; }

	void SetPos(Vec2 _Pos) { m_Pos = _Pos; }
	void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

	int GetLayerIdx() { return m_iLayerIdx; }


protected:
	template<typename T>
	T* AddComponent(const wstring& _strName = L"")
	{
		T* pNewCom = new T(this);
		m_vecComponent.push_back(pNewCom);
		pNewCom->SetName(_strName);
		return pNewCom;
	}

public:
	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < m_vecComponent.size(); ++i)
		{
			if (dynamic_cast<T*>(m_vecComponent[i]))
			{
				return (T*)m_vecComponent[i];
			}
		}

		return nullptr;
	}

	template<typename T>
	void GetComponents(vector<T*>& _out)
	{
		for (size_t i = 0; i < m_vecComponent.size(); ++i)
		{
			if (dynamic_cast<T>(m_vecComponent[i]))
			{
				_out.push_back((T*)m_vecComponent[i]);
			}
		}
	}


public:
	// Level �� ������ �� Level �ȿ� ����ִ� ������Ʈ or ������ ���۵ǰ��� ������ �շ��ϴ� ������Ʈ
	virtual void begin() {};

	// �� ƽ���� ȣ��
	virtual void tick(float _DT);

	// ��ӹ��� �ڽ� Ŭ�������� ������(override) �� �� ����
	virtual void finaltick(float _DT) final;

	// ������ �Լ�
	virtual void render(HDC _dc);


	void Destroy();


	// �浹 �̺�Ʈ
	/*virtual void BeginOverlap(Collider* _OwnCol, Obj* _OtherObj, Collider* _OtherCol) {}
	virtual void Overlap(Collider* _OwnCol, Obj* _OtherObj, Collider* _OtherCol) {}
	virtual void EndOverlap(Collider* _OwnCol, Obj* _OtherObj, Collider* _OtherCol) {}*/

private:
	void SetDead();

public:
	virtual Obj* Clone() = 0;
	Obj();
	Obj(const Obj& _Origin);
	virtual ~Obj();

	friend class Level;
	friend class TaskMgr;
};

