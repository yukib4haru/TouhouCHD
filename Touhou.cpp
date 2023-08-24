// Touhou.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//无位运算移动、透明化贴图

#include "kyo.h"
#pragma comment(lib,"winmm.lib")

character	hero, pinkE, blackE, redE;

list* hero_bullet_list = NULL; // 飞机子弹链表的头节点
list* pinkE_bullet_list = NULL;
list* blackE_bullet_list = NULL;
list* redE_bullet_list = NULL;

bullet	bullet0, bullet1, bullet2, bullet3;

IMAGE img_bk, img_menu, img_cur, img_end;
IMAGE  img_hero, img_pinkE, img_redE, img_blackE;
IMAGE img_bullet0, img_bullet1, img_bullet2, img_bullet3;
IMAGE img_menu1, img_menu2, img_menu3;

int clearChance = 3;

int PINKE_LIFE = 200;
int BLACKE_LIFE = 150;
int REDE_LIFE = 150;
int speed = 7;
int score = 0;
int game_over = 0;

int which = 0;

/*#define _stprintf
#define _CRT_SECURE_NO_WARNINGS*/


//数据载入
void dataInit();
void loadG();

//框架相关
int showMenu();
void showGameOver();
void logPrint();

//子弹相关
void listPushBack(list** pplist, list* newNode);
list* creatHeroBullet(float vx, float vy);
void listChangeXY(list** pplist);
void listRemoveNode(list** pplist);
void showBullet();
list* creatPINKEBullet(float vx, float vy);
list* creatBLACKEBullet(float vx, float vy);
void clearBullet(list** pplist);
void clearAllBullet();

//碰撞判断
void bulletHitE(character* tmp);
void charaReborn(character* tmp, int life);
void charaLifeJudge();
void bulletHitHero(list* bullet_list);
void charaCrash(character* tmp);
int isPointIn(int x, int y);

//人物相关
void ctrlChara();
void showChara();
void pinkEm();
void blackEm();
void redEm();

//音乐音效
void playMBgmMusic();
void playBgmMusic();
void playShootMusic();
void playBoom1Music();
void curMoveMusic();
void playHBoomMusic();

//文本显示
void ctrlFps(int start_time);
void showScore(int x, int y, int score);
void showLife(int x, int y, int life);
void showChance(int x, int y, int clearChance);



int main() 
{
	dataInit();//初始化所有人物
	initgraph(WIDTH, HEIGHT, 0);// 创建绘图窗口 
	loadG();
	BeginBatchDraw();
	showMenu();
	EndBatchDraw();
	clock_t start_time;
	playBgmMusic();		//脑子瓦特把它放进死循环里了
	BeginBatchDraw();
	srand((unsigned)time(0));	//种子
	while (1)
	{
		start_time = clock();
		pinkEm();
		blackEm();
		redEm();
		ctrlChara();
		showChara();
		showBullet();
		charaLifeJudge();
		charaCrash(&blackE);
		charaCrash(&redE);
		charaCrash(&pinkE);
		Sleep(10);
		ctrlFps(start_time);
		showScore(560, 100, score);
		showLife(560, 150, hero.life);
		showChance(560, 200, clearChance);
		FlushBatchDraw();
		if (game_over)
		{
			playHBoomMusic();	//待完成
			logPrint();
			showGameOver();
		}
	}		//实现人物移动
	EndBatchDraw();

	_getch();	//?
	closegraph(); 
	return 0; 
}



