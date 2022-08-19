#ifndef _ERROR_H_
#define _ERROR_H_
//The purpose of this class is to check the integrity of the board
#include <iostream>
#include <string>

using std::string;

class Error {
protected:
	string msg;

public:

	Error(string s) : msg(s) {}
	string getMsg() { return msg; }
};

class TooManyPacmansError : public Error { // checking if there is only single pacman on the board

public:
	TooManyPacmansError() : Error("Error: There are too many pacman charcters in the text file"){}
};
class PacmanNotFoundError : public Error { // checking if there is only single pacman on the board

public:
	PacmanNotFoundError() : Error("Error: Pacman not found in the text file"){}
};
class GhostError : public Error { // check if num of ghost is valid (0-4 ghosts)

public:
	GhostError() : Error("Error: Too many ghosts found in the text File"){}
};

class TooManyLegendsError : public Error { // check if Legend is valid

public:
	TooManyLegendsError() : Error("Error: There are too many Legend charcters in the text file"){}
};
class LegendNotFoundError : public Error { // check if Legend is valid

public:
	LegendNotFoundError() : Error("Error: Legend not found in the text file") {}
};
class EmptyFileError : public Error { // check if File is

public:
	EmptyFileError() :  Error("Error: File is empty"){}
};
class ShortBoardError : public Error {

public:
	ShortBoardError() : Error("Error: The board has under 20 columns"){}
};
class TooManyColumnsError : public Error {

public:
	TooManyColumnsError() : Error("Error: The board has more than 80 columns"){}
};
class TooManyRowsError : public Error {

public:
	TooManyRowsError() : Error("Error: The board has more than 25 rows"){}
};
class sizeOfRowsError : public Error {

public:
	sizeOfRowsError() : Error("Error: There is a Row shorter than the first row"){}
};
#endif
