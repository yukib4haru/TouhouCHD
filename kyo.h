#ifndef KYO_H  //条件编译：避免多次包含时的重定义问题
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
using namespace std;	//出错一次,未声明命名空间

//C风格宏常量
#define HEIGHT 750  // 游戏画面尺寸
#define WIDTH 750
#define tWIDTH 520
#define PI 3.1415926

//定义角色结构体
struct character
{
	int x, y;
	int width;
	int height;
	int speed;
	int life;
	int new_born_flg;
};

//定义子弹的结构体, 组成链表,使用数组的话内存溢出？
typedef struct bullet	//加上typedefine为结构体bullet定义了一个别名list
{
	float x, y;			//若不为浮点型为整形则射出来的子弹圈不是圆的
	float vx, vy;		//存放数据
	int width;
	int height;
	int damage;
	int isExist;	//判断子弹是否存在
	struct bullet* pnext;
}list;	//起一个别名list,为了使用二级指针表示头结点，表示链表的信息
//或新建一个list结构体		头节点决定链表在哪

#endif



