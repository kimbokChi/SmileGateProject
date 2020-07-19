#include "DXUT.h"
#include "StageONE.h"

#include "Player.h"
#include "DummyEnemy.h"

void StageONE::Init()
{
	mButton = new Button(Vector2(WINSIZEX - 160, 20));
	mButton->SetChangeImage("DaengDaengYi1", "DaengDaengYi3", "DaengDaengYi2");
	mButton->SetButtonScale(RECT{ 0, 0, 128, 128 });

	mBackGround = IMAGE->AddImage("BackGround","./image/BackGround/backgruond.png");

	mEnemySpawnTimer.SetTimer(1.85f, true);

	OBJECT->AddObject(new Player());

	USER_INTERFACE->AddUI(new PHealthBar());
	USER_INTERFACE->AddUI(mButton);

	mHCloud[0] = IMAGE->AddImage("CloudHuge", "./image/BackGround/Cloud/Cloud1.png");
	mHCloud[1] = mHCloud[0];

	mMCloud[0] = IMAGE->AddImage("CloudMiddle", "./image/BackGround/Cloud/Cloud2.png");
	mMCloud[1] = mMCloud[0];

	mSCloud[0] = IMAGE->AddImage("CloudSmall", "./image/BackGround/Cloud/Cloud3.png");
	mSCloud[1] = mSCloud[0];

	mHCloudPos[0] = ZERO; mHCloudPos[1] = Vector2(WINSIZEX, 0);
	mMCloudPos[0] = ZERO; mMCloudPos[1] = Vector2(WINSIZEX, 0);
	mSCloudPos[0] = ZERO; mSCloudPos[1] = Vector2(WINSIZEX, 0);
}

void StageONE::Update()
{
	mEnemySpawnTimer.Update();

	if (mEnemySpawnTimer.TimeOver())
	{
		int ScrOffset = SCREEN_OFFSET;

		Vector2 Pos;
				Pos = Vector2(WINSIZEX, RANDOM(ScrOffset, WINSIZEY - ScrOffset));


		switch (RANDOM(0, 3))
		{
		case 0:
			OBJECT->AddObject(new DummyEnemy(Pos + (LEFT * 55.f), 2.5f));
			OBJECT->AddObject(new DummyEnemy(Pos + (DOWN * 80.f), 2.5f));
			OBJECT->AddObject(new DummyEnemy(Pos + (  UP * 80.f), 2.5f));
			break;

		case 1:
			OBJECT->AddObject(new DummyEnemy(Pos, 4.f));
			break;

		default:
			OBJECT->AddObject(new DummyEnemy(Pos, 0.f));
			break;
		}
	}

	for (int i = 0; i < 2; ++i)
	{
		mHCloudPos[i] += LEFT *   HUGE_CLOUD_SPEED;
		mMCloudPos[i] += LEFT * MIDDLE_CLOUD_SPEED;
		mSCloudPos[i] += LEFT *  SMALL_CLOUD_SPEED;

		if (mHCloudPos[i].x <= -WINSIZEX) { mHCloudPos[i].x = WINSIZEX; }
		if (mMCloudPos[i].x <= -WINSIZEX) { mMCloudPos[i].x = WINSIZEX; }
		if (mSCloudPos[i].x <= -WINSIZEX) { mSCloudPos[i].x = WINSIZEX; }
	}
}

void StageONE::Render()
{
	mBackGround->Render(ZERO);

	mSCloud[0]->Render(mSCloudPos[0]);
	mSCloud[1]->Render(mSCloudPos[1]);

	mMCloud[0]->Render(mMCloudPos[0]);
	mMCloud[1]->Render(mMCloudPos[1]);

	mHCloud[0]->Render(mHCloudPos[0]);
	mHCloud[1]->Render(mHCloudPos[1]);
}

void StageONE::Release()
{
	USER_INTERFACE->Release();
	OBJECT->Release();
	//파티클을 지우지 않는것이 아직은 더 자연스러운것 같다
	//PARTICLE->Release();
}
