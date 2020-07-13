#include "DXUT.h"
#include "Object.h"

Object::Object() : Parent(nullptr), Child(nullptr), Name(""), Tag(TAG::NONE), IsDestory(false), IsActive(true), IsPrevCollision(false), IsCrntCollision(false), Rotation(0.0f), Position(ZERO), Scale(ONE), Velocity(ZERO), Direction(ZERO), CircleRadius(0.f)
{
}

Object::~Object()
{
}

ObjectManager::~ObjectManager()
{
	for (auto iter : mNewObjects)
	{
		SAFE_DELETE(iter);
	}
	mNewObjects.clear();

	for (auto iter : mCurObjects)
	{
		iter->Release();

		SAFE_DELETE(iter);
	}
	mCurObjects.clear();
}

void ObjectManager::AddObject(Object* object)
{
	object->Init();

	mNewObjects.emplace_back(object);
}

Object* ObjectManager::FindObject(const string& name)
{
	for (auto iter : mCurObjects)
	{
		if (iter->Name == name) return iter;
	}
	return nullptr;
}

Object* ObjectManager::FindObject(TAG tag)
{
	for (auto iter : mCurObjects)
	{
		if (iter->Tag == tag) return iter;
	}
	return nullptr;
}

void ObjectManager::CollisionCheck(TAG tagA, TAG tagB)
{
	if (mCurObjects.empty()) return;

	for (auto& iterA = mCurObjects.begin(); iterA != mCurObjects.end(); iterA++)
	{
		if ((*iterA)->Tag != tagA) continue;

		for (auto& iterB = mCurObjects.begin(); iterB != mCurObjects.end(); iterB++)
		{
			if ((*iterB)->Tag != tagB) continue;

			(*iterB)->IsPrevCollision = (*iterB)->IsCrntCollision;

			if (Math::CircleCollision((*iterA)->Position, (*iterA)->CircleRadius, (*iterB)->Position, (*iterB)->CircleRadius))
			{
				(*iterB)->IsCrntCollision = true;

				if ((*iterB)->IsCrntCollision && (*iterB)->IsPrevCollision)
				{
					(*iterB)->OnCollisionStay(*iterA);
					(*iterA)->OnCollisionStay(*iterB);
				}
				else if ((*iterB)->IsCrntCollision && !(*iterB)->IsPrevCollision)
				{
					(*iterB)->OnCollisionEnter(*iterA);
					(*iterA)->OnCollisionEnter(*iterB);
				}
			}
			else
			{
				(*iterB)->IsCrntCollision = false;

				if ((*iterB)->IsPrevCollision)
				{
					(*iterB)->OnCollisionExit(*iterA);
					(*iterA)->OnCollisionExit(*iterB);
				}
			}			
		}
	}
}

void ObjectManager::Update()
{
	if (!mNewObjects.empty())
	{
		for (auto iter : mNewObjects)
		{
			mCurObjects.emplace_back(iter);

			// 더이상 mNewObjects에서는 사용하지 않는다! 머 그런 의미
			SAFE_RELEASE(iter);
		}
	}
	mNewObjects.clear();

	if (mCurObjects.empty()) return;

	CollisionCheck(TAG::PLAYER, TAG::EBULLET);
	CollisionCheck(TAG::ENEMY, TAG::PBULLET);

	for (auto iter = mCurObjects.begin(); iter != mCurObjects.end();)
	{
		if ((*iter)->IsDestory || (*iter)->IsOutMap() || (*iter)->CURHealth <= 0.f)
		{
			SAFE_DELETE(*iter);

			// list는 Bidirectionaliterator(순서대로 차근차근 접근)이기 때문에, 
			// 쏙! 하고 지워버리면 iterator의 다음 요소에대한 정보가 증발해버린다
			// 때문에 erase의 반환값을 사용한다. erase의 반환값은 삭제한 요소의 다음 요소이다
			iter = mCurObjects.erase(iter);
			// mCurObjects.erase(iter++); 이런식으로 사용하는 것을 상상할 수도 있는데, 
			// 이미 iter는 erase함수를 통해 갈곳을 잃었기 때문에 엄한곳만 가리키게된다
		}
		else
		{
			if ((*iter)->IsActive) (*iter)->Update();
			//안됨(*iter++)->Update();
			// Array[i++].Update();

			iter++;
		}
	}
}

void ObjectManager::Render()
{
	if (!mCurObjects.empty())
	{
		for (auto iter : mCurObjects)
		{
			if (iter->IsActive && !iter->Parent)
			{
				if (iter->Child)
				{
					iter->Child->Render();
				}
				iter->Render();
			}
		}
	}
}

void Object::HealthInit(float max)
{
	MAXHealth = max;
	CURHealth = max;
}
