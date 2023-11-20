#pragma once
#include "EHLevel.h"

class StartLevel : public Level
{
private:

public:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;

	virtual void begin();
	virtual void tick();
	virtual void render(HDC _dc);
};

