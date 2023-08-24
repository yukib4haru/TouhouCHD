#include "kyo.h"
#pragma comment(lib,"winmm.lib")

extern character	hero, pinkE, blackE, redE;

extern list* hero_bullet_list; // 飞机子弹链表的头节点
extern list* pinkE_bullet_list;
extern list* blackE_bullet_list;	//不应加赋值语句在句尾

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
extern int clearChance;

void playBoom1Music();

//敌方人物的再登场
void charaReborn(character* tmp, int life)
{
	tmp->new_born_flg = 1;
	tmp->life = life;
}

//人物生存判断	//redE不出来BUG
void charaLifeJudge()
{
	if (pinkE.life <= 0)
	{
		charaReborn(&pinkE, PINKE_LIFE);
		score += PINKE_LIFE;
		hero.life += 10;
		clearChance++;
		playBoom1Music();
	}
	if (blackE.life <= 0)
	{
		charaReborn(&blackE, BLACKE_LIFE);
		score += BLACKE_LIFE;
		hero.life += 10;
		//clearChance++;
		playBoom1Music();
	}
	if (redE.life <= 0)
	{
		charaReborn(&redE, REDE_LIFE);
		score += REDE_LIFE;
		hero.life += 10;
		//clearChance++;
		playBoom1Music();
	}
	if (hero.life <= 0)
		game_over = 1;
}

//把图片简化为一个点判断
int isPointIn(int x, int y)
{
	int flag = 0;
	if (x > hero.x && x<hero.x + hero.width && y>hero.y && y < hero.y + hero.height)
		flag = 1;
	return flag;
}

//存在问题
//判断人物是否相撞
void charaCrash(character* tmp)
{
	if (isPointIn(tmp->x + tmp->width / 4, tmp->y + tmp->height / 2) || isPointIn(tmp->x + tmp->width / 4 * 3, tmp->y + tmp->height / 2)
		|| isPointIn(tmp->x + tmp->width / 2, tmp->y + tmp->height / 4) || isPointIn(tmp->x + tmp->width / 2, tmp->y + tmp->height / 4 * 3))
	{
		hero.life = hero.life / 2;	//生命值减少一半
		tmp->life = 0;
	}
}