#ifndef _MENU_H_
#define _MENU_H_

#include "utilis.h"
#include "MenuOptions.h"
#include "LEVELS.h"
class Menu {
	char option;
	char level;
public:
	void printMenu();
	char getChoice()const { return option; }
	char getLevel()const { return level; }
};
#endif
