#pragma once
#include "EHObj.h"

class Player
	: public Obj
{
private:
	float m_speed;

public:
	virtual void tick(float _DT)override;
	virtual void render(HDC _dc)override;

	virtual Obj* Clone() override { return this; }

public:
	Player();
	~Player();
};

