#include "pch.h"
#include "EHProjectile.h"

#include "EHTimeMgr.h"

Projectile::Projectile()
	:m_fSpeed(200.f)
	, m_fTheta(0.f)
{
}

Projectile::~Projectile()
{
}

void Projectile::tick(float _DT)
{
	Vec2 _pos = GetPos();

	_pos.x += TimeMgr::GetInst()->GetDeltaTime() * m_fSpeed * cosf(m_fTheta);
	_pos.y += TimeMgr::GetInst()->GetDeltaTime() * m_fSpeed * sinf(m_fTheta);

	SetPos(_pos);
}

void Projectile::render(HDC _dc)
{
	HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(_dc, hRedPen);

	HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(_dc, hGreenBrush);

	Obj::render(_dc);

	SelectObject(_dc, hOldPen);
	DeleteObject(hRedPen);

	SelectObject(_dc, hOldBrush);
	DeleteObject(hGreenBrush);
}
