#include <graphics.h>

int const WIDTH = 400, HEIGHT = 330;
int const TextStartColor = COLOR(0, 0, 0);
int const TextStartUpColor = COLOR(255, 0, 0);
int const BackgroundColor = COLOR(0, 0, 0);

void StartUp()
{
    setfillstyle(1, BackgroundColor);
	settextjustify(1, 1);
	settextstyle(2, 0, 4);
	setcolor(2);
	outtextxy(350, 315, "Created by Parsa.zf");
	setcolor(TextStartUpColor);
	settextstyle(5, 0, 1);
	outtextxy(80, 160, "The Red");
	delay(500);
	settextstyle(4, 0, 5);
	outtextxy(120, 140, "S");
	delay(350);
	outtextxy(162, 140, "n");
	delay(350);
	outtextxy(201, 140, "a");
	delay(350);
	outtextxy(240, 140, "k");
	delay(350);
	outtextxy(279, 140, "e");
	setcolor(TextStartColor);

	while (!kbhit())
	{
		settextstyle(3, 0, 3);
		outtextxy(200, 215, "..: Start :..");
		settextstyle(8, 0, 1);
		outtextxy(200, 235, "Press any key");

		delay(400);
		bar(50, 180, 280, 300);

		if (kbhit()) break; // for more speed
		delay(450);
	}
}

int main(int argc, char const *argv[])
{
    HWND Handle = GetConsoleWindow();
	ShowWindow(Handle ,SW_HIDE);
    initwindow (WIDTH, HEIGHT, "Snake", 300, 300);

    // Start up window
    StartUp();

    return 0;
}
