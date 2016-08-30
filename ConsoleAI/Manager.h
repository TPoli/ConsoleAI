#pragma once
#ifndef _MANAGER_H_
#define _MANAGER_H_

#define PLAYERCOUNT 4
#define COLOURCOUNT 16

class Player;

class Manager
{
private:
	static Manager* m_opInstance;
	Manager();

	
	Player** m_oppPlayers;

public:
	static Manager* Instance();
	void Init();
	~Manager();

	Player* GetPlayer(unsigned short a_uiID);
};

#endif// _MANAGER_H_