#include "GameFromFile.h"
using std::cout;
using std::cin;
using::std::endl;
using std::string;
using std::ifstream;
using std::filesystem::directory_iterator;
using std::map;
map<string, int> DirectionsMap({ {"L", 0}, {"R", 1},{ },{"U",2},{"D",3},{"S",4} });

int GameFromFile::getPacmanDir(int ind)const
{
	return DirectionsMap.at(pacmanSteps[ind]); 
}
int GameFromFile::getFruitDir(int ind)const
{
	return DirectionsMap.at(fruitSteps[ind]);
}
int GameFromFile::getGhostDir(int numOfGhost, int ind)const
{
	return DirectionsMap.at(ghostStepsArr[numOfGhost][ind]);
}
void GameFromFile::setResultFiles()
{
	int ind;
	whenPacmanDied.clear();
	whenPacmanFinishedScreen.clear();
	sort(resultFiles.begin(), resultFiles.end());
	nameOfFile = resultFiles[fileIndex];
	ifstream file(nameOfFile);
	if (!file.is_open())
		cout << "Could not open the file " << endl;
	string line;
	while (file.peek() != EOF)
	{
		getline(file, line);
		if (line.find("pacman died") != string::npos)
		{
			int num = findNumOfSteps(line);
			whenPacmanDied.push_back(num);
		}
		else if (line.find("pacman finished") != string::npos)
		{
			int num2 = findNumOfSteps(line);
			whenPacmanFinishedScreen.push_back(num2);

		}
	}
}
int GameFromFile::findNumOfSteps(string line)
{
	size_t i = 0;
	int index = line.find("after");
	string str = line.substr(index + 1, line.size());
	for (; i < str.length(); i++) { if (isdigit(str[i])) break; }
	line = str.substr(i, str.length() - i);
	int num = atoi(line.c_str());
	return num;
}
void GameFromFile::setGameFromFile()
{
	fruitLocations.clear();
	fruitFiguers.clear();
	pacmanSteps.clear();
	for (int i = 0; i < MAX_NUM_GHOSTS; i++)
		ghostStepsArr[i].clear();
	fruitSteps.clear();
	int i;
	sort(stepsFiles.begin(), stepsFiles.end());
	if (stepsFiles.empty())
	{
		cout << "Couldn't find any steps file" << endl;
		exit(0);
	}
	else {
		nameOfFile = stepsFiles[fileIndex];
		ifstream file(nameOfFile);
		if (!file.is_open())
			cout << "Could not open the file " << endl;
		string line;
		while (file.peek() != EOF)
		{
			getline(file, line);
			if (line[0] == 'p')
			{
				pacmanSteps.push_back(line.substr(3));
			}
			else if (line[0] == 'g')
			{
				i = line[1] - '0';
				ghostStepsArr[i].push_back(line.substr(4));
			}
			else if (line[0] == 'f' && line[1] == 'L') {

				fruitLocations.push_back(setFruitLocations(line));
			}
			else if (line[0] == 'f' && line[1] == 'F')
				fruitFiguers.push_back(setFruitFigure(line));
			else if(line[0] == 'f')
				fruitSteps.push_back(line.substr(3));
		}
	}
}
char GameFromFile::setFruitFigure(string line)
{
	string str = line.substr(6);
	int fig = atoi(str.c_str());
	return (char)fig;
}
Point GameFromFile::setFruitLocations(string line)
{
	Point location;
	string str = line.substr(4);
	std::string delimiter = ",";
	std::string x=(str.substr(0, str.find(delimiter)));
	std::string y = (str.substr(str.find(delimiter)+1, str.size()));
	location.setPoint(atoi(x.c_str()), atoi(y.c_str()));
	return location;
}
bool  GameFromFile::has_suffix(const string& str, const string& suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
void GameFromFile::getStepsFilesFromDirectory()
{
	string path = ".";
	for (const auto& file : directory_iterator(path))
	{
		if (has_suffix(file.path().string(), ".steps"))
		{
			stepsFiles.push_back(file.path().string().substr(2));
		}
	}
}
void GameFromFile::getResultFilesFromDirectory()
{
	string path = ".";
	for (const auto& file : directory_iterator(path))
	{
		if (has_suffix(file.path().string(), ".result"))
		{
			resultFiles.push_back(file.path().string().substr(2));
		}
	}
}
