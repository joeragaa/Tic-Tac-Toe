#pragma once
#include "Grid.h"
class Menu
{
private:
	bool SinglePlayer;
	diff difficulty;
	bool selected_mark;
	bool menustatus; //menu is closed or still open

public:
	Menu() //default is two player and first is X
	{
		SinglePlayer = 0;
		difficulty = easy;
		selected_mark = 1; 
		menustatus = 1;
	}
	void set_difficulty(diff d)
	{
		difficulty = d;
	}
	void setplayerNumber(bool s)
	{
		SinglePlayer = s;
	}
	void selectMark(bool m)
	{
		selected_mark = m;
	}
	bool getselectedMark()
	{
		return selected_mark;
	}
	bool getnumberofplayer()
	{
		return SinglePlayer;
	}
	diff getDifficulty()
	{
		return difficulty;
	}
	bool isopen()
	{
		return menustatus;
	}
	void closeMenu()
	{
		menustatus = 0;
	}
};