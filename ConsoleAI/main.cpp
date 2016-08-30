
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
void Update(float a_fDeltaTime);

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

	clock_t previousTime = clock();
	clock_t currentTime = clock();

	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD   index = 0;
	
	//get initial console state
	GetConsoleScreenBufferInfo(hstdout, &m_ConsoleInfoDefault);

	std::cout << "Press escape to quit.\n";

	OutputText(Manager::Instance()->GetPlayer(0)->GetColour(), "AI A\n");
	OutputText(Manager::Instance()->GetPlayer(1)->GetColour(), "AI B\n");
	OutputText(Manager::Instance()->GetPlayer(2)->GetColour(), "AI C\n");
	OutputText(Manager::Instance()->GetPlayer(3)->GetColour(), "AI D\n");

	// need to create the map, bases to place on map, units to populate bases / move around map, AI to take bases

	bool running = true;

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

void Update(float a_fDeltaTime)
{
	std::cout << a_fDeltaTime << '\n';
}