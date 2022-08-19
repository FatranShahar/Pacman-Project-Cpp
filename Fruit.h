#ifndef  _FRUIT_H
#define  _FRUIT_H

#include "Creature.h" 
class Fruit : public Creature {
public:
	//This function sets the fruit figure - a random number between 5-9
	virtual void setFigure(unsigned char ch) {
		if (ch == C)
		{
			Creature::setFigure(C);
		}
		else if (ch == ' ')
		{
			Creature::setFigure(' ');
		}
		else
		{
			int random = rand() % 5 + 5;
			Creature::setFigure(random + '0');
		}
	}
	//This function sets a random location within the board boundries.
	void setLocation(Board& board);
	void move(Board& board,bool loadMode);
	void setDirection() { Creature::setDirection(rand() % 5); }
};

#endif