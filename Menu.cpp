#include "Menu.h"
using std::cout;
using std::cin;
using std::endl;
const unsigned char C = 249, W = 219; //W- WALL, C-CRUMB

void Menu::printMenu()
{
	char key;
	char choice;
	char game;
	system("cls");
	hideCursor();
	cout << "(1) Start a new game" << endl << "(8) Present instructions and keys" << endl << "(9) EXIT" << endl;
	choice = _getch();
	if (choice == (char)MenuOptions::NewGame)
	{
		system("cls");
		cout << "please choose level: " << endl << "(1)NOVICE" << endl << "(2)GOOD" << endl << "(3)BEST" << endl;
		key = _getch();
		if (key == (char)LEVELS::NOVICE)
			level = (char)LEVELS::NOVICE;
		else if (key == (char)LEVELS::GOOD)
			level = (char)LEVELS::GOOD;
		else if (key == (char)LEVELS::BEST)
			level = (char)LEVELS::BEST;

		system("cls");
		cout << "would you like to play with single board or with multiple boards?" << endl << "(3) single board" << endl << "(4)multiple boards";
		key = _getch();
		system("cls");
		if (key == (char)MenuOptions::singleBoard)
			option = (char)MenuOptions::singleBoard;
		else if (key == (char)MenuOptions::multipleBoards)
			option = (char)MenuOptions::multipleBoards;

	}
	else if (choice == (char)MenuOptions::SpecificScreen)
	{
		system("cls");
		option = (char)MenuOptions::SpecificScreen;
	}
	else if (choice == (char)MenuOptions::Instructions)
	{
		system("cls");
		cout << "The game characters: " << endl << "@ - pacman" << endl << "$ - ghosts" << endl;
		cout << C << " - bread crumb" << endl << endl;
		cout << "Game instructions:" << endl << "In order to move to right press keys d or D" << endl << "To move left press a or A" << endl <<
			"To move up press w or W" << endl << "To move down press x or X" << endl << "To stay press s or S" << endl << endl;
		cout << "The Goal of the game: " << endl << "in order to win the game, pacman have to eat all the breadcrumbs on the board and reach 1000 points!" << endl
			<< "If one of the ghosts ($) catches pacman, pacman losing life." << endl;
		cout << "Pacman has 3 lives. if pacman only got 1 life and a ghost catches him, you losing the game" << endl << endl << "What are you waiting for ?? LETS PLAY!" << endl;
		key = _getch();
		if (key)
		{
			system("cls");
			option = (char)MenuOptions::BackToMenu;
		}
	}
	else if (choice == '9')
	{
		//option =(char)MenuOptions::Exit;
		exit(1);
	}
	else {
		system("cls");
		cout << "Your choice is not valid! press any key to go back to the main menu" << endl;
		key = _getch();
		if (key)
		{
			system("cls");
			option = (char)MenuOptions::BackToMenu;
		}
	}
}

