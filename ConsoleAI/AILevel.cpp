#include "AILevel.h"
#include "Manager.h"


AILevel::AILevel(unsigned short a_usWidth, unsigned short a_usHeight)
	: m_usWidth(a_usWidth), m_usHeight(a_usHeight)
{
	m_cpBuffer = new char[m_usWidth * m_usHeight + 1];
	m_cpBuffer[m_usWidth * m_usHeight] = 0;

	m_uspColours = new unsigned short[m_usWidth * m_usHeight];
	for (unsigned short i = 0; i < m_usWidth * m_usHeight; ++i)
	{
		m_uspColours[i] = 0;
		m_cpBuffer[i] = ' ';
	}
}


AILevel::~AILevel()
{
	delete[] m_cpBuffer;
}

void AILevel::Draw()
{
	Manager::Instance()->OutputText(0, "\n");
	unsigned int bufferIndex = 0;// how far through m_cpBuffer we are
	unsigned int colourindex = 0;// how far through m_uspColours we are
	bool displayed = false;
	for (colourindex = 1; colourindex < m_usWidth * m_usHeight + 1; ++colourindex)
	{
		unsigned short OriginalColour = *(m_uspColours + bufferIndex);
		unsigned short CurrentColour = *(m_uspColours + colourindex);
		if (*(m_uspColours + colourindex) == *(m_uspColours + bufferIndex))// if colour im looking at is the same as the starting colour continue on untill colour changes then 
		{//build a buffer for that colour
			displayed = false;
			continue;
		}
		else
		{
			displayed = true;
			char* colouredBuffer = new char[colourindex - bufferIndex + 1];
			colouredBuffer[colourindex - bufferIndex] = 0;// nullterminator
			for (unsigned int i = 0; i < colourindex - bufferIndex; ++i)//copy segment of m_cpBuffer to colouredBuffer
			{
				colouredBuffer[i] = m_cpBuffer[bufferIndex + i];
			}
			Manager::Instance()->OutputText(*(m_uspColours + bufferIndex), colouredBuffer);

			bufferIndex = colourindex;

			delete[] colouredBuffer;
		}
	}
	if (!displayed)// the last of the buffer hs not yet been displayed so display it
	{
		char* colouredBuffer = new char[m_usWidth * m_usHeight - bufferIndex + 1];
		colouredBuffer[m_usWidth * m_usHeight - bufferIndex] = 0;// nullterminator
		for (unsigned int i = 0; i < m_usWidth * m_usHeight - bufferIndex; ++i)//copy final segment of m_cpBuffer to colouredBuffer
		{
			colouredBuffer[i] = m_cpBuffer[bufferIndex + i];
		}
		Manager::Instance()->OutputText(*(m_uspColours + bufferIndex), colouredBuffer);
	}
}

void AILevel::SetCharacter(unsigned short a_usX, unsigned short a_usY, char a_cValue, unsigned short a_usColour)
{
	unsigned int ID = a_usX + a_usY * m_usWidth;
	m_cpBuffer[ID] = a_cValue;
	m_uspColours[ID] = a_usColour;
}