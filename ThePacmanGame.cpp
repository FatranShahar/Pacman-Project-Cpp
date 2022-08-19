#include "ThePacmanGame.h"
using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;
using std::filesystem::directory_iterator;

std::map<int, std::string> directionsMap({ {0, "L"}, {1, "R"},{ },{2,"U"},{3,"D"},{4,"S"} });

void ThePacmanGame::loadModeGame() //take care of single board option, to run only 1 screen according to his index in Files (need to fix it)
{
	loadGame.setGameFromFile();
 	loadGame.setResultFiles();
	for (int i = 0; i < Files.size(); i++)
	{
		int pos1=Files[i].find(".");
		string str=Files[i].substr(0,pos1);
		string str2=loadGame.getNameOfFile();
		int pos2 = str2.find(".");
		str2=str2.substr(0,pos2);
		if (str == str2)
			numOfFile = i;
	}
	init(numOfFile);
	runLoadMode();
}

//This fuction handles the choices of the user
bool ThePacmanGame::Menu()
{
	bool oneScreen = false;
	bool EXIT = false;
	char choice, key;
	menu.printMenu();
	choice = menu.getChoice();
	if (choice == (char)MenuOptions::singleBoard)
	{
		cout << "please choose the name of the screen: " << endl;
		for (int i = 0; i < Files.size(); i++)
			cout << "(" << i << ")" << Files[i] << endl;
		oneScreen == true;
		key = _getch();
		system("cls");
		init(key - '0');
		EXIT = run(menu.getLevel(),oneScreen);
	}
	else if (choice == (char)MenuOptions::multipleBoards)
	{
		init();
		EXIT = run(menu.getLevel(),oneScreen);
		if (choice == (char)MenuOptions::Exit)
			EXIT = true;

	}
	else if (choice == (char)MenuOptions::BackToMenu)
	{
		menu.printMenu();
		choice = menu.getChoice();
		if (choice == (char)MenuOptions::Exit)
			EXIT = true;
		else if (choice == (char)MenuOptions::singleBoard)
		{
			cout << "please choose the name of the screen: " << endl;
			for (int i = 0; i < Files.size(); i++)
				cout << "(" << i << ")" << Files[i] << endl;
			key = _getch();
			system("cls");
			init(key - '0');
			EXIT = run(menu.getLevel(),oneScreen);
		}
		else if (choice == (char)MenuOptions::multipleBoards)
		{
			init();
			EXIT = run(menu.getLevel(),oneScreen);
			if (choice == (char)MenuOptions::Exit)
				EXIT = true;

		}
	}
	else if (choice == (char)MenuOptions::Exit)
	{
		EXIT = true;  
	}
	return EXIT;
}
void ThePacmanGame::runLoadMode()
{
	system("cls");
	bool testFailed = false;
	Point disAppearance;
	disAppearance.setPoint(-1, -1);
	char key;
	bool fruitOnScreen = false;
	bool EXIT = false;
	int dir, ghostsDir,finishedScreenInd=0;
	int i = 0, stepsPerScreen = 0, pacmanDied = 0, pacInd = 0, ghostsInd = 0, fruitInd = 0, pacmanDiedPerScreen = 0, locationInd = 0,fruitFigureInd=1;
	bool ghostCaughtPacman = false, isFirstAppearance = true, died_in_even = true;
	bool pacmanAteAfruit = false;
	if (!_loadMode)
		p.setDirection((int)directions::Stay);

	do
	{
			dir = loadGame.getPacmanDir(pacInd);
			p.setDirection(dir);
			pacInd++;
		

		score += p.move(board);
		if (!_silentMode)
		{
			gotoxy(legendLocation.getX() + 14, legendLocation.getY());
			cout << score;
			gotoxy(legendLocation.getX() + 6, legendLocation.getY());
			cout << lives;
		}
		
		ghostCaughtPacman = pacmanLives(p, ghosts);
		if (ghostCaughtPacman)
		{
			ghostCaughtPacman = pacmanGotCaught();
			if (pacmanDiedPerScreen < loadGame.getWhenPacmanDiedSize())
			{
				if (i != loadGame.getTheTimePacmanDied(pacmanDiedPerScreen))
				{
					testFailed = true;
				}
				pacmanDiedPerScreen++;
			}
		}
		

		if(i%2==0)
		{
			for (int i = 0; i < numOfGhosts; i++)
			{
				ghostsDir = loadGame.getGhostDir(i, ghostsInd);
				ghosts[i].setDirection(ghostsDir);
			}
			ghostsInd+=2;

			for (int i = 0; i < numOfGhosts; i++)
				ghosts[i].move(board);
		}
		
		ghostCaughtPacman = pacmanLives(p, ghosts);
		if (ghostCaughtPacman)
		{
			ghostCaughtPacman = pacmanGotCaught();
			if (pacmanDiedPerScreen < loadGame.getWhenPacmanDiedSize()) 
			{
				if (i != loadGame.getTheTimePacmanDied(pacmanDiedPerScreen))
				{
					testFailed = true;
				}
				pacmanDiedPerScreen++;
			}
		}

		if (loadGame.getFruitLocation(locationInd) == disAppearance)
		{
			fruitOnScreen = false;
			if (i % 200 == 199)
			{
				if (fruitFigureInd < loadGame.getFruitFiguresSize())
				{
					fruit.Creature::setFigure(loadGame.getFruitFigure(fruitFigureInd));
					fruit.printCreature();
					fruitFigureInd++;
				}
			}
			else {
				if (fruitFigureInd < loadGame.getFruitFiguresSize())
				{
					fruit.Creature::setFigure(loadGame.getFruitFigure(fruitFigureInd));
					fruit.printCreature();
					fruitFigureInd++;
				}
				locationInd++;
				isFirstAppearance = true;
			}
		}
		else
		{
			if (isFirstAppearance)
			{
				fruit.Creature::setLocation(loadGame.getFruitLocation(locationInd).getX(), loadGame.getFruitLocation(locationInd).getY());
			}
			fruitOnScreen = true;
			fruit.printCreature();
			if (i % 4 == 0 && !isFirstAppearance)
			{
				fruit.Creature::setDirection(loadGame.getFruitDir(fruitInd));
				if (fruitFigureInd < loadGame.getFruitFiguresSize())
				{
					fruit.Creature::setFigure(loadGame.getFruitFigure(fruitFigureInd));
					fruit.printCreature();
					fruitFigureInd++;
				}
				fruit.move(board, _loadMode);
			}
			locationInd++;
			fruitInd++;
			isFirstAppearance = false;
		}

		if (!_silentMode)
		{
			gotoxy(legendLocation.getX() + 6, legendLocation.getY());
			cout << lives;
		}
		pacmanAteAfruit = pacmanAteAFruit(p, fruit, fruitOnScreen);
		if (pacmanAteAfruit == true)
		{
			raiseScore(fruit);
			bonusScore += fruit.getFigure() - '0';
		}
		if (!_silentMode)
		{
			gotoxy(legendLocation.getX() + 14, legendLocation.getY());
			cout << score;
		}
		
		if (!_silentMode)
			Sleep(150);
		if (testFailed)
		{
			system("cls");
			cout << "TEST FAILED";
			exit(0);
		}
		i++;
		stepsPerScreen++;
	} while (lives > 0 && score < totalBreadCrumbs + bonusScore && !EXIT);
	if (lives == 0)
	{
		if (!_silentMode)
		{
			system("cls");
			cout << "GAME OVER " << endl;
		}
		if (_silentMode)
		{
			system("cls");
			if (testFailed)
			{
				cout << "TEST FAILED";
				exit(0);
			}
			else cout << "TEST SUCCEEDED";
		}
		
	}
	else if (score == totalBreadCrumbs + bonusScore)
	{
		system("cls");
		if (i != loadGame.getTheTimeWhenPacmanFinishedScreen(finishedScreenInd))
			testFailed = true;
		if (testFailed)
		{
			cout << "TEST FAILED";
			exit(0);
		}
		finishedScreenInd++;
		if (loadGame.getFileIndex() + 1 < loadGame.getStepsFilesSize())
		{
			if (!_silentMode)
			{
				cout << "-----NEXT LEVEL-----" << endl;
				Sleep(600);
			}
			system("cls");
			numOfFile++;
			stepsPerScreen = 0;
			loadGame.setFileIndex(loadGame.getFileIndex() + 1);
			loadModeGame();
		}
		else
		{
			if (!_silentMode)
				cout << "congrats!! You WON!!" << endl;
			else if (_silentMode)
			{
				system("cls");
				if (testFailed)
				{
					cout << "TEST FAILED";
					exit(0);
				}
				else cout << "TEST SUCCEEDED";
			}
			exit(0);
		}
	}
}

//This function initate the game: sets the board, sets the creatures locations and figures , etc..
void ThePacmanGame::init(int fileIndex)
{
	int ind = 0;
	fruit.setSilentMode(_silentMode);
	p.setSilentMode(_silentMode);
	if (!_loadMode)
	{
		fruit.setFigure('f');
		if (_saveMode)
			steps.push_back("fFig: " + std::to_string(fruit.getFigure()));
	}
	else if (_loadMode)
		fruit.Creature::setFigure(loadGame.getFruitFigure(ind));

	board.initBoard(_silentMode);
	bool isSet = false;
	while (!isSet && fileIndex < Files.size()) {
		isSet = setScreen(fileIndex);
		fileIndex = fileIndex + 1;
	}
	totalBreadCrumbs += board.getNumOfBreadCrumbs();
	board.setXYBR();
	board.setXYTL();
	if (!_loadMode)
	{
		p.setArrowKeys("aAdDwWxXsS");
		p.setDirection((int)directions::Stay);
		fruit.setLocation(board);
	}
	p.setFigure('@');
	for (int i = 0; i < numOfGhosts; i++)
	{
		ghosts[i].setFigure('$');
		ghosts[i].setSilentMode(_silentMode);
	}

	board.drawBoard();
	p.printCreature();
	for (int i = 0; i < numOfGhosts; i++)
		ghosts[i].printCreature();
}
//This function runs the game and handles all the different stages: winning, losing , next level..
bool ThePacmanGame::run(char level, bool singleBoard)
{
	
	bool fruitOnScreen = false;
	bool EXIT = false;
	char key = 0;
	int dir;
	int i = 0, stepsPerScreen = 0;
	int countESC = 0, pacmanDied=0;
	bool ghostCaughtPacman = false, isFirstAppearance = true;;
	bool pacmanAteAfruit = false;
	if (!_loadMode)
		p.setDirection((int)directions::Stay);
	do
	{

		if (countESC % 2 == 0)
		{
			if (_kbhit())
			{
				key = _getch();
				if (key == ESC)
					countESC++;
				if ((dir = p.getDirection(key)) != -1)
					p.setDirection(dir);
			}
			score += p.move(board);

			gotoxy(legendLocation.getX() + 14, legendLocation.getY());
			cout << score;
			ghostCaughtPacman = pacmanLives(p, ghosts);
			if (ghostCaughtPacman)
			{
				if (_saveMode)
				{
					pacmanDied++;
					result.push_back("pacman died at the " + std::to_string(pacmanDied) + " time, after " + std::to_string(i) + " steps");
					toResultFile();
				}
				ghostCaughtPacman = pacmanGotCaught();
			}

			if (i % 2 == 0)
			{
				if (level == (char)LEVELS::NOVICE)
					for (int i = 0; i < numOfGhosts; i++)
						ghosts[i].setDirection(rand() % 10);

				else if (level == (char)LEVELS::GOOD)
				{
					if (i % 25 < 20)
						for (int i = 0; i < numOfGhosts; i++)
							ghosts[i].smartMove(board, p.getLocation());

					else
						for (int i = 0; i < numOfGhosts; i++)
							ghosts[i].setDirection(rand() % 10);
				}
				else if (level == (char)LEVELS::BEST)
					for (int i = 0; i < numOfGhosts; i++)
						ghosts[i].smartMove(board, p.getLocation());

					 for (int i = 0; i < numOfGhosts; i++)
						 ghosts[i].move(board);
			}


			if (i % 200 < 100)
			{
				if (i % 4 == 0)
				{
					fruitOnScreen = true;
					if (_saveMode)
						steps.push_back("fFig: " + std::to_string(fruit.getFigure()));
					fruit.printCreature();
					if (i % 4 == 0)
						fruit.move(board, _loadMode);
				}
			}
			else
			{
				fruitOnScreen = false;
				int iFruit = fruit.getLocation().getY();
				int jFruit = fruit.getLocation().getX();

				if (board.getSquare(iFruit, jFruit) == C)
				{
					fruit.setFigure(C);
					if (_saveMode)
						steps.push_back("fFig: " + std::to_string(fruit.getFigure()));
					fruit.printCreature();
				}
				else if (board.getSquare(iFruit, jFruit) == ' ')
				{
					fruit.setFigure(' ');
					if (_saveMode)
						steps.push_back("fFig: " + std::to_string(fruit.getFigure()));
					fruit.printCreature();
				}
				if (i % 200 == 199)
				{
					fruit.setFigure('f');
					if (_saveMode)
						steps.push_back("fFig: " + std::to_string(fruit.getFigure()));
					fruit.setLocation(board);
				}
			}

			ghostCaughtPacman = pacmanLives(p, ghosts);
			if (ghostCaughtPacman)
			{
				if (_saveMode)
				{
					pacmanDied++;
					result.push_back("pacman died at the " + std::to_string(pacmanDied) + " time, after " + std::to_string(i) + " steps");
					toResultFile();
				}
				ghostCaughtPacman = pacmanGotCaught();
			}
			gotoxy(legendLocation.getX() + 6, legendLocation.getY());
			cout << lives;

			pacmanAteAfruit = pacmanAteAFruit(p, fruit, fruitOnScreen);
			if (pacmanAteAfruit == true)
			{
				raiseScore(fruit);
				bonusScore += fruit.getFigure() - '0';
			}

			gotoxy(legendLocation.getX() + 14, legendLocation.getY());
			cout << score;
			Sleep(150);
			i++;
			stepsPerScreen++;
		}
		else {
			system("cls");
			cout << "The game is paused, press ESC to continue the game!" << endl << "To go back to the main menu press g or G!" << endl;
			key = _getch();
			if (key == ESC)
			{
				countESC++;
				system("cls");
				board.drawBoard();
				gotoxy(legendLocation.getX() + 14, legendLocation.getY());
				cout << score;
				gotoxy(legendLocation.getX() + 6, legendLocation.getY());
				cout << lives;
			}

			else if (key == 'g' || key == 'G')
			{
				system("cls");
				score = 0;
				lives = 3;
				numOfFile = 0;
				totalBreadCrumbs = 0;
				bonusScore = 0;
				if (Menu() == true)
					EXIT = true;

			}
		}
		if (_saveMode)
		{
			steps.push_back("p: " + directionsMap.at(p.Creature::getDirection()));
			for (int i = 0; i < numOfGhosts; i++)
				steps.push_back("g" + std::to_string(i) + ": " + directionsMap.at(ghosts[i].getDirection()));
			if (fruitOnScreen)
			{
				steps.push_back("fL: " + std::to_string((fruit.getLocation().getX())) + "," + std::to_string((fruit.getLocation().getY())));
				steps.push_back("f: " + directionsMap.at(fruit.getDirection()));
			}
			else 	steps.push_back("fL: " + std::to_string(-1) + "," + std::to_string(-1));

		}

	} while (lives > 0 && score < totalBreadCrumbs + bonusScore && !EXIT);
	if (_saveMode)
	{
		saveToFile();
		steps.clear();
	}
	if (lives == 0)
	{
		system("cls");
		score = 0;
		lives = 3;
		cout << "GAME OVER " << endl << "Press any key to return to main menu";
		key = _getch();
		system("cls");
		totalBreadCrumbs = 0;
		bonusScore = 0;
		numOfFile = 0;
		if (Menu() == true)
			EXIT = true;
	}
	else if (singleBoard && score == totalBreadCrumbs + bonusScore)
	{
		cout << "congrats!! You WON!!" << endl << "Press any key to return to main menu";
		score = 0;
		lives = 3;
		key = _getch();
		system("cls");
		numOfFile = 0;
		totalBreadCrumbs = 0;
		bonusScore = 0;
		result.clear();
		if (Menu() == true)
			EXIT = true;
	}


	else if (score == totalBreadCrumbs + bonusScore)
	{
		if (_saveMode)
		{
			result.push_back("pacman finished screen number " + std::to_string(numOfFile + 1) + " after " + std::to_string(stepsPerScreen) + " steps");
			toResultFile();
			result.clear();
		}
		system("cls");
		if (numOfFile + 1 < Files.size())
		{
			cout << "-----NEXT LEVEL-----" << endl;
			Sleep(600);
			system("cls");
			numOfFile++;
			p.setDirection((int)directions::Stay);
			init(numOfFile);
			run(level,singleBoard);
		}
		while (!EXIT)
		{
			cout << "congrats!! You WON!!" << endl << "Press any key to return to main menu";
			score = 0;
			lives = 3;
			key = _getch();
			system("cls");
			numOfFile = 0;
			totalBreadCrumbs = 0;
			bonusScore = 0;
			result.clear();
			if (Menu() == true)
				EXIT = true;
		}
	}

	return EXIT;
}
void ThePacmanGame::toResultFile()
{
	string nameOfFile = "pacman_" + std::to_string(numOfFile + 1) + ".result";
	ofstream File(nameOfFile);

	for (const auto& e : result) File << e << "\n";

	File.close();
}
void ThePacmanGame::saveToFile()
{
	string nameOfFile = "pacman_" + std::to_string(numOfFile + 1) + ".steps";
	ofstream File(nameOfFile);

	for (const auto& e : steps) File << e << "\n";

	File.close();
}
//This function set all the creatures to their first location and updates pacman lives
bool ThePacmanGame::pacmanGotCaught()
{
	lives--;
	gotoxy(p.getLocation().getX(), p.getLocation().getY());
	cout << ' ';
	p.setLocation(p.getFirstLocation().getX(), p.getFirstLocation().getY());
	for (int i = 0; i < numOfGhosts; i++)
	{
		Point currPoint;
		currPoint = ghosts[i].getLocation();
		if (board.getSquare(currPoint.getY(), currPoint.getX()) == ' ')
			currPoint.draw(' ');
		else
			currPoint.draw(C);
	}
	for (int i = 0; i < numOfGhosts; i++)
	{
		ghosts[i].setLocation(ghosts[i].getFirstLocation().getX(), ghosts[i].getFirstLocation().getY());
	}
	return false;
}
//This function checks if one of the ghosts caught pacman
bool ThePacmanGame::pacmanLives(Pacman& p, Ghosts ghosts[MAX_NUM_GHOSTS])
{
	for (int i = 0; i < numOfGhosts; i++)
	{
		if (p.getLocation() == ghosts[i].getLocation())
			return true;
	}
	return false;
}
//This function checks if pacman ate a fruit
bool ThePacmanGame::pacmanAteAFruit(Pacman& p, Fruit& fruit, bool isFruitOnScreen)
{
	if (p.getLocation() == fruit.getLocation() && isFruitOnScreen)
		return true;
	else
		return false;
}
//if pacman ate a fruit this function raise the score according to the fruit figure
void ThePacmanGame::raiseScore(Fruit& fruit)
{
	char figure = fruit.getFigure();
	int addedScore = figure - '0';
	score += addedScore;
}
//This function checks if a file ends with a specific ending
bool ThePacmanGame::has_suffix(const std::string& str, const std::string& suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

//This function gets the file names ends with .screen and save it in Files data member
void ThePacmanGame::getFilesFromDirectory()
{
	string path = ".";
	for (const auto& file : directory_iterator(path))
	{
		if (has_suffix(file.path().string(), ".screen"))
		{
			Files.push_back(file.path().string().substr(2));
		}
	}
}
//This function submit the chosen screens from the workig directory
bool ThePacmanGame::setScreen(int fileIndex)
{
	if (fileIndex != 0)
		numOfFile = fileIndex;
	ifstream file(Files[fileIndex]);
	sort(Files.begin(), Files.end());
	int ind = 0, i = 0, j = 0;
	string line;
	if (!file.is_open())
		cout << "Could not open the file " << endl;

	while (file.peek() != EOF)
	{
		getline(file, line);
		if (i == 0)
			board.setLogWID(line.size());
		for (int j = 0; j < line.length(); j++)
			board.setSquare(i, j, line[j]);
		i++;
	}
	board.setLogLen(i);

	try {
		setBoard();

	}
	catch (Error& e)
	{
		++errorFileCounter;
		system("cls");
		cout << e.getMsg();
		cout << endl << "press any key to continue" << endl;
		char c = _getch();
		if (errorFileCounter == Files.size())
		{
			system("cls");
			cout << "there are problems with all files" << endl << "cannot run game" << endl << "exiting... :(";

			exit(1);
		}
			
		system("cls");
		return false;

	}
	return true;

}
//This function inserts the legend where it should be placed according to the file
void ThePacmanGame::insertLegend(int i, int j)

{
	int s = 0;
	int ind = j;
	string legend = "Lives:  Score:      ";
	while (legend[s] != '\0')
	{
		board.setSquare(i, ind, legend[s]);
		s++;
		ind++;
	}
	for (int l = i + 1; l < i + 3; l++)
		for (int c = j; c < j + 20; c++)
			board.setSquare(l, c, ' ');

}

//This function gets all the infromation about the creatures and the board according to the file
void ThePacmanGame::setBoard()
{
	bool foundTheLeg = false;
	int legendCounter = 0;
	int GhostsNum = 0;
	int pacCounter = 0;
	int legI, legJ;
	int wid = board.getLogWID();
	int len = board.getLogLEN();
	bool allRowsLensEqual;
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < wid; j++)
		{
			if (board.getSquare(i, j) == '&')
			{
				++legendCounter;
				legI = i;
				legJ = j;
				legendLocation.setPoint(j, i);
				insertLegend(i, j);
				foundTheLeg = true;
			}
			else if (board.getSquare(i, j) == '@')
			{
				++pacCounter;
				p.setLocation(j, i);
				p.setFirstLocation(j, i);
				board.setSquare(i, j, ' ');
			}
			else if (board.getSquare(i, j) == '$')
			{
				ghosts[GhostsNum].setLocation(j, i);
				ghosts[GhostsNum].setFirstLocation(j, i);
				board.setSquare(i, j, ' ');
				GhostsNum++;
			}
			else if (board.getSquare(i, j) == '#')
				board.setSquare(i, j, W);
			else if (foundTheLeg == true)
			{
				if (((i >= legI && i < legI + 3) && (j >= legJ && j < legJ + 20)) == false)
				{
					if (board.getSquare(i, j) == '%')
						board.setSquare(i, j, ' ');
					else board.setSquare(i, j, C);

				}
			}
			else if (board.getSquare(i, j) != '%')
				board.setSquare(i, j, C);
			else board.setSquare(i, j, ' ');
		}
	}
	if (GhostsNum > 4)
		throw GhostError();
	else if (legendCounter > 1)
		throw TooManyLegendsError();
	else if (foundTheLeg == false)
		throw LegendNotFoundError();
	//else if (wid == 0 && len == 0) // &&/||?
	//	throw EmptyFileError();
	else if (pacCounter == 0)
		throw PacmanNotFoundError();
	else if (pacCounter > 1)
		throw TooManyPacmansError();
	else if (wid > 80)
		throw TooManyColumnsError();
	else if (wid < 20)
		throw ShortBoardError();
	else if (len > 25)
		throw TooManyRowsError();
	//else if () 
	//	throw BoardErrors::SizeOfRows
	this->numOfGhosts = GhostsNum;
}