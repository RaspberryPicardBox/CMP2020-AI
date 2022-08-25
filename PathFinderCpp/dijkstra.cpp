#include "bots.h"
#include "level.h"
#include <iostream>
using namespace std;

void cDijkstra::Build(cBotBase &bot)
{
	for (int i = 0; i < GRIDHEIGHT; i++)
	{
		for (int j = 0; j < GRIDWIDTH; j++)
		{
			closed[i][j] = false;
			cost[i][j] = 1000000.0f;
			linkX[i][j] = -1;
			linkY[i][j] = -1;
			inPath[i][j] = false;
		}
	}
	cost[bot.PositionX()][bot.PositionY()] = 0;

	bool end = false;

	while (!closed[gTarget.PositionX()][gTarget.PositionY()])
	{
		int currentX = 0;
		int currentY = 0;
		float position = cost[0][0];

		for (int i = 0; i < GRIDHEIGHT; i++)
		{
			for (int j = 0; j < GRIDWIDTH; j++)
			{
				if (cost[i][j] < position && closed[i][j] == false && gLevel.isValid(i, j))
				{
					position = cost[i][j];
					currentX = i;
					currentY = j;
				}
			}
		}

		closed[currentX][currentY] = true;

		float up = cost[currentX][currentY] + 1;
		float down = cost[currentX][currentY] + 1;
		float left = cost[currentX][currentY] + 1;
		float right = cost[currentX][currentY] + 1;

		float upLeft = cost[currentX][currentY] + 1.4f;
		float downLeft = cost[currentX][currentY] + 1.4f;
		float upRight = cost[currentX][currentY] + 1.4f;
		float downRight = cost[currentX][currentY] + 1.4f;

		if (gLevel.isValid(currentX, currentY - 1) && closed[currentX][currentY - 1] == false && up < cost[currentX][currentY -1])
		{
			cost[currentX][currentY - 1] = up;
			linkX[currentX][currentY - 1] = currentX;
			linkY[currentX][currentY - 1] = currentY;
			//cout << "up";
		}
		if (gLevel.isValid(currentX, currentY + 1) && closed[currentX][currentY + 1] == false && down < cost[currentX][currentY + 1])
		{
			cost[currentX][currentY + 1] = down;
			linkX[currentX][currentY + 1] = currentX;
			linkY[currentX][currentY + 1] = currentY;
			//cout << "down";
		}
		if (gLevel.isValid(currentX - 1, currentY) && closed[currentX - 1][currentY] == false && left < cost[currentX - 1][currentY])
		{
			cost[currentX - 1][currentY] = left;
			linkX[currentX - 1][currentY] = currentX;
			linkY[currentX - 1][currentY] = currentY;
			//cout << "left";
		}
		if (gLevel.isValid(currentX + 1, currentY) && closed[currentX + 1][currentY] == false && right < cost[currentX + 1][currentY])
		{
			cost[currentX + 1][currentY] = right;
			linkX[currentX + 1][currentY] = currentX;
			linkY[currentX + 1][currentY] = currentY;
			//cout << "right";
		}
		if (gLevel.isValid(currentX - 1, currentY - 1) && closed[currentX - 1][currentY - 1] == false && upLeft < cost[currentX - 1][currentY - 1])
		{
			cost[currentX - 1][currentY - 1] = upLeft;
			linkX[currentX - 1][currentY - 1] = currentX;
			linkY[currentX - 1][currentY - 1] = currentY;
			//cout << "upLeft";
		}
		if (gLevel.isValid(currentX - 1, currentY + 1) && closed[currentX - 1][currentY + 1] == false && downLeft < cost[currentX - 1][currentY + 1])
		{
			cost[currentX - 1][currentY + 1] = downLeft;
			linkX[currentX - 1][currentY + 1] = currentX;
			linkY[currentX - 1][currentY + 1] = currentY;
			//cout << "downLeft";
		}
		if (gLevel.isValid(currentX + 1, currentY - 1) && closed[currentX + 1][currentY - 1] == false && upRight < cost[currentX + 1][currentY - 1])
		{
			cost[currentX + 1][currentY - 1] = upRight;
			linkX[currentX + 1][currentY - 1] = currentX;
			linkY[currentX + 1][currentY - 1] = currentY;
			//cout << "upRight";
		}
		if (gLevel.isValid(currentX + 1, currentY + 1) && closed[currentX + 1][currentY + 1] == false && downRight < cost[currentX + 1][currentY + 1])
		{
			cost[currentX + 1][currentY + 1] = downRight;
			linkX[currentX + 1][currentY + 1] = currentX;
			linkY[currentX + 1][currentY + 1] = currentY;
			//cout << "downRight";
		}
	}

	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY()))
		{
			done = true;
		}
	}
	completed = true;
}

cDijkstra gDijkstra;

void cAStar::Build(cBotBase& bot)
{
	for (int i = 0; i < GRIDHEIGHT; i++)
	{
		for (int j = 0; j < GRIDWIDTH; j++)
		{
			closed[i][j] = false;
			cost[i][j] = 1000000.0f;
			linkX[i][j] = -1;
			linkY[i][j] = -1;
			inPath[i][j] = false;
		}
	}
	cost[bot.PositionX()][bot.PositionY()] = 0;

	bool end = false;

	while (!closed[gTarget.PositionX()][gTarget.PositionY()])
	{
		int currentX = 0;
		int currentY = 0;
		float position = cost[0][0];

		for (int i = 0; i < GRIDHEIGHT; i++)
		{
			for (int j = 0; j < GRIDWIDTH; j++)
			{
				if (cost[i][j] < position && closed[i][j] == false && gLevel.isValid(i, j))
				{
					position = cost[i][j];
					currentX = i;
					currentY = j;
				}
			}
		}

		closed[currentX][currentY] = true;

		//manhatten distance
		float manhatten = fabs(gTarget.PositionX() - currentX) + fabs(gTarget.PositionY() - currentY);
		std::cout << "Cost + Heuristic: " << cost[currentX][currentY] + (1 + manhatten) << std::endl;

		//diagonal distance
		float diagonal = fabs(gTarget.PositionX() - currentX) + fabs(gTarget.PositionY() - currentY) - (0.6) * fmin(gTarget.PositionX() - currentX, fabs(gTarget.PositionY() - currentY));
		std::cout << "Cost + Heuristic: " << cost[currentX][currentY] + (1 + diagonal) << std::endl;

		//eucidean distance
		float euclidean = fabs((gTarget.PositionX() - currentX) ^ 2) + fabs((gTarget.PositionY() - currentY) ^ 2);
		std::cout << "Cost + Heuristic: " << cost[currentX][currentY] + (1 + euclidean) << std::endl;

		float up = cost[currentX][currentY] + 1;
		float down = cost[currentX][currentY] + 1;
		float left = cost[currentX][currentY] + 1;
		float right = cost[currentX][currentY] + 1;

		float upLeft = cost[currentX][currentY] + 1.4f;
		float downLeft = cost[currentX][currentY] + 1.4f;
		float upRight = cost[currentX][currentY] + 1.4f;
		float downRight = cost[currentX][currentY] + 1.4f;

		if (gLevel.isValid(currentX, currentY - 1) && closed[currentX][currentY - 1] == false && cost[currentX][currentY] + (1 + manhatten) < cost[currentX][currentY - 1])
		{
			cost[currentX][currentY - 1] = up;
			linkX[currentX][currentY - 1] = currentX;
			linkY[currentX][currentY - 1] = currentY;
			//cout << "up";
		}
		if (gLevel.isValid(currentX, currentY + 1) && closed[currentX][currentY + 1] == false && cost[currentX][currentY] + (1 + manhatten) < cost[currentX][currentY + 1])
		{
			cost[currentX][currentY + 1] = down;
			linkX[currentX][currentY + 1] = currentX;
			linkY[currentX][currentY + 1] = currentY;
			//cout << "down";
		}
		if (gLevel.isValid(currentX - 1, currentY) && closed[currentX - 1][currentY] == false && cost[currentX][currentY] + (1 + manhatten) < cost[currentX - 1][currentY])
		{
			cost[currentX - 1][currentY] = left;
			linkX[currentX - 1][currentY] = currentX;
			linkY[currentX - 1][currentY] = currentY;
			//cout << "left";
		}
		if (gLevel.isValid(currentX + 1, currentY) && closed[currentX + 1][currentY] == false && cost[currentX][currentY] + (1 + manhatten) < cost[currentX + 1][currentY])
		{
			cost[currentX + 1][currentY] = right;
			linkX [currentX + 1] [currentY] = currentX;
			linkY[currentX + 1][currentY] = currentY;
			//cout << "right";
		}
		if (gLevel.isValid(currentX - 1, currentY - 1) && closed[currentX - 1][currentY - 1] == false && cost[currentX][currentY] + (1.4f + manhatten) < cost[currentX - 1][currentY - 1])
		{
			cost[currentX - 1][currentY - 1] = upLeft;
			linkX[currentX - 1][currentY - 1] = currentX;
			linkY[currentX - 1][currentY - 1] = currentY;
			//cout << "upLeft";
		}
		if (gLevel.isValid(currentX - 1, currentY + 1) && closed[currentX - 1][currentY + 1] == false && cost[currentX][currentY] + (1.4f + manhatten) < cost[currentX - 1][currentY + 1])
		{
			cost[currentX - 1][currentY + 1] = downLeft;
			linkX[currentX - 1][currentY + 1] = currentX;
			linkY[currentX - 1][currentY + 1] = currentY;
			//cout << "downLeft";
		}
		if (gLevel.isValid(currentX + 1, currentY - 1) && closed[currentX + 1][currentY - 1] == false && cost[currentX][currentY] + (1.4f + manhatten) < cost[currentX + 1][currentY - 1])
		{
			cost[currentX + 1][currentY - 1] = upRight;
			linkX[currentX + 1][currentY - 1] = currentX;
			linkY[currentX + 1][currentY - 1] = currentY;
			//cout << "upRight";
		}
		if (gLevel.isValid(currentX + 1, currentY + 1) && closed[currentX + 1][currentY + 1] == false && cost[currentX][currentY] + (1.4f + manhatten) < cost[currentX + 1][currentY + 1])
		{
			cost[currentX + 1][currentY + 1] = downRight;
			linkX[currentX + 1][currentY + 1] = currentX;
			linkY[currentX + 1][currentY + 1] = currentY;
			//cout << "downRight";
		}
	}

	bool done = false; //set to true when we are back at the bot position
	int nextClosedX = gTarget.PositionX(); //start of path
	int nextClosedY = gTarget.PositionY(); //start of path
	while (!done)
	{
		inPath[nextClosedX][nextClosedY] = true;
		int tmpX = nextClosedX;
		int tmpY = nextClosedY;
		nextClosedX = linkX[tmpX][tmpY];
		nextClosedY = linkY[tmpX][tmpY];
		if ((nextClosedX == bot.PositionX()) && (nextClosedY == bot.PositionY())) done = true;
	}
	completed = true;
}

cAStar gAStar;