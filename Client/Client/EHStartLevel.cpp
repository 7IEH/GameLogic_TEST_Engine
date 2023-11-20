#include "pch.h"
#include "EHStartLevel.h"

#include "EHKeyMgr.h"
#include "EHLevelMgr.h"

#include "EHPlayer.h"

void StartLevel::init()
{
	Player* _player = new Player();
	_player->SetPos(Vec2(100.f, 100.f));
	_player->SetScale(Vec2(200.f, 200.f));
	AddObject(PLAYER, _player);
}

void StartLevel::enter()
{
}

void StartLevel::exit()
{

}

void StartLevel::begin()
{
}

void StartLevel::tick()
{
	Level::tick();

	if (KEY_CHECK(KEY::ENTER, KEY_STATE::TAP))
	{
		LevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::LOADING_LEVEL);
	}
}

void StartLevel::render(HDC _dc)
{
	Level::render(_dc);
}
