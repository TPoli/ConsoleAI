
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

#include "Manager.h"
#include "Player.h"
#include "AILevel.h"
#include "AIBase.h"

#pragma region Defines

#define SCREEN_HEIGHT 25

#define COLOUR_TEXT_BLUE		1
#define COLOUR_TEXT_GREEN		2
#define COLOUR_TEXT_RED			4
#define COLOUR_TEXT_INTENSITY	8

#define COLOUR_BACK_BLUE		16
#define COLOUR_BACK_GREEN		32
#define COLOUR_BACK_RED			64
#define COLOUR_BACK_INTENSITY	128

#pragma endregion

#pragma region function Prototypes

int main();
void Shutdown();
void Update(float a_fDeltaTime);

#pragma endregion


int main()
{
	srand(time(NULL));
	Manager::Instance()->Init();

	clock_t previousTime = clock();
	clock_t currentTime = clock();

	Manager::Instance()->g_hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD   index = 0;
	
	//get initial console state
	GetConsoleScreenBufferInfo(Manager::Instance()->g_hstdout, &(Manager::Instance()->g_ConsoleInfoDefault));

	Manager::Instance()->g_usBufferWidth = Manager::Instance()->g_ConsoleInfoDefault.srWindow.Right - Manager::Instance()->g_ConsoleInfoDefault.srWindow.Left + 1;
	Manager::Instance()->g_usBufferHeight = Manager::Instance()->g_ConsoleInfoDefault.srWindow.Bottom - Manager::Instance()->g_ConsoleInfoDefault.srWindow.Top;//no +1 to give a space between each screen

	Manager::Instance()->PostInit();// fold into Init

	std::cout << "Press escape to quit.\n";

	Manager::Instance()->OutputText(Manager::Instance()->GetPlayer(0)->GetColour(), "AI A\n");
	Manager::Instance()->OutputText(Manager::Instance()->GetPlayer(1)->GetColour(), "AI B\n");
	Manager::Instance()->OutputText(Manager::Instance()->GetPlayer(2)->GetColour(), "AI C\n");
	Manager::Instance()->OutputText(Manager::Instance()->GetPlayer(3)->GetColour(), "AI D\n");

	// TODO: units to populate bases / move around map, AI to take bases

	bool running = true;

	int TargetBaseCount = 16;
	int BaseCount = 4;

	Manager::Instance()->AddBase(new AIBase(0, 0, 100, 0));
	Manager::Instance()->AddBase(new AIBase(0, Manager::Instance()->g_usBufferHeight - 1, 100, 1));
	Manager::Instance()->AddBase(new AIBase(Manager::Instance()->g_usBufferWidth - 1, 0, 100, 2));
	Manager::Instance()->AddBase(new AIBase(Manager::Instance()->g_usBufferWidth - 1, Manager::Instance()->g_usBufferHeight - 1, 100, 3));

	while (BaseCount < BASECOUNT)
	{
		bool IsValidPosition = true;
		short X = rand() % Manager::Instance()->g_usBufferWidth;
		short Y = rand() % Manager::Instance()->g_usBufferHeight;
		for (int i = 0; i < BaseCount; ++i)
		{
			AIBase* ExistingBase = Manager::Instance()->GetBase(i);
			unsigned short DistX = abs((signed)ExistingBase->X() - X);
			unsigned short DistY = abs((signed)ExistingBase->Y() - Y);
			if (DistX + DistY < 5)
			{
				IsValidPosition = false;
				break;
			}
		}
		if (IsValidPosition)
		{
			++BaseCount;
			Manager::Instance()->AddBase(new AIBase(X,Y,(rand() % 9 + 1) * 10));
		}
	}

	Manager::Instance()->GetLevel()->Draw();

	while (running)
	{
		currentTime = clock();
		if (GetAsyncKeyState(VK_ESCAPE) != 0)
		{
			running = false;
			break;
		}
		Update(float(currentTime - previousTime) / CLOCKS_PER_SEC);
		previousTime = currentTime;
		
	}

	Shutdown();

	return 0;
}


void Shutdown()
{
	delete Manager::Instance();
}

void Update(float a_fDeltaTime)// use this to update AI then level
{
	//std::cout << a_fDeltaTime << '\n';
}