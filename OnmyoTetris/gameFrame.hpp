#ifndef _GAMEFRAME_
#define _GAMEFRAME_	

#include "Tetromino.hpp"
#include <time.h>
#include "include/SFML/Audio.hpp"
#include "include/SFML/Graphics.hpp"
#include <vector>


class GameFrame
{
	
public:
	GameFrame();

	GameFrame(double width, double height);
	
	//Initialze the game body and play
	void play();

	//Draw all of the graphical elements onto the window
	void drawWindow();

	//Clear any lines that are full
	void cancelLine();

	//Reset the game to its initial state
	void resetGame();

	//Clear the tetromino and to be redrew later
	void clearTetromino();

	//Clear the treromino in the waiting area
	void clearNextTetromino();

	//Place the tetromino into the playing field
	bool putTetromino(Cell *field[HEIGHT][WIDTH]);

	//Place the next tetromino into the waiting area
	void putNextTetromino(Cell *nextTetro[cheight][cwidth]);

	//Put a tetromino into the playing field
	bool putTetromino();

	//Put the next tetromino into the waiting area
	void putNextTetromino();

	//The control panel of the game
	void controlPanel(Event e);

	//Auto falling of the current tetrimino
	void autoFalling(int code);

	//Generate a random tetromino
	Tetromino *ranTetromino(int code);

	//Load the sound resource of the game 
	void loadSound();

	//Load the music resouce of the game 
	void loadMusic();

	//Load the text resource of the game
	void loadText();

	//Load the image resource of the game
	void loadImg();

private:
	//Check if the current row of the grid is empty
	bool isRowEmpty(int row);
	//Set the current row to be empty to clearing
	void setRowEmpty(int row);
	//Move the dstRow to srcRow 
	void copyRow(int dstRow, int srcRow);
	//Move down all of the levels by 1
	void moveDown(int row);
	

private:
	Cell *field[HEIGHT][WIDTH];
	Cell *nextTetro[cwidth][cheight];
	RenderWindow *window;

	Tetromino *currT;
	Tetromino *nextT;

	Clock *clock;

	SoundBuffer moveBuffer, hitBuffer, scoreBuffer;
	Sound  *moveAction, *hitCell, *getScore;
	Music *bgMusic;

	Font *textFont;
	Color *fontColor;
	Text *Title, *Level, *Pause, *Exit;

	Texture *fieldImg, *scrollImg, *grid, *bottom,
		*scoreBoard, *nextTetroFrame, *gameOver,
		*pauseText, *exit, *level, *Iimg, *Jimg, *Simg, *Zimg,
		*Limg, *Oimg, *Timg;
	
	vector <Sprite*>sprites;
	vector <Text*>texts;


	bool pause;
	float timeElapsed, timer;
};

#endif