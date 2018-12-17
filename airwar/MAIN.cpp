#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string>
//#include<mmsystem.h>
//#pragma comment(lib,"WINMM.lib")

//宏定义
#define Num 120
#define NumOfBullet 20

//全局变量声明
typedef struct object {
	int x, y;
	int type;
}object;
int score;
int speed;

//函数声明
void init();
int menu();
void draw();
void playing();
void ifsave();
bool ifrestart();
void readrank();
void death();
void load();

//Game类
class Game {
public:
	
	object players[Num];//player  bullets  enemys
	int NumberOfEnemy;//
	


	//函数声明
	void initplane();
	void initenemy();
	void initbullet();

	void move_plane(char);
	void move_enemy();
	void move_bullet();


	void drawall();

	void pause();
	void playing();

	bool judge();

	void shoot();
};




//函数定义
void Game::playing() {
	bool fg = 1;
	int N1 = 10;
	int numofbullet = 0;
	while (fg){
		/*if (_kibhit) {
			moveplane();
			pause();
			//exits();

		}*/
		if (numofbullet == N1) {
			move_bullet();
			if(judge());
		}
		numofbullet++;

		//enmey

		draw();

	}



}





/////////////////////////////////////////////////////////////////////
int main() {
	int choose;
	load();
	while (1) {
		choose=menu();
		if (choose == 1) {
			while (1) {
				init();
				playing();
				death();
				ifsave();
				if (!ifrestart()) {
					break;
				}
			}
		}
		else if (choose == 2) {
			readrank();
		}
		else if (choose == 3) {
			break;
		}
	}
	return 0;
}