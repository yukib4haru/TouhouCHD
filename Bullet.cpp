#include "kyo.h"
#pragma comment(lib,"winmm.lib")

extern character	hero, pinkE, blackE, redE;

extern list* hero_bullet_list; // �ɻ��ӵ������ͷ�ڵ�
extern list* pinkE_bullet_list;
extern list* blackE_bullet_list;	//��Ӧ�Ӹ�ֵ����ھ�β
extern list* redE_bullet_list;

extern bullet	bullet0, bullet1, bullet2, bullet3;

extern IMAGE img_bk, img_menu, img_cur;
extern IMAGE  img_hero, img_pinkE, img_redE, img_blackE;
extern IMAGE img_bullet0, img_bullet1, img_bullet2, img_bullet3;

void playBeatenMusic();

//��������
//��ĳ����β������һ������
void listPushBack(list** pplist, list* newNode)
{
	if (*pplist == NULL)//�������Ϊ�գ���ô�����Ľڵ���ǵ�һ��
	{
		*pplist = newNode;
		return;
	}		//current or cursor���
	list* cur = *pplist;	//��pplist��ַ
	while (cur->pnext != NULL)//�ҵ����һ���ڵ�
	{
		cur = cur->pnext;
	}
	cur->pnext = newNode;//�����µĽڵ�
}

//�����ҷ��ӵ�
list* creatHeroBullet(float vx, float vy)  //����һ��ָ��
{
	list* p = new list;	//����ڵ��ڴ�	//newȡ��
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

//�����ҷ������ӵ���
list* creatHeroLBullet(float vx, float vy)  //����һ��ָ��
{
	list* p = new list;	//����ڵ��ڴ�
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

//�����ҷ������ӵ���
list* creatHeroRBullet(float vx, float vy)  //����һ��ָ��
{
	list* p = new list;	//����ڵ��ڴ�
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

//�޸�ĳ�������нڵ�����ꡣ
void listChangeXY(list** pplist)
{
	if (*pplist == NULL)
		return;
	list* cur = *pplist;
	while (cur != NULL)//����
	{
		cur->x += cur->vx;
		cur->y += cur->vy;
		//�ж��ӵ��Ƿ��뿪��Ұ
		if ((cur->x < -20) || (cur->x > tWIDTH) || (cur->y < -20) || (cur->y > HEIGHT))
		{
			cur->isExist = 0;
		}
		cur = cur->pnext;//ָ����һ�ڵ�
	}
}

//ɾ��������isExist==0�Ľڵ�
void listRemoveNode(list** pplist)
{
	if (*pplist == NULL)
		return;
	list* cur = *pplist;//current��ָ���һ���ڵ�
	list* prev = NULL;//previousָ����һ���ڵ��ָ��
	while (cur != NULL)//��������
	{
		if (0 == cur->isExist)
		{
			if (*pplist == cur)//�����һ��ֱ��
			{
				*pplist = cur->pnext;//��������ĵ�ַ������һ���ڵ���Ϊͷ�ڵ㣬���û�нڵ㣬������Ϊ��
				free(cur);	//�ͷŵ�ǰ�ڵ�ռ�
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
		{	//���뿴ȫ
			prev = cur;
			cur = cur->pnext;
		}
	}
}

//�ж��ӵ��Ƿ������ҷ���ɫ
void bulletHitHero(list* bullet_list)
{
	//�ӵ����ҷ���ɫͼƬ�ڣ���Ϊ����
	for (list* cur = bullet_list; cur != NULL; cur = cur->pnext)
	{
		if ((cur->x > hero.x) && (cur->x < hero.x + hero.width))
			if ((cur->y > hero.y) && (cur->y < hero.y + hero.height))
			{
				hero.life -= cur->damage;	//������������ֵ
				cur->isExist = 0;	//����ӵ����ڱ��
				playBeatenMusic();
			}
	}
}

//�жϽ�ɫ���ӵ��Ƿ���ез���ִ����Ӧ�ļӷ�������Ĳ���
void bulletHitE(character* tmp)
{
	//�ӵ��ڵз���ɫͼƬ�ڣ���Ϊ����
	for (list* cur = hero_bullet_list; cur != NULL; cur = cur->pnext)
	{
		if ((cur->x > tmp->x) && (cur->x < tmp->x + tmp->width))
			//if ((cur->x + cur->width > tmp->x) && (cur->x+cur->width < tmp->x + tmp->width))
			if ((cur->y > tmp->y) && (cur->y < tmp->y + tmp->height))
				//if ((cur->y + cur->height > tmp->y) && (cur->y + cur->height < tmp->y + tmp->height))
			{
				tmp->life -= cur->damage;	//���ٵз���������ֵ
				cur->isExist = 0;	//����ӵ����ڱ��
				//playBeatenMusic();
			}
	}
}

//���Ʒ���������ӵ�
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

//����PE�ӵ�
list* creatPINKEBullet(float vx, float vy)  //����һ��ָ��
{
	list* p = new list;	//����ڵ��ڴ�
	p->x = pinkE.x + pinkE.width / 2;
	p->y = pinkE.y + pinkE.height;
	p->vx = vx;
	p->vy = vy;
	p->isExist = 1;
	p->pnext = NULL;
	p->damage = 10;
	return p;
}

//����BE�ӵ�
list* creatBLACKEBullet(float vx, float vy)  //����һ��ָ��
{
	list* p = new list;	//����ڵ��ڴ�
	p->x = blackE.x + blackE.width / 2;
	p->y = blackE.y + blackE.height;
	p->vx = vx;
	p->vy = vy;
	p->isExist = 1;
	p->pnext = NULL;
	p->damage = 20;
	return p;
}

//����RE�ӵ�
list* creatREDEBullet(float vx,float vy)
{
	list* p = new list;	//����ڵ��ڴ�
	p->x = redE.x + redE.width / 2;
	p->y = redE.y + redE.height;
	p->vx = vx;
	p->vy = vy;
	p->isExist = 1;
	p->pnext = NULL;
	p->damage = 20;
	return p;
}

//��������ӵ�
void clearBullet(list** pplist)
{
	if (*pplist == NULL)
		return;
	list* cur = *pplist;	//currentָ���һ���ڵ�
	while (cur != NULL)
	{
		cur->isExist = 0;
		cur = cur->pnext;
	}
	listRemoveNode(pplist);
}

//��������ӵ�
void clearAllBullet()
{
	clearBullet(&hero_bullet_list);
	clearBullet(&pinkE_bullet_list);
	clearBullet(&blackE_bullet_list); 
	clearBullet(&redE_bullet_list);
}


