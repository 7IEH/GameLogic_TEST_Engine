#include "pch.h"
#include "EHPlayer.h"

#include "EHKeyMgr.h"
#include "EHProjectile.h"

#include "EHLevelMgr.h"
#include "EHLevel.h"

Player::Player()
	:m_speed(400.f)
{
}

Player::~Player()
{

}

void Player::tick(float _DT)
{
	Vec2 _pos = GetPos();

	bool flat = false;
	if (KEY_PRESSED(KEY::A))
	{
		_pos.x -= _DT * m_speed;
	}

	
	if (KEY_PRESSED(KEY::D))
	{
		_pos.x += _DT * m_speed;
	}

	if (KEY_PRESSED(KEY::W))
	{
		_pos.y -= _DT * m_speed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		_pos.y += _DT * m_speed;
	}

	if (KEY_TAP(KEY::SPACE))
	{
		for (int i = 1;i <= 3;i++)
		{
			Projectile* _proj = new Projectile;
			_proj->SetPos(this->GetPos());
			_proj->SetScale(Vec2(20.f, 20.f));
			_proj->SetTheta((-45.f*i)/(180.f /3.14f));

			LevelMgr::GetInst()->GetCurLevel()->GetLayer(LAYER::PLAYER_PJ)->AddObject(_proj);
		}
	}

	SetPos(_pos);
}

void Player::render(HDC _dc)
{
	HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hOldPen = (HPEN)SelectObject(_dc,hRedPen);

	HBRUSH hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(_dc, hGreenBrush);

	Rectangle(_dc, GetPos().x - GetScale().x / 2.f,
		GetPos().y - GetScale().y / 2.f,
		GetPos().x + GetScale().x / 2.f,
		GetPos().y + GetScale().y / 2.f);

	SelectObject(_dc, hOldPen);
	DeleteObject(hRedPen);

	SelectObject(_dc, hOldBrush);
	DeleteObject(hGreenBrush);
}