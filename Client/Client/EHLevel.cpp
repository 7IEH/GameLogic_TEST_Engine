#include "pch.h"
#include "EHLevel.h"

#include "EHTimeMgr.h"
#include "EHLayer.h"
#include "EHObj.h"

Level::Level()
	: m_TileRow(0)
	, m_TileCol(0)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i] = new Layer;
	}
}

Level::~Level()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		if (nullptr != m_Layer[i])
			delete m_Layer[i];
	}
}

void Level::begin()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->begin();
	}
}

void Level::tick()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->clear();
	}

	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->tick(DT);
	}

	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->finaltick(DT);
	}
}

void Level::render(HDC _dc)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->render(_dc);
	}
}

void Level::AddObject(LAYER _LayerType, Obj* _Object)
{
	// 레이어에 오브젝트를 집어넣는다.
	m_Layer[_LayerType]->AddObject(_Object);

	// 레이어 인덱스값을 오브젝트에 세팅해준다(오브젝트가 자신이 소속된 레이어 인덱스를 알게 한다)
	_Object->m_iLayerIdx = _LayerType;
}

void Level::DeleteAllObjects()
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		m_Layer[i]->DeleteAllObjects();
	}
}

void Level::DeleteObjectsByLayer(LAYER _Layer)
{
	m_Layer[_Layer]->DeleteAllObjects();
}

//void Level::CreateTile(UINT _Row, UINT _Col)
//{
//	DeleteObjectsByLayer(LAYER::TILE);
//
//	m_TileRow = _Row;
//	m_TileCol = _Col;
//
//	for (UINT i = 0; i < _Row; ++i)
//	{
//		for (UINT j = 0; j < _Col; ++j)
//		{
//			Tile* pTile = new CTile;
//
//			pTile->SetPos(Vec2(TILE_SIZE * j, TILE_SIZE * i));
//
//			AddObject(LAYER::TILE, pTile);
//		}
//	}
//}

Obj* Level::FindObjectByName(const wstring& _Name)
{
	for (UINT i = 0; i < LAYER::END; ++i)
	{
		const vector<Obj*>& vecObjects = m_Layer[i]->GetObjects();
		for (size_t j = 0; j < vecObjects.size(); ++j)
		{
			if (vecObjects[j]->GetName() == _Name)
			{
				return vecObjects[j];
			}
		}
	}

	return nullptr;
}
