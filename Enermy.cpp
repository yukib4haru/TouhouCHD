#include "kyo.h"
#pragma comment(lib,"winmm.lib")

extern character	hero, pinkE, blackE, redE;

extern list* hero_bullet_list; // 飞机子弹链表的头节点
extern list* pinkE_bullet_list;
extern list* blackE_bullet_list;	//不应加赋值语句在句尾
extern list* redE_bullet_list;

extern bullet	bullet0, bullet1, bullet2, bullet3;

extern IMAGE img_bk, img_menu, img_cur;
extern IMAGE  img_hero, img_pinkE, img_redE, img_blackE;
extern IMAGE img_bullet0, img_bullet1, img_bullet2, img_bullet3;

extern int PINKE_LIFE;
extern int BLACKE_LIFE;
extern int REDE_LIFE;
extern int speed;
extern int score;
extern int game_over;

void listPushBack(list** pplist, list* newNode);
list* creatPINKEBullet(float vx, float vy);
list* creatBLACKEBullet(float vx, float vy); 
list* creatREDEBullet(float vx, float vy);

//圆圈弹幕
void pinkEm()
{
	static int dir = 1;//1前进，局部静态变量，只初始化一次
	static int cnt = 0;
	int pinkE_reload_cnt = 60;//发射子弹的计数器，数值越小发射子弹越快
	int pinkE_fire_num = 20;//共发射几路子弹
	static int step = pinkE.speed;

	if (1 == pinkE.new_born_flg)//刷新的角色，重置x，y的坐标
	{
		pinkE.new_born_flg = 0;
		pinkE.x = rand() % (tWIDTH - pinkE.width);//随机生成位置
		pinkE.y = -50;
	}
	if (pinkE.y > 150)
	{
		dir = 0;
	}
	else if (pinkE.y < 0)
	{
		dir = 1;
		//pinkE.new_born_flg = 1;
	}
	if (1 == dir)
	{
		pinkE.y += pinkE.speed;
	}
	else
	{
		pinkE.y -= pinkE.speed;
	}
	if (pinkE.x<0||pinkE.x + pinkE.width > tWIDTH)
	{
		step = -step;
	}
	pinkE.x += step;
	if (++cnt % pinkE_reload_cnt == 0)
	{
		for (int i = 0; i < pinkE_fire_num; ++i)
		{
			float angle = i * 2 * PI / pinkE_fire_num;
			float vx = 4 * cos(angle);
			float vy = 4 * sin(angle);
			listPushBack(&pinkE_bullet_list, creatPINKEBullet(vx, vy));
		}
	}
	if (cnt > 999999)
		cnt = 0;
}

//斜向移动覆盖弹幕
void blackEm()
{
	static int cnt = 0;
	int blackE_reload_cnt = 14;//发射子弹的计数器，数值越小发射子弹越快
	int blackE_fire_num = 5;//共连发几粒子弹	

	static int step1 = blackE.speed;//step表示方向与速度
	static int step2 = blackE.speed;
	if (1 == blackE.new_born_flg)
	{
		blackE.new_born_flg = 0;
		blackE.x = rand() % (tWIDTH - blackE.width);
		blackE.y = 5;
	}
	if (blackE.x < 0 || blackE.x + blackE.width > tWIDTH)
	{
		step1 = -step1;	//反弹
	}
	if (blackE.y < 0 || blackE.y + blackE.height > HEIGHT)
	{
		step2 = -step2;
	}
	blackE.x += step1;
	blackE.y += step2;
	if (blackE.y > HEIGHT)
	{
		blackE.new_born_flg = 1;
	}
	//连发功能，待思考
	if (++cnt % blackE_reload_cnt == 0)
	{
		listPushBack(&blackE_bullet_list, creatBLACKEBullet(0, 7));
	}
	if (cnt > 999999)
		cnt = 0;
}

//两种攻击模式
void redEm()
{
	static int cnt = 0;
	int pinkE_reload_cnt = 150;//发射子弹的计数器，数值越小发射子弹越快
	int pinkE_fire_num = 5;//共发射几路子弹

	static float dist_x = 0, dist_y = 0;	//储存与玩家的横竖距离
	static float tmp_x = 0, tmp_y = 0;		//储存x,y坐标的临时变量，浮点型方便计算
	static float vx = 0, vy = 0;	//横纵速度
	float step = 400 / redE.speed;	//调整速度
	if (1 == redE.new_born_flg)
	{
		redE.new_born_flg = 0;
		tmp_x = rand() % (tWIDTH - redE.width);
		tmp_y = redE.height;
		vx = redE.speed / 3;	
		vy = 0;
	}
	if (redE.life <= 0.5 * REDE_LIFE)
	{
		dist_x = hero.x - tmp_x;
		dist_y = hero.y - tmp_y;
		vx = dist_x / step;
		vy = dist_y / step;
	}
	if (++cnt % pinkE_reload_cnt == 0)
	{
		for (int i = 0; i < pinkE_fire_num; ++i)
		{
			float angle = i * PI / pinkE_fire_num;
			float vx1 = 4 * cos(angle);
			float vy1 = 4 * sin(angle);
			listPushBack(&redE_bullet_list, creatREDEBullet(vx1, vy1));
		}
	}
	if (cnt > 999999)
		cnt = 0;
	tmp_x += vx;	//移动
	tmp_y += vy;
	redE.x = (int)(tmp_x + 0.5);
	redE.y = (int)(tmp_y + 0.5);	//四舍五入转换成整形
	//边界判断，可以超出画面，但不能太多
	if (redE.x < 0)
		vx = -vx;
	else if (redE.x > tWIDTH - redE.width)
		vx = -vx;
	if (redE.y >= HEIGHT)
		redE.new_born_flg = 1;
}
