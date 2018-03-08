#include "Console.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleGUI.h"
#include "Label.h"

Console::Console() {
	name = "console";
}

void Console::Init()
{
	active = false;
}

bool Console::Awake(pugi::xml_node& AwakeNode)
{
	return true;
}

bool Console::Update(float dt) 
{

	return true;
}

bool Console::CleanUp()
{
	return true;
}

void Console::PrintAtConsole(std::string textToPrint) 
{

}

bool Console::ExecConsoleOrder(std::string name)
{
	for (int i = 0; i <= consoleOrderList.size(); i++) 
	{
		if (consoleOrderList[i]->orderName == name) 
		{
			i = consoleOrderList.size() + 1;
			consoleOrderList[i]->Exec();
		}
	}
	actualConsoleTextOrder = "";
	return true;
}

void Console::AddConsoleOrderToList(ConsoleOrder* consoleOrder) 
{
	consoleOrderList.push_back(consoleOrder);
}