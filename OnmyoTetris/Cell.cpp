#include "Cell.hpp"

Cell::Cell() = default;

Cell::Cell(int x, int y, Texture *img)
{
	this->x = x;
	this->y = y;
	this->s = Sprite(*img);
	this->s.setTextureRect(IntRect(0, 0, cwidth, cheight));
}

Cell::~Cell()
{
	cout << "Destruct x: " << x << " y: " << y << endl;
};

int Cell::getX() { return this->x; }

int Cell::getY() { return this->y; }

void Cell::setX(int x) { this->x = x; }

void Cell::setY(int y) { this->y = y; }

void Cell::drawCell(RenderWindow *window, int x, int y)
{
	this->s.setPosition(y * 26 + 442, x * 26 + 72);
	window->draw(this->s);
}

void Cell::drawNextCell(RenderWindow *window, int x, int y)
{
	this->s.setPosition(x * 26 + 130, y * 26 + 26 * 7);
	window->draw(this->s);
}

void Cell::moveRight() { this->x++; }
void Cell::moveLeft(){ this->x--; }
void Cell::moveDown(){ this->y++; }
