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
//12344412


//ȫ�ֱ�������
IMAGE plane[2];
struct people {
	int x, y;
	int _x, _y;
}person={0,0,250,250};



//��������
void init();
void draw();

//��������
void init() {
	initgraph(480,600);
	IMAGE img;
	loadimage(&plane[0], _T("./pic/plane1.jpg"),100,100,true);
	loadimage(&plane[1], _T("./pic/plane_mask1.jpg"),100,100,true);
}

void draw()
{BeginBatchDraw();
	loadimage(NULL, "./pic/timg.jpg");
	
//	putimage(0, 0, &people[0]);
	//������ͼ
//	putimage(0,0,&plane[1], SRCINVERT);
	putimage(0 ,0, &plane[1], NOTSRCERASE);
	putimage(0, 0, &plane[0], SRCINVERT);


	/*SetWorkingImage(&plane[0]);
	putimage(0, 0, &plane[1], SRCINVERT);
	SetWorkingImage(NULL);
	putimage(400, 465, &plane[1], SRCAND);
	putimage(400, 465, &plane[0], SRCPAINT);*/

	EndBatchDraw();
	Sleep(10);
}



void walk()
{
	if (person.x > person._x&&person.y > person._y) { person.x -= 1, person.y -= 1; return; }//���Ϸ�
	if (person.x < person._x&&person.y > person._y) { person.x += 1, person.y -= 1; return; }//���Ϸ�
	if (person.x > person._x&&person.y < person._y) { person.x -= 1, person.y += 1; return; }//���·�
	if (person.x < person._x&&person.y < person._y) { person.x += 1, person.y += 1; return; }//���·�
	if (person.x > person._x) { person.x -= 1; return; }//��
	if (person.x < person._x) { person.x += 1; return; }//��
	if (person.y > person._y) { person.y -= 1; return; }//��
	if (person.y < person._y) { person.y += 1; return; }//��
}

void Changedir()
{
	//�õ������Ϣ
	if (MouseHit())
	{
		MOUSEMSG msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN://�������
			person._x = msg.x - 35;
			person._y = msg.y - 62;
			break;

		}

	}
}




int main() {
	init();
	draw();
	getchar();
	closegraph();
	system("pause");
	return 0;
}