#include "Fruit.h"

void Fruit::move(Board& board,bool loadMode)
{
	bool nextMove = true;
	int currX, currY;
	currX = getLocation().getX();
	currY = getLocation().getY();
	if(!loadMode)
		setDirection();
	nextMove = getLocation().isMoveValid(currX, currY, board, Creature::getDirection());
	if (nextMove == false)
	{
		if(!loadMode)
			Creature::setDirection((int)directions::Stay);
		printCreature();
	}
	else
	{
		if (board.getSquare(currY, currX) == ' ')
		{
			getLocation().draw(' ');
			getLocation().moveCreatures(getDirection(), board);
			printCreature();
		}
		else
		{
			getLocation().draw(C);
			getLocation().moveCreatures(getDirection(), board);
			printCreature();
		}
	}
}

void Fruit::setLocation(Board& board)
{
	int _x, _y;
	bool FruitIsPlaced = false;
	while (FruitIsPlaced == false)
	{
		_x = rand() % (board.getXBR() - board.getXTL()) + board.getXTL();
		_y = rand() % (board.getYBR() - board.getYTL()) + board.getYTL();

		if (board.getSquare(_y, _x) != W)
		{
			getLocation().setPoint(_x, _y);
			FruitIsPlaced = true;
		}
	}
}