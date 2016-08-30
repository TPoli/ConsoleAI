
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <time.h>

#include "Manager.h"
#include "Player.h"
#include "AILevel.h"

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

//void OutputText(unsigned short a_usColour, char* a_szText);
int main();
void Shutdown();
void Update(float a_fDeltaTime);

#pragma endregion

#pragma region Global Variables

//HANDLE hstdout = nullptr;
//CONSOLE_SCREEN_BUFFER_INFO m_ConsoleInfoDefault;
unsigned short g_usBufferWidth = 0;
unsigned short g_usBufferHeight = 0;

#pragma endregion


//void OutputText(unsigned short a_usColour, char* a_szText)
//{
//	SetConsoleTextAttribute(hstdout, a_usColour);
//	std::cout << a_szText << std::endl;
//	SetConsoleTextAttribute(hstdout, m_ConsoleInfoDefault.wAttributes);
//}

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

	g_usBufferWidth = Manager::Instance()->g_ConsoleInfoDefault.srWindow.Right - Manager::Instance()->g_ConsoleInfoDefault.srWindow.Left + 1;
	g_usBufferHeight = Manager::Instance()->g_ConsoleInfoDefault.srWindow.Bottom - Manager::Instance()->g_ConsoleInfoDefault.srWindow.Top;//no +1 to give a space between each screen

	std::cout << "Press escape to quit.\n";

	Manager::Instance()->OutputText(Manager::Instance()->GetPlayer(0)->GetColour(), "AI A\n");
	Manager::Instance()->OutputText(Manager::Instance()->GetPlayer(1)->GetColour(), "AI B\n");
	Manager::Instance()->OutputText(Manager::Instance()->GetPlayer(2)->GetColour(), "AI C\n");
	Manager::Instance()->OutputText(Manager::Instance()->GetPlayer(3)->GetColour(), "AI D\n");

	AILevel AiLevel = AILevel(g_usBufferWidth, g_usBufferHeight);

	// TODO: bases to place on map, units to populate bases / move around map, AI to take bases

	bool running = true;


	AiLevel.SetCharacter(0, 0, '1', COLOUR_TEXT_RED | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(0, 1, '2', COLOUR_TEXT_RED | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(0, 2, '3', COLOUR_TEXT_RED | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(0, 3, '4', COLOUR_TEXT_RED | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(0, 4, '5', COLOUR_TEXT_RED | COLOUR_TEXT_INTENSITY);

	AiLevel.SetCharacter(1, 0, '2', COLOUR_TEXT_GREEN | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(1, 1, '3', COLOUR_TEXT_GREEN | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(1, 2, '4', COLOUR_TEXT_GREEN | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(1, 3, '5', COLOUR_TEXT_GREEN | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(1, 4, '6', COLOUR_TEXT_GREEN | COLOUR_TEXT_INTENSITY);

	AiLevel.SetCharacter(g_usBufferWidth - 2, g_usBufferHeight - 1, 'A', COLOUR_TEXT_RED | COLOUR_TEXT_INTENSITY);
	AiLevel.SetCharacter(g_usBufferWidth - 1, g_usBufferHeight - 1, 'B', COLOUR_TEXT_GREEN | COLOUR_TEXT_INTENSITY);

	AiLevel.Draw();

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