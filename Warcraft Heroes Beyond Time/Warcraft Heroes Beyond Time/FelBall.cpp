#include "FelBall.h"
#include "Application.h"
#include "ModulePrinter.h"
#include "ModuleColliders.h"

#include "Scene.h"
#include "Guldan.h"
#include "ModuleInput.h"

FelBall::FelBall(const FelBallInfo* info, Projectile_type type) : Projectile(info, type)
{
	felAnims[(uint)FelAnimations::moving_anim].PushBack({ 21,33,14,14 });
	felAnims[(uint)FelAnimations::moving_anim].PushBack({ 36,33,14,14 });
	felAnims[(uint)FelAnimations::moving_anim].speedFactor = 4.5f;

	felAnims[(uint)FelAnimations::back_anim].PushBack({ 21,48,14,14 });
	felAnims[(uint)FelAnimations::back_anim].PushBack({ 36,48,14,14 });
	//felAnims[(uint)FelAnimations::back_anim].speedFactor = 4.5f;

	actualAnim = &felAnims[(uint)FelAnimations::moving_anim];

	projCollider = App->colliders->AddEnemyAttackCollider({ 0, 0, 49, 74 }, toData, 50, EnemyAttack::E_Attack_Type::GULDAN_BALL);

	toData = (FelBallInfo*)info;
}

FelBall::~FelBall()
{
	App->colliders->deleteCollider(projCollider);
	RELEASE(data);
}

bool FelBall::Update(float dt)
{
	bool ret = true;

	switch (toData->fel_movement)
	{
	case FelBallInfo::fel_ball_movement::odd_even_type:

		timer += 1.0f * dt;

		if (timer <= TIME_ODD_EVEN)
		{
			toData->startRadius += toData->radiusToIncrease * dt;
			data->pos = RotateAround(data->pos, toData->rotationPivot, 0.0f, toData->startRadius);
		}
		else
		{
			toData->startRadius += (toData->radiusToIncrease - RADIUS_DECREASE_ODD_EVEN) * dt;
			data->pos = RotateAround(data->pos, toData->rotationPivot, toData->angle * dt, toData->startRadius);
		}

		break;

	case FelBallInfo::fel_ball_movement::complete_circle:
	case FelBallInfo::fel_ball_movement::hexagon:

		toData->startRadius += toData->radiusToIncrease * dt;
		data->pos = RotateAround(data->pos, toData->rotationPivot, 0.0f, toData->startRadius);

		break;

	case FelBallInfo::fel_ball_movement::spiral:

		if (App->scene->guldan->GetTimeToComeBackSpiral() < TIME_UNTIL_BALLS_BACK_SPIRAL)
		{
			toData->startRadius += toData->radiusToIncrease * dt;
			data->pos = RotateAround(data->pos, toData->rotationPivot, 0.0f, toData->startRadius);
		}
		else
		{
			actualAnim = &felAnims[(uint)FelAnimations::back_anim];
			toData->startRadius -= 75.0f * dt;
			data->pos = RotateAround(data->pos, toData->rotationPivot, 0.0f, toData->startRadius);
		}

		if (fPoint(App->scene->guldan->pos.x + 34, App->scene->guldan->pos.y + 34).DistanceTo(data->pos) < DISTANCE_TO_DELETE_FROM_GULDAN_SPIRAL)
			App->projectiles->DestroyProjectile(this);

		break;
	}

	DecreaseLifePerTime(dt);

	actualAnim->speed = actualAnim->speedFactor * dt;

	return ret;
}

bool FelBall::Draw() const
{
	bool ret = true;

	ret = App->printer->PrintSprite({ (int)data->pos.x - 7,(int)data->pos.y - 7 }, (SDL_Texture*)App->projectiles->GetProjectileAtlas(), actualAnim->GetCurrentFrame(), data->layer, ModulePrinter::Pivots::UPPER_LEFT);

	return ret;
}

void FelBall::OnCollision(Collider* yours, Collider* collideWith)
{
}

void FelBall::OnCollisionContinue(Collider* yours, Collider* collideWith)
{
}

void FelBall::OnCollisionLeave(Collider* yours, Collider* collideWith)
{
}
