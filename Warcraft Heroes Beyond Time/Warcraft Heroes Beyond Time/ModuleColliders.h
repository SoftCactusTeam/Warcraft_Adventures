#ifndef __ModuleColliders_H__
#define __ModuleColliders_H__

#include "Module.h"
#include "Entity.h"
#include "EntitiesEnums.h"
#include <vector>
#include <list>

struct Collider
{
	enum class ATTACK_TYPE
	{
		NONE,
		ENEMY_ARROW,
		ENEMY_MELEE,
		PLAYER_MELEE,
		THRALL_SKILL
	};

	Collider(SDL_Rect colliderRect, COLLIDER_TYPE type, Entity* owner = nullptr, iPoint offset = iPoint(0, 0));
	SDL_Rect colliderRect;										// El X i Y del Rect fan de offset !!!
	COLLIDER_TYPE type;
	ATTACK_TYPE attackType = ATTACK_TYPE::NONE;

	Entity* owner = nullptr;
	COLLIDER_TYPE collidingWith = COLLIDER_TYPE::COLLIDER_NONE;	// when isn't property of an entity
};

class ModuleColliders : public Module
{
public:
	ModuleColliders();

	void Init()
	{
		active = false;
	}

	bool Awake(pugi::xml_node& consoleNode);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void AddCommands();

	Collider* AddCollider(SDL_Rect colliderRect, COLLIDER_TYPE type, Entity* owner = nullptr, iPoint offset = iPoint(0, 0), Collider::ATTACK_TYPE attackType = Collider::ATTACK_TYPE::NONE);
	Collider* AddTemporalCollider(SDL_Rect colliderRect, COLLIDER_TYPE type, int timer);
	void deleteCollider(Collider* col);
	void CleanCollidersEntity(Entity* entity);
	bool isWallCollider(SDL_Rect here, Collider* colWith = nullptr) const;

private:
	bool CheckTypeCollMatrix(COLLIDER_TYPE type, COLLIDER_TYPE type2);
	bool CheckCollision(Collider* col1, Collider* col2);
	void PrintColliders();

private:
	std::list<Collider*> colliders;
	// Aquestes 2 llistes van en paralel
	std::list<Collider*> temporalColliders;
	std::vector<int> temporalColliderstimer;

public:
	bool printColliders = false;

};


#endif