#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
private:
	unsigned short m_usColour;
	unsigned short m_usID;

	void GenerateColour();
	void FindMyBases();

public:
	Player(unsigned short a_usID);
	Player() {}
	~Player();

	unsigned short GetColour();

	void Update();
};

#endif// _PLAYER_H_