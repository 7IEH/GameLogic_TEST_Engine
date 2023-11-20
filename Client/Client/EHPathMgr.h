#pragma once

class PathMgr
{
	SINGLETON(PathMgr)
private:
	vector<FKeyData>	m_vecKeyData;

public:
	KEY_STATE GetKeyState(KEY _key) { return m_vecKeyData[_key].eState; }

public:
	void init();
	void tick();
};

