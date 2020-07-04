#include "DXUT.h"
#include "StageONE.h"

#include "Player.h"
#include "DummyEnemy.h"

void StageONE::Init()
{
	mEnemySpawnTimer.SetTimer(0.5f, true);

	OBJECT->AddObject(new Player());
}

void StageONE::Update()
{
	if (mEnemySpawnTimer.TimeOver())
	{
		OBJECT->AddObject(new DummyEnemy());
	}
}

void StageONE::Render()
{
}

void StageONE::Release()
{
}