#include "Ghosts.h"
using std::queue;
void Ghosts::move(Board& board)
{
	bool nextMove = true;
	bool ghostNextMove;
	int currX, currY;
	currX = getLocation().getX();
	currY = getLocation().getY();

	nextMove = getLocation().isMoveValid(currX, currY, board, getDirection());
	if (nextMove == false)
	{
		setDirection((int)directions::Stay);
		printCreature();
	}
	else
	{
		if (board.getSquare(currY, currX) == ' ')
		{
			getLocation().draw(' ');
			getLocation().moveCreatures(getDirection(), board);
			printCreature();
		}
		else
		{
			getLocation().draw(C);
			getLocation().moveCreatures(getDirection(), board);
			printCreature();
		}
	}
}
void Ghosts::smartMove(Board& board, Point& pacLocation)
{
	int pacmanX = pacLocation.getX(), pacmanY = pacLocation.getY();
	int ghostX = getLocation().getX(), ghostY = getLocation().getY();

	vector<vector<bool>> visit(board.getLogLEN() + 1, vector<bool>(board.getLogWID() + 1, false));
	Point newPos = BFS(board, visit, pacmanY, pacmanX);

	//newPos is to the left
	if (newPos.getX() == ghostX - 1)
		setDirection((int)directions::Left);

	//newPos is to the right
	else if (newPos.getX() == ghostX + 1)
		setDirection((int)directions::Right);

	//newPos is to the up
	else if (newPos.getY() == ghostY - 1)
		setDirection((int)directions::Up);

	//newPos is to the down
	else setDirection((int)directions::Down);


}

bool Ghosts::isValidStep(const vector<vector<bool>>& visit, int y, int x, Board& board)
{
	if (x < 0 || y < 0) {
		return false;
	}

	// If cell is bounds
	if (y >= board.getLogLEN() || x >= board.getLogWID())
		return false;

	// If cell is bounds
	else if (x == board.getXTL() || y == board.getYTL() || board.getSquare(y, x) == W)
		return false;

	// If cell is already visited
	else if (visit[y][x])
		return false;

	// Otherwise
	return true;


}
Point Ghosts::BFS(Board& board, vector<vector<bool>>& visit, int row, int col)
{
	int test = 0;
	Point ghostLocation = getLocation();
	int dRow[] = { -1, 0, 1, 0 };
	int dCol[] = { 0, 1, 0, -1 };
	// Stores indices of the matrix cells
	queue<Point> q;
	int xGhost = getLocation().getX();
	int yGhost = getLocation().getY();
	// Mark the starting cell as visited and push it into the queue
	Point tempXY;

	tempXY.setPoint(col, row);
	q.push(tempXY);
	visit[row][col] = true;


	// Iterate while the queue is not empty
	while (!q.empty()) {

		Point cell = q.front();
		int _x = cell.getX();
		int _y = cell.getY();

		q.pop();

		// Go to the adjacent cells
		for (int i = 0; i < 4; i++) {
			int adjy = _y + dCol[i];
			int adjx = _x + dRow[i];
			Point adjXY;
			adjXY.setPoint(adjx, adjy);
			if (adjXY == ghostLocation)
			{
				Point _X_Y;
				_X_Y.setPoint(_x, _y);
				return _X_Y;
			}
			else if (isValidStep(visit, adjy, adjx, board)) {
				q.push(adjXY);
				visit[adjy][adjx] = true;
			}
		}
	}

	// if short way has not found - return the curr position
	// the ghost dir will be down
	return getLocation();
}