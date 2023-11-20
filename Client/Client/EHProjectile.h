#pragma once
#include "EHObj.h"

class Projectile
	:public Obj
{
private:
	float m_fSpeed;
	float m_fTheta;

public:
	void SetTheta(float _Theta) { m_fTheta = _Theta; }

public:
	virtual void tick(float _DT)override;
	virtual void render(HDC _dc)override;

	virtual Obj* Clone() override { return this; }

public:
	Projectile();
	~Projectile();
};


