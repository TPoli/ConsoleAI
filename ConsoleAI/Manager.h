#pragma once
#ifndef _MANAGER_H_
#define _MANAGER_H_

#define PLAYERCOUNT 4
#define COLOURCOUNT 16

#include <Windows.h>

class Player;

class Manager
{
private:
	static Manager* m_opInstance;
	Manager();

	
	Player** m_oppPlayers;

public:
	CONSOLE_SCREEN_BUFFER_INFO g_ConsoleInfoDefault;
	HANDLE g_hstdout = nullptr;//console output handle

	static Manager* Instance();
	void Init();
	~Manager();

	Player* GetPlayer(unsigned short a_uiID);

	void OutputText(unsigned short a_usColour, char* a_szText);
};

#endif// _MANAGER_H_