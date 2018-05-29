#ifndef __INPUT_H__
#define __INPUT_H__

#include "Module.h"

#include "SDL\include\SDL_gamecontroller.h"
#include "SDL\include\SDL_scancode.h"
#include "Log.h"

#include <map>

#define NUM_MOUSE_BUTTONS 5
#define J_DEAD_ZONE 12000
#define NUM_J_BUTTONS 16
#define MAX_JAXIS_VALUE 32767.0f

struct SDL_Rect;

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	NON_VALID_STATE = -1,
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum class Axis
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX
};

class Input : public Module
{

public:

	Input();
	virtual ~Input();

	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool CleanUp();

	bool GetWindowEvent(EventWindow ev);
	void InitController();

	inline const char* toString(SDL_GameControllerButton b)
	{
		switch (b)
		{
			case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A:   return "A";
			case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B:   return "B";
			case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_X:   return "X";
			case SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_Y:   return "Y";
			default:      return "[Unknown Button]";
		}
	}

	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouse_buttons[id - 1];
	}

	KeyState GetPadButtonDown(int id) const
	{
		return jButtons[id];
	}

	KeyState GetAction(char* action)
	{
		uint enumValue = -1;
		try
		{
			enumValue = bindingMap.at(action);
		}
			
		catch (const std::out_of_range& oor)
		{
			LOG("Action not binded yet");
			return KeyState::NON_VALID_STATE;
		}

		return GetPadButtonDown(enumValue);
	}

	float GetXAxis() const
	{
		return xAxis;
	}

	float GetYAxis() const
	{
		return yAxis;
	}

	KeyState GetAxis(int id) const
	{
		return axis[id];
	}

	bool InsideDeadZone() const
	{
		return xDeadZone && yDeadZone;
	}

	float GetPercentageFromAxis() const;
	float GetAngleFromAxis() const;

	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

	bool IsAnyKeyPressed();
	bool IsTextReady() { return textReady; };
	void SetTextReadyFalse() { textReady = false; };
	char* GetText() { return inputText; };
	bool IsKeyboardAvailable() { return kbAvailable; }
	void ExternActionsAtKeyInput(int key);
	bool PlayJoyRumble(float strength, Uint32 length);
	bool isControllerConnected()const { return controller != nullptr; }

private:
	bool		windowEvents[WE_COUNT];
	KeyState*	keyboard;
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	KeyState	jButtons[NUM_J_BUTTONS];
	KeyState    axis[(int)Axis::MAX];

	float		axis_counters[(int)Axis::MAX] = {0.0f, 0.0f, 0.0f, 0.0f};

	int			mouse_motion_x;
	int			mouse_motion_y;
	int			mouse_x;
	int			mouse_y;

	char*		inputText = nullptr;
	bool		textReady = false;
	bool		key_pressed = false;

	SDL_Joystick* joystick = NULL;
	SDL_GameController* controller = NULL;
	SDL_Haptic* controllerHaptic = NULL;

	std::map<char*, uint> bindingMap;
	std::map<char*, uint> DEFAULTbindingMap;

	float xAxis = 0;
	float yAxis = 0;
	bool xDeadZone = false;
	bool yDeadZone = false;
	bool kbAvailable = false;
};

#endif