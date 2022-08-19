#ifndef  _GHOSTS_H
#define  _GHOSTS_H

#include <cstring>
#include "Creature.h"
#include <vector>
#include <queue>

using std::vector;
class Ghosts :public Creature {
	Point firstLocation;
public:
	void setFirstLocation(int x, int y) { firstLocation.setPoint(x, y); }
	Point& getFirstLocation() { return firstLocation; }
	void move(Board& board);
	//This function is for the good and best levels- when ghosts chase pacman
	void smartMove(Board& board, Point& pacPos);
	bool isValidStep(const vector<vector<bool>>& visit, int y, int x, Board& board);
	Point BFS(Board& board, vector<vector<bool>>& visit, int row, int col);
};


#endif