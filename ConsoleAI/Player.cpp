#include "Player.h"

#include "Manager.h"

#include <random>

Player::Player(unsigned short a_usID)
	: m_usID(a_usID)
{
	if (PLAYERCOUNT >= COLOURCOUNT - 1)// too many players to have a unique colour thats not black
		return;
	bool ColourExists = false;
	do
	{
		GenerateColour();
		for (unsigned short i = 0; i < m_usID; ++i)
		{
			if (m_usColour == 0 || Manager::Instance()->GetPlayer(i)->GetColour() == m_usColour)//the colour was black or allready taken
			{
				ColourExists = true;
				break;
			}
			ColourExists = false;
		}
	}while (ColourExists);
}


Player::~Player()
{

}

void Player::GenerateColour()
{
	m_usColour = rand() % COLOURCOUNT;
}

unsigned short Player::GetColour()
{
	return m_usColour;
}