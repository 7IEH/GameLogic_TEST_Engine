#include "pch.h"
#include "EHLevelMgr.h"

#include "EHEngine.h"
#include "EHLevel.h"

#include "EHObj.h"
#include "EHPlayer.h"

#include "EHStartLevel.h"
#include "EHLoadingLevel.h"

LevelMgr* LevelMgr::m_SingleInstance = nullptr;

LevelMgr::LevelMgr()
	:m_pCurLevel(nullptr)
	, m_arrLevels{}
{
	typedef void (*VOID_FUNC)(); atexit((VOID_FUNC)(&LevelMgr::Destroy));
}

LevelMgr::~LevelMgr()
{

}

void LevelMgr::ChangeLevel(LEVEL_TYPE _Level_Type)
{
	if (m_pCurLevel == m_arrLevels[(UINT)_Level_Type])
		return;

	if (nullptr != m_pCurLevel)
		m_pCurLevel->exit();

	m_pCurLevel = m_arrLevels[(UINT)_Level_Type];

	m_pCurLevel->enter();

	m_pCurLevel->begin();
}

void LevelMgr::init()
{
	// 모든 레벨 생성
	m_arrLevels[(UINT)LEVEL_TYPE::START_LEVEL] = new StartLevel;
	m_arrLevels[(UINT)LEVEL_TYPE::LOADING_LEVEL] = new LoadingLevel;

	// 레벨 초기화
	for (UINT i = 0; i < (UINT)LEVEL_TYPE::END; ++i)
	{
		m_arrLevels[i]->init();
	}

	// Level
	ChangeLevel(LEVEL_TYPE::START_LEVEL);
}

void LevelMgr::tick()
{
	m_pCurLevel->tick();
}

void LevelMgr::render(HDC _dc)
{
	POINT ptResolution = Engine::GetInst()->GetResolution();
	Rectangle(_dc, -1, -1, ptResolution.x, ptResolution.y);

	m_pCurLevel->render(_dc);

	BitBlt(Engine::GetInst()->GetMainDC(), 0, 0, ptResolution.x, ptResolution.y, _dc, 0, 0, SRCCOPY);
}
