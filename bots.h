#pragma once
//======================================================================================
//Header file for bots: initially cBotRandom is defined here, but other bot classes
//can go here too
//
//(c) Patrick Dickinson, University of Lincoln, School of Computer Science, 2020
//======================================================================================

#include "botbase.h"
#include <utility>
#include <vector>
#include <tuple>

class cBotRandom : public cBotBase
{
	virtual void ChooseNextGridPosition();
};

class cBotSimple : public cBotBase
{
	virtual void ChooseNextGridPosition();
};

class cBotSimple2 : public cBotBase
{
	virtual void ChooseNextGridPosition();
};

class cBotAStar : public cBotBase
{
public:
	int loop = 0;
	bool flag = false;
	std::vector<std::tuple<int, int>> path;

	virtual void ChooseNextGridPosition();
};

class cDijkstra
{
public:
	bool closed[GRIDWIDTH][GRIDHEIGHT];
	float cost[GRIDWIDTH][GRIDHEIGHT];
	int linkX[GRIDWIDTH][GRIDHEIGHT];
	int linkY[GRIDWIDTH][GRIDHEIGHT];
	bool inPath[GRIDWIDTH][GRIDHEIGHT];

	bool completed;

	cDijkstra() { completed = false; }

	virtual void Build(cBotBase& bot);
};

class cAStar : public cDijkstra
{
public:
	std::vector<std::tuple<int, int>> path;
	int pathEnd;

	virtual void Build(cBotBase& bot);
};

extern cDijkstra gDijkstra;
extern cAStar gAStar;
