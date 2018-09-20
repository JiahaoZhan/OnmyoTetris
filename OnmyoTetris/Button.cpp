#include "Button.hpp"

Button::Button() = default;

Button::Button(string fileName, string& text, Font& font, Color& color, int size, double x, double y)
{
	Texture button_texture;
	button_texture.loadFromFile(mkDir(fileName, texture));
	this->pressed = new Sprite(button_texture);
	this->button_color = new Color(color);
	this->button_text = new Text(text, font, size);
	
}

Button::~Button()
{

}

void Button::drawButton()
{

}

void Button::press()
{

}
