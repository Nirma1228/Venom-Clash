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

// Draw the top wall
    for (int i = 0; i < Width + 2; i++) {
        cout << "#";
    }
    cout << endl;

// Draw the game field (sides and inside)
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width + 2; j++) {
            if (j == 0 || j == Width + 1) {
                cout << "#"; 				// Side walls
            } else if (i == Y1 && j == X1 + 1) {
                cout << "O"; 				// Player 1's head
            } else if (i == Y2 && j == X2 + 1) {
                cout << "X"; 				// Player 2's head
            } else if (i == fruitY && j == fruitX + 1) {
                cout << "F";				// Fruit
            } else {
                bool print = false;
                for (int k = 0; k < ntail1; k++) {
                    if (tailX1[k] == j - 1 && tailY1[k] == i) {
                        cout << "o"; 		// Player 1's tail
                        print = true;
                        break;
                    }
                }

for (int k = 0; k < ntail2 && !print; k++) {
                    if (tailX2[k] == j - 1 && tailY2[k] == i) {
                        cout << "x"; 		// Player 2's tail
                        print = true;
                        break;
                    }
                }
 if (!print) {
                    cout << " "; 			// Empty space
                }
            }
        }
        cout << endl;
    }

 // Draw the bottom wall
    for (int i = 0; i < Width + 2; i++) {
        cout << "#";
    }
    cout << endl;

// Display player names and scores
    cout << playerName1 << "'s Score: " << score1 << "\t\t" << playerName2 << "'s Score: " << score2 << endl;
}

/ Function to set up the initial state of the game
void IniSetup (){
	Gameover = false;					// Reset the game over flag
	Dir1 = STOP;						// Set initial direction to STOP for Player 1	
	X1 = Width /4;						// Set initial position for Player 1
	Y1 = Height / 4;
	fruitX = rand() % (Width - 2) + 1;	// Random position for the fruit
	fruitY = rand() % (Height - 2) + 1;
	score1 = 0;							// Set initial score for Player 1
	ntail1 = 0;							// Set initial tail length for Player 1
	
	X2 = (Width / 4) * 3;				// Set initial position for Player 2
	Y2 = (Height / 4) * 3;
	Dir2 = STOP;						// Set initial direction to STOP for Player 2
	ntail2 = 0;							// Set initial tail length for Player 2
	score2 = 0;							// Set initial score for Player 2

}

// Function to display Pause Message
void Pause() {
    // Clear the console screen
    system("cls");

// Display pause message
    cout << "\n\n\t<<<<< Game Paused >>>>>\n";
    cout << "\tPress 'P' to resume the game.";
}

// Function to handle player input
void Input (){
	
	if (_kbhit()){		// Check if a key is pressed
		switch(_getch()){
			
			case 'a':
				if (Dir1 != RIGHT)		// Ensure that the Player 1's snake not going on right to avoid going back in it's direction of coming
					Dir1 = LEFT;		// Player 1 moves left
				break;
			case 'd':
				if (Dir1 != LEFT)		// Ensure that the Player 1's snake not going on right to avoid going back in it's direction of coming
					Dir1 = RIGHT;		// Player 1 moves right
				break;
			case 'w':
				if (Dir1 != DOWN)		// Ensure that the Player 1's snake not going on right to avoid going back in it's direction of coming
					Dir1 = UP;			// Player 1 moves up
				break;
			case 's':
				if (Dir1 != UP)			// Ensure that the Player 1's snake not going on right to avoid going back in it's direction of coming
					Dir1 = DOWN;		// Player 1 moves down
				break;
				
			case 'j':
				if (Dir2 != RIGHT)		// Ensure that the Player 2's snake not going on right to avoid going back in it's direction of coming
                	Dir2 = LEFT;		// Player 2 moves left
                break;
            case 'l':
            	if (Dir2 != LEFT)		// Ensure that the Player 2's snake not going on right to avoid going back in it's direction of coming
                	Dir2 = RIGHT;		// Player 2 moves right
                break;
            case 'i':
            	if (Dir2 != DOWN)		// Ensure that the Player 2's snake not going on right to avoid going back in it's direction of coming
                	Dir2 = UP;			// Player 2 moves up
                break;
            case 'k':
            	if (Dir2 != UP)			// Ensure that the Player 2's snake not going on right to avoid going back in it's direction of coming
                	Dir2 = DOWN;		// Player 2 moves down
                break;	
            case 'p':
                paused = !paused;
                if (paused) {
                    Pause();  // Display pause message and clear the screen
                } else {
                    Draw();  // Redraw the game screen when resuming
                }
                break;
            case 'q':
                Gameover = true;
                winner = 0;
                break;
		}
	}
	
}

/ Function to implement game logic
void Logic (){
	
	// Logic for 1st Snake
	int PrevX = tailX1[0];		// Previous position of Player 1's first tail segment
	int PrevY = tailY1[0];
	int Prev2X, Prev2Y;
	tailX1[0] = X1;				// Update tail to follow the head
	tailY1[0] = Y1;
	
	for (int i=1; i < ntail1; i++){
		Prev2X = tailX1[i];
		Prev2Y = tailY1[i];
		tailX1[i] = PrevX;
		tailY1[i] = PrevY;
		PrevX = Prev2X;
		PrevY = Prev2Y;
	}

// Move Player 1 based on direction
	switch (Dir1){
		case LEFT:
		X1--;	
		break;
		case RIGHT:
		X1++;
		break;
		case UP:
		Y1--;
		break;
		case DOWN:
		Y1++;
		break;
		default:
		break;
	}

/*if (X1 > Width - 1 || X1 < 0 || Y1 > Height - 1 || Y1 < 0){
		Gameover = true;
	}*/

// Handle boundary wrapping for Player 1
	if (X1 >= Width){
		X1 = 0;
	}
	else if (X1 < 0){
		X1 = Width - 1;
	}
	if (Y1 >= Height){
		Y1 = 0;
	}
	else if (Y1 < 0){
		Y1 = Height - 1;
	}

// Check for collision with Player 1's tail
	for (int i=0; i < ntail1; i++){
		if (tailX1[i] == X1 && tailY1[i] == Y1){
			Gameover = true;
			winner = 2;
		}
	}

// Check for fruit collision for Player 1
	if (X1 == fruitX && Y1 == fruitY){
		ntail1++;
		score1 += 10;
    	fruitX = rand() % (Width - 2) + 1;
    	fruitY = rand() % (Height - 2) + 1;
	}
