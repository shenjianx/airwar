﻿#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string>
//#include<mmsystem.h>
//#pragma comment(lib,"WINMM.lib")
using namespace std;

//宏定义
#define MAXSTAR					300	// 星星总数
#define NUM						140
#define SWIDTH					1080
#define SHEIGTHT				640
#define PLANE_H					70
#define PLANE_W					70
#define ENEMY_H					40
#define ENEMY_W					40
#define BULLET_H				15
#define BULLET_W				15
#define PLANESPEED				18

//全局变量声明
typedef struct object {
	int x, y;
	int type;
}object;

struct STAR
{
	double	x;
	int		y;
	double	step;
	int		color;
};
STAR star[MAXSTAR];

int score;
int speed;
IMAGE img[11];
char p[15];

//函数声明
int menu();
void draw();
void ifsave();
bool ifrestart();
void readrank();
void load();
void InitStar(int);
void MoveStar(int);
char *numtostr(int);

//Game类
class Game
{
public:

	object players[NUM];			//player  bullets  enemys  ...    helps
	int NumberOfEnemy;				//敌人数目
	int NumberOfBullet;				//子弹数目
	int NumberOfHelp;				//医疗包数目

	//函数声明
	void initplane();
	void initenemy();
	void initbullet();
	void inithelp();

	void move_plane(char);
	void move_plane(int);
	void move_enemy();
	void move_bullet();
	void move_help();


	void drawall();

	void init();
	void pause();
	void playing();
	void endgame();
	void printhelp();

	bool judge(object,object);

	void shoot();
};

//函数定义
void Game::playing()
{
	bool death = 1;						//标记死亡	1 存活	2 死亡
	int bullet_speed = 1;				//子弹速度
	int enemy_speed = 2;				//敌人速度
	int help_speed = 2;					//医疗包速度
	int bullet = 0;						//要发出的子弹数目
	int bulletrate = 30;				//子弹频率
	int countrate = 0;
	int drawrate = 80;
	int count_bullet = 0;
	int count_enemy = 0;
	int count_draw = 0;
	int count_help = 0;
	while (death)
	{
		//player move							///////////////////////////////////////player_move
		if (_kbhit()) 
		{
			char x = _getch();
			switch (x)
			{
			case 'w':
			case 's':
			case 'a':
			case 'd':
				move_plane(x); break;
			case 72:
			case 80:
			case 75:
			case 77:
				move_plane((int)x); break;
			case ' ':
				bullet++;
				break;
			case 27:
				printhelp();
				pause();
			default:break;
			}
		//	pause();
		}
		//enemy move							///////////////////////////////////////enemy_move
		if (count_enemy == enemy_speed)
		{
			count_enemy = 0;
			move_enemy();
			for (int i = NumberOfBullet + 1; i <= NumberOfBullet + NumberOfEnemy; i++)
			{
				if (players[i].x == -1 && players[i].y == -1)
				{
					continue;
				}
				if (judge(players[i], players[0]))
				{/*
					players[0].x = -1;
					players[0].y = -1;*/
					players[i].x = -1;
					players[i].y = -1;
					players[0].type -= 40;
				}
			}
		}
		count_enemy++;
		//help move								///////////////////////////////////////help_move
		if (count_help == help_speed)
		{
			count_help = 0;
			move_help();
			for (int i = NUM - 1; i >= NUM - NumberOfHelp; i--)
			{
				if (players[i].x == -1 && players[i].y == -1)
				{
					continue;
				}
				if (judge(players[i], players[0]))
				{/*
					players[0].x = -1;
					players[0].y = -1;*/
					players[i].x = -1;
					players[i].y = -1;
					players[0].type += 40;
				}
			}
		}
		count_help++;
		//bullet move							///////////////////////////////////////bullet_move
		if (bullet > 2)
		{
			bullet = 1;
		}
		if (bullet > 0)
		{
			if (countrate == bulletrate)
			{
				shoot();
				bullet--;
				countrate = 0;
			}
			countrate++;
		}
		else
		{
			countrate = 0;
		}
		if (count_bullet == bullet_speed)
		{
			count_bullet = 0;
			move_bullet();
			for (int i = 1; i <= NumberOfBullet; i++)
			{
				if (players[i].x == -1 && players[i].y == -1)
				{
					continue;
				}
				for (int j = NumberOfBullet + 1; j <= NumberOfBullet + NumberOfEnemy; j++)
				{
					if (players[j].x == -1 && players[j].y == -1)
					{
						continue;
					}
					//printf("in playing %d", players[i].type);
					if (judge(players[j], players[i]))
					{
						players[j].x = -1;
						players[j].y = -1;
						players[i].x = -1;
						players[i].y = -1;
						score += 20;
					}
				}
				for (int j = NUM - 1; j >=NUM - NumberOfHelp; j--)
				{
					if (players[j].x == -1 && players[j].y == -1)
					{
						continue;
					}
					//printf("in playing %d", players[j].type);
					if (judge(players[j], players[i]))
					{
						players[j].x = -1;
						players[j].y = -1;
						players[i].x = -1;
						players[i].y = -1;
						score += 120;
					}
				}
			}
		}
		count_bullet++;
		/*
		if (count_draw == drawrate)
		{
			count_draw = 0;
			drawall();
		}
		count_draw++;
		*/
		if (players[0].type <= 0)
		{
			death = 0;
		}
		//draw									///////////////////////////////////////draw
		drawall();
		Sleep(1);
	}


}

void Game::drawall()
{
	cleardevice();
	BeginBatchDraw();
	//draw stars
	/*
	static int countstar = 0;
	int starrate = 15;
	if (countstar == starrate)
	{
		static int k = 0;
		printf("%d\n",k++);
		for (int i = 0; i < MAXSTAR; i++)
			MoveStar(i);
		countstar = 0;
	}
	else
	{
		for (int i = 0; i < MAXSTAR; i++)
			putpixel((int)star[i].x, star[i].y, star[i].color);
	}
	countstar++;

	*/
	for (int i = 0; i < MAXSTAR; i++)
		MoveStar(i);
	//draw enemy
	for (int i = NumberOfBullet + 1; i <= NumberOfBullet + NumberOfEnemy; i++)
	{
		if (players[i].x != -1 && players[i].y != -1)
		{
			putimage(players[i].x, players[i].y, &img[4], SRCAND);
			putimage(players[i].x, players[i].y, &img[3], SRCPAINT);
		}
	}
	//draw help

	for (int i = NUM - 1; i >= NUM - NumberOfHelp; i--)
	{
		if (players[i].x != -1 && players[i].y != -1)
		{
			putimage(players[i].x, players[i].y, &img[10], SRCAND);
			putimage(players[i].x, players[i].y, &img[9], SRCPAINT);
		}
	}

	//draw player
	if (players[0].type >= 0)
	{
		putimage(players[0].x, players[0].y, &img[2], SRCAND);
		putimage(players[0].x, players[0].y, &img[1], SRCPAINT);
	}
	//draw bullet
	for (int i = 1; i <= NumberOfBullet; i++)
	{
		if (players[i].x != -1 && players[i].y != -1 && players[0].type > 0)
		{
			putimage(players[i].x, players[i].y, &img[6], SRCAND);
			putimage(players[i].x, players[i].y, &img[5], SRCPAINT);
		}
	}
	//draw score
	RECT r[5] = { {60,0,120,30} ,{120,0,180,30},{200,0,260,30}, {260,0,320,30}, {720,0,1080,30} };
	char *s;
	char *life;
	if (players[0].type > 0)
	{
		life = numtostr(players[0].type);
		drawtext(_T("HP:"), &r[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T(life), &r[3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		drawtext(_T("HP:"), &r[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T(" 0 "), &r[3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	s = numtostr(score);
	drawtext(_T("得分:"), &r[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T(s), &r[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("按ESC以暂停/获得帮助"), &r[4], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	EndBatchDraw();
}

void Game::init()
{
	int i;
	//初始化星星
	for (i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % SWIDTH;
	}
	//游戏初始化数据
	NumberOfEnemy = 7;
	NumberOfBullet = 25;
	NumberOfHelp = 1;
	score = 0;
	initplane();
	initbullet();
	initenemy();
	inithelp();
}

void Game::initplane()
{
	//player	0
	players[0].x = 0 + 20;
	players[0].y = SHEIGTHT / 2;
	players[0].type = 100;
}

void Game::initenemy()
{
	int i;
	//enemy		2
	for (i = NumberOfBullet + 1; i <= NumberOfBullet + NumberOfEnemy; i++) {
		players[i].x = rand()%400+SWIDTH;
		players[i].y = rand()%(SHEIGTHT - ENEMY_H);
		printf("%d\n", players[i].y);
		players[i].type = 2;
	}
}

void Game::inithelp()
{
	int i;
	//help		3
	for (i = NUM - 1; i >= NUM -NumberOfHelp; i--) {
		players[i].x = rand() % 400 + SWIDTH;
		players[i].y = rand() % (SHEIGTHT - ENEMY_H);
		printf("---%d\n", players[i].y);
		players[i].type = 3;
	}
}

void Game::initbullet()
{
	int i;
	//bullet	1
	for (i = 1; i <= NumberOfBullet; i++)
	{
		players[i].x = -1;
		players[i].y = -1;
		players[i].type = -1;
	}
}

void Game::move_plane(char x)
{
	int dir[4][2] = { {0,-PLANESPEED},{0,PLANESPEED},{-PLANESPEED,0},{PLANESPEED,0} };//w 0//s 1//a 2//d 3
	int dirx=0;
	switch (x)
	{
	case 'w':dirx = 0; break;
	case 's':dirx = 1; break;
	case 'a':dirx = 2; break;
	case 'd':dirx = 3; break;
	}
	players[0].x += dir[dirx][0];
	players[0].y += dir[dirx][1];
}

void Game::move_plane(int x)
{
	int dir[4][2] = { {0,-PLANESPEED},{0,PLANESPEED},{-PLANESPEED,0},{PLANESPEED,0} };//w 0//s 1//a 2//d 3
	int dirx = 0;
	switch (x)
	{
	case 72:dirx = 0; break;
	case 80:dirx = 1; break;
	case 75:dirx = 2; break;
	case 77:dirx = 3; break;
	}
	players[0].x += dir[dirx][0];
	players[0].y += dir[dirx][1];
}

void Game::move_bullet()
{
	for (int i = 1; i <= NumberOfBullet; i++)
	{
		if (players[i].x == -1 && players[i].y == -1)
		{
			continue;
		}
		players[i].x += 5;
		if (players[i].x > SWIDTH)
		{
			players[i].x = -1;
			players[i].y = -1;
		}
	}
}

void Game::move_enemy()
{
	for (int i = NumberOfBullet + 1; i <= NumberOfBullet + NumberOfEnemy; i++)
	{
		if (players[i].x == -1 && players[i].y == -1 && players[i].type == 2)
		{
			players[i].x = rand() % 400 + SWIDTH;
			players[i].y = rand() %(SHEIGTHT-ENEMY_H-30);
		}
		else
		{
			players[i].x -= 4;
			if (players[i].x < -ENEMY_W)
			{
				players[i].x = -1;
				players[i].y = -1;
			}
		}
	}

}

void Game::move_help()
{
	for (int i = NUM - 1; i >= NUM - NumberOfHelp; i--)
	{
		if (players[i].x == -1 && players[i].y == -1 && players[i].type == 3)
		{
			players[i].x = rand() % 400 + SWIDTH;
			players[i].y = rand() % (SHEIGTHT - ENEMY_H - 30);
		}
		else
		{
			players[i].x -= 3;
			if (players[i].x < -ENEMY_W)
			{
				players[i].x = -1;
				players[i].y = -1;
			}
		}
	}

}

void Game::shoot()
{
	for (int i = 1; i <= NumberOfBullet; i++)
	{
		if (players[i].x == -1 && players[i].y == -1 && players[i].type == -1 )
		{
			players[i].x = players[0].x + PLANE_W;
			players[i].y = players[0].y + PLANE_H / 2-BULLET_H/2-1;
			break;
		}
	}
}

void Game::pause()
{
	char c = _getch();
	while (c != 27 && c != ' ')
		c = _getch();
}

bool Game::judge(object enemy, object porb)
{
	//printf("in judge %d", porb.type);
	if (porb.type >= 0)
	{
		int enemy_x = enemy.x + ENEMY_W / 2;
		int enemy_y = enemy.y + ENEMY_H / 2;
		int plane_x = porb.x;
		int plane_y = porb.y;
		if (enemy_x - plane_x <= ENEMY_W / 2 && enemy_x - plane_x >= -(ENEMY_W / 2) && enemy_y >= plane_y - ENEMY_W / 2 && enemy_y <= plane_y + PLANE_H - 1 + ENEMY_W / 2)
		{
			return 1;
		}
		else if (enemy_y >= plane_y && enemy_y <= (plane_y + PLANE_H / 2 - 1) && enemy_x - ENEMY_W <= plane_x + 2 * (enemy_y - plane_y) && enemy_x + ENEMY_W >= plane_x + 2 * (enemy_y - plane_y))
		{
			return 1;
		}
		else if (enemy_y >= plane_y + PLANE_H / 2 - 1 && enemy_y <= (plane_y + PLANE_H - 1) && enemy_x - ENEMY_W <= plane_x + 2 * (plane_y + PLANE_H - 1 - enemy_y) && enemy_x + ENEMY_W >= plane_x + 2 * (plane_y + PLANE_H - 1 - enemy_y))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if (porb.type == -1)
	{
		int bullet_x = porb.x+BULLET_W/2;
		int bullet_y = porb.y+BULLET_H/2;
		int enemy_x = enemy.x + ENEMY_W / 2;
		int enemy_y = enemy.y + ENEMY_H / 2;
		if ((bullet_x - enemy_x)*(bullet_x - enemy_x) + (bullet_y - enemy_y)*(bullet_y - enemy_y) <= (BULLET_W / 2 + ENEMY_W / 2)*(BULLET_W / 2 + ENEMY_W / 2))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void Game::endgame()
{
	int times = 30;
	drawall();
	while (times--)
	{
		Sleep(100);
		drawall();
	}
	BeginBatchDraw();
	putimage(0, 0, &img[8], SRCAND);
	putimage(0, 0, &img[7], SRCPAINT);
	EndBatchDraw();
	while (getchar() != '\n');
}

void Game::printhelp()
{
	//151515151515151515151
}

int menu()
{
	int nowj;//当前选项框所在位置右下角纵坐标
	RECT r[3] = { {0, 340, SWIDTH, 410},{0, 410, SWIDTH, 480},{0, 480, SWIDTH, 550} };
	settextstyle(28, 0, _T("微软雅黑"));
	nowj = 0;
	drawtext(_T("> 开始游戏PLAY <"), &r[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("查看排名READ"), &r[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("退出游戏EXIT"), &r[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//	settextstyle(32, 0, _T("Consolas"));
//	outtextxy(0, 0, _T("AB测试"));
	while (1)
	{
		if (_kbhit())
		{
			char x = _getch();
			if (x < 0)
				x = _getch();
			switch (x) {
			case 'w':
			case 72:
				if (nowj == 1)
				{
					nowj = 0;
					drawtext(_T("> 开始游戏PLAY <"), &r[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext(_T("     查看排名READ     "), &r[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (nowj == 2)
				{
					nowj = 1;
					drawtext(_T("> 查看排名READ <"), &r[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext(_T("     退出游戏EXIT     "), &r[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				printf("W or Up is pressed\n"); 
				break;
			case 's':
			case 80:
				if (nowj == 0)
				{
					nowj = 1;
					drawtext(_T("     开始游戏PLAY     "), &r[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext(_T("> 查看排名READ <"), &r[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (nowj == 1)
				{
					nowj = 2;
					drawtext(_T("     查看排名READ     "), &r[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					drawtext(_T("> 退出游戏EXIT <"), &r[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				printf("S or Down is pressed\n"); 
				break;
			case 'k':
			case 32:
			case 13:
				return nowj + 1;
			default :
				printf("%d", x);
				break;
			}
		}
	}
}

void load()
{
	//预加载
	loadimage(&img[0], _T("./pic/openimg.jpg"), SWIDTH, SHEIGTHT);
	loadimage(&img[1], _T("./pic/plane.png"), PLANE_W, PLANE_H);
	loadimage(&img[2], _T("./pic/planemask.png"), PLANE_W, PLANE_H);
	loadimage(&img[3], _T("./pic/enemy.png"), ENEMY_W, ENEMY_H);
	loadimage(&img[4], _T("./pic/enemymask.png"), ENEMY_W, ENEMY_H);
	loadimage(&img[5], _T("./pic/bullet.png"), BULLET_W, BULLET_H);
	loadimage(&img[6], _T("./pic/bulletmask.png"), BULLET_W, BULLET_H);
	loadimage(&img[7], _T("./pic/death.png"), SWIDTH, SHEIGTHT);
	loadimage(&img[8], _T("./pic/deathmask.png"), SWIDTH, SHEIGTHT);
	loadimage(&img[9], _T("./pic/help.png"), ENEMY_W, ENEMY_H);
	loadimage(&img[10], _T("./pic/helpmask.png"), ENEMY_W, ENEMY_H);
	putimage(0, 0, &img[0]);
	getchar();
	cleardevice();
}

char *numtostr(int n)
{
	int m = n;
	int j = 0;
	if (n == 0)
	{
		p[0] = '0';
		p[1] = '\0';
		return p;
	}
	while (n != 0)
	{
		j++;
		n = n / 10;
	}
	j--;
	n = j;
	while (m != 0)
	{
		p[j--] = m % 10+'0';
		m = m / 10;
	}
	p[n + 1] = '\0';
	return p;
}





/////////////////////////stars

// 初始化星星
void InitStar(int i)
{
	star[i].x = SWIDTH;
	star[i].y = rand() % SHEIGTHT;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// 移动星星
void MoveStar(int i)
{
	// 计算新位置
	star[i].x -= star[i].step;
	if (star[i].x < 0)	InitStar(i);

	// 画新星星
	putpixel((int)star[i].x, star[i].y, star[i].color);
}

//////////////////////////////

/////////////////////////////////////////////////////////////////////
int main()
{
	int choose;
	srand((unsigned)time(NULL));
	Game game;
	printf("测试");
	initgraph(SWIDTH, SHEIGTHT, SHOWCONSOLE);
	load();
	//	getchar();
	while (1)
	{
		choose = menu();
		if (choose == 1)
		{
				while (1) {
					game.init();
					game.playing();
					game.endgame();
					/*
					ifsave();
					if (!ifrestart()) {
						break;
					}*/
				}
		}
		else if (choose == 2)
		{
			//	readrank();
		}
		else if (choose == 3)
		{
			break;
		}
	}
	closegraph();
	return 0;
}



///////////////////////////////////////////
/*



if (_kbhit())
		{
			char x = _getch();
			if (x < 0)
				x = _getch();
			switch (x) {
			case 'w':
			case 72:
				printf("wwwwww"); break;
			case 's':
			case 80:
				printf("ssssss"); break;
			case 'a':
			case 75:
				printf("aaaaaa"); break;
			case 'd':
			case 77:
				printf("dddddd"); break;
			case 'k':
			case 32:
				printf("space!"); break;
			default :
				printf("%d", x);
			}
		}














*/