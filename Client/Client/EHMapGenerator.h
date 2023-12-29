#pragma once

#include "EHThreadTask.h"

class Node;
struct Rect
{
	int x;
	int y;
	int w;
	int h;

	Rect()
		:x(0)
		,y(0)
		,w(0)
		,h(0)
	{

	}

	Rect(int _x,int _y,int _w, int _h)
		:x(_x)
		,y(_y)
		,w(_w)
		,h(_h)
	{

	}

	~Rect()
	{

	}
};

class MapGenerator
	:public ThreadTask
{
private:
	Vec2			m_mapSize;
	Node* m_RootNode;


public:
	virtual void Awake() override;
	virtual void Update() override;

private:
	void Divide(Node* _node, int _level, int _maxLevel);
	Rect GenerateRoom(Node* _node, int _level, int _maxLevel);
	void GenerateRoad();
	void FillRoom(Rect _rect);

	void DrawRectangle(Rect _drawinfo);

public:
	MapGenerator();
	virtual ~MapGenerator();
};

