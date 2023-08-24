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

void playBeatenMusic();

//存在问题
//在某链表尾部插入一个数据
void listPushBack(list** pplist, list* newNode)
{
	if (*pplist == NULL)//如果链表为空，那么新增的节点就是第一个
	{
		*pplist = newNode;
		return;
	}		//current or cursor简称
	list* cur = *pplist;	//存pplist地址
	while (cur->pnext != NULL)//找到最后一个节点
	{
		cur = cur->pnext;
	}
	cur->pnext = newNode;//插入新的节点
}

//生成我方子弹
list* creatHeroBullet(float vx, float vy)  //返回一个指针
{
	list* p = new list;	//申请节点内存	//new取代
	p->x = hero.x + hero.width / 2 - 5;
	p->y = hero.y - 5;
	p->vx = vx;
	p->vy = vy;
	p->damage = 20;
	p->isExist = 1;
	p->pnext = NULL;
	p->width = 10;
	p->height = 50;
	return p;
}

//生成我方升级子弹左
list* creatHeroLBullet(float vx, float vy)  //返回一个指针
{
	list* p = new list;	//申请节点内存
	p->x = hero.x + hero.width / 2 - 10;
	p->y = hero.y - 5;
	p->vx = vx;
	p->vy = vy;
	p->damage = 15;
	p->isExist = 1;
	p->pnext = NULL;
	p->width = 10;
	p->height = 50;
	return p;
}

//生成我方升级子弹右
list* creatHeroRBullet(float vx, float vy)  //返回一个指针
{
	list* p = new list;	//申请节点内存
	p->x = hero.x + hero.width / 2 + 10;
	p->y = hero.y - 5;
	p->vx = vx;
	p->vy = vy;
	p->damage = 15;
	p->isExist = 1;
	p->pnext = NULL;
	p->width = 10;
	p->height = 50;
	return p;
}

//修改某链中所有节点的坐标。
void listChangeXY(list** pplist)
{
	if (*pplist == NULL)
		return;
	list* cur = *pplist;
	while (cur != NULL)//遍历
	{
		cur->x += cur->vx;
		cur->y += cur->vy;
		//判断子弹是否离开视野
		if ((cur->x < -20) || (cur->x > tWIDTH) || (cur->y < -20) || (cur->y > HEIGHT))
		{
			cur->isExist = 0;
		}
		cur = cur->pnext;//指向下一节点
	}
}

//删除链表中isExist==0的节点
void listRemoveNode(list** pplist)
{
	if (*pplist == NULL)
		return;
	list* cur = *pplist;//current先指向第一个节点
	list* prev = NULL;//previous指向上一个节点的指针
	while (cur != NULL)//遍历链表
	{
		if (0 == cur->isExist)
		{
			if (*pplist == cur)//如果第一个直接
			{
				*pplist = cur->pnext;//更改链表的地址，让下一个节点作为头节点，如果没有节点，则链表为空
				free(cur);	//释放当前节点空间
				cur = *pplist;
			}
			else
			{
				prev->pnext = cur->pnext;
				free(cur);
				cur = prev;
			}
		}
		else
		{	//代码看全
			prev = cur;
			cur = cur->pnext;
		}
	}
}

//判断子弹是否命中我方角色
void bulletHitHero(list* bullet_list)
{
	//子弹在我方角色图片内，认为击中
	for (list* cur = bullet_list; cur != NULL; cur = cur->pnext)
	{
		if ((cur->x > hero.x) && (cur->x < hero.x + hero.width))
			if ((cur->y > hero.y) && (cur->y < hero.y + hero.height))
			{
				hero.life -= cur->damage;	//减少人物生命值
				cur->isExist = 0;	//清除子弹存在标记
				playBeatenMusic();
			}
	}
}

//判断角色的子弹是否击中敌方，执行相应的加分与减命的操作
void bulletHitE(character* tmp)
{
	//子弹在敌方角色图片内，认为击中
	for (list* cur = hero_bullet_list; cur != NULL; cur = cur->pnext)
	{
		if ((cur->x > tmp->x) && (cur->x < tmp->x + tmp->width))
			//if ((cur->x + cur->width > tmp->x) && (cur->x+cur->width < tmp->x + tmp->width))
			if ((cur->y > tmp->y) && (cur->y < tmp->y + tmp->height))
				//if ((cur->y + cur->height > tmp->y) && (cur->y + cur->height < tmp->y + tmp->height))
			{
				tmp->life -= cur->damage;	//减少敌方人物生命值
				cur->isExist = 0;	//清除子弹存在标记
				//playBeatenMusic();
			}
	}
}

//绘制发射出来的子弹
void showBullet()
{
	//Hero
	listChangeXY(&hero_bullet_list);
	listRemoveNode(&hero_bullet_list);
	for (list* cur = hero_bullet_list; cur != NULL; cur = cur->pnext)
	{
		putimage(cur->x, cur->y, &img_bullet0);
	}
	bulletHitE(&pinkE);
	bulletHitE(&blackE);
	bulletHitE(&redE);

	//pinkE
	listChangeXY(&pinkE_bullet_list);
	listRemoveNode(&pinkE_bullet_list);
	for (list* cur = pinkE_bullet_list; cur != NULL; cur = cur->pnext)
	{
		putimage(cur->x, cur->y, &img_bullet1);
	}
	bulletHitHero(pinkE_bullet_list);

	//blackE
	listChangeXY(&blackE_bullet_list);
	listRemoveNode(&blackE_bullet_list);
	for (list* cur = blackE_bullet_list; cur != NULL; cur = cur->pnext)
	{
		putimage(cur->x, cur->y, &img_bullet3);
	}
	bulletHitHero(blackE_bullet_list);

	//redE
	listChangeXY(&redE_bullet_list);
	listRemoveNode(&redE_bullet_list);
	for (list* cur = redE_bullet_list; cur != NULL; cur = cur->pnext)
	{
		putimage(cur->x, cur->y, &img_bullet2);
	}
	bulletHitHero(redE_bullet_list);
}

//生成PE子弹
list* creatPINKEBullet(float vx, float vy)  //返回一个指针
{
	list* p = new list;	//申请节点内存
	p->x = pinkE.x + pinkE.width / 2;
	p->y = pinkE.y + pinkE.height;
	p->vx = vx;
	p->vy = vy;
	p->isExist = 1;
	p->pnext = NULL;
	p->damage = 10;
	return p;
}

//生成BE子弹
list* creatBLACKEBullet(float vx, float vy)  //返回一个指针
{
	list* p = new list;	//申请节点内存
	p->x = blackE.x + blackE.width / 2;
	p->y = blackE.y + blackE.height;
	p->vx = vx;
	p->vy = vy;
	p->isExist = 1;
	p->pnext = NULL;
	p->damage = 20;
	return p;
}

//生成RE子弹
list* creatREDEBullet(float vx,float vy)
{
	list* p = new list;	//申请节点内存
	p->x = redE.x + redE.width / 2;
	p->y = redE.y + redE.height;
	p->vx = vx;
	p->vy = vy;
	p->isExist = 1;
	p->pnext = NULL;
	p->damage = 20;
	return p;
}

//清除单种子弹
void clearBullet(list** pplist)
{
	if (*pplist == NULL)
		return;
	list* cur = *pplist;	//current指向第一个节点
	while (cur != NULL)
	{
		cur->isExist = 0;
		cur = cur->pnext;
	}
	listRemoveNode(pplist);
}

//清除所有子弹
void clearAllBullet()
{
	clearBullet(&hero_bullet_list);
	clearBullet(&pinkE_bullet_list);
	clearBullet(&blackE_bullet_list); 
	clearBullet(&redE_bullet_list);
}


