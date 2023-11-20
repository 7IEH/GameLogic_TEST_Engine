#include "pch.h"
#include "EHTimeMgr.h"
#include "EHEngine.h"

TimeMgr* TimeMgr::m_SingleInstance = nullptr;

TimeMgr::TimeMgr()
	: m_iFrequency{}
	, m_iPrevCounter{}
	, m_iCurCounter{}
	, m_fTime(0.f)
	, m_iCall(0)
{
	typedef void (*VOID_FUNC)(); atexit((VOID_FUNC)(&TimeMgr::Destroy));
}

TimeMgr::~TimeMgr()
{

}

void TimeMgr::init()
{
	QueryPerformanceFrequency(&m_iFrequency);

	QueryPerformanceCounter(&m_iPrevCounter);
}

void TimeMgr::tick()
{
	QueryPerformanceCounter(&m_iCurCounter);

	LONGLONG diffCounter = m_iCurCounter.QuadPart - m_iPrevCounter.QuadPart;
	m_fDelatTime = static_cast<float>(diffCounter) / static_cast<float>(m_iFrequency.QuadPart);

	m_iPrevCounter = m_iCurCounter;

	m_fTime += m_fDelatTime;
	if (1.f <= m_fTime)
	{
		wchar_t szText[50] = {};
		swprintf_s(szText, 50, L"DeltaTime : %f, FPS : %d", m_fDelatTime, m_iCall);
		SetWindowText(Engine::GetInst()->GetMainWind(), szText);

		m_iCall = 0;
		m_fTime = 0.f;
	}

	++m_iCall;
}
