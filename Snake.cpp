/*
Name Snake Game 
Author: Parsazfi
Year: 2023
*/

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

// You can change the value of these variables
int const WIDTH = 400, HEIGHT = 330;
int const PrizeColor = 10;
int const SnakeColor = COLOR(255, 0, 0);
int const TextStartColor = COLOR(255, 128, 128);
int const TextStartUpColor = COLOR(255, 0, 0);
int const TextStyle1Color = COLOR(255, 0, 0);
int const TextStyle2Color = COLOR(0, 0, 0);
int const BackgroundColor = COLOR(35, 35, 35);
int const PanelColor = COLOR(255, 128, 128);;

int const PrizeLine = 22;
int const firstSpeed = 160;
int const maxSpeed = 40;
int const speedRate = 5;
int const prizeRate = 20;
int const MAX_SIZE = 1000;
int const LEN = 5;
int score;
int highScore;
int r = 5;

// I recommend you to not change these varibales (unless you know what you doing!)
int len;
int dist = 2 * r;
int sX = dist; // Left and Right
int prizeX = -1, prizeY = -1;
int sY = 0; // Up and Down
int _delay;
bool isPlaying;
bool isRunning = true;

void StartUp()
{
	setfillstyle(1, BackgroundColor);
	setbkcolor(BackgroundColor);
	bar(0, 0, WIDTH, HEIGHT);
	settextjustify(1, 1);
	settextstyle(2, 0, 4);
	setcolor(2);
	outtextxy(WIDTH - 50, HEIGHT - 15, (char*)"Created by Parsa.zf");
	setcolor(TextStartUpColor);
	settextstyle(5, 0, 1);
	outtextxy(80, HEIGHT / 2, (char*)"The Red");
	delay(500);
	settextstyle(4, 0, 5);
	outtextxy(WIDTH / 2 - 82, HEIGHT / 2 - 25, (char*)"S");
	delay(350);
	outtextxy(WIDTH / 2 - 40, HEIGHT / 2 - 25, (char*)"n");
	delay(350);
	outtextxy(WIDTH / 2 - 0,  HEIGHT / 2 - 25, (char*)"a");
	delay(350);
	outtextxy(WIDTH / 2 + 40, HEIGHT / 2 - 25, (char*)"k");
	delay(350);
	outtextxy(WIDTH / 2 + 80, HEIGHT / 2 - 25, (char*)"e");
	delay(150);
	setcolor(TextStartColor);

	while (!kbhit())
	{
		//215
		settextstyle(3, 0, 3);
		outtextxy(WIDTH / 2, HEIGHT / 1.53, (char*)"..: Start :..");
		settextstyle(8, 0, 1);
		outtextxy(WIDTH / 2, HEIGHT / 1.53 + 20, (char*)"Press any key");
		delay(400);

		bar(WIDTH / 2 - 100, HEIGHT / 1.53 - 20, WIDTH / 2 + 100, HEIGHT / 1.53 + 50);
		
		if (kbhit()) break; // for more speed
		delay(450);
	}
}

char* Score()
{
	string s = to_string(score);
	return strcpy (new char[s.length() + 1], s.c_str());
}

void UpdateScore(int value = 0)
{
	setcolor(TextStyle1Color);

	score += value;
	settextstyle(9, 0, 1);	
	outtextxy(200, 17, Score());
	
	setcolor (BackgroundColor);
}

void GeneratePrize()
{
	prizeX = ((rand() % 36) + 2) * 10;
	prizeY = ((rand() % 26) + 5) * 10;

	setfillstyle(9, PrizeColor);
	fillellipse(prizeX, prizeY , r+1, r+1);
}

void CheckPrize(int x, int y)
{
	if ((x == prizeX) && (y == prizeY))
	{
		len++;
		if (_delay > maxSpeed) _delay -= speedRate;
		setfillstyle(9, BackgroundColor);
		fillellipse(prizeX, prizeY , r+1, r+1);
		GeneratePrize();

		UpdateScore(prizeRate);
	}
}

int LoadData()
{
	fstream file;
    file.open("data.txt", ios::in);
	if (!file) {
		file.close();
		return 0;
	}
	else
	{
		string value = "";
		char ch;

		while (1) {
			file >> ch;
			if (file.eof())
				break;
			value += ch;
		}
		file.close();

		for (int i = 0; i < value.length(); i++)
			if (!isdigit(value[i]))
				return 0;
		
		highScore = stoi(value);
		return highScore;
	}
}

void SaveData(int value)
{
	fstream file;
    file.open("data.txt", ios::out);
    file << value;
    file.close();
}

void GameOver (int x[], int y[])
{
	bool flag = false;
	for (int i = 0; i < 8; i++)
	{
		if (flag) setfillstyle(1, SnakeColor);
		else setfillstyle(1, BackgroundColor);

		for (int j = 0; j < len; j++)
			fillellipse(x[j], y[j] ,r ,r);

		flag = !flag;
		delay (300);
	}

	delay (300);
	setfillstyle(1, PanelColor);
	bar (WIDTH / 2 - 135, HEIGHT / 2 - 75, WIDTH / 2 + 135, HEIGHT / 2 + 75);

	setfillstyle(1, BackgroundColor);
	setlinestyle(0,0,0);
	rectangle (WIDTH / 2 - 130, HEIGHT / 2 - 70, WIDTH / 2 + 130, HEIGHT / 2 + 70);

	delay (500);
	setbkcolor(PanelColor);
	setcolor(TextStyle2Color);
	settextstyle(10, 0, 5);
	
	if (score > highScore)
	{
		highScore = score;
		SaveData(highScore);
	}
	
	outtextxy(WIDTH / 2, HEIGHT / 2 - 20, (char*)"Game Over");
	settextstyle(8, 0, 1);
	string message = "Highscore: " + to_string(highScore);
	char * m = new char [message.length() + 1];
	settextstyle(8, 0, 2);
	outtextxy(WIDTH / 2, HEIGHT / 2 + 15, strcpy(m, message.c_str()));
	settextstyle(8, 0, 1);
	outtextxy(WIDTH / 2, HEIGHT / 2 + 45, (char*)"Press R to reset");
}

void CheckBite (int x[], int y[])
{
	for (int i = 1; i < len; i++)
	{
		if ((x[i] == x[0]) && (y[i] == y[0]))
		{
			isPlaying = false;
			GameOver(x, y);
			while (true)
			{
				if (kbhit())
				{
					int code = getch();
					if (code == 'r')
					{
						break;
					}
					else if (code == 27)
					{
						isRunning = false;
						break;
					}
				}
			}
			break;
		}
	}
}

void SnakeMoving (int x[], int y[])
{
	if (len == -1) // Run in first time
	{
		len = LEN;

		x[0] = 200;
		y[0] = 200;
		
		setfillstyle(1, SnakeColor);
		fillellipse(x[0], y[0], r, r);

		for (int i = 1; i < len; i++)
		{		
			x[i] = x[i-1] - sX;
			y[i] = y[i-1] - sY;
			fillellipse(x[i], y[i] ,r ,r);
		}

		GeneratePrize();
	}
	else // run after first time
	{
		setfillstyle(1, BackgroundColor);
		fillellipse(x[len-1], y[len-1] ,r ,r);
		for (int i = len - 1; i > 0; i--)
		{		
			x[i] = x[i-1];
			y[i] = y[i-1];
		}
		x[0] += sX;
		y[0] += sY;

		if (x[0] < 10) x[0] = WIDTH - 10;
		else if (x[0] > WIDTH - 10) x[0] = 10;
		
		if (y[0] < 30) y[0] = HEIGHT - 10;
		else if (y[0] > HEIGHT - 10) y[0] = 30;

		CheckPrize(x[0], y[0]);

		setfillstyle(1, SnakeColor);
		fillellipse(x[0], y[0] ,r ,r);

		CheckBite(x, y);
	}

}

void ChangeDirection(int code)
{
	if (code == 77)
	{
		if (sX != -2*r)
			sX = 2*r;
		sY = 0;
	}
	else if (code == 75)
	{
		if (sX != 2*r)
			sX = -2*r;
		sY = 0;
	}
	else if (code == 80)
	{
		if (sY != -2*r)
			sY = 2*r;
		sX = 0;
	}
	else if (code == 72)
	{
		if (sY != 2*r)
			sY = -2*r;
		sX = 0;
	}
}

void Pause(int x[], int y[])
{
	setfillstyle(1, PanelColor);
	setlinestyle(0,0,0);
	bar (WIDTH / 2 - 135, HEIGHT / 2 - 75, WIDTH / 2 + 135, HEIGHT / 2 + 75);
	setfillstyle(1, BackgroundColor);
	rectangle (WIDTH / 2 - 130, HEIGHT / 2 - 70, WIDTH / 2 + 130, HEIGHT / 2 + 70);
	setbkcolor(PanelColor);
	setcolor(TextStyle2Color);
	settextstyle(10, 0, 5);
	outtextxy(WIDTH / 2, HEIGHT / 2, (char*)"Pause");
	settextstyle(3, 0, 1);
	outtextxy(WIDTH / 2, HEIGHT / 2 + 30, (char*)"Press any key to resume");

	getch();

	setbkcolor(BackgroundColor);
	setcolor (BackgroundColor);
	setfillstyle(1, BackgroundColor);
	bar(0, PrizeLine + 1, WIDTH, HEIGHT);
	
	setfillstyle(1, SnakeColor);
	for (int i = 0; i < len; i++)
		fillellipse(x[i], y[i] ,r ,r);

	setfillstyle(9, PrizeColor);
	fillellipse(prizeX, prizeY , r+1, r+1);
}

void Game ()
{
	while (isRunning)
	{
		setbkcolor (BackgroundColor);
		setfillstyle(1, BackgroundColor);
		bar(0, 0, WIDTH, HEIGHT);
		
		delay (1000);

		setcolor(TextStyle1Color);
		setlinestyle(1,0,0);
		line(0, PrizeLine, WIDTH, PrizeLine);
		score = 0;

		UpdateScore();

		int key;

		int x [MAX_SIZE] = {MAX_SIZE};
		int y [MAX_SIZE] = {MAX_SIZE};
		
		_delay = firstSpeed;
		len = -1;

		isPlaying = true;
		while (isPlaying)
		{
			if (kbhit())
				switch (key = getch())
				{
					case 'p':
						Pause(x, y);
						break;
						
					default:
						ChangeDirection(key);
						break;
				}

			SnakeMoving(x, y);
			delay (_delay); 
		}
	}
	
}

int main(int argc, char const *argv[])
{
    HWND Handle = GetConsoleWindow();
	ShowWindow(Handle ,SW_HIDE);
    initwindow (WIDTH, HEIGHT, "Snake", 300, 300);
	highScore = LoadData();

    // Start up window
    StartUp();

	// Run the game
	Game();

    return 0;
}
