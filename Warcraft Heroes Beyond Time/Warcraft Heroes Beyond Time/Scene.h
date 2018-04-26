#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "p2Point.h"

#include "Animation.h"

class GUIWindow;
class PlayerEntity;
class ChestEntity;
class PortalEntity;
class Guldan;
class Item;

class Scene : public Module
{
public:

	Scene();
	virtual ~Scene();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void AddCommands();
	void GeneratePortal();

public:

	virtual bool OnUIEvent(GUIElem* UIelem, UIEvents _event);
	void CreateMainMenuScreen();
	void CreateSettingsScreen();
	void CreatePauseMenu();
	void CreateGratitudeScreen();
	void CreateItemSelectionScreen(Item*, Item*, Item*);
	bool gratitudeON = false;
	void GoMainMenu();
	void GoBossRoom();
	void Restart()
	{
		restart = true;
	}

	void GoNextLevel();

public:
	enum class Stages
	{
		NO_STAGE,
		MAIN_MENU,
		SETTINGS,
		INGAME,
		BOSS_ROOM

	} actual_scene = Stages::MAIN_MENU;

	PlayerEntity* player = nullptr;
	ChestEntity* lvlChest = nullptr;
	Guldan* guldan = nullptr;
	bool paused = false;

	GUIElem* player_HP_Bar = nullptr;
	PortalEntity* portal = nullptr;

	GUIWindow* ItemSelection = nullptr;


private:

	GUIWindow* PauseMenu = nullptr;

	uint currentPercentAudio = 0u;
	

	bool restart = false;

	// map
	std::list<iPoint> gridSizePerLevel;
	std::list<int> iterationsPerLevel;
	int lvlIndex = 0;
	int numberOfLevels = 0;
	int mapSeed = 0;
};

#endif