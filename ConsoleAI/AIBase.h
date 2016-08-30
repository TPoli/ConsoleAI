#pragma once
#ifndef _AIBASE_H_
#define _AIBASE_H_

#define NOPLAYER (unsigned short)-1

class AIBase
{
private:
	unsigned int m_uiArmyStrength = 0;
	unsigned int m_uiMaxArmyStrength = 0;
	unsigned short m_usX = 0;
	unsigned short m_usY = 0;
	unsigned short m_usOwner = 0;

	void AddTroops(unsigned int a_uiTroopCount);
public:
	AIBase() {};
	AIBase(unsigned short a_usX, unsigned short a_usY, unsigned int a_uiMaxArmy,unsigned short a_usOwner = NOPLAYER);
	~AIBase();

	unsigned int GetTroopCount() { return m_uiArmyStrength; }
	unsigned int GetMaxTroopCount() { return m_uiMaxArmyStrength; }
	unsigned short GetOwner() { return m_usOwner; }

	void Send(unsigned int a_uiTroopsToSend, unsigned short a_usX, unsigned short a_usY);
	void Receive(unsigned int a_uiTroopsSent, unsigned short a_usOwner);
	void BeginTurn();

	unsigned int X() { return m_usX; }
	unsigned int Y() { return m_usY; }
};

#endif// _AIBASE_H_