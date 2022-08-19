#include "Board.h"
using std::cout;
using std::endl;

void Board::initBoard(bool silentMode)
{
	for (int i = 0; i < LEN; i++)
		for (int j = 0; j < WID; j++)
			board[i][j] = ' ';
	_silentMode = silentMode;
}


int Board::getNumOfBreadCrumbs()const
{
	int countBreadCrumb = 0;
	for (int i = 0; i < logLEN; i++)
	{
		for (int j = 0; j < logWID; j++)
		{
			if (board[i][j] == C)
				countBreadCrumb++;
		}
	}
	return countBreadCrumb;
}
void Board::drawBoard()
{
	if (!_silentMode)
	{
		for (int i = 0; i < logLEN; i++)
		{
			for (int j = 0; j < logWID; j++)
			{
				cout << board[i][j];
			}
			cout << endl;
		}
	}
}

void Board::getBoardSize()
{
	int i = 0, j = 0;
	int len = 0, wid = 0;

	while (board[i][j] != 'X') {
		len++;
		i++;
	}
	logLEN = len;
}
void Board::setXYTL()
{
	int i, j;
	bool flag = false;

	for (i = 0; i < logLEN && flag == false; i++)
	{
		for (j = 0; j < logWID && flag == false; j++)
		{
			if (board[i][j] == W)
			{
				xTL = j;
				yTL = i;
				flag = true;
			}
		}
	}
}
void Board::setXYBR()
{
	int i, j;
	bool flag = false;

	for (i = logLEN - 1; i >= 0 && flag == false; i--)
	{
		for (j = logWID - 1; j >= 0 && flag == false; j--)
		{
			if (board[i][j] == W)
			{
				xBR = j;
				yBR = i;
				flag = true;
			}
		}
	}
}
