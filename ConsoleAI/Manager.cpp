#include "Manager.h"
#include "Player.h"
#include "AILevel.h"
#include "AIBase.h"

#include <stdlib.h>
#include <stdio.h>
//#include <Windows.h>
#include <iostream>
#include <time.h>


Manager* Manager::m_opInstance = nullptr;

Manager::Manager()
{
	
}

void Manager::Init()
{
	m_oppPlayers = new Player*[PLAYERCOUNT];
	m_oppBases = new AIBase*[BASECOUNT];

	Player** playerIter = m_oppPlayers;

	for (unsigned short i = 0; i < PLAYERCOUNT; ++i)//set players to null
	{
		*playerIter = nullptr;
		++playerIter;
	}

	playerIter = m_oppPlayers;

	for (unsigned short i = 0; i < PLAYERCOUNT; ++i)// set players 1 by 1
	{
		*playerIter = new Player(i);
		++playerIter;
	}

	for (int i = 0; i < BASECOUNT; ++i)
	{
		m_oppBases[i] = nullptr;
	}

	m_opLevel = new AILevel(g_usBufferWidth, g_usBufferHeight);
}

Manager::~Manager()
{
	Player** iter = m_oppPlayers;

	for (unsigned short i = 0; i < PLAYERCOUNT; ++i)
	{
		delete *iter;
		*iter = nullptr;
		++iter;
	}

	for (unsigned int i = 0; i < BASECOUNT; ++i)
	{
		delete m_oppBases[i];
		m_oppBases[i] = nullptr;
	}

	delete m_oppBases;
	delete m_oppPlayers;
	delete m_opLevel;
	m_oppPlayers = nullptr;
}

Manager* Manager::Instance()
{
	if (m_opInstance == nullptr)
		m_opInstance = new Manager();
	return m_opInstance;
}


Player* Manager::GetPlayer(unsigned short a_uiID)
{
	if (a_uiID >= PLAYERCOUNT)
		return nullptr;
	return *(m_oppPlayers + a_uiID);
}

void Manager::OutputText(unsigned short a_usColour, char* a_szText)
{
	SetConsoleTextAttribute(g_hstdout, a_usColour);
	std::cout << a_szText;
	SetConsoleTextAttribute(g_hstdout, g_ConsoleInfoDefault.wAttributes);
}

AILevel* Manager::GetLevel()
{
	return m_opLevel;
}

void Manager::AddBase(AIBase* a_opBase)
{
	for (int i = 0; i < BASECOUNT; ++i)
	{
		if (m_oppBases[i] == nullptr)
		{
			m_oppBases[i] = a_opBase;
			return;
		}
	}
}

AIBase* Manager::GetBase(unsigned short a_usX, unsigned short a_usY)
{
	for (int i = 0; i < BASECOUNT; ++i)
	{
		if (m_oppBases[i] == nullptr)
			return nullptr;
		else if (a_usX == m_oppBases[i]->X() && a_usY == m_oppBases[i]->Y())
			return m_oppBases[i];
	}
}