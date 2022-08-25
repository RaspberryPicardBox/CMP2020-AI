#include "bots.h"
#include <algorithm>
#include <tuple>
#include <iostream>


void cDijkstra::Build(cBotBase &bot)
{
	// Setting the cost of every grid space to ~infinite and reseting linkages
	for (int x = 0; x < GRIDWIDTH; x++)
	{
		for (int y = 0; y < GRIDHEIGHT; y++)
		{
			closed[x][y] = false;
			cost[x][y] = 1000000.0f;
			linkX[x][y] = -1;
			linkY[x][y] = -1;
			inPath[x][y] = false;
		}
	}

	cost[bot.PositionX()][bot.PositionY()] = 0;  // Set current space cost to 0

	int loop = 0;

	while (!closed[gTarget.PositionX()][gTarget.PositionY()])  // Until the player's position is closed (found)
	{
		int hereX = 0;
		int hereY = 0;
		float temp = cost[0][0];

		// Check if the cost of anywhere is lower than the current cost (0) to find the next grid path to take
		for (int x = 0; x < GRIDWIDTH; x++)
		{
			for (int y = 0; y < GRIDHEIGHT; y++)
			{
				if (cost[x][y] < temp && closed[x][y] == false && gLevel.isValid(x, y))  // Making sure it's a valid location and not already been to
				{
					temp = cost[x][y];
					hereX = x;
					hereY = y;
				}
			}
		}
		
		closed[hereX][hereY] = true;  // Close the current position

		/*std::cout << "Current: " << cost[hereX][hereY] << std::endl;
		std::cout << "Up: " << cost[hereX][hereY - 1] << std::endl;
		std::cout << "Down: " << cost[hereX][hereY + 1] << std::endl;
		std::cout << "Left: " << cost[hereX - 1][hereY] << std::endl;
		std::cout << "Right: " << cost[hereX + 1][hereY] << std::endl;
		std::cout << "Top Left: " << cost[hereX - 1][hereY - 1] << std::endl;
		std::cout << "Top Right: " << cost[hereX + 1][hereY - 1] << std::endl;
		std::cout << "Bottom Left: " << cost[hereX - 1][hereY + 1] << std::endl;
		std::cout << "Bottom Right: " << cost[hereX + 1][hereY + 1] << std::endl;*/

		// Checking each location's cost around the bot within 1 move, and if valid, adding it to the link of movements
		if (gLevel.isValid(hereX, hereY - 1) && closed[hereX][hereY - 1] == false && cost[hereX][hereY] + 1 < cost[hereX][hereY - 1]) // Up - adding 1 cost for straight move
		{
			cost[hereX][hereY - 1] = cost[hereX][hereY] + 1;
			linkX[hereX][hereY - 1] = hereX;
			linkY[hereX][hereY - 1] = hereY;
		}
		if (gLevel.isValid(hereX, hereY + 1) && closed[hereX][hereY + 1] == false && cost[hereX][hereY] + 1 < cost[hereX][hereY + 1]) // Down
		{
			cost[hereX][hereY + 1] = cost[hereX][hereY] + 1;
			linkX[hereX][hereY + 1] = hereX;
			linkY[hereX][hereY + 1] = hereY;
		}
		if (gLevel.isValid(hereX - 1, hereY) && closed[hereX - 1][hereY] == false && cost[hereX][hereY] + 1 < cost[hereX - 1][hereY]) // Left
		{
			cost[hereX - 1][hereY] = cost[hereX][hereY] + 1;
			linkX[hereX - 1][hereY] = hereX;
			linkY[hereX - 1][hereY] = hereY;
		}
		if (gLevel.isValid(hereX + 1, hereY) && closed[hereX + 1][hereY] == false && cost[hereX][hereY] + 1 < cost[hereX + 1][hereY]) // Right
		{
			cost[hereX + 1][hereY] = cost[hereX][hereY] + 1;
			linkX[hereX + 1][hereY] = hereX;
			linkY[hereX + 1][hereY] = hereY;
		}
		if (gLevel.isValid(hereX - 1, hereY - 1) && closed[hereX - 1][hereY - 1] == false && cost[hereX][hereY] + 1.4f < cost[hereX - 1][hereY - 1]) // Top-Left - adding 1.4 cost for diagonal move
		{
			cost[hereX - 1][hereY - 1] = cost[hereX][hereY] + 1.4f;
			linkX[hereX - 1][hereY - 1] = hereX;
			linkY[hereX - 1][hereY - 1] = hereY;
		}
		if (gLevel.isValid(hereX + 1, hereY - 1) && closed[hereX + 1][hereY - 1] == false && cost[hereX][hereY] + 1.4f < cost[hereX + 1][hereY - 1]) // Top-Right
		{
			cost[hereX + 1][hereY - 1] = cost[hereX][hereY] + 1.4f;
			linkX[hereX + 1][hereY - 1] = hereX;
			linkY[hereX + 1][hereY - 1] = hereY;
		}
		if (gLevel.isValid(hereX - 1, hereY + 1) && closed[hereX - 1][hereY + 1] == false && cost[hereX][hereY] + 1.4f < cost[hereX - 1][hereY + 1]) // Bottom-Left
		{
			cost[hereX - 1][hereY + 1] = cost[hereX][hereY] + 1.4f;
			linkX[hereX - 1][hereY + 1] = hereX;
			linkY[hereX - 1][hereY + 1] = hereY;
		}
		if (gLevel.isValid(hereX + 1, hereY + 1) && closed[hereX + 1][hereY + 1] == false && cost[hereX][hereY] + 1.4f < cost[hereX + 1][hereY + 1]) // Bottom-Right
		{
			cost[hereX + 1][hereY + 1] = cost[hereX][hereY] + 1.4f;
			linkX[hereX + 1][hereY + 1] = hereX;
			linkY[hereX + 1][hereY + 1] = hereY;
		}
		loop += 1;
		//std::cout << loop << std::endl;
	}

	bool done = false;

	std::cout << "DONE" << std::endl;

	int nextClosedX = gTarget.PositionX();
	int nextClosedY = gTarget.PositionY();

	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;  // Adding all chosen linked grids to the path

		int tmpX = nextClosedX;
		int tmpY = nextClosedY;

		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];

		if (nextClosedX == bot.PositionX() && nextClosedY == bot.PositionY())  // And finishing when the path links the player and bot
		{
			done = true;
		}
	}

	completed = true;
}

void cAStar::Build(cBotBase& bot)
{
	for (int x = 0; x < GRIDWIDTH; x++)
	{
		for (int y = 0; y < GRIDHEIGHT; y++)
		{
			closed[x][y] = false;
			cost[x][y] = 1000000.0f;
			linkX[x][y] = -1;
			linkY[x][y] = -1;
			inPath[x][y] = false;
		}
	}

	cost[bot.PositionX()][bot.PositionY()] = 0;

	int loop = 0;

	while (!closed[gTarget.PositionX()][gTarget.PositionY()])
	{
		int hereX = 0;
		int hereY = 0;
		float temp = cost[0][0];

		for (int x = 0; x < GRIDWIDTH; x++)
		{
			for (int y = 0; y < GRIDHEIGHT; y++)
			{
				if (cost[x][y] < temp && closed[x][y] == false && gLevel.isValid(x, y))
				{
					temp = cost[x][y];
					hereX = x;
					hereY = y;
				}
			}
		}

		closed[hereX][hereY] = true;
		//std::cout << "Current: " << cost[hereX][hereY] << std::endl;

		// Difference starts here - heuristic values are calculated

		//float heuristic = fabs(gTarget.PositionX() - hereX) + fabs(gTarget.PositionY() - hereY);  // Manhattan heuristic
		//float heuristic = (fabs(gTarget.PositionX() - hereX) + fabs(gTarget.PositionY() - hereY)) - ((0.6) * fmin(fabs(gTarget.PositionX() - hereX), fabs(gTarget.PositionY() - hereY)));  // Diagonal Heuristic
		float heuristic = sqrt(fabs(pow((gTarget.PositionX() - hereX), 2)) + fabs(pow((gTarget.PositionY() - hereY), 2)));  // Euclidian Heuristic
		//std::cout << "Cost + Heuristic: " << cost[hereX][hereY] + (1 + heuristic) << std::endl;

		if (gLevel.isValid(hereX, hereY - 1) && closed[hereX][hereY - 1] == false && cost[hereX][hereY] + (1 + heuristic) < cost[hereX][hereY - 1]) // Up - 1 cost + heuristic is added
		{
			cost[hereX][hereY - 1] = cost[hereX][hereY] + 1;
			//std::cout << "Up: " << cost[hereX][hereY - 1] << std::endl;
			linkX[hereX][hereY - 1] = hereX;
			linkY[hereX][hereY - 1] = hereY;
		}
		if (gLevel.isValid(hereX, hereY + 1) && closed[hereX][hereY + 1] == false && cost[hereX][hereY] + (1 + heuristic) < cost[hereX][hereY + 1]) // Down
		{
			cost[hereX][hereY + 1] = cost[hereX][hereY] + 1;
			//std::cout << "Down: " << cost[hereX][hereY + 1] << std::endl;
			linkX[hereX][hereY + 1] = hereX;
			linkY[hereX][hereY + 1] = hereY;
		}
		if (gLevel.isValid(hereX - 1, hereY) && closed[hereX - 1][hereY] == false && cost[hereX][hereY] + (1 + heuristic) < cost[hereX - 1][hereY]) // Left
		{
			cost[hereX - 1][hereY] = cost[hereX][hereY] + 1;
			//std::cout << "Left: " << cost[hereX - 1][hereY] << std::endl;
			linkX[hereX - 1][hereY] = hereX;
			linkY[hereX - 1][hereY] = hereY;
		}
		if (gLevel.isValid(hereX + 1, hereY) && closed[hereX + 1][hereY] == false && cost[hereX][hereY] + (1 + heuristic) < cost[hereX + 1][hereY]) // Right
		{
			cost[hereX + 1][hereY] = cost[hereX][hereY] + 1;
			//std::cout << "Right: " << cost[hereX + 1][hereY] << std::endl;
			linkX[hereX + 1][hereY] = hereX;
			linkY[hereX + 1][hereY] = hereY;
		}
		if (gLevel.isValid(hereX - 1, hereY - 1) && closed[hereX - 1][hereY - 1] == false && cost[hereX][hereY] + (1.4f + heuristic) < cost[hereX - 1][hereY - 1]) // Top-Left - 1.4 cost + heuristic is added
		{
			cost[hereX - 1][hereY - 1] = cost[hereX][hereY] + 1.4f;
			//std::cout << "Top Left: " << cost[hereX - 1][hereY - 1] << std::endl;
			linkX[hereX - 1][hereY - 1] = hereX;
			linkY[hereX - 1][hereY - 1] = hereY;
		}
		if (gLevel.isValid(hereX + 1, hereY - 1) && closed[hereX + 1][hereY - 1] == false && cost[hereX][hereY] + (1.4f + heuristic) < cost[hereX + 1][hereY - 1]) // Top-Right
		{
			cost[hereX + 1][hereY - 1] = cost[hereX][hereY] + 1.4f;
			//std::cout << "Top Right: " << cost[hereX + 1][hereY - 1] << std::endl;
			linkX[hereX + 1][hereY - 1] = hereX;
			linkY[hereX + 1][hereY - 1] = hereY;
		}
		if (gLevel.isValid(hereX - 1, hereY + 1) && closed[hereX - 1][hereY + 1] == false && cost[hereX][hereY] + (1.4f + heuristic) < cost[hereX - 1][hereY + 1]) // Bottom-Left
		{
			cost[hereX - 1][hereY + 1] = cost[hereX][hereY] + 1.4f;
			//std::cout << "Bottom Left: " << cost[hereX - 1][hereY + 1] << std::endl;
			linkX[hereX - 1][hereY + 1] = hereX;
			linkY[hereX - 1][hereY + 1] = hereY;
		}
		if (gLevel.isValid(hereX + 1, hereY + 1) && closed[hereX + 1][hereY + 1] == false && cost[hereX][hereY] + (1.4f + heuristic) < cost[hereX + 1][hereY + 1]) // Bottom-Right
		{
			cost[hereX + 1][hereY + 1] = cost[hereX][hereY] + 1.4f;
			//std::cout << "Bottom Right: " << cost[hereX + 1][hereY + 1] << std::endl;
			linkX[hereX + 1][hereY + 1] = hereX;
			linkY[hereX + 1][hereY + 1] = hereY;
		}
		loop += 1;
		//std::cout << loop << std::endl;
	}

	bool done = false;

	std::cout << "DONE" << std::endl;

	int nextClosedX = gTarget.PositionX();
	int nextClosedY = gTarget.PositionY();

	int loop1 = 0;

	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;

		int tmpX = nextClosedX;
		int tmpY = nextClosedY;

		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];

		std::tuple<int, int> coord = std::tuple<int, int>(nextClosedX, nextClosedY);  // Turning the next coordinate values into a tuple
		path.push_back(coord);  // And adding to a member variable for use by the bot

		loop1 += 1;
		if (nextClosedX == bot.PositionX() && nextClosedY == bot.PositionY())
		{
			done = true;
			pathEnd = loop1;  // Also adding the ending index of the vector
		}
	}

	completed = true;
}

cDijkstra gDijkstra;
cAStar gAStar;