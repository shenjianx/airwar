#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<string>
//#include<mmsystem.h>
//#pragma comment(lib,"WINMM.lib")

//�궨��
#define Num 120
#define NumOfBullet 20

//ȫ�ֱ������
typedef struct object {
	int x, y;
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

//Game��
class Game {
public:
	
	object players[Num];//player  bullets  enemys
	int NumberOfEnemy;//
	


	//��������
	void initplane();
	void initenemy();
	void initbullet();

	void moveplane(char);
	void moveenemy();
	void movebullet();


	void drawall();

	void pause();
	void playing();

	bool judge();

	void shoot();
};




//������
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
			movebullet();
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