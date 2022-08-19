#ifndef _CREATURE_H_
#define _CREATURE_H_
//This class is the "father" class of all the creatures: pacman,ghosts and fruit
#include "Point.h"

class Creature {
	Point location;
	char figure;
	int direction;
	bool _silentMode = false;
public:
	void setSilentMode(bool silentMode) { _silentMode = silentMode; }
	void setLocation(int x, int y) { location.setPoint(x, y); }
	Point& getLocation() { return location; }
	virtual void moveFigure(Board& board) { location.move(direction, board); }
	void setDirection(int dir) { direction = dir; }
	int getDirection() const { return direction; }
	void printCreature() 
	{ if(!_silentMode)
		location.draw(figure); }
	void setFigure(char ch) { figure = ch;  }
	char getFigure() const { return figure; }
};


#endif
