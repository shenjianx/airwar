#include<iostream>
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
#define MAXSTAR 200	// 星星总数
#define NUM 120
#define SWIDTH 1080
#define SHEIGTHT 640

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
IMAGE img[10];

//函数声明
int menu();
void draw();
void ifsave();
bool ifrestart();
void readrank();
void death();
void load();
void InitStar(int);
void MoveStar(int);

//Game类
class Game
{
public:

	object players[NUM];//player  bullets  enemys
	int NumberOfEnemy;//
	int NumberOfBullet;//


	//函数声明
	void initplane();
	void initenemy();
	void initbullet();

	void move_plane(char);
	void move_enemy();
	void move_bullet();


	void drawall();

	void init();
	void pause();
	void playing();

	bool judge();

	void shoot();
};




//函数定义
void Game::playing()
{
	bool death = 1;//标记死亡
	int bullet_speed = 10;//子弹速度
	int enemy_speed = 15;//敌人速度
	int count_bullet = 0;
	int count_enemy = 0;
	while (death)
	{
		/*if (_kibhit) {
			move_plane();
			pause();
			//exits();

		}*/
		/*	if (count_bullet == bullet_speed) {
				move_bullet();
				if(judge());
			}
			count_bullet++;

			//enmey

			draw();*/

	}



}

void Game::drawall()
{
	cleardevice();
	BeginBatchDraw();
	for (int i = 0; i < MAXSTAR; i++)
		MoveStar(i);
	EndBatchDraw();
}

void Game::init()
{
	//初始化星星
	for (int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % 640;
	}
}

int menu()
{
	RECT r1 = { 0, 340, SWIDTH, 410 };
	RECT r2 = { 0, 410, SWIDTH, 480 };
	RECT r3 = { 0, 480, SWIDTH, 550 };
	settextstyle(28, 0, _T("微软雅黑"));
	drawtext(_T("开始游戏PLAY"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("查看排名READ"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("退出游戏EXIT"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	settextstyle(32, 0, _T("Consolas"));
	outtextxy(0, 0, _T("AB测试"));

	return 1;
}

void load()
{
	//预加载
	loadimage(&img[0], _T("./pic/openimg.jpg"), SWIDTH, SHEIGTHT);
	putimage(0, 0, &img[0]);
	Sleep(1000);
	cleardevice();
}


/////////////////////////stars

// 初始化星星
void InitStar(int i)
{
	star[i].x = 0;
	star[i].y = rand() % SHEIGTHT;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// 移动星星
void MoveStar(int i)
{
	// 计算新位置
	star[i].x += star[i].step;
	if (star[i].x > SWIDTH)	InitStar(i);

	// 画新星星
	putpixel((int)star[i].x, star[i].y, star[i].color);
}

//////////////////////////////

/////////////////////////////////////////////////////////////////////
int main()
{
	int choose;
	srand((unsigned)time(NULL));
	//	Game game;
	printf("测试");
	initgraph(SWIDTH, SHEIGTHT, SHOWCONSOLE);
	load();
	//	getchar();
	while (1)
	{
		choose = menu();
		if (choose == 1)
		{
			/*	while (1) {
					game.init();
					game.playing();
					death();
					ifsave();
					if (!ifrestart()) {
						break;
					}
				}*/
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