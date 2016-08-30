
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

#include "Manager.h"
#include "Player.h"

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

void OutputText(unsigned short a_usColour, char* a_szText);
int main();
void Shutdown();

#pragma endregion

#pragma region Global Variables

HANDLE hstdout = nullptr;
CONSOLE_SCREEN_BUFFER_INFO m_ConsoleInfoDefault;

#pragma endregion


void OutputText(unsigned short a_usColour, char* a_szText)
{
	SetConsoleTextAttribute(hstdout, a_usColour);
	std::cout << a_szText << std::endl;
	SetConsoleTextAttribute(hstdout, m_ConsoleInfoDefault.wAttributes);
}

int main()
{
	srand(time(NULL));
	Manager::Instance()->Init();

	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD   index = 0;
	
	//get initial console state
	GetConsoleScreenBufferInfo(hstdout, &m_ConsoleInfoDefault);

	std::cout << "Press escape to quit.\n";

	OutputText(Manager::Instance()->GetPlayer(0)->GetColour(), "Player A\n");
	OutputText(Manager::Instance()->GetPlayer(1)->GetColour(), "Player B\n");
	OutputText(Manager::Instance()->GetPlayer(2)->GetColour(), "Player C\n");
	OutputText(Manager::Instance()->GetPlayer(3)->GetColour(), "Player D\n");

	// need to create the map, bases to place on map, units to populate bases / move around map, AI to take bases, deltatime to prevent stupid timeing

	bool running = true;

	while (running)
	{
		if (GetAsyncKeyState(VK_ESCAPE) != 0)
		{
			running = false;
			break;
		}
	}

	Shutdown();

	return 0;
}


void Shutdown()
{
	delete Manager::Instance();
}
