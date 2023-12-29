#include "pch.h"
#include "EHLoadingLevel.h"

#include "EHKeyMgr.h"
#include "EHLevelMgr.h"

#include "EHPlayer.h"

#include "EHMapGenerator.h"

#include<mutex>
#include<condition_variable>

extern HANDLE test;

void LoadingLevel::init()
{
	Player* _player = new Player();
	_player->SetPos(Vec2(100.f, 100.f));
	_player->SetScale(Vec2(100.f, 100.f));
	AddObject(PLAYER, _player);
}

void LoadingLevel::enter()
{
	// 대기중인 스레드 깨움
	::SetEvent(test);
}

void LoadingLevel::exit()
{
}

void LoadingLevel::begin()
{
}

void LoadingLevel::tick()
{
	Level::tick();
	if (KEY_CHECK(KEY::ENTER, KEY_STATE::TAP))
	{
		LevelMgr::GetInst()->ChangeLevel(LEVEL_TYPE::START_LEVEL);
	}
}

void LoadingLevel::render(HDC _dc)
{
	Level::render(_dc);

	wchar_t num[50];
	swprintf(num, 50, L"%d", MapGenerator::GetProgress());
	TextOutW(_dc, 100, 100, num, sizeof(num));
}
