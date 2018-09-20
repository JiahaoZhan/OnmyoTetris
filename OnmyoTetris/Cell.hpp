#ifndef _CELL_HPP_
#define _CELL_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Config.hpp"

using namespace std;
using namespace sf;


class Cell
{
public:
	Cell();
	Cell(int x, int y, Texture *img);
	~Cell();

	//Return the current x-coordinate of the cell in the game field
	int getX();

	//Return the current y-coordinate of the cell in the game field
	int getY();

	//Return the pointer of the texture of the cell
	Texture *getTexture();
	
	//Set the x-coordinate of the cell in the game field
	void setX(int x);

	//Set the y-coordinate of the cell in the game field
	void setY(int y);

	//Paint the cell in the game field
	void drawCell(RenderWindow *window, int x, int y);

	//Paint the cell in the waiting area
	void drawNextCell(RenderWindow *window, int x, int y);

	//Move the cell 1 unit to the right
	void moveRight();

	//Move the cell 1 unit to the left
	void moveLeft();

	//Move the cell 1 unit down
	void moveDown();

protected:
	int x, y;
	Sprite s;
};

#endif