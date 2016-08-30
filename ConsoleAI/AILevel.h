#pragma once
#ifndef _AILEVEL_H_
#define _AILEVEL_H_

class AILevel
{
private:
	unsigned short m_usWidth, m_usHeight;
	char* m_cpBuffer = nullptr;
	unsigned short* m_uspColours = nullptr;
public:
	AILevel(unsigned short a_usWidth, unsigned short a_usHeight);

	void Draw();

	~AILevel();

	void SetCharacter(unsigned short a_usX, unsigned short a_usY,char a_cValue,unsigned short a_usColour);
};

#endif// _AILEVEL_H_