#ifndef KYO_H  //�������룺�����ΰ���ʱ���ض�������
#define KYO_H	//?

#include<cstdio> 
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include <graphics.h> 
#include <conio.h>
using namespace std;	//����һ��,δ���������ռ�

//C���곣��
#define HEIGHT 750  // ��Ϸ����ߴ�
#define WIDTH 750
#define tWIDTH 520
#define PI 3.1415926

//�����ɫ�ṹ��
struct character
{
	int x, y;
	int width;
	int height;
	int speed;
	int life;
	int new_born_flg;
};

//�����ӵ��Ľṹ��, �������,ʹ������Ļ��ڴ������
typedef struct bullet	//����typedefineΪ�ṹ��bullet������һ������list
{
	float x, y;			//����Ϊ������Ϊ��������������ӵ�Ȧ����Բ��
	float vx, vy;		//�������
	int width;
	int height;
	int damage;
	int isExist;	//�ж��ӵ��Ƿ����
	struct bullet* pnext;
}list;	//��һ������list,Ϊ��ʹ�ö���ָ���ʾͷ��㣬��ʾ�������Ϣ
//���½�һ��list�ṹ��		ͷ�ڵ������������

#endif



