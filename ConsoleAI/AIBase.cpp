#include "AIBase.h"

#include "Manager.h"
#include "AILevel.h"
#include "Player.h"

AIBase::AIBase(unsigned short a_usX, unsigned short a_usY, unsigned int a_uiMaxArmy, unsigned short a_usOwner)
	: m_usX(a_usX), m_usY(a_usY),m_usOwner(a_usOwner)
{
	m_uiMaxArmyStrength = a_uiMaxArmy;
	m_uiArmyStrength = m_uiMaxArmyStrength / 10;

	//sets level display to white if unowned or to team colour if owned
	Manager::Instance()->GetLevel()->SetCharacter(m_usX, m_usY, 178, (m_usOwner == NOPLAYER) ? 15 : Manager::Instance()->GetPlayer(m_usOwner)->GetColour());
}


AIBase::~AIBase()
{
}


void AIBase::Send(unsigned int a_uiTroopsToSend, unsigned short a_usX, unsigned short a_usY)
{
	m_uiArmyStrength -= a_uiTroopsToSend;
	//send a army when armies have been created
}

void AIBase::Receive(unsigned int a_uiTroopsSent, unsigned short a_usOwner)
{
	if (a_usOwner == m_usOwner)
	{
		AddTroops(a_uiTroopsSent);
	}
	else
	{
		if (a_uiTroopsSent > m_uiArmyStrength)
		{
			m_usOwner = a_usOwner;
			m_uiArmyStrength = min(m_uiMaxArmyStrength, a_uiTroopsSent - m_uiArmyStrength);
			Manager::Instance()->GetLevel()->SetCharacter(m_usX, m_usY, 178, (m_usOwner == NOPLAYER) ? 15 : Manager::Instance()->GetPlayer(m_usOwner)->GetColour());
		}
		else
		{
			m_uiArmyStrength -= a_uiTroopsSent;
		}
	}
}

void AIBase::BeginTurn()
{
	if (m_usOwner != NOPLAYER)//owned, replenish army
		AddTroops(m_uiMaxArmyStrength / 10);
}

void AIBase::AddTroops(unsigned int a_uiTroopCount)
{
	m_uiArmyStrength += a_uiTroopCount;
	if (m_uiArmyStrength > m_uiMaxArmyStrength)
		m_uiArmyStrength = m_uiMaxArmyStrength;
}