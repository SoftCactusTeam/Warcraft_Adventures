#include "BossEntity.h"
#include "Guldan.h"
#include <time.h>

Guldan::Guldan(fPoint coor, BOSS_TYPE type, SDL_Texture* texture) : BossEntity(coor, type, texture)
{
	idle.PushBack({ 1,1,68,68 });
	idle.PushBack({ 70,1,68,68 });
	idle.PushBack({ 139,1,68,68 });
	idle.PushBack({ 208,1,68,68 });
	idle.PushBack({ 277,1,68,68 });
	idle.speedFactor = 9.0f;

	teleport.PushBack({ 484,73,68,68 });
	teleport.PushBack({ 554,73,68,68 });
	teleport.PushBack({ 623,73,68,68 });
	teleport.PushBack({ 697,73,68,68 });
	teleport.PushBack({ 767,73,68,68 });
	teleport.PushBack({ 837,73,68,68 });
	teleport.PushBack({ 907,73,68,68 });
	teleport.PushBack({ 3,146,68,68 });
	teleport.PushBack({ 149,146,68,68 });
	teleport.PushBack({ 226,146,68,68 });
	teleport.PushBack({ 294,146,68,68 });
	teleport.PushBack({ 353,146,68,68 });
	teleport.PushBack({ 705,146,68,68 });
	teleport.speedFactor = 9.0f;

	inverseTeleport.PushBack({ 484,73,68,68 });
	inverseTeleport.PushBack({ 554,73,68,68 });
	inverseTeleport.PushBack({ 623,73,68,68 });
	inverseTeleport.PushBack({ 697,73,68,68 });
	inverseTeleport.PushBack({ 767,73,68,68 });
	inverseTeleport.PushBack({ 837,73,68,68 });
	inverseTeleport.PushBack({ 907,73,68,68 });
	inverseTeleport.PushBack({ 3,146,68,68 });
	inverseTeleport.PushBack({ 149,146,68,68 });
	inverseTeleport.PushBack({ 226,146,68,68 });
	inverseTeleport.PushBack({ 294,146,68,68 });
	inverseTeleport.PushBack({ 353,146,68,68 });
	inverseTeleport.PushBack({ 705,146,68,68 });
	inverseTeleport.speedFactor = 9.0f;

	live = 1000;
	anim = &idle;
}

Guldan::~Guldan()
{
}

bool Guldan::Start()
{
	effectsTexture = App->textures->Load("sprites/Guldan_Effects.png");

	srand(time(NULL));
	statesBoss = BossStates::IDLE;

	CreateFelBalls({ pos.x, pos.y });

	for (std::list<FelBall*>::const_iterator it = fellBallsList.begin(); it != fellBallsList.end(); ++it)
	{
		(*it)->StartMovement();
	}

	return true;
}

bool Guldan::Update(float dt)
{
	if (startTimeForTP)
	{
		fellBallsList.clear();
		floatTimeForTp += 1.0f + dt;

	}

	if (readeForTimeNewBalls)
	{
		timeForNewBalls += 1.0f * dt;
		if (timeForNewBalls >= 2.0f)
		{
			readeForTimeNewBalls = false;
			timeForNewBalls = 0.0f;
			createNewBalls = true;
		}
	}

	switch (statesBoss)
	{
		case BossStates::IDLE:
		{
			if (floatTimeForTp >= 2.0f)
			{
				statesBoss = BossStates::TELEPORT;
				anim = &teleport;
				floatTimeForTp = 0.0f;
				startTimeForTP = false;
				break;
			}

			break;
		}
		case BossStates::TELEPORT:
		{

			if (anim->Finished())
			{
				createNewBalls = false;
				int randomtp = rand() % 5;
				pos.x = tpPoints[randomtp].x * 48;
				pos.y = tpPoints[randomtp].y * 48;
				anim = &inverseTeleport;
				teleport.Reset();;
				statesBoss = BossStates::INVERSETELEPORT;
				break;
			}

			break;
		}

		case BossStates::INVERSETELEPORT:
		{

			if (anim->Finished())
			{
				anim = &idle;
				statesBoss = BossStates::IDLE;
				readeForTimeNewBalls = true;
				inverseTeleport.Reset();
				break;
			}

			break;
		}

	}

	anim->speed = anim->speedFactor * dt;

	if (createNewBalls)
	{
		createNewBalls = false;
		CreateFelBalls({ pos.x, pos.y });
		for (std::list<FelBall*>::const_iterator it = fellBallsList.begin(); it != fellBallsList.end(); ++it)
		{
			(*it)->StartMovement();
		}
	}
	

	for (std::list<FelBall*>::const_iterator it = fellBallsList.begin(); it != fellBallsList.end(); ++it)
	{
		(*it)->Update(dt);
		(*it)->BlitFel();
	}


	for (std::list<FelBall*>::const_iterator it = fellBallsList.begin(); it != fellBallsList.end(); ++it)
	{
		if ((*it)->dead)
		{
			delete *it;
			startTimeForTP = true;
		}
		
	}

	return true;
}

bool Guldan::Finish()
{
	App->textures->UnLoad(effectsTexture);
	return true;
}

bool Guldan::CreateFelBalls(fPoint pos)
{
	fellBallsList.push_back(new FelBall({ pos.x + 23 / 2, pos.y + 23 / 2 }, 60, 0, effectsTexture, 90));

	fellBallsList.push_back(new FelBall({ pos.x + 23 / 2, pos.y + 23 / 2 }, 60, 45, effectsTexture, 90));

	fellBallsList.push_back(new FelBall({ pos.x + 23 / 2, pos.y + 23 / 2 }, 60, 90, effectsTexture, 90));

	fellBallsList.push_back(new FelBall({ pos.x + 23 / 2, pos.y + 23 / 2 }, 60, 135, effectsTexture, 90));
														
	fellBallsList.push_back(new FelBall({ pos.x + 23 / 2, pos.y + 23 / 2 }, 60, 180, effectsTexture, 90));
														
	fellBallsList.push_back(new FelBall({ pos.x + 23 / 2, pos.y + 23 / 2 }, 60, 225, effectsTexture, 90));
														
	fellBallsList.push_back(new FelBall({ pos.x + 23 / 2, pos.y + 23 / 2 }, 60, 270, effectsTexture, 90));
														
	fellBallsList.push_back(new FelBall({ pos.x + 23 / 2, pos.y + 23 / 2 }, 60, 315, effectsTexture, 90));

	return true;
}
