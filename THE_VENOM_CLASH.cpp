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

// Player 1 (Snake 1) Variables
int X1, Y1;						//Position of the first snake's head
int tailX1[100];				// Position of the first snake's head
int tailY1[100];
int score1;						// Score of the first snake
int ntail1;						// Length of the first snake's tail`
Direction Dir1;				// Direction of the first snake

Player 2 (Snake 2) Variables
int X2, Y2;                   	// Position of the second snake's head
int tailX2[100];              	// Position of the second snake's tail
int tailY2[100];
int ntail2;                   	// Length of the second snake's tail
Direction Dir2;              	// Direction of the second snake
int score2;						// Score of the second snake

string playerName1, playerName2; // Both Player's Name
bool paused = false;

// Function to hide the console cursor
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false; // Hide the cursor
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// Function to set the console cursor position
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
