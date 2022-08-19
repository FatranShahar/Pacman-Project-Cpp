#ifndef _POINT_H_
#define _POINT_H_
#include "Board.h"
#include  "directions.h"
using std::cout;
using std::endl;
class Point {
	int x, y;

public:
	void draw(char ch)const {
		gotoxy(this->x, this->y);
		cout << ch << endl;
	}
	//This function moves pacman and ghosts x and y according to the direction - they can't pass in tunnels
	void moveCreatures(int dir, Board& board) { boardBoundries(dir, board); }
	void setPoint(int a, int b) { x = a; y = b; }
	int getX()const { return x; }
	int getY()const { return y; }
	void move(int dir, Board& board);
	bool isMoveValid(int x, int y, Board& board, int direction)const;
	Point boardBoundries(int dir, Board& board);
	bool operator==(const Point& other)
	{
		if (x == other.x && y == other.y)
			return true;
		else
			return false;
	}
};

#endif
