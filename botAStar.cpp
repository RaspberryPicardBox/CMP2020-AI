#include "bots.h"
#include <utility>
#include <iostream>
#include <vector>
#include<tuple>

void cBotAStar::ChooseNextGridPosition()
{
	if (flag == false and gAStar.pathEnd > 0) {  // Whils the init flag isnt set and the path not initialised
		std::cout << "Running..." << std::endl;
		for (std::vector<std::tuple<int, int>>::reverse_iterator it = gAStar.path.rbegin(); it != gAStar.path.rend();) {
			//std::cout << "X = " << std::get<0>(*it) << " Y = " << std::get<1>(*it) << std::endl;
			path.push_back(*it);  // Add values to the new path in reverse to reverse the path
			it++;
		}
		flag = true;  // Set the initilisation flag to true
	}
	if (flag == true and loop<path.size()) {  // If the path has been initialised and the bot is not at the end of the path
		SetNext(std::get<0>(path[loop]), std::get<1>(path[loop]), gLevel); // Move to the next path location
		loop += 1;
	}
	else if (loop = path.size()) {  // If bot is at the end of the path
		loop = 0;  // Reset the path loop counter
		flag = false;  // Reset the initialisation flag to false
	}
};