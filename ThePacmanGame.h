#ifndef _THEPACMANGAME_H_
#define _THEPACMANGAME_H_
// This class operates the whole game.

#include "utilis.h"
#include "Pacman.h"
#include "Ghosts.h"
#include "Point.h"
#include "Fruit.h"
#include "Board.h"
#include"Menu.h"
#include "GameFromFile.h"
#include <map>
#include <fstream>
#include "Error.h"
using std::string;

enum { ESC = 27 };

class ThePacmanGame {
	Pacman p;
	Ghosts ghosts[MAX_NUM_GHOSTS];
	int numOfGhosts = 0;
	Fruit fruit;
	int score = 0, lives = 3, bonusScore = 0;
	int totalBreadCrumbs = 0;
	Board board;
	vector<string> Files = {}; //names of the files in the directory which ends with .screen 
	int numOfFile = 0;
	int errorFileCounter = 0;
	Menu menu;
	Point legendLocation;
	bool _loadMode, _saveMode, _silentMode;
	vector<string> steps;
	vector<string> result;
	GameFromFile loadGame;
public:
	ThePacmanGame(bool loadMode, bool saveMode, bool silentMode) { _loadMode = loadMode; _saveMode = saveMode; _silentMode = silentMode; }
	void init(int fileIndex = 0);
	bool run(char level, bool singleBoard);
	bool pacmanLives(Pacman& p, Ghosts ghosts[MAX_NUM_GHOSTS]);
	bool pacmanGotCaught();
	bool pacmanAteAFruit(Pacman& p, Fruit& fruit, bool isFruitOnScreen);
	void raiseScore( Fruit& fruit);
	bool setScreen(int fileIndex);
	void setBoard();
	void insertLegend(int i, int j);
	void getFilesFromDirectory();
	bool Menu();
	bool has_suffix(const std::string& str, const std::string& suffix);
	void saveToFile();
	void toResultFile();
	void loadModeGame();
	void runLoadMode();
	GameFromFile& getLoadGame() { return loadGame; }




};

#endif