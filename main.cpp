#include <iostream>
#include <Windows.h>
#include "ThePacmanGame.h"

int main(int argc, char** argv)
{
	bool saveMode = false, loadMode = false, silentMode = false;
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "-save")
			saveMode = true;
		else if (arg == "-load")
			loadMode = true;
		else if (arg == "-silent")
			silentMode = true;
		else cout << "Your choice is not valid!" << endl << "You can choose these following modes:" << endl << "-save" << endl << "-load" << endl << "-load-silent";
	}
	if (!loadMode)
		silentMode = false;

	srand(time(NULL));
	bool EXIT = false;
	ThePacmanGame game(loadMode, saveMode, silentMode);
	game.getFilesFromDirectory();
	
	
	if (loadMode || silentMode)
	{
		game.getLoadGame().getStepsFilesFromDirectory();
		game.getLoadGame().getResultFilesFromDirectory();
		game.loadModeGame();
	}
	
	else {
		do
		{
			EXIT = game.Menu();

		} while (EXIT == false);
	}

}