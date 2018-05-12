#include "ShieldBallItem.h"
#include "ModuleRender.h"
#include "ModuleColliders.h"
#include "Scene.h"
#include "PlayerEntity.h"
#include "ModulePrinter.h"

bool ShieldBallItem::Start()
{
	angular_vel = 50.0f;
	radius = 20;
	ball_col = App->colliders->AddPlayerAttackCollider({ 0, 0, 25, 25 }, App->scene->player, 0, PlayerAttack::P_Attack_Type::SHIELDBALL_ITEM);
	return true;
}

bool ShieldBallItem::Act(ModuleItems::ItemEvent event, float dt)
{
	//Here you manage your item depending of the event you receive.
	switch (event)
	{
	case ModuleItems::ItemEvent::UPDATE:
		if(ball_col.expired())
			ball_col = App->colliders->AddPlayerAttackCollider({ 0, 0, 25, 25 }, App->scene->player, 0, PlayerAttack::P_Attack_Type::SHIELDBALL_ITEM);
			
		ball_counter += dt;
		angle = angular_vel * ball_counter;
		if (angle > 360)
		{
			ball_counter = 0;
		}
		(*ball_col.lock())->rectArea.x = Ball_pos.x = cos(angle*PI / 180) * radius + 0;
		(*ball_col.lock())->rectArea.y = Ball_pos.y = sin(angle*PI / 180) * radius + 0;
		break;
	}
	return true;
}

bool ShieldBallItem::Draw()
{
	//Use the ModulePrinter to print all the stuff.
	iPoint Draw_pos = { (int)(App->scene->player->pos.x + Ball_pos.x), (int)(App->scene->player->pos.y + Ball_pos.y) };
	App->printer->PrintSprite(Draw_pos, App->items->getItemsTexture(), CRYSIS_ITEM, 0, ModulePrinter::Pivots::UPPER_LEFT, { 0,0 }, ModulePrinter::Pivots::CENTER, { 0,0 },angle);
	return true;
}

bool ShieldBallItem::printIconOnScreen(iPoint pos)
{
	//The GUI uses this method, fill it in all the items.
	return App->render->Blit(App->items->getItemsTexture(), pos.x, pos.y, &SDL_Rect(CRYSIS_ITEM), 1, 0);
}

