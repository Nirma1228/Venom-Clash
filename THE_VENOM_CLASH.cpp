#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;

// Global Variables for Game sttings
bool Gameover;					//Gameover Flag
const int Width = 40;			// Width of the Game
const int Height = 20;			// Height of the Game
int fruitX, fruitY;				//Position of the Fruit
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN};	//Directions of the Snake
int winner = 0;  				// 0 means no winner yet, 1 means player 1 wins, 2 means player 2 wins
