#include "bots.h"
#include <vector>
#include <iostream>

void cBotSimple2::ChooseNextGridPosition()
{
	std::vector<int> direction = { 0, 0 };
	std::vector<int> move = { 0, 0 };

	bool blockedx;
	bool blockedy;

	if (gTarget.PositionX() > PositionX()) 
	{
		direction[0] = 1;
	}
	else if (gTarget.PositionX() < PositionX()) 
	{
		direction[0] = -1;
	}
	else 
	{
		if (gTarget.PositionY() > PositionY()) 
		{
			direction[1] = 1;
		}
		else if (gTarget.PositionY() < PositionY())
		{
			direction[1] = -1;
		}
		else 
		{
			direction[0] = 0;
			direction[1] = 0;
		}
	}

	if (gLevel.isBlocked(PositionX() + direction[0], PositionY())) 
	{ 
		blockedx = true; 
		std::cout << "Blocked in x" << std::endl;
	}
	else 
	{
		blockedx = false;
	}

	if (gLevel.isBlocked(PositionX(), PositionY() + direction[1]))
	{
		blockedy = true;
		std::cout << "Blocked in y" << std::endl;
	}
	else
	{
		blockedy = false;
	}

	if (!blockedx && !blockedy)
	{
		move[0] = PositionX() + direction[0];
		move[1] = PositionY() + direction[1];

		std::cout << "Not blocked... Moving to: " << move[0] << " " << move[1] << std::endl;
	}
	else if (blockedx && !blockedy) 
	{
		move[0] = PositionX();
		move[1] = PositionY() - 1;
		blockedx = false;
	}

	SetNext(move[0], move[1], gLevel);
}

void findTarget() {

}