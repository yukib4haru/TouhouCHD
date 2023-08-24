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

//ԲȦ��Ļ
void pinkEm()
{
	static int dir = 1;//1ǰ�����ֲ���̬������ֻ��ʼ��һ��
	static int cnt = 0;
	int pinkE_reload_cnt = 60;//�����ӵ��ļ���������ֵԽС�����ӵ�Խ��
	int pinkE_fire_num = 20;//�����伸·�ӵ�
	static int step = pinkE.speed;

	if (1 == pinkE.new_born_flg)//ˢ�µĽ�ɫ������x��y������
	{
		pinkE.new_born_flg = 0;
		pinkE.x = rand() % (tWIDTH - pinkE.width);//�������λ��
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

//б���ƶ����ǵ�Ļ
void blackEm()
{
	static int cnt = 0;
	int blackE_reload_cnt = 14;//�����ӵ��ļ���������ֵԽС�����ӵ�Խ��
	int blackE_fire_num = 5;//�����������ӵ�	

	static int step1 = blackE.speed;//step��ʾ�������ٶ�
	static int step2 = blackE.speed;
	if (1 == blackE.new_born_flg)
	{
		blackE.new_born_flg = 0;
		blackE.x = rand() % (tWIDTH - blackE.width);
		blackE.y = 5;
	}
	if (blackE.x < 0 || blackE.x + blackE.width > tWIDTH)
	{
		step1 = -step1;	//����
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
	//�������ܣ���˼��
	if (++cnt % blackE_reload_cnt == 0)
	{
		listPushBack(&blackE_bullet_list, creatBLACKEBullet(0, 7));
	}
	if (cnt > 999999)
		cnt = 0;
}

//���ֹ���ģʽ
void redEm()
{
	static int cnt = 0;
	int pinkE_reload_cnt = 150;//�����ӵ��ļ���������ֵԽС�����ӵ�Խ��
	int pinkE_fire_num = 5;//�����伸·�ӵ�

	static float dist_x = 0, dist_y = 0;	//��������ҵĺ�������
	static float tmp_x = 0, tmp_y = 0;		//����x,y�������ʱ�����������ͷ������
	static float vx = 0, vy = 0;	//�����ٶ�
	float step = 400 / redE.speed;	//�����ٶ�
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
	tmp_x += vx;	//�ƶ�
	tmp_y += vy;
	redE.x = (int)(tmp_x + 0.5);
	redE.y = (int)(tmp_y + 0.5);	//��������ת��������
	//�߽��жϣ����Գ������棬������̫��
	if (redE.x < 0)
		vx = -vx;
	else if (redE.x > tWIDTH - redE.width)
		vx = -vx;
	if (redE.y >= HEIGHT)
		redE.new_born_flg = 1;
}
