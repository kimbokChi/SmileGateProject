#pragma once
#include "PHealthBar.h"

class StageONE : public Scence
{
public:
	virtual void Init   () override;
	virtual void Update () override;
	virtual void Render () override;
	virtual void Release() override;

private:

	Timer mEnemySpawnTimer;

	PHealthBar mPlayerHPUI;
};

