#include <stdlib.h>

#include "p2Defs.h"
#include "Log.h"
#include "App.h"
// This is needed here because SDL redefines main function
// do not add any other libraries here, instead put them in their modules
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )


enum MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App* Application = nullptr;

int main(int argc, char* args[])
{
	LOG("Engine starting ... %d");

	MainState state = MainState::CREATE;
	int result = EXIT_FAILURE;

	while(state != EXIT)
	{
		switch(state)
		{

			// Allocate the engine --------------------------------------------
			case CREATE:
			LOG("CREATION PHASE ===============================");

			Application = new App(argc, args);

			if(Application != NULL)
				state = AWAKE;
			else
				state = FAIL;

			break;

			// Awake all modules -----------------------------------------------
			case AWAKE:
			LOG("AWAKE PHASE ===============================");
			if(Application->Awake() == true)
				state = START;
			else
			{
				LOG("ERROR: Awake failed");
				state = FAIL;
			}

			break;
			
			// Call all modules before first frame  ----------------------------
			case START:
			LOG("START PHASE ===============================");
			if(Application->Start() == true)
			{
				state = LOOP;
				LOG("UPDATE PHASE ===============================");
			}
			else
			{
				state = FAIL;
				LOG("ERROR: Start failed");
			}
			break;			

			// Loop all modules until we are asked to leave ---------------------
			case LOOP:
			{
				if (Application->Update() == false)
					state = CLEAN;
			}
			break;

			// Cleanup allocated memory -----------------------------------------
			case CLEAN:
			LOG("CLEANUP PHASE ===============================");
			if(Application->CleanUp() == true)
			{
				RELEASE(Application);
				result = EXIT_SUCCESS;
				state = EXIT;
			}
			else
				state = FAIL;

			break;

			// Exit with errors and shame ---------------------------------------
			case FAIL:
			LOG("Exiting with errors :(");
			result = EXIT_FAILURE;
			state = EXIT;
			break;
		}
	}

	LOG("Closing Game\n");

	return result;
}