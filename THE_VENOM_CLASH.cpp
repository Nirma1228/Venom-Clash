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

// Function to display the main menu
void MainMenu() {
    int choice;
    while (true) {
        system("cls");  // Clear the console
        cout << "=================================" << endl;
        cout << "=================================" << endl;
        cout << "======== THE VENOM CLASH ========" << endl;
        cout << "=================================" << endl;
        cout << "=================================" << endl;
        cout << "\t1. Play" << endl;
        cout << "\t2. Instructions" << endl;
        cout << "\t3. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;

if (choice == 1) {
            cout << endl;
            cout << "Enter Player 1's Name: ";
            cin >> playerName1;
            cout << endl;
            cout << "Enter Player 2's Name: ";
            cin >> playerName2;
            return;  // Start the game
        } else if (choice == 2) {
system("cls");
            cout << "INSTRUCTIONS:" << endl;
            cout << endl;
            cout << "01) It's a two players' Game which based on classical Snake Game" << endl;
            cout << endl;
            cout << "02) Player 1 (Snake denoted by O): W, A, S, D to move" << endl;
            cout << "\t W - Move Up \t A - Move Left \t S - Move Down \t D - Move Right" << endl;
            cout << endl;
            cout << "03) Player 2 (Snake denoted by X): I, J, K, L to move" << endl;
            cout << "\t I - Move Up \t J - Move Left \t K - Move Down \t L - Move Right" << endl;
            cout << endl;
            cout << "04) To Pause and Resume the game use key 'P'" << endl;
            cout << endl;
            cout << "05) To exit from the game use key 'Q'" << endl;
            cout << endl;
            cout << "06) Collect fruits(F) to grow" << endl;
            cout << endl;
            cout << "07) Avoid colliding with the other snake or yourself" << endl;
            cout << endl;
            cout << "08) If the head collides each other, the one with highest score wins, if both have same score it leads to Draw." << endl;
            cout << endl;
            cout << "09) Press any key to return to the main menu." << endl;
            _getch();  // Wait for user input to go back to the menu
        } else if (choice == 3) {
 exit(0);  // Exit the game
        } else {
            cout << "Invalid choice! Please try again." << endl;
            _getch();  // Wait for user input before showing the menu again
        }
    }
}

void Draw() {
    // Move the cursor to the top-left corner of the console
	gotoxy (0,0);
