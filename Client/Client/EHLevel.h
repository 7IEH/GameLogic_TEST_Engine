#pragma once

#include "EHEntity.h"

#include "EHLayer.h"

class Obj;

class Level
	: public Entity
{
private:
	Layer* m_Layer[LAYER::END];

	UINT	m_TileRow;
	UINT	m_TileCol;


public:
	virtual void init() = 0;
	virtual void enter() = 0;
	virtual void exit() = 0;

	virtual void begin();
	virtual void tick();
	virtual void render(HDC _dc);

	// 레벨이 소유하고 있는 모든 레이어를 순회하면서 T 타입에 해당하는 객체를 찾아서 결과(_Out) 벡터에 담아준다.
	template<typename T>
	void GetObjects(vector<T*>& _Out);

	// 레벨이 소유하고 있는 특정 레이어의 오브젝트 목록을 반환한다.
	const vector<Obj*>& GetObjects(LAYER _LayerType) { return m_Layer[_LayerType]->GetObjects(); }

	Layer* GetLayer(int LayerIdx)
	{
		assert(!(LayerIdx < 0 || LAYER::END <= LayerIdx));
		return m_Layer[LayerIdx];
	}

protected:
	void AddObject(LAYER _LayerType, Obj* _Object);
	void DeleteAllObjects();
	void DeleteObjectsByLayer(LAYER _Layer);

public:
	void CreateTile(UINT _Row, UINT _Col);
	UINT GetTileCol() { return m_TileCol; }
	UINT GetTileRow() { return m_TileRow; }

	Obj* FindObjectByName(const wstring& _Name);

public:
	CLONE_DISABLE(Level);
	Level();
	Level(const Level& _Origin) = delete;
	~Level();

	friend class LevelMgr;
	friend class TaskMgr;
};

template<typename T>
inline void Level::GetObjects(vector<T*>& _Out)
{
	for (UINT j = 0; j < LAYER::END; ++j)
	{
		for (size_t i = 0; i < m_Layer[j]->m_vecObjects.size(); ++i)
		{
			T* pObj = dynamic_cast<T*>(m_Layer[j]->m_vecObjects[i]);

			if (nullptr != pObj)
			{
				_Out.push_back(pObj);
			}
		}
	}
}
