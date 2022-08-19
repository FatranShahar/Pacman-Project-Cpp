#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include "utilis.h"
#include <string>
#include <fstream>


enum { LEN = 25, WID = 80 };
static const unsigned char C = 249, W = 219; //W- WALL, C-CRUMB

class Board {
	int logLEN, logWID;
	int xTL, yTL, xBR, yBR;
	unsigned char board[LEN][WID];
	bool _silentMode=false;
public:
	void initBoard(bool silentMode);
	void setSquare(int x, int y, char c) {
		board[x][y] = c;
	}
	unsigned char getSquare(int x, int y)
	{
		return board[x][y];
	}
	//gets the logical len
	void setLogLen(int len) { logLEN = len; }
	//gets the logical wid
	void setLogWID(int wid) { logWID = wid; }
	int getLogLEN() const { return logLEN; }
	int getLogWID() const { return logWID; }
	void drawBoard();
	void getBoardSize();
	//sets the x coord of top left sqare which is a wall
	void setXYTL();
	void setXYBR();
	int getXTL() const { return xTL; }
	int getYTL() const { return yTL; }
	int getXBR() const { return xBR; }
	int getYBR() const { return yBR; }
	int getNumOfBreadCrumbs()const;
};
#endif
