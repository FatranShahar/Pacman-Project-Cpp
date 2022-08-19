#include "Pacman.h"
void Pacman::setArrowKeys(const char* keys) {
	arrowKeys[0] = keys[0];
	arrowKeys[1] = keys[1];
	arrowKeys[2] = keys[2];
	arrowKeys[3] = keys[3];
	arrowKeys[4] = keys[4];
	arrowKeys[5] = keys[5];
	arrowKeys[6] = keys[6];
	arrowKeys[7] = keys[7];
	arrowKeys[8] = keys[8];
	arrowKeys[9] = keys[9];
}
int Pacman::move(Board& board)
{
	bool nextMove = true;
	int currX, currY;
	currX = getLocation().getX();
	currY = getLocation().getY();
	int count;
	count = updateBoard(board, currX, currY);
	nextMove = getLocation().isMoveValid(currX, currY, board, Creature::getDirection());
	if (!nextMove)
	{
		setDirection((int)directions::Stay);
		printCreature();
	}
	else
	{
		getLocation().draw(' ');
		moveFigure(board);
		printCreature();
	}
	return count;
}
//This function updates the board if pacman ate a bread crumb and returns 1 which will be added to pacman's score.
int Pacman::updateBoard(Board& board, int x, int y)
{
	if (board.getSquare(y, x) == C)
	{
		board.setSquare(y, x, ' ');
		return 1;
	}
	else
		return 0;
}
int Pacman::getDirection(char key)const
{
	if (key == 'a' || key == 'A')
		return (int)directions::Left;
	else if (key == 'd' || key == 'D')
		return (int)directions::Right;
	else if (key == 'w' || key == 'W')
		return (int)directions::Up;
	else if (key == 'x' || key == 'X')
		return (int)directions::Down;
	else if (key == 's' || key == 'S')
		return (int)directions::Stay;
	else return -1;
}