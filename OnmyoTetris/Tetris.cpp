#include "gameFrame.hpp"

int main()
{
	GameFrame *frame = new GameFrame();
	frame->play();
	delete frame;
	return 0;
}