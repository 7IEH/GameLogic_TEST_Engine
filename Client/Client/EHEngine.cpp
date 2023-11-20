#include "pch.h"
#include "EHEngine.h"

//Manger
#include "EHTimeMgr.h"
#include "EHKeyMgr.h"
#include "EHLevelMgr.h"

Engine* Engine::m_SingleInstance = nullptr;

Engine::Engine()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_DC(nullptr)
	, m_subDC(nullptr)
	, m_SubBitMap(nullptr)
	, m_Level(nullptr)
{
	typedef void (*VOID_FUNC)(); atexit((VOID_FUNC)(&Engine::Destroy));
}

Engine::~Engine()
{

}

void Engine::CreateDefaultGDI()
{
	m_arrPen[RED_PEN] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[BLUE_PEN] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[GREEN_PEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
}

//
void Engine::init(HWND _hwnd, POINT _ptResolution)
{
	m_hWnd = _hwnd;
	m_ptResolution = _ptResolution;

	SetWindowPos(m_hWnd, nullptr, 10, 10, m_ptResolution.x, m_ptResolution.y, 0);

	m_DC = GetDC(m_hWnd);

	m_SubBitMap = CreateCompatibleBitmap(m_DC, m_ptResolution.x, m_ptResolution.y);
	m_subDC = CreateCompatibleDC(m_DC);

	DeleteObject((HBITMAP)SelectObject(m_subDC, m_SubBitMap));

	// Manger 초기화
	TimeMgr::GetInst()->init();
	KeyMgr::GetInst()->init();
	LevelMgr::GetInst()->init();

	// Pen 초기화
	CreateDefaultGDI();
}

//
void Engine::tick()
{
	// Manager Update
	TimeMgr::GetInst()->tick();
	KeyMgr::GetInst()->tick();

	// LevelMgr
	LevelMgr::GetInst()->tick();
	LevelMgr::GetInst()->render(m_subDC);
}
