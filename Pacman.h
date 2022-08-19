#ifndef _PACMAN_H_
#define _PACMAN_H_

#include <cstring>
#include "Creature.h"

class Pacman :public Creature {
	char arrowKeys[10];
	Point firstLocation;
public:
	void setFirstLocation(int x, int y) { firstLocation.setPoint(x, y); }
	Point& getFirstLocation() { return firstLocation; }
	void setArrowKeys(const char* keys);
	int getDirection(char key)const;
	int move(Board& board);
	int updateBoard(Board& board, int x, int y);
};


#endif