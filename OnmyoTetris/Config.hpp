#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_
#include <string>

using namespace std;

//Width of the game field
const int WIDTH = 12;

//Height of the game field
const int HEIGHT = 20;

//The length of the array of images to be loaded
const int IMG_NUM = 9;

//The length of the array of the texts to be loaded
const int TEXT_NUM = 4;

//The time interval between each auto falling of a tetromino
const double DELAY = 6;

//Dimension of the img of the cell in pixels
const int cwidth = 26;
const int cheight = 26;

//Max FPS
const int MAX_FRAME_RATE = 60;

//Scaled window
const int swidth = 800;
const int sheight = 661;

//Grid dimension
const int gwidth = 312;
const int gheight = 520;

//Directories for loading resources
const string textureRes = "./Src/Texture";
const string soundRes = "./Src/Sound";
const string musicRes = "./Src/Music";
const string fontRes = "./Src/Font";

//Enum for representing the names of different types
const enum fileType{ texture, sound, music, font };

string mkDir(const string filename, fileType type);


#endif