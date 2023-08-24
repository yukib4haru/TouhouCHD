#include "kyo.h"
#pragma comment(lib,"winmm.lib")

extern character	hero, pinkE, blackE, redE;

extern list* hero_bullet_list; // �ɻ��ӵ������ͷ�ڵ�
extern list* pinkE_bullet_list;
extern list* blackE_bullet_list;	//��Ӧ�Ӹ�ֵ����ھ�β

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


//���� ���Ų˵�BGM
void playMBgmMusic()
{
	mciSendString(_T("close Ebgm"), NULL, 0, NULL);
	mciSendString(_T("close Mbgm"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\menu.mp3 alias Mbgm"), NULL, 0, NULL);
	mciSendString(_T("play Mbgm repeat"), NULL, 0, NULL);
}

//���� ����ս��BGM
void playBgmMusic()
{
	mciSendString(_T("close Ebgm"), NULL, 0, NULL);
	mciSendString(_T("close Mbgm"), NULL, 0, NULL);
	mciSendString(_T("close bgm"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\battle.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("play bgm repeat"), NULL, 0, NULL);
}

//����BGM
void playEBgmMusic()
{
	mciSendString(_T("close Mbgm"), NULL, 0, NULL);
	mciSendString(_T("close bgm"), NULL, 0, NULL);
	mciSendString(_T("close Ebgm"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\end.mp3 alias Ebgm"), NULL, 0, NULL);
	mciSendString(_T("play Ebgm repeat"), NULL, 0, NULL);
}

//ս����Ч
void playHBoomMusic()
{
	mciSendString(_T("open Sound\\boom.wav alias Hboom"), NULL, 0, NULL);
	mciSendString(_T("play Hbomm"), NULL, 0, NULL);
}

//��������Ч
void playBeatenMusic()
{
	mciSendString(_T("close beaten"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\beaten.wav alias beaten"), NULL, 0, NULL);
	mciSendString(_T("play beaten"), NULL, 0, NULL);
}

//������Ч
void playClearMusic()
{
	mciSendString(_T("close clear"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\clear.wav alias clear"), NULL, 0, NULL);
	mciSendString(_T("play clear"), NULL, 0, NULL);
}

//������ ��ը��Ч
void playBoom0Music()
{
	mciSendString(_T("close boom"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\battle.mp3 alias boom"), NULL, 0, NULL);
	mciSendString(_T("play bomm"), NULL, 0, NULL);
}

//�� ��ը��Ч
void playBoom1Music()
{
	mciSendString(_T("close boom1"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\boom1.wav alias boom1"), NULL, 0, NULL);
	mciSendString(_T("play boom1"), NULL, 0, NULL);
}

//�����Ч
void playShootMusic()
{
	mciSendString(_T("close shoot"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\shoot.mp3 alias shoot"), NULL, 0, NULL);
	mciSendString(_T("play shoot"), NULL, 0, NULL);
}

//����ƶ���Ч
void curMoveMusic()
{
	mciSendString(_T("close choose"), NULL, 0, NULL);
	mciSendString(_T("open Sound\\choose.wav alias choose"), NULL, 0, NULL);
	mciSendString(_T("play choose"), NULL, 0, NULL);
}