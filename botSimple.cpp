#include "bots.h"
void cBotSimple::ChooseNextGridPosition()
{
	if (gTarget.PositionY() > PositionY()) {
		SetNext(PositionX(), PositionY() + 1, gLevel);
	}
	else if (gTarget.PositionY() < PositionY()) {
		SetNext(PositionX(), PositionY() - 1, gLevel);
	}
	else {
		if (gTarget.PositionX() > PositionX()) {
			SetNext(PositionX() + 1, PositionY(), gLevel);
		}
		else {
			SetNext(PositionX() - 1, PositionY(), gLevel);
		}
	}
}