#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

char name[40];
int score;
int difficulty;
int lives;
int x_pos;
int y_pos;
int maze[8][8];
int path[100];

void reamoveRecord(string file_name);
void saveExit(int path_size);
void generateMaze();
void startGame();
void displayMaze();
void playGame();

void reamoveRecord(string file_name)
{
	ofstream ofs;
	ofs.open(file_name, ofstream::out | ofstream::trunc);
	ofs.close();
}
void generateMaze()
{
	reamoveRecord("EasyLevelMaze.txt");
	reamoveRecord("MediumLevelMaze.txt");
	reamoveRecord("HardLevelMaze.txt");
	ofstream easy_file;
	ofstream medium_file;
	ofstream hard_file;
	easy_file.open("EasyLevelMaze.txt", fstream::in | fstream::out | fstream::app);
	medium_file.open("MediumLevelMaze.txt",  fstream::in | fstream::out |  fstream::app);
	hard_file.open("HardLevelMaze.txt",  fstream::in |  fstream::out |  fstream::app);

	easy_file << "M 1 1 0\n0 1 1 1\n0 -2 1 1\n0 0 0 1" << endl;

	medium_file << "M 1 1 0 1 0\n0 1 1 1 1 0\n0 -2 1 1 1 1\n0 0 0 1 1 1"
		<< "\n0 0 1 1 -2 0\n1 1 1 0 1 0" << endl;

	hard_file << "M 1 1 0 0 0 -2 -2\n0 1 1 1 0 0 1 0\n0 -2 1 1 1 1 0 -2\n0 0 0 1 1 1 1 0"
		<< "\n0 0 1 1 -2 0 1 1\n1 1 1 0 0 0 -2 1\n1 1 0 0 -2 0 1 1"
		<< "\n1 1 1 1 1 1 1 D" << endl;

}
void startGame() 
{
	cout << "\nEnter Your name: ";
	cin.ignore();
	cin >> name ;

	score = 0;
	cout << "\n\n1. Easy\n2. Medium\n3. Hard";
	cout << "\nSelect Difficulty: ";
	cin >> difficulty;
	lives = 3;
	x_pos = 0;
	y_pos = 0;
	displayMaze();
}

void displayMaze() 
{
	ifstream file;
	string numbers;
	string line;
	string file_name;
	int i = 0, j = 0;
	if (difficulty == 1)
		file_name = "EasyLevelMaze.txt";
	else if (difficulty == 2)
		file_name = "MediumLevelMaze.txt";
	else
		file_name = "HardLevelMaze.txt";
	file.open(file_name);
	if (file.fail())
	{
		cout << "\nFailed to display maze from file record!!";
		exit(1);
	}
	while (getline(file, line))
	{
		stringstream ss(line);
		j = 0;
		while (getline(ss, numbers, ' ')) 
		{
			if (!(i == 0 && j == 0 || i == j))
				maze[i][j] = stoi(numbers);
			j++;
		}
		i++;
	}
	playGame();
}
void playGame()
{
	int move = 0;
	int max;
	int path_size = 0;
	bool is_finish = false;
	bool is_block = false;
	if (difficulty == 1)
		max = 3;
	else if (difficulty == 2)
		max = 5;
	else
		max = 7;
	while (true) 
	{
		cout << "\n-------------------------------------------------------------------------------------";
		cout << "\nName: " << name << "\t\t" << "Score: " << score << "\t\tLives: " << lives;
		cout << "\n\n0: = BLOCKED\n1 = MOVEABLE\n-2 = HURDLE";
		cout << "\n\n";
		for (int i = 0; i <= max; i++) 
		{
			for (int j = 0; j <= max; j++)
			{
				if (i == 0 && j == 0)
					cout << "\tM" << "   |   ";
				else if (i == max && j == max)
					cout << "\tD" << "   |   ";
				else if (x_pos == i && y_pos == j)
					cout << "\tM" << "   |   ";
				else
					cout << "\t" << maze[i][j] << "   |   ";
			}
			cout << endl << endl;
		}
		cout << "\n\n1. left\n2. down\n3. right\n5. up\n0. Save & Back";
		cout << "\nEnter your move : ";
		cin >> move;
		if (move == 1) 
		{
			if ((y_pos - 1) >= 0) 
			{
				y_pos -= 1;
			}
			else
				is_block = true;
		}
		else if (move == 3)
		{
			if ((y_pos + 1) <= max) 
			{
				y_pos += 1;
			}
			else
				is_block = true;
		}
		else if (move == 5) 
		{
			if ((x_pos - 1) >= 0)
			{
				x_pos -= 1;
			}
			else
				is_block = true;
		}
		else if (move == 2) 
		{
			if ((x_pos + 1) <= max)
			{
				x_pos += 1;
			}
			else
				is_block = true;
		}
		else if (move == 0) 
		{
			goto save;
		}
		else 
		{
			cout << "\nInvalid move option selected....!!";
		}
		system("cls");
		if (is_block)
			cout << "\nNot possible move!!";

		is_block = false;
		if (maze[x_pos][y_pos] == -2)
		{
			lives -= 1;
			score -= 5;
		}
		else if (x_pos == max && y_pos == max) 
		{
			is_finish = true;
			score += 5;
		}
		else if (maze[x_pos][y_pos] == 0)
			score -= 1;
		if (is_finish)
		{
			cout << "\nYou won!!";
			goto save;
		}
		if (lives <= 0)
		{
			cout << "\nSorry!! you lose the game.";
			saveExit(path_size);
		}
		path[path_size] = move;
		path_size++;
	}
save:
	saveExit(path_size);
}
void saveExit(int path_size)
{
	fstream file;
	file.open("scores.txt", fstream ::in | fstream::out | fstream::app);
	file << score << endl;
	file.close();
	cout << "\nPlayer Game Path: \n";
	for (int i = 0; i < path_size; i++) 
	{
		if (path[i] == 1)
			cout << "left";
		else if (path[i] == 2)
			cout << "right";
		else if (path[i] == 3)
			cout << "up";
		else if (path[i] == 4)
			cout << "down";
		cout << "->";
	}
	cout << "\nYour score is updated into scores.txt file....!!";
	return;
}
void displayScores() 
{
	fstream file;
	file.open("scores.txt");
	string line;
	string numbers;
	int size = 0;
	int p[100];
	while (getline(file, line))
	{
		p[size] = stoi(line);
		size++;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (p[j] > p[i])
				swap(p[i], p[j]);
		}
	}
	cout << "\nTop Scores: \n\n";
	for (int i = 0; i < size; i++)
	{
		cout << "score: " << p[i] << endl;
	}
}
int main()
{
	int choice;
	generateMaze();
	while (true) 
	{
		cout << "\n1. Play Game\n2. Display Top Scores\n 0. Exit";
		cout << "\nEnter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			startGame();
			break;
		case 2:
			displayScores();
			break;
		case 0:
			exit(0);
		default:
			break;
		}
	}
	return 0;
}
