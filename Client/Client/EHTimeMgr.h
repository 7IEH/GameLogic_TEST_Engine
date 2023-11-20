#pragma once


class TimeMgr
{
	SINGLETON(TimeMgr)
private:
	LARGE_INTEGER m_iFrequency;
	LARGE_INTEGER m_iPrevCounter;
	LARGE_INTEGER m_iCurCounter;
	float m_fDelatTime;

	UINT			m_iCall;
	float			m_fTime;

public:
	float GetDeltaTime() { return m_fDelatTime; }

public:
	void init();
	void tick();

};

