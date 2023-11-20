#pragma once

class Level;

class Engine
{
	SINGLETON(Engine);
private:
	HWND		m_hWnd;
	POINT		m_ptResolution;

	HDC			m_DC;
	HDC			m_subDC;
	HBITMAP		m_SubBitMap;

	Level*		m_Level;
	HPEN		m_arrPen[PEN_END];

public:
	// Access Func
	HWND GetMainWind() { return m_hWnd; }
	HDC GetMainDC() { return m_DC; }
	POINT GetResolution() { return m_ptResolution; }

	HPEN GetPen(PEN_TYPE _type) { return m_arrPen[_type]; }

public:
	void CreateDefaultGDI();

public:
	void init(HWND _hwnd, POINT _ptResolution);
	void tick();
};

