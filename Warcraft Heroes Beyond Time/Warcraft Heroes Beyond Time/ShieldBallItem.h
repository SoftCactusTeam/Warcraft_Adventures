#ifndef _SHIELD_BALL_ITEM_
#define _SHIELD_BALL_ITEM_

#include "Item.h"
#include <memory>

#define CRYSIS_ITEM {34,51,32,32} //The rect from the texture of your gui icon

class Collider;

class ShieldBallItem : public Item
{
public:
	ShieldBallItem() {}
	virtual ~ShieldBallItem() {}

	bool Start();
	bool Act(ModuleItems::ItemEvent event, float dt = App->dt);
	bool Draw();
	bool printIconOnScreen(iPoint pos);

private:
	fPoint Ball_pos = { 0,0 };
	fPoint Ball_final_pos = { 0,0 };
	uint radius = 50;
	std::weak_ptr<Collider*> ball_col;
	float ball_counter = 0.0f;
	float angle = 0.0f;
	float angular_vel = 0.0f;
};

#endif

