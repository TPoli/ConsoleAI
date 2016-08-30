#include "Manager.h"
#include "Player.h"

Manager* Manager::m_opInstance = nullptr;

Manager::Manager()
{
	
}

void Manager::Init()
{
	m_oppPlayers = new Player*[PLAYERCOUNT];

	Player** iter = m_oppPlayers;

	for (unsigned short i = 0; i < PLAYERCOUNT; ++i)//set players to null
	{
		*iter = nullptr;
		++iter;
	}

	iter = m_oppPlayers;

	for (unsigned short i = 0; i < PLAYERCOUNT; ++i)// set players 1 by 1
	{
		*iter = new Player(i);
		++iter;
	}
}


Manager::~Manager()
{
	Player** iter = m_oppPlayers;

	for (unsigned short i = 0; i < PLAYERCOUNT; ++i)//set players to null
	{
		delete *iter;
		++iter;
	}
	delete m_oppPlayers;
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