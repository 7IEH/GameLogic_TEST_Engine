#pragma once
#include "EHLevel.h"

class MapGenerator;
class LoadingLevel : public Level
{
private:

public:
	virtual void init() override;
	virtual void enter() override;
	virtual void exit() override;

	virtual void begin() override;
	virtual void tick() override;
	virtual void render(HDC _dc) override;
};

