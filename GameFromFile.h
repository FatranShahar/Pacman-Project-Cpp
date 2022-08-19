#ifndef _GameFromFile_H_
#define _GameFromFile_H_
#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>
#include "Point.h"
using::std::vector;
using std::array;
using std::string;
#include <iterator>
enum : size_t { MAX_NUM_GHOSTS = 4 };
class GameFromFile
{
	vector<char> fruitFiguers;
	vector<Point> fruitLocations;
	vector<int>whenPacmanDied;
	vector<int> whenPacmanFinishedScreen = { 0 };
	int fileIndex = 0;
	vector<string> resultFiles;
	vector<string> stepsFiles;
	string nameOfFile;
	vector<string> pacmanSteps;
	vector<string> fruitSteps;
	array<vector<string>, MAX_NUM_GHOSTS> ghostStepsArr;
public:
	string& getNameOfFile() { return nameOfFile; }
	void setGameFromFile();
	void getStepsFilesFromDirectory();
	void getResultFilesFromDirectory();
	void setResultFiles();
	bool  has_suffix(const std::string& str, const std::string& suffix);
	int getPacmanDir(int ind)const;
	int getGhostDir(int numOfGhost, int ind)const;
	int getFruitDir(int ind)const;
	void setFileIndex(int newInd) { fileIndex = newInd; }
	int getFileIndex()const { return fileIndex; }
	int getWhenPacmanDiedSize()const { return whenPacmanDied.size(); }
	int findNumOfSteps(string line);
	int getTheTimePacmanDied(int ind) {return whenPacmanDied[ind];} 
	int getStepsFilesSize()const { return stepsFiles.size(); }
	Point setFruitLocations(string line);
	Point getFruitLocation(int ind)const { return fruitLocations[ind]; }
	char getFruitFigure(int ind)const { return fruitFiguers[ind]; }
	char setFruitFigure(string line);
	int getFruitFiguresSize()const { return fruitFiguers.size(); }
	int getTheTimeWhenPacmanFinishedScreen(int ind)const { return whenPacmanFinishedScreen[ind]; }
};

#endif