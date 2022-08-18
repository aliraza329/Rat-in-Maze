#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;

void initGame();
void getUserName();
void printMenu();
void printGamestartmsg();
void printSelectLevelMsg();
void startGame(int size);
void prepareMaze(int size);
void printMaze(int size, bool hitHurdle);
void loadFileIntoMaze(int size);
void playGame(int size);
int getKeyPress();
void printWinMsg();
void printLoseMsg();
void saveScore();
void loadHighScore();
void printHighScore();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


// GLOBAL VARIABLES
int** maze;
int lives = 3;
int x_index = 0;
int y_index = 0;
int movesCount = 0;
string name;
string* highscoreTableName;
int* highscoreTableScore;
int highscoreCount = 1000;
int highscoreItr = 0;

int main()
{

	initGame();
	return 0;
}


void initGame() {

	lives = 3;
	x_index = 0;
	y_index = 0;
	movesCount = 0;

	char option = '0';

	printMenu();

	while (1) {

		cin >> option;

		if (option == '1') {
			getUserName();
			break;
		}

		if (option == '2') {

			loadHighScore();
			printHighScore();
			initGame();

			break;
		}

		if (option == '3') {
			break;
		}

		cout << "\nInvalid Option Provided\n";
	}
}

void getUserName() {

	cout << flush;
	system("CLS");

	cout << "Please enter your name: ";
	cin >> name;

	printGamestartmsg();
}


void printMenu()
{


	system("CLS");

	cout << "Please select an option: \n\n";

	cout << "Start New Game - Press 1" << endl;
	cout << "Show Highest Score Table - Press 2" << endl;
	cout << "Exit - Press 3" << endl;
}

void printGamestartmsg()
{

	printSelectLevelMsg();

}

void printSelectLevelMsg()
{


	system("CLS");

	cout << "Select Difficulty Level: \n\n";

	cout << "Easy - Press 1\n";
	cout << "Medium - Press 2\n";
	cout << "Hard - Press 3\n";

	char option = '0';

	while (1)
	{

		cin >> option;

		if (option == '1') {//4 x 4 Matrix
			startGame(4);
		}

		if (option == '2') {//6 x 6 Matrix
			startGame(6);
		}

		if (option == '3') {//8 x 8 Matrix
			startGame(8);
		}
	}
}

void startGame(int size) {

	prepareMaze(size);
	loadFileIntoMaze(size);
	printMaze(size, false);
	system("pause");
}

void prepareMaze(int size) {

	maze = new int* [size];
	for (int i = 0; i < size; i++) {
		maze[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			maze[i][j] = 0;
		}
	}
}

void printMaze(int size, bool hitHurdle) {


	system("CLS");

	cout << "Name: " << name << "\t\t" << "Score: " << movesCount << "\t" << "Lives: " << lives;

	cout << endl << endl;

	cout << "0 = BLOCKED\n1 = MOVABLE\n-2 = HURDLE\n\n";

	if (hitHurdle) {
		cout << "Oops! You hit a hurdle...!" << endl;
	}

	//	cout <<endl <<"Press \"p\" to pause the game";

	//	cout << endl<< "-"<< "-"<< "-"<< "-"<< "-"<< "-"<< "-"<< "-"<< endl;
	cout << endl;
	for (int i = 0; i <= size; i++) {
		cout << "-----";
	}
	cout << endl;

	for (int i = 0; i < size; i++) {
		cout << "|  ";
		for (int j = 0; j < size; j++) {

			if (i == y_index && j == x_index) {
				cout << "M";
			}
			else if (i == (size - 1) && j == (size - 1)) {
				cout << "D";
			}
			else {
				cout << maze[i][j];
			}
			if (maze[i][j] != -2) {
				cout << " ";
			}
			cout << " |  ";
		}
		cout << endl;
	}

	cout << endl;
	for (int i = 0; i <= size; i++) {
		cout << "-----";
	}
	cout << endl;
}

/* CONTINUE FROM HERE- THIS FUNCTION IS NOT WORKING PROPERLY */
void loadFileIntoMaze(int size)
{

	fstream myfile;

	if (size == 4)
	{//4 x 4
		myfile.open("fourbyfour.txt");
	}

	if (size == 6)
	{//6 x 6
		myfile.open("sixbysix.txt");
	}

	if (size == 8) {//8 x 8
		myfile.open("eightbyeight.txt");
	}
	string stream;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			//			getline(myfile,stream);//maze[i][j]);
			int temp;
			myfile >> temp;
			maze[i][j] = temp;
		}
	}


	playGame(size);
}


// Handle Rat Movement
void playGame(int size) {

	bool hitHurdle = false;

	int key = 0;
	int temp = 0;

	bool game_switch = true;
	bool win_switch = false;

	while (1 && game_switch && !win_switch) {

		printMaze(size, hitHurdle);
		hitHurdle = false;

		key = getKeyPress();

		switch (key) {
		case KEY_UP:
			// If rat is in top row, skip move UP
			if (y_index == 0) {
				continue;
			}

			temp = y_index - 1;

			//If route is blocked - Do nothing and -1 score
			if (maze[temp][x_index] == 0) {
				movesCount--;
				continue;
			}

			//Deduct Lives For Hitting Hurdle
			if (maze[temp][x_index] == -2) {

				lives--;
				movesCount -= 5;
				hitHurdle = true;

				if (lives == 0) {
					game_switch = false;
				}
				continue;
			}

			movesCount += 5;
			y_index = y_index - 1;

			//Win game script
			if (x_index == (size - 1) && y_index == (size - 1))
			{
				win_switch = true;
				continue;
			}

			break;
		case KEY_DOWN:
			// If mouse is in bottom most row, skip move Down
			if ((y_index + 1) == size) {
				continue;
			}

			temp = y_index + 1;

			//If route is blocked - Do nothing and -1 score
			if (maze[temp][x_index] == 0) {
				movesCount--;
				continue;
			}

			//Deduct Lives For Hitting Hurdle
			if (maze[temp][x_index] == -2) {

				lives--;
				movesCount -= 5;
				hitHurdle = true;

				if (lives == 0) {
					game_switch = false;
				}
				continue;
			}

			movesCount += 5;
			y_index = y_index + 1;

			//Win game script
			if (x_index == (size - 1) && y_index == (size - 1))
			{
				win_switch = true;
				continue;
			}

			break;
		case KEY_LEFT:
			// If mouse is in left most column, skip move left
			if (x_index == 0) {
				continue;
			}

			temp = x_index - 1;

			//If route is blocked - Do nothing and -1 score
			if (maze[y_index][temp] == 0) {
				movesCount--;
				continue;
			}

			//Deduct Lives For Hitting Hurdle
			if (maze[y_index][temp] == -2) {

				lives--;
				movesCount -= 5;
				hitHurdle = true;

				if (lives == 0) {
					game_switch = false;
				}
				continue;
			}

			movesCount += 5;
			x_index = x_index - 1;

			//Win game script
			if (x_index == (size - 1) && y_index == (size - 1))
			{
				win_switch = true;
				continue;
			}

			break;
		case KEY_RIGHT:
			// If mouse is in right most column, skip move right
			if (x_index == size) {
				continue;
			}

			temp = x_index + 1;

			//If route is blocked - Do nothing and -1 score
			if (maze[y_index][temp] == 0) {
				movesCount--;
				continue;
			}

			//Deduct Lives For Hitting Hurdle
			if (maze[y_index][temp] == -2) {

				lives--;
				movesCount -= 5;
				hitHurdle = true;

				if (lives == 0) {
					game_switch = false;
				}
				continue;
			}

			movesCount += 5;
			x_index = x_index + 1;

			//Win game script
			if (x_index == (size - 1) && y_index == (size - 1))
			{
				win_switch = true;
				continue;
			}

			break;
		default:
			continue;
		}//Switch End
	}//While End

	if (win_switch) {
		//Show win message
		printWinMsg();
		//Save score to file
		saveScore();
		//Restart Game
		initGame();
	}

	if (!game_switch) {
		printLoseMsg();
	}
}//Function End

int getKeyPress() {

	int c = 0;

	switch (c = _getch())
	{
	case KEY_UP:
		//	        cout << endl << "Up" << endl;//key up
		return KEY_UP;
		break;
	case KEY_DOWN:
		//	        cout << endl << "Down" << endl;   // key down
		return KEY_DOWN;
		break;
	case KEY_LEFT:
		//	        cout << endl << "Left" << endl;  // key left
		return KEY_LEFT;
		break;
	case KEY_RIGHT:
		//	        cout << endl << "Right" << endl;  // key right
		return KEY_RIGHT;
		break;
	default:
		//	        cout << endl << "null" << endl;  // not arrow
		return 0;
		break;
	}

}

//Print Win message
void printWinMsg() {


	system("CLS");

	cout << endl << "Congrats " << name << "!!! You won the game with a score of " << movesCount << endl;
	cout << endl << "Press 0 key to goto home screen...";

	_getch();

}

//Print Lose Message
void printLoseMsg() {

	cout << flush;
	system("CLS");

	cout << endl << "Sorry " << name << "!!! You lost. " << endl;
	cout << endl << "Press any key to goto home screen...";
	_getch();
	initGame();
}

void saveScore() {

	ofstream myfile;
	myfile.open("highscore.txt", ios_base::app);

	myfile << name << endl << movesCount << endl;
	myfile.close();


	ifstream myfile2("highscore.txt");

	string* tempName = new string[highscoreCount];
	int* tempScore = new int[highscoreCount];
	int itr = 0;

	while (!myfile2.eof()) {
		myfile2 >> tempName[itr];
		myfile2 >> tempScore[itr];
		itr++;
	}

	myfile2.close();

	for (int i = 0; i < itr - 1; i++) {
		for (int j = 0; j < itr - 1; j++) {

			if (tempScore[i] > tempScore[j]) {
				int swap = tempScore[i];
				tempScore[i] = tempScore[j];
				tempScore[j] = swap;

				string swapStr = tempName[i];
				tempName[i] = tempName[j];
				tempName[j] = swapStr;
			}
		}
	}

	ofstream myfile3;
	myfile3.open("Data/highscore.txt");

	for (int i = 0; i < itr - 1; i++) {
		myfile3 << tempName[i] << endl << tempScore[i] << endl;
	}
	myfile3.close();
}

void loadHighScore() {

	int itr = 0;

	highscoreTableName = new string[highscoreCount];
	highscoreTableScore = new int[highscoreCount];

	ifstream myfile("Data/highscore.txt");

	while (!myfile.eof()) {
		myfile >> highscoreTableName[itr];
		myfile >> highscoreTableScore[itr];
		itr++;
	}

	highscoreItr = itr;

	myfile.close();
}

void printHighScore() {

	cout << flush;
	system("CLS");

	cout << "High Scores" << endl << endl;

	cout << "Name \t Score" << endl;

	for (int i = 0; i < highscoreItr - 1; i++)
	{
		for (int j = 0; j < highscoreItr - 1; j++)
		{

			if (highscoreTableScore[i] > highscoreTableScore[j])
			{
				int swap = highscoreTableScore[i];
				highscoreTableScore[i] = highscoreTableScore[j];
				highscoreTableScore[j] = swap;

				string swapStr = highscoreTableName[i];
				highscoreTableName[i] = highscoreTableName[j];
				highscoreTableName[j] = swapStr;
			}
		}
	}


	for (int i = 0; i < highscoreItr - 1; i++) {
		cout << highscoreTableName[i] << "\t" << highscoreTableScore[i] << endl;
	}


	cout << endl << "Press any key to go back to homescreen..." << endl;

	delete[] highscoreTableName;
	delete[] highscoreTableScore;

	return;
}