#ifndef _TETROMINO_HPP_
#define _TETROMINO_HPP_

#include "Cell.hpp"

class Tetromino : public Cell
{

public:
	Tetromino();

	~Tetromino();

	//Rotate the tetromino
	bool rotate(Cell *field[HEIGHT][WIDTH]);
	
	//Move the tetromino 1 unit down
	bool moveDown(Cell *field[HEIGHT][WIDTH]);

	//Move the tetromino 1 unit left
	bool moveLeft(Cell *field[HEIGHT][WIDTH]);

	//Move the tetromino 1 unit right
	bool moveRight(Cell *field[HEIGHT][WIDTH]);

	typedef struct Point { int x; int y; };

	//Check if the tetromino can be moved 1 unit in the given direction dir
	bool canMove(char dir, Cell *field[HEIGHT][WIDTH]);

	//Check if the tetromino can be rotated
	bool canRotate(Cell *field[HEIGHT][WIDTH]);

	bool isSelfCell(Point points[], int x, int y);

	Point *initializePoint(Cell *cells[]);

public:
	Cell *cells[4];
	char shape;
};


class I : public Tetromino
{
public:
	I(Texture *img);
};

class J : public Tetromino
{
public:
	J(Texture *img);
};

class O : public Tetromino
{
public:
	O(Texture *img);
};

class Z : public Tetromino
{
public:
	Z(Texture *img);
};

class S : public Tetromino
{
public:
	S(Texture *img);
};

class T : public Tetromino
{
public:
	T(Texture *img);
};

class L : public Tetromino
{
public:
	L(Texture *img);
};

#endif