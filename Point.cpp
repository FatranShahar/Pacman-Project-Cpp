#include "Point.h"

void Point::move(int dir, Board& board)
{
	switch (dir) {

	case (int)directions::Left:
		if (x == board.getXTL())
			x = board.getXBR();
		else
			--x;
		break;

	case (int)directions::Right:
		if (x == board.getXBR())
			x = board.getXTL();
		else
			++x;

		break;

	case (int)directions::Up:
		if (y == board.getYTL())
			y = board.getYBR();
		else
			--y;
		break;

	case (int)directions::Down:
		if (y == board.getYBR())
			y = board.getYTL();
		else
			++y;
		break;

	case (int)directions::Stay:
		break;
	}
}

Point Point::boardBoundries(int dir, Board& board) {
	Point currPoint;
	currPoint.x = x;
	currPoint.y = y;
	switch (dir) {

	case (int)directions::Left:
		if (x != board.getXTL())
			--x;
		currPoint.x = x;
		break;

	case (int)directions::Right:
		if (x != board.getXBR())
			++x;
		currPoint.x = x;
		break;

	case (int)directions::Up:
		if (y != board.getYTL())
			--y;
		currPoint.y = y;
		break;

	case (int)directions::Down:
		if (y != board.getYBR())
			++y;
		currPoint.y = y;
		break;

	case (int)directions::Stay:
		break;
	}
	return currPoint;
}
bool Point::isMoveValid(int x, int y, Board& board, int direction)const
{
	int xTL = board.getXTL();
	int xBR = board.getXBR();
	int yTL = board.getYTL();
	int yBR = board.getYBR();
	switch (direction) {

	case (int)directions::Left:
		if (x == xTL + 1 && board.getSquare(y, xTL) != W && board.getSquare(y, xBR) != W)
			return true;
		else if (x == xTL && board.getSquare(y, xBR) == W)
			return false;
		{
			if (board.getSquare(y, x - 1) != W)
				return true;
			else
				return false;
		}
		break;

	case (int)directions::Right:
		if (x == xBR - 1 && board.getSquare(y, xBR) != W && board.getSquare(y, xTL) != W)
			return true;
		else if (x == xBR && board.getSquare(y, xTL) == W)
			return false;
		else
		{
			if (board.getSquare(y, x + 1) != W)
				return true;
			else
				return false;
		}
		break;

	case (int)directions::Up:
		if (y == yTL + 1 && board.getSquare(yTL, x) != W && board.getSquare(yBR, x) != W)
			return true;
		else if (y == yTL && board.getSquare(yBR, x) == W)
			return false;
		else {
			if (board.getSquare(y - 1, x) != W)
				return true;
			else
				return false;
		}

		break;

	case (int)directions::Down:
		if (y == yBR - 1 && board.getSquare(yBR, x) != W && board.getSquare(yTL, x) != W)
			return true;
		else if (y == yBR && board.getSquare(yTL, x) == W)
			return false;
		else
		{
			if (board.getSquare(y + 1, x) != W)
				return true;
			else
				return false;
		}

		break;
	default:
		return false;
		break;
	}
}
