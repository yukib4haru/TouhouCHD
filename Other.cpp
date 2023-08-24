#include "kyo.h"
#pragma comment(lib,"winmm.lib")

extern character	hero, pinkE, blackE, redE;

extern list* hero_bullet_list; // 飞机子弹链表的头节点
extern list* pinkE_bullet_list;
extern list* blackE_bullet_list;	//不应加赋值语句在句尾

extern bullet	bullet0, bullet1, bullet2, bullet3;

extern IMAGE img_bk, img_menu, img_cur,img_end;
extern IMAGE  img_hero, img_pinkE, img_redE, img_blackE;
extern IMAGE img_bullet0, img_bullet1, img_bullet2, img_bullet3;
extern IMAGE img_menu1, img_menu2, img_menu3;

extern int clearChance;

extern int PINKE_LIFE;
extern int BLACKE_LIFE;
extern int REDE_LIFE;
extern int speed;
extern int score;
extern int game_over;

void listPushBack(list** pplist, list* newNode);
void playShootMusic();
void clearAllBullet();
void playEBgmMusic();
void playMBgmMusic();
void clearAllBullet();
void playClearMusic();
list* creatHeroBullet(float vx, float vy);
list* creatHeroLBullet(float vx, float vy);
list* creatHeroRBullet(float vx, float vy);

//角色数据初始化
void dataInit()
{
	hero.x = tWIDTH / 2 - 15;
	hero.y = 600;
	hero.width = 30;
	hero.height = 50;
	hero.life = 150;

	pinkE.x = 300;
	pinkE.y = 300;
	pinkE.width = 60;
	pinkE.height = 60;
	pinkE.speed = 2;
	pinkE.new_born_flg = 1;
	pinkE.life = PINKE_LIFE;

	blackE.x = 50;
	blackE.y = 150;
	blackE.width = 60;
	blackE.height = 60;
	blackE.speed = 3;
	blackE.new_born_flg = 1;
	blackE.life = BLACKE_LIFE;

	redE.x = 520;
	redE.y = 0;
	redE.width = 60;
	redE.height = 60;
	redE.speed = 10;
	redE.new_born_flg = 1;
	redE.life = REDE_LIFE;
}

//载入数据
void loadG()
{
	loadimage(&img_bk, _T("Image\\background.bmp"));
	loadimage(&img_menu, _T("Image\\menu.bmp"));
	loadimage(&img_cur, _T("Image\\cur.bmp"));
	loadimage(&img_end, _T("Image\\end1.bmp"));

	loadimage(&img_hero, _T("Image\\hero1.bmp"));
	loadimage(&img_pinkE, _T("Image\\pinkE.bmp"));
	loadimage(&img_redE, _T("Image\\redE.bmp"));
	loadimage(&img_blackE, _T("Image\\blackE.bmp"));

	loadimage(&img_bullet0, _T("Image\\bullet0.bmp"));
	loadimage(&img_bullet1, _T("Image\\bullet1.bmp"));
	loadimage(&img_bullet2, _T("Image\\bullet2.bmp"));
	loadimage(&img_bullet3, _T("Image\\bullet3.bmp"));

	loadimage(&img_menu1, _T("Image\\menu1.bmp"));
	loadimage(&img_menu2, _T("Image\\menu2.bmp"));
	loadimage(&img_menu3, _T("Image\\menu3.bmp"));
}

//绘制所有人物
void showChara()
{	//未使用透明化
	putimage(0, 0, &img_bk);
	putimage(hero.x, hero.y, &img_hero);
	putimage(pinkE.x, pinkE.y, &img_pinkE);
	putimage(redE.x, redE.y, &img_redE);
	putimage(blackE.x, blackE.y, &img_blackE);
	//暂停时也绘制子弹
	//putimage(bullet0.x, bullet0.y, &img_bullet0);
	putimage(bullet1.x, bullet1.y, &img_bullet1);
	putimage(bullet2.x, bullet2.y, &img_bullet2);
	putimage(bullet3.x, bullet3.y, &img_bullet3);
}

//控制角色
void ctrlChara()	//进阶：用GetAsynKeyState位运算实现
{
	int reload_time = 180;		//CD
	static int fire_start = 0;	//局部静态变量，保存开火时间
	int reloadC_time = 1000;		//CD
	static int fireC_start = 0;	//局部静态变量，保存清屏时间
	int tmp = clock();			//缓存当前时间
	
	if (GetKeyState(65) < 0 && hero.x > 1)
		hero.x -= speed;	//a,向左
	if (GetKeyState(68) < 0 && hero.x < tWIDTH - 30)
		hero.x += speed;	//d,向右
	if (GetKeyState(83) < 0 && hero.y < HEIGHT - 50)
		hero.y += speed;	//s,向下
	if (GetKeyState(87) < 0 && hero.y > 1)
		hero.y -= speed;	//w,向上
	if (GetKeyState(74) < 0 && tmp - fire_start >= reload_time)	//j，子弹攻击 */
	{
		if (score < 500)
		{
			listPushBack(&hero_bullet_list, creatHeroBullet(0, -10));
			fire_start = tmp;
			playShootMusic();
		}
		else
		{
			listPushBack(&hero_bullet_list, creatHeroLBullet(0, -10));
			listPushBack(&hero_bullet_list, creatHeroRBullet(0, -10));
			fire_start = tmp;
			playShootMusic();
		}
	}
	if (GetKeyState(75) < 0 && clearChance > 0 && tmp - fireC_start >= reloadC_time)	//k,清屏
	{
		clearAllBullet();
		playClearMusic();
		clearChance--;
	}
}

//控制FPS
//存在问题
void ctrlFps(int start_time)
{
	clock_t running_time = clock() - start_time;
	if (20 - running_time >= 0)
		Sleep(20 - running_time);
	TCHAR time_text[50];	//存疑
	int FPS = 1000 / (clock() - start_time);
	/*cout << "FPS=" << FPS;*/
	_stprintf_s(time_text, _T("FPS:%d"), FPS);  //存疑
	settextstyle(20, 0, _T("Times New Roman"));
	outtextxy(0, 0, time_text);
}

//存在问题
//展示分数
void showScore(int x, int y, int score)
{
	TCHAR time_text[50];	//存疑
	_stprintf_s(time_text, _T("Score:%d"), score);  //存疑
	settextstyle(30, 0, _T("Times New Roman"));
	outtextxy(x, y, time_text);
}

//显示角色生命值
void showLife(int x, int y, int life)
{
	TCHAR time_text[50];	//存疑
	_stprintf_s(time_text, _T("Life:%d"), life);  //存疑
	settextstyle(30, 0, _T("Times New Roman"));
	outtextxy(x, y, time_text);
}

//显示可用次数
void showChance(int x, int y, int clearChance)
{
	TCHAR time_text[50];	//存疑
	_stprintf_s(time_text, _T("ClearChance:%d"), clearChance);  //存疑
	settextstyle(30, 0, _T("Times New Roman"));
	outtextxy(x, y, time_text);
}

//显示开场界面
int showMenu()
{
	playMBgmMusic();

	int reload_time = 200;		//CD
	static int fire_start = 0;	//局部静态变量，保存开火时间
	int tmp = clock();			//缓存当前时间

	static int cur = 3 * 100;
	static int flag = cur % 3;
	
	if (0 == flag)
	{
		putimage(0, 0, &img_menu1);
	}
	else if (1 == flag)
	{
		putimage(0, 0, &img_menu2);
	}
	else if (2 == flag)
	{
		putimage(0, 0, &img_menu3);
	}
	if (GetKeyState(83) < 0 && flag <2 )
		++cur;	//s,向下
	if (GetKeyState(87) < 0 && flag > 0)
		--cur;	//w,向上
	if (GetKeyState(74) < 0 && fire_start < reload_time)
	{
		if (0 == flag)
			return 1;
		else if (2 == flag)
			return 0;
	}

	FlushBatchDraw();
	_getch();		//关键?
}

//结束界面
void showGameOver()
{
	playEBgmMusic();
	putimage(0, 0, &img_end);
	FlushBatchDraw();
	while (' ' != _getch());
	score = 0;
	game_over = 0;
	clearChance = 3;
	dataInit();
	clearAllBullet();
	showMenu();
}

//保存记录
void logPrint()
{
	ofstream fout("Log.txt");
	fout << endl<<"Score:" << score << endl;
}