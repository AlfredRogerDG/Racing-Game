#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define ROAD_LEFT 180
#define ROAD_RIGHT 460 

//STRUCTURE TO MANAGE ENEMY CARS DYNAMICALLY
typedef struct {
	int x,y;
	int speed;
	int color;
}Enemy;

//FUNCTION TO DRAW A DETAILED CAR
void drawCar(int x, int y, int bodyColor) 
{
	//MAIN BODY
	setfillstyle(SOLID_FILL, bodyColor);
	bar(x, y, x+35, y+65);
	
	//WINDSHIELD
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	bar(x+5, y+15, x+30, y+25);
	
	//REARGLASS
	bar(x+5, y+50, x+30, y+55);
	
	//WHEELS
	setfillstyle(SOLID_FILL, BLACK);
	bar(x-6, y+8, x, y+20);
	bar(x+35, y+8, x+41, y+20);
	bar(x-6, y+45, x, y+57);
	bar(x+35, y+45, x+41, y+57);
}
//PAGE 1: MAIN TITLE SCREEN
void showTitleScreen() {
	cleardevice();
	
	//DECORATIVE OUTER BORDER
	setcolor(RED);
	setlinestyle(SOLID_LINE,1 ,3);
	rectangle(20, 20, SCREEN_WIDTH - 20,SCREEN_HEIGHT - 20);
	
	//MAIN TITLE
	setcolor(YELLOW);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
	outtextxy(140,150,(char*)"DG RACER");
	
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	outtextxy(210,220,(char*)"SWERVE WITH YOUR SKILLS!!!");
	
	//FLASHING PRESS ENTER PROMPT
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	int flash = 0;
	while (!kbhit()) 
	{
		if (flash %2 == 0)
		{
			setcolor(GREEN);
			outtextxy(180,360,(char*)"PRESS ENTER TO NEXT");
		}
		else
		{
			setcolor(BLACK);
			outtextxy(180,360,(char*)"PRESS ENTER TO NEXT");
		}
		delay(400);
		flash++;
	}
	getch();
}

void showInstructionPage() 
{
	cleardevice();
	
	setcolor(BLUE);
	setlinestyle(SOLID_LINE, 1, 3);
	rectangle(20, 20, SCREEN_WIDTH - 20, SCREEN_HEIGHT -20);
	
	setcolor(YELLOW);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR, 4);
	outtextxy(180,50,(char*)"HOW TO PLAY");
	
	setcolor(LIGHTGRAY);
	rectangle(80,120,SCREEN_WIDTH - 80, 340);
	
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT,HORIZ_DIR, 1);
	
	outtextxy(120,150,(char*)"-> Use LEFT Arrow or 'A' key to move Left.");
	outtextxy(120,180,(char*)"-> Use RIGHT Arrow or 'D' key to move Right.");
	
	outtextxy(120,220,(char*)"-> Avoid incoming BLUE and GREEN enemy cars.");
	outtextxy(120,250,(char*)"-> Every car passed gives you +10 points.");
	outtextxy(120,280,(char*)"-> Difficulty increases every 50 points!");
	outtextxy(120,310,(char*)"-> Press ESC key anytime during gameplay to Exit.");
	
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	int flash = 0;
	while(!kbhit())
	{
		if (flash % 2 == 0)
		{
			setcolor(GREEN);
			outtextxy(160,380,(char*)"PRESS ENTER TO START");
		}
		else
		{
			setcolor(BLACK);
			outtextxy(169,380,(char*)"PRESS ENTER TO START");
		}
		delay(400);
		flash++;
	}
	getch();
}

int main()
{
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	
	int playerX, playerY;
	Enemy enemies[2];
	int roadLineY = 0;
	int score = 0;
	int level = 1;
	int baseSpeed = 8;
	int page = 0;
	char textBuff[50];
	
	srand(time(0));
	
	showTitleScreen();
	showInstructionPage();
	
	restart:
	playerX = 300;
	playerY = 380;
	score = 0;
	level = 1;
	baseSpeed = 8;
	page = 0;
	
	enemies[0].x = ROAD_LEFT + 20 + rand() % 100;
	enemies[0].y = -100;
	enemies[0].speed = baseSpeed;
	enemies[0].color = BLUE;
	
	enemies[1].x = ROAD_LEFT + 140 + rand() % 100;
	enemies[1].y = -350;
	enemies[1].speed = baseSpeed + 2;
	enemies[1].color = LIGHTGREEN;
	
	while (1)
	{
		setactivepage(page);
		cleardevice();
		
		setfillstyle(SOLID_FILL, GREEN);
		bar(0,0 ,ROAD_LEFT, SCREEN_HEIGHT);
		bar(ROAD_RIGHT, 0,SCREEN_WIDTH, SCREEN_HEIGHT);
		
		setfillstyle(SOLID_FILL, DARKGRAY);
		bar(ROAD_LEFT, 0,ROAD_RIGHT, SCREEN_HEIGHT);
		
		setcolor(WHITE);
		setlinestyle(SOLID_LINE, 1, 3);
		line(ROAD_LEFT, 0,ROAD_LEFT, SCREEN_HEIGHT);
		line(ROAD_RIGHT, 0,ROAD_RIGHT, SCREEN_HEIGHT);
		
		setlinestyle(DASHED_LINE, 1, 3);
		for (int i = -40; i< SCREEN_HEIGHT; i += 80)
		{
			line((ROAD_LEFT + ROAD_RIGHT) / 2, i + roadLineY, (ROAD_LEFT + ROAD_RIGHT)/2, i+40+roadLineY);
		}
		roadLineY += baseSpeed;
		if (roadLineY >= 80) roadLineY = 0;
		
		//4.DRAW PLAYER AND ACTIVE ENEMY BLOCKS
		drawCar(playerX,playerY,RED);
		for (int i=0; i<2; i++) 
		{
			drawCar(enemies[i].x,enemies[i].y,enemies[i].color);
		}
		
		//5.SIDEBAR DASHBOARDS UI
		setfillstyle(SOLID_FILL, BLACK);
		bar(0, 0, ROAD_LEFT - 10,120);
		setcolor(YELLOW);
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		sprintf(textBuff, "SCORE; %d", score);
		outtextxy(15,20,textBuff);
		sprintf(textBuff, "LEVEL: %d", level);
		outtextxy(15, 80,(char*)"ESC: Quit");
		
		//6.SPEED & OBJECT LOGIC
		for (int i = 0; i<2 ; i++)
		{
			enemies[i].y += enemies[i].speed;
			
			if (enemies[i].y > SCREEN_HEIGHT)
			{
				enemies[i].y = -100;
				if(i == 0)
				{
					enemies[i].x = ROAD_LEFT + 15 + rand() % 110;
				}
				else
				{
					enemies[i].x = ROAD_LEFT + 135 + rand() % 110;
				}
				
				score += 10;
				
				//TRACK PACING INCREMENTS
				if (score > 0 && score % 50 == 0) 
				{
					level++;
					baseSpeed += 2;
				}
				enemies[i].speed = baseSpeed + (rand()%4);
			}
		}
		//7.CHECK CONTROLLER INPUTS
		if (kbhit()) 
		{
			char ch = getch();
			if (ch == 27)break;
			
			if (ch == 0 || ch == 224)
			{
				ch = getch();//CAPTURE ACTUAL DIRECTION ARROW VALUE
			}
			if (ch == 75 || ch == 'a' || ch == 'A')
{
    if (playerX > ROAD_LEFT + 5)
        playerX -= 20;
}

if (ch == 77 || ch == 'd' || ch == 'D')
{
    if (playerX < ROAD_RIGHT - 45)
        playerX += 20;
}
		}
		//8.OVERLAP CRASH BOUNDARIES CHECK
		int gameOver = 0;
		for (int i = 0; i < 2; i++)
		{
			if ((playerX < enemies[i].x + 35 && playerX + 35 > enemies[i].x) &&
			(playerY < enemies[i].y + 65 && playerY + 65 > enemies[i].y)){
			    	gameOver = 1;
			}
		}
		
		//FLIP ACTIVE DOUBLE-BUFFERED PAGE
		setvisualpage(page);
		page = 1 - page;
		
		delay(30);
		
		//9.CRASH HANDLING SEQUENCE INTERCEPT
		if (gameOver) 
		{
			setactivepage(page);
			cleardevice();
			setfillstyle(SOLID_FILL, BLACK);
			bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			
			setcolor(RED);
			settextstyle(TRIPLEX_FONT, HORIZ_DIR,4);
			outtextxy(180, 160, (char*)"GAME OVER");
			
			setcolor(WHITE);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
			sprintf(textBuff, "Final Score: %d",score);
			outtextxy(220, 230, textBuff);

			setcolor(YELLOW);
			outtextxy(130, 300, (char*)"Press 'R' to Restart");
			outtextxy(130, 330, (char*)"Press 'ESC' to Exit");
			setvisualpage(page);
			
			while(1)
			{
				char choice = getch();
				if (choice == 'r' || choice == 'R')
				{
					goto restart;
				}
				if (choice == 27) 
				{
					closegraph();
					return 0;
				}
			}
		}
	}
	
	closegraph();
	return 0;
}
