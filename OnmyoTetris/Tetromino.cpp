#include "Tetromino.hpp"
#include "Cell.hpp"

Tetromino::Tetromino() = default;

Tetromino::~Tetromino()
	{
		for (int i = 0; i < 4; i++)
		{
			delete cells[i];
		}
	}

bool Tetromino::rotate(Cell *field[HEIGHT][WIDTH])
	{
		if (!canRotate(field)) return false;
		int iRow = this->cells[2]->getX();
		int iCol = this->cells[2]->getY();
		for (int i = 0; i < 4; i++)
		{
			int nRow = this->cells[i]->getX();
			int nCol = this->cells[i]->getY();
			this->cells[i]->setX(iRow - iCol + nCol);
			this->cells[i]->setY(iRow + iCol - nRow);
		}
		return true;
	}

bool Tetromino::moveDown(Cell *field[HEIGHT][WIDTH])
	{
		if (!canMove('D', field)) return false;
		for (int i = 0; i < 4; i++)
			cells[i]->moveDown();
		return true;
	}

bool Tetromino::moveLeft(Cell *field[HEIGHT][WIDTH])
	{
		if (!canMove('L', field)) return false;
		for (int i = 0; i < 4; i++)
			cells[i]->moveLeft();
		return true;
	}

bool Tetromino::moveRight(Cell *field[HEIGHT][WIDTH])
	{
		if (!canMove('R', field)) return false;
		for (int i = 0; i < 4; i++)
			cells[i]->moveRight();
		return true;
	}

bool Tetromino::canMove(char dir, Cell *field[HEIGHT][WIDTH])
	{
		int a, b;
		switch (dir)
		{
		case 'D':
			a = 0; b = 1;
			break;
		case 'L':
			a = -1; b = 0;
			break;
		case 'R':
			a = 1; b = 0;
			break;
		}
		Point *points = initializePoint(this->cells);
		//The lowest hight in the field is 0, which corresponds to the topmost row
		for (int i = 0; i < 4; i++)
		{
			int x = this->cells[i]->getX(), y = this->cells[i]->getY();
			if (y + b >= HEIGHT || x + a < 0 || x + a >= WIDTH)
			{
				delete[]points;
				//cout << "canMove" << dir << " : false" << endl;
				return false;
			}
			if (field[y+b][x+a] != 0 && !this->isSelfCell(points, x + a, y + b))
			{
				delete[]points;
				//cout << "canMove" << dir << " : false" << endl;
				return false;
			}
		}
		//cout << "canMove" << dir << " : true" << endl;
		delete[]points;
		return true;
	}

bool Tetromino::canRotate(Cell *field[HEIGHT][WIDTH])
	{
		int iRow = this->cells[2]->getX();
		int iCol = this->cells[2]->getY();
		int newX, newY;
		//Prepare the points before rotation for collision detection (on heap)
		Tetromino::Point *points = this->initializePoint(this->cells);

		for (int i = 0; i < 4; i++)
		{
			int nRow = this->cells[i]->getX();
			int nCol = this->cells[i]->getY();
			newX = iRow - iCol + nCol;
			newY = iRow + iCol - nRow;

			//Check if out of bounds after the rotation
			if (newX >= WIDTH || newX < 0 || newY >= HEIGHT || newY <= 0)
			{
				cout << "Out of bounds: true" << endl;
				delete[] points;
				return false;
			}

			//Check if any cell of the Tetromino hits other existing cell in the field
			if (field[newX][newY] != 0 && !this->isSelfCell(points, newX, newY))
			{
				delete[]points;
				return false;
			}
		}
		cout << "Out of bounds: false" << endl;
		delete[]points;
		return true;
	}

bool Tetromino::isSelfCell(Point points[], int x, int y)
	{
		bool flag = false;
		for (int i = 0; i < 4; i++)
		{
			if (x == points[i].x && y == points[i].y)
				flag = true;
		}

		//is not cell of the tetromino itself
		if (!flag)
			return false;
	}

Tetromino::Point * Tetromino::initializePoint(Cell *cells[])
{
	Point *points = new Point[4];
	for (int i = 0; i < 4; i++)
	{
		points[i] = { this->cells[i]->getX(), this->cells[i]->getY() };
	}
	return points;
}

I::I(Texture *img)
{
	cells[0] = new Cell(0, 0, img);
	cells[1] = new Cell(0, 1, img);
	cells[2] = new Cell(0, 2, img);
	cells[3] = new Cell(0, 3, img);
	this->shape = 'I';
}

J::J(Texture *img)
{
	cells[0] = new Cell(1, 0, img);
	cells[1] = new Cell(1, 1, img);
	cells[2] = new Cell(1, 2, img);
	cells[3] = new Cell(0, 2, img);
	this->shape = 'J';
}

O::O(Texture *img)
{
	cells[0] = new Cell(0, 0, img);
	cells[1] = new Cell(0, 1, img);
	cells[2] = new Cell(1, 0, img);
	cells[3] = new Cell(1, 1, img);
	this->shape = 'O';
}

Z::Z(Texture *img)
{
	cells[0] = new Cell(0, 0, img);
	cells[1] = new Cell(0, 1, img);
	cells[2] = new Cell(1, 1, img);
	cells[3] = new Cell(1, 2, img);
	this->shape = 'Z';
}

S::S(Texture *img)
{
	cells[0] = new Cell(1, 0, img);
	cells[1] = new Cell(1, 1, img);
	cells[2] = new Cell(0, 1, img);
	cells[3] = new Cell(0, 2, img);
	this->shape = 'S';
};

T::T(Texture *img)
{
	cells[0] = new Cell(0, 0, img);
	cells[1] = new Cell(0, 2, img);
	cells[2] = new Cell(0, 1, img);
	cells[3] = new Cell(1, 1, img);
	this->shape = 'T';
}

L::L(Texture *img)
{
	cells[0] = new Cell(0, 0, img);
	cells[1] = new Cell(1, 0, img);
	cells[2] = new Cell(1, 1, img);
	cells[3] = new Cell(1, 2, img);
	this->shape = 'L';
}
