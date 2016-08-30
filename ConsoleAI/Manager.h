#pragma once
#ifndef _MANAGER_H_
#define _MANAGER_H_

#define PLAYERCOUNT 4
#define COLOURCOUNT 15
#define BASECOUNT 32

#include <Windows.h>

class Player;
class AILevel;
class AIBase;

class Manager
{
private:
	static Manager* m_opInstance;
	Manager();

	
	Player** m_oppPlayers;
	AILevel* m_opLevel;
	AIBase** m_oppBases;

public:
	unsigned short g_usBufferWidth = 0;
	unsigned short g_usBufferHeight = 0;

	CONSOLE_SCREEN_BUFFER_INFO g_ConsoleInfoDefault;
	HANDLE g_hstdout = nullptr;//console output handle

	static Manager* Instance();
	void Init();
	~Manager();

	Player* GetPlayer(unsigned short a_uiID);

	AILevel* GetLevel();

	void AddBase(AIBase* a_opBase);

	void OutputText(unsigned short a_usColour, char* a_szText);

	AIBase* GetBase(unsigned short a_usX, unsigned short a_usY);
	AIBase* GetBase(unsigned int a_uiID) { return m_oppBases[a_uiID]; }
};

#endif// _MANAGER_H_