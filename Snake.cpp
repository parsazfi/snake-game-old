#include <graphics.h>
#include <conio.h>

int const WIDTH = 400, HEIGHT = 330;
int const PrizeColor = 12;
int const SnakeColor = COLOR(255, 0, 0);
int const TextStartColor = COLOR(255, 128, 128);
int const TextStartUpColor = COLOR(255, 0, 0);
int const BackgroundColor = COLOR(0, 0, 0);

int const speed = 220;
int const maxSpeed = 100;
int const MAX_SIZE = 1000;
int const LEN = 5;
int r = 5;
int len;
int dist = 2 * r;
int sX = dist; //LeftRight
int sY = 0; //UpDown

void StartUp()
{
    setfillstyle(1, BackgroundColor);
	settextjustify(1, 1);
	settextstyle(2, 0, 4);
	setcolor(2);
	outtextxy(350, 315, (char*)"Created by Parsa.zf");
	setcolor(TextStartUpColor);
	settextstyle(5, 0, 1);
	outtextxy(80, 160, (char*)"The Red");
	delay(500);
	settextstyle(4, 0, 5);
	outtextxy(120, 140, (char*)"S");
	delay(350);
	outtextxy(162, 140, (char*)"n");
	delay(350);
	outtextxy(201, 140, (char*)"a");
	delay(350);
	outtextxy(240, 140, (char*)"k");
	delay(350);
	outtextxy(279, 140, (char*)"e");
	delay(150);
	setcolor(TextStartColor);

	while (!kbhit())
	{
		settextstyle(3, 0, 3);
		outtextxy(200, 215, (char*)"..: Start :..");
		settextstyle(8, 0, 1);
		outtextxy(200, 235, (char*)"Press any key");
		delay(400);

		bar(50, 180, 280, 300);
		
		if (kbhit()) break; // for more speed
		delay(450);
	}
}

void SnakeMoving (int x[], int y[], char state = '0') // r: right, l: left, u: up, d: down, 0: nothing
{
	if (len == -1)
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
	}
	else
	{
		setfillstyle(1, 0);
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

		setfillstyle(1, SnakeColor);
		fillellipse(x[0], y[0] ,r ,r);
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

void Game ()
{
	setcolor(BackgroundColor);
	setfillstyle(1, BackgroundColor);
	bar(0, 0, WIDTH, HEIGHT);
	delay (1000);

	int key;

	int x [MAX_SIZE];
	int y [MAX_SIZE];
	
	int  _delay = speed;
	len = -1;

	bool isPlaying = true;
	while (isPlaying)
	{
		if (kbhit())
			ChangeDirection(key = getch());
		SnakeMoving(x, y);
		delay (_delay); 
	}
}

int main(int argc, char const *argv[])
{
    HWND Handle = GetConsoleWindow();
	ShowWindow(Handle ,SW_HIDE);
    initwindow (WIDTH, HEIGHT, "Snake", 300, 300);

    // Start up window
    StartUp();

	//Game
	Game();

    return 0;
}
