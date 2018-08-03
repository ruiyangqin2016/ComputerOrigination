#include "myLib.h"
#include "bg.h"
#include "monkey.h"
#include "monkeyW.h"
#include "banana.h"
#include "main.h"
#include <stdlib.h>
#include "enemyLog.h"
#include "heart.h"
#include "text.h"


BANANAS BAN[7];
ENEMYS ENEMY[7];
PLAYER pl;
HEARTS h2;
GOAL g;

int location;
int location2;


int main()
{

	REG_DISPCNT = MODE3 | BG2_ENABLE;

	pl.y = 80;
	pl.oldy = pl.y;
	pl.x = 0;

	h2.x = 2;
	h2.oldx = h2.x;
	h2.y = 0;

	g.x = 219;


	for(int i = 0; i < 7; i++)
	{
    BAN[i].isbanana = 0;
    ENEMY[i].isenemy = 0;
    }

	while(!KEY_DOWN_NOW(BUTTON_START))
	{
		drawImageSpray(0,0,160,240,bg);
	}
	drawRect(0,0,160,240,WHITE);


gameon = 1;
	while(1)
	{
        if(gameon == 1) {
        drawBanana();
        drawEnemy();
        drawHeart();
        drawImageSpray(0,219,20,20,monkeyW);
		drawHollowRect(0,0,20,239,RED);
		drawRect(pl.oldy,0,20,20,WHITE);
		drawImageSpray(pl.y,0,20,20,monkey);



		pl.oldy= pl.y;
		h2.oldx = h2.x;

		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			if(pl.y > 22)
			{
			pl.y = pl.y - 2;
			}
		}

		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			if(pl.y <= 138)
			{
			pl.y = pl.y + 2;
			}
		}

		if(h2.x <= 0)
		{
            gameon = 0;
            gameover();

		}

		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			reset();
		}

		//if(h2.x >= 219)
		//{
           // gameon = 0;
		//}



	waitForVblank();
	colMonLog();
	colMonBan();
	colMonGoal();
	}
if(KEY_DOWN_NOW(BUTTON_SELECT))
		{
			reset();
		}
	}

	
}

void drawBanana(void)
{
static int delaycounter = 0;



    for(int i = 0; i < 7; i++)
    {
        if(BAN[i].isbanana == 1)
        {
            drawRect(BAN[i].y , BAN[i].oldx, BANANA_HEIGHT, BANANA_WIDTH, WHITE);
            drawImageSpray(BAN[i].y , BAN[i].x, BANANA_HEIGHT, BANANA_WIDTH, banana);
            BAN[i].oldy = BAN[i].y;
            BAN[i].oldx = BAN[i].x;
            BAN[i].x -=3;
            if(BAN[i].x < 0)
            {
                BAN[i].isbanana = 0;
                drawRect(BAN[i].y , BAN[i].oldx, BANANA_HEIGHT, BANANA_WIDTH, WHITE);
            }
        }
        else
        {
            if(delaycounter == 0)
            {
                BAN[i].y = 21;
                BAN[i].isbanana = rand()%2;

                location = rand()%233;
                if (location > 20 && location < 140)
                {
                    BAN[i].y = location;
                }
                BAN[i].x = 230;
                BAN[i].oldx = BAN[i].x;
                BAN[i].oldy = BAN[i].y;
            }
        }
    }

    delaycounter++;
    if(delaycounter > 10)
    {
        delaycounter = 0;
    }


}




void drawEnemy(void)
{
static int delaycounter = 0;

    for(int i = 0; i < 7; i++)
    {
        if(ENEMY[i].isenemy == 1)
        {
            drawRect(ENEMY[i].y , ENEMY[i].oldx,ENEMYLOG_HEIGHT , ENEMYLOG_WIDTH, WHITE);
            drawImageSpray(ENEMY[i].y , ENEMY[i].x, ENEMYLOG_HEIGHT, ENEMYLOG_WIDTH, EnemyLog);
            ENEMY[i].oldy = ENEMY[i].y;
            ENEMY[i].oldx = ENEMY[i].x;
            ENEMY[i].x -=6;
            if(ENEMY[i].x < 0)
            {
                ENEMY[i].isenemy = 0;
                drawRect(ENEMY[i].y , ENEMY[i].oldx, 10, 10, WHITE);
            }
        }
        else
        {
            if(delaycounter == 0)
            {
                ENEMY[i].y = 21;
                ENEMY[i].isenemy = rand()%2;

                location2 = rand()%233;
                if (location2 > 20 && location2 < 140)
                {
                    ENEMY[i].y = location2;
                }
                ENEMY[i].x = 230;
                ENEMY[i].oldx = ENEMY[i].x;
                ENEMY[i].oldy = ENEMY[i].y;
            }
        }
    }


    delaycounter++;
    if(delaycounter > 10)
    {
        delaycounter = 0;
    }

}


void drawHeart(void)
{
    drawRect(0,h2.oldx,20,20,WHITE);
    drawImageSpray(0,h2.x,20,20,heart);

}



void colMonLog(void)
{
    int i;
    //int Log10, Log00, Log11, Log01, Mon10, Mon00, Mon11, Mon01;
    for(i = 0; i < 7; i++)
    {
        if(ENEMY[i].isenemy == 1)
        {
            int LogL = ENEMY[i].x;
            int LogT = ENEMY[i].y;
           // int LogR = ENEMY[i].x + ENEMYLOG_WIDTH;
            int LogB = ENEMY[i].y + ENEMYLOG_HEIGHT;
            //int log22 = Log00 + Log11;

            //int MonL = pl.x;
            int MonT = pl.y;
            int MonR = pl.x + MONKEY_WIDTH;
            int MonB = pl.y + MONKEY_HEIGHT;
           // int Mon22 = Mon10 + Mon11;

            //if(!(Mon00 < Log10 || Log00 < Mon10 || Mon22 < Log10 || log22 < Mon10))


            if (!(MonB < LogT || LogB < MonT || MonR < LogL))
        {
            //gameon = 0;

            h2.x = h2.x - 10;
            ENEMY[i].isenemy = 0;
            drawRect(ENEMY[i].y , ENEMY[i].x, ENEMYLOG_HEIGHT, ENEMYLOG_WIDTH + 7, WHITE);


        }
        }
    }
}


void colMonBan(void)
{
    int i;
    for(i = 0; i < 7; i++)
    {
        if(BAN[i].isbanana == 1)
        {
            int BanL = BAN[i].x;
            int BanT = BAN[i].y;
            int BanB = BAN[i].y + BANANA_HEIGHT;

            int MonT = pl.y;
            int MonR = pl.x + MONKEY_WIDTH;
            int MonB = pl.y + MONKEY_HEIGHT;

        if (!(MonB < BanT || BanB < MonT || MonR < BanL))
        {

            h2.x = h2.x + 10;
            BAN[i].isbanana = 0;
            drawRect(BAN[i].y , BAN[i].x, BANANA_HEIGHT, BANANA_WIDTH + 5, WHITE);


        }
        }
    }

}


void colMonGoal(void)
{
    int WL = g.x;
    int WT = g.y;
    int WB = g.y + MONKEYW_HEIGHT;

    int HT = h2.y;
    int HR = h2.x + HEART_WIDTH;
    int HB = h2.y + HEART_HEIGHT;


    if (!(HB < WT || WB < HT || HR < WL))
    {

        gameon = 0;
        gameover1();
}

}


void gameover(void)
{
						
    drawRect(0,0,160,240,WHITE);
    drawChar(70,80,71,BLACK);
    drawChar(70,88,65,BLACK);
    drawChar(70,96,77,BLACK);
    drawChar(70,104,69,BLACK);
    drawChar(70,112,79,BLACK);
    drawChar(70,120,86,BLACK);
    drawChar(70,128,69,BLACK);
    drawChar(70,136,82,BLACK);

}

void gameover1(void)
{

    drawRect(0,0,160,240,WHITE);
    drawImageSpray(60,65,20,20,monkey);
    drawImageSpray(60,115,20,20,heart);
    drawImageSpray(60,165,20,20,monkeyW);
}



void reset(void)
{
main();

}


