#include "DXUT.h"
#include "Player.h"

#include "PBullet.h"
#include "DummyEnemy.h"

#include "PBoost.h"

Player::Player()
{
}

Player::~Player()
{
	mAnimation.Clear();
}

void Player::Init()
{
	Name = "Player";
	Tag = TAG::PLAYER;

	Position = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	mAttackPoint = (Position + Vector2(130.5f, 20.5f));

	mAnimation.AddFrame("./image/Player/Default/", "Player", 18);

	CircleRadius = 50.f;

	mSpeed = 12.f;

	mTimer.SetTimer(0.15f, true);

	mAttackParticle = nullptr;

					  mBoostEffect = new PBoost();
	OBJECT->AddObject(mBoostEffect);

	this->Child = mBoostEffect;
				  mBoostEffect->Parent = this;

	HealthInit(10.f);
}

void Player::Update()
{
	Velocity = ZERO;

	if (INPUT->GetKeyDown(ATTACKKEY) && mAttackParticle == nullptr)
	{
		mAttackParticle = PARTICLE->Instantiate(PARTICLES::PATTACK, mAttackPoint);
	}
	if (INPUT->GetKey(VK_SPACE) && mTimer.TimeOver())
	{		
		OBJECT->AddObject(new PBullet(mAttackPoint));
	}
	if (INPUT->GetKey(VK_UP))
	{
		Velocity = UP * mSpeed;
	}
	else if (INPUT->GetKey(VK_DOWN))
	{
		Velocity = DOWN * mSpeed;
	}
	if (INPUT->GetKey(VK_RIGHT))
	{
		Velocity = RIGHT * mSpeed;
	}
	else if (INPUT->GetKey(VK_LEFT))
	{
		Velocity = LEFT * mSpeed;
	}
	Position += Velocity;

	mAttackPoint = (Position + ATK_PARTICLE_OFFSET);

	mBoostEffect->Position = (Position + BOOST_OFFSET);

	if (mAttackParticle)
	{
		mAttackParticle->Position = mAttackPoint;
	}
}

void Player::Render()
{
	IMAGE->CenterRender(mAnimation.Play(), Position);
}

void Player::Release()
{
}

void Player::OnCollisionEnter(Object* other)
{
	if (CURHealth <= 0)
	{
		CURHealth = MAXHealth;
	}
}

void Player::OnCollisionStay(Object* other)
{
}

void Player::OnCollisionExit(Object* other)
{
}
