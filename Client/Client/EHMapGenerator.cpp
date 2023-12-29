#include "pch.h"
#include "EHMapGenerator.h"
#include <random>

class Node
{
public:
	Node* leftNode;
	Node* rightNode;
	Node* parentNode;
	Rect  m_rect;
	Rect  m_roomRect;
	
public:
	Vec2 Center()
	{
		return Vec2(m_roomRect.x + m_roomRect.w / 2.f, m_roomRect.y + m_roomRect.h / 2.f);
	}

public:
	Node(Rect _rect)
		:leftNode(nullptr)
		, rightNode(nullptr)
		, parentNode(nullptr)
		, m_rect(_rect)
		, m_roomRect{}
	{
	}

	~Node()
	{};
};

MapGenerator::MapGenerator()
{
}

MapGenerator::~MapGenerator()
{
	delete m_RootNode;
}

void MapGenerator::Awake()
{
	m_RootNode = new Node(Rect(0.f, 0.f, 6400.f, 3600.f));
	ThreadTask::Awake();
	Update();
}

//void MapGenerator::DrawRectangle(Rect _drawinfo)
//{
//	GameObject* _test = new GameObject();
//	Transform* tr = _test->AddComponent<Transform>();
//	tr->SetRelativeScale(Vec4(_drawinfo.w, _drawinfo.h, 1.f, 1.f));
//	tr->SetRelativePosition(Vec4(_drawinfo.x + _drawinfo.w / 2.f, _drawinfo.y + _drawinfo.h / 2.f, 0.f, 1.f));
//	tr->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
//
//	MeshRenderer* _playerRenderer = _test->AddComponent<MeshRenderer>();
//	_playerRenderer->SetMesh(AssetMgr::GetInst()->FindAsset<Mesh>(L"randMesh"));
//	_playerRenderer->SetMaterial(AssetMgr::GetInst()->FindAsset<Material>(L"randMat"));
//
//	Object::Instantiate(_test, (UINT)LAYER_TYPE::PLAYER);
//}

void MapGenerator::Update()
{
	Divide(m_RootNode, 0, 4);
	GenerateRoom(m_RootNode, 0, 4);
	GenerateRoad();
}

void MapGenerator::Divide(Node* _node, int _level, int _maxLevel)
{
	if (_level == _maxLevel)
		return;

	int _maxLength = (int)max(_node->m_rect.h, _node->m_rect.w);
	int _temp = (_maxLength * 0.6f - _maxLength * 0.4f + 1);
	int _split = rand() % _temp + _maxLength * 0.4f;

	if (_node->m_rect.h <= _node->m_rect.w)
	{
		_node->leftNode = new Node(Rect(_node->m_rect.x, _node->m_rect.y, _split, _node->m_rect.h));
		_node->rightNode = new Node(Rect(_node->m_rect.x + _split, _node->m_rect.y, _node->m_rect.w - _split, _node->m_rect.h));
	}
	else
	{
		_node->leftNode = new Node(Rect(_node->m_rect.x, _node->m_rect.y, _node->m_rect.w, _split));
		_node->rightNode = new Node(Rect(_node->m_rect.x, _node->m_rect.y + _split, _node->m_rect.w, _node->m_rect.h - _split));
	}
	_node->leftNode->parentNode = _node;
	_node->rightNode->parentNode = _node;

	Divide(_node->leftNode, _level + 1, _maxLevel);
	Divide(_node->rightNode, _level + 1, _maxLevel);
}

// random rand()%(b-a+1)+a

Rect MapGenerator::GenerateRoom(Node* _node, int _level, int _maxLevel)
{
	Rect _temporary = {};
	if (_level == _maxLevel)
	{
		Rect _rect = _node->m_rect;

		int _temp = _rect.w - _rect.w / 2.f + 1;
		_node->m_roomRect.w = rand() % _temp + _rect.w / 2.f;

		_temp = _rect.h - _rect.h / 2.f + 1;
		_node->m_roomRect.h = rand() % _temp + _rect.h / 2.f;

		_temp = _rect.w - _node->m_roomRect.w - 1.f + 1;
		_node->m_roomRect.x = _rect.x + (rand() % _temp + 1.f);

		_temp = _rect.h - _node->m_roomRect.h - 1.f + 1;
		_node->m_roomRect.y = _rect.y + (rand() % _temp + 1.f);


		//DrawRectangle(_node->m_roomRect);
		_temporary = _node->m_roomRect;
		FillRoom(_node->m_roomRect);
	}
	else
	{
		_node->leftNode->m_roomRect = GenerateRoom(_node->leftNode, _level + 1, _maxLevel);
		_node->rightNode->m_roomRect = GenerateRoom(_node->rightNode, _level + 1, _maxLevel);
		_temporary = _node->leftNode->m_roomRect;
	}

	return _temporary;
}

void MapGenerator::GenerateRoad()
{
}

void MapGenerator::FillRoom(Rect _rect)
{
	for (size_t y = _rect.y;y <= _rect.y + _rect.h - 64.f;y += 64)
	{
		for (size_t x = _rect.x;x <= _rect.x + _rect.w - 64.f;x += 64)
		{
			Rect _temp = {};
			_temp.x = x;
			_temp.y = y;
			_temp.h = 64.f;
			_temp.w = 64.f;
			DrawRectangle(_temp);
		}
	}
}