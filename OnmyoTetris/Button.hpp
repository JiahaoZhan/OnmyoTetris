#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include "Config.hpp"

using namespace sf; 
using namespace std;

class Button
{
public:
	Button();

	Button(string texturePath, string &text, Font& font, Color &color, int size, double x, double y);

	virtual~Button();

	void drawButton();

	virtual void press();

private:
	Sprite* pressed;
	Color* button_color; 
	Text * button_text;
};

#endif