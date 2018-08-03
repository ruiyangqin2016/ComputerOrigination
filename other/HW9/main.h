void drawBanana(void);
void drawEnemy(void);
void colMonLog(void);
void drawHeart(void);
void colMonBan(void);
void colMonGoal(void);
void gameover(void);
void gameover1(void);
void reset(void);

int gameon;


typedef struct
{
    int x;
    int y;
    int height;
    int width;
    int oldx;
    int oldy;
    int isbanana;
    int iscol;
}BANANAS;


typedef struct
{
    int x;
    int y;
    int height;
    int width;
    int oldx;
    int oldy;
    int isenemy;
}ENEMYS;

typedef struct
{
    int x;
    int y;
    int height;
    int width;
    int oldx;
    int oldy;
    int isplayer;
}PLAYER;

typedef struct
{
    int x;
    int y;
    int height;
    int width;
    int oldx;
    int oldy;
    int isheart;
}HEARTS;


typedef struct
{
    int x;
    int y;
    int height;
    int width;
    int oldx;
    int oldy;
    int isgoal;
}GOAL;


