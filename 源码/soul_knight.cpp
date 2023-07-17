#pragma warning(disable : 4996)
#include<iostream>
#include<cmath>
#include<graphics.h>
#include<time.h>
#include<conio.h>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<stdio.h>
using namespace std;
#define num 5
#define pi 3.141
#define width 30
char movedirection[2];
float xp = 60, yp = 300;
//角色位置坐标
float xe[num], ye[num];
//怪物位置坐标
double xbsbu[8] = { 11111 ,11111 ,11111 ,11111 ,11111 ,11111,11111,11111 };
double ybsbu[8] = { 11111 ,11111 ,11111 ,11111 ,11111 ,11111,11111,11111 };
double xeb[num], yeb[num];
double xb = -1000, yb = -1000;
//子弹坐标
char attack;
int R;
//子弹方向(离玩家最近)
int m, n;
//子弹位移时XY移动量
int me[num], ne[num], mb[8], nb[8];
int p = 0;
int weapon0 = 0;
//武器一具体为何
int weapon1 = 1;
//武器二具体是何
int weaponstate = 0;
//主副手武器状态

//敌人
class Enemy {
public:
	int getlife() { return life; }
	//怪物生命状态，1为存活，0为死亡
	void setlife(int a) { life = a; }
	int getblood() { return blood; }
	//怪物血量
	void setblood(int b) { blood = b; }
	Enemy() { blood = 20; }
	void damage();
	//伤害函数
	void setboss() {
		boss = 1;
		blood = 200;
	}
	//生成boss
	void offboss() {
		boss = 0;
	}
	bool getboss() {
		return boss;
	}
	//boss独用状态
private:
	int blood;
	int life = 1;
	bool boss = false;
};

//游戏数据
IMAGE player, enermy1[num], enermy2[num];
IMAGE bullet1[6], bullet2, boss1, boss2;
Enemy enemies[num];
//怪物数组
int k;
//当前关卡
int mapx, mapy;
//人物坐标在map数组里的下标
IMAGE knight11, knight12, knight21, knight22, knight13, hknight11, hknight12, hknight21, hknight22;
//玩家各状态图片
#define BLOCK_SIZE 30
#define HEIGHT 20
#define WIDTH 36
int Temp[HEIGHT][WIDTH];

//地图数组，用二维数组将地图分格表示以便绘制
int Blocks0[HEIGHT][WIDTH] =
{

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,0,0,0,4,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,4,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,4,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,4,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,0,
	2,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,4,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,0,
	2,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,0,0,0,4,0,0,0,0,0,0,0,0,0,
	2,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,
	2,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	2,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};
//关卡一


int Blocks1[HEIGHT][WIDTH] =
{

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
	2,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};
//关卡二


int Blocks2[HEIGHT][WIDTH] =
{

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};
//关卡三


int Blocks3[HEIGHT][WIDTH] =
{

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,
	2,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,2,
	2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};
//关卡四


int Blocks4[HEIGHT][WIDTH] =
{

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,
	1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};
//关卡五


int Blocksboss[HEIGHT][WIDTH] =
{

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
	1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

};
//关卡六
int flag = 0;
//判定游戏结束返回主界面
int flag2 = 0;
int winflag = 0;
int flag3 = 0;
bool flagl0 = 0;
//第一关初始化状态
bool flagl1 = 1;
//第二关初始化状态
bool flagl2 = 1;
//第三关初始化状态
bool flagl3 = 1;
//第四关初始化状态
bool flagl4 = 1;
//boss关初始化状态
bool flagl5 = 1;
//以上状态用于判断各关卡状态，以便切换关卡时初始化怪物数组
int* flag2ptr = &flag2;
int* winflagptr = &winflag;
int* flag3ptr = &flag3;



//打印地图
void printmap() {
	IMAGE wall, closewall, fl, wood, fl2;
	//fl 0 wall 1 closewall 2 wood 3 fl2 4
	loadimage(&wall, _T("./冰墙.png"), 30, 30);
	loadimage(&closewall, _T("./左右门（开）.png"), 30, 30);
	loadimage(&fl, _T("./冰地板.png"), 30, 30);
	loadimage(&wood, _T("./木箱.png"), 30, 30);
	loadimage(&fl2, _T("./冰地板2.png"), 30, 30);
	//加载图片

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 36; j++)
		{
			//以k表示关卡数用以绘制地图及初始化
			switch (k) {
			case 0:Temp[i][j] = Blocks0[i][j];
			{
				if (flagl0) {
					for (int i = 0; i <= num - 1; i++)
					{
						enemies[i].setblood(20);
						enemies[i].setlife(1);
					}
					flagl0 = 0;
					//第一关初始化完毕
					flagl5 = 1;
					//boss关进入待初始化状态
				}
				break;
			}
			//数组值为0时绘制地板
			case 1:Temp[i][j] = Blocks1[i][j];
			{
				if (flagl1) {
					for (int i = 0; i <= num - 1; i++)
					{
						enemies[i].setblood(20);
						enemies[i].setlife(1);
					}
					flagl1 = 0;
					//第二关初始化完毕
					flagl0 = 1;
					//第一关进入待初始化状态
				}
				break;
			}
			case 2:Temp[i][j] = Blocks2[i][j];
			{
				if (flagl2) {
					for (int i = 0; i <= num - 1; i++)
					{
						enemies[i].setblood(20);
						enemies[i].setlife(1);
					}
					flagl2 = 0;
					//第三关初始化完毕
					flagl1 = 1;
					//第二关进入待初始化状态
				}
				break;
			}
			case 3:Temp[i][j] = Blocks3[i][j];
			{
				if (flagl3) {
					for (int i = 0; i <= num - 1; i++)
					{
						enemies[i].setblood(20);
						enemies[i].setlife(1);
					}
					flagl3 = 0;
					//第四关初始化完毕
					flagl2 = 1;
					//第三关进入待初始化状态
				}
				break;
			}
			case 4:Temp[i][j] = Blocks4[i][j];
			{
				if (flagl4) {
					for (int i = 0; i <= num - 1; i++)
					{
						enemies[i].setblood(20);
						enemies[i].setlife(1);
					}
					flagl4 = 0;
					//第五关初始化完毕
					flagl3 = 1;
					//第四关进入待初始化状态
				}
				break;
			}
			case 5:Temp[i][j] = Blocksboss[i][j];
			{
				if (flagl5) {
					for (int i = 0; i < num; i++) {
						xeb[i] = 10000;
						yeb[i] = 10000;
					}
					enemies[0].setboss();
					enemies[0].setlife(1);
					for (int i = 1; i <= num - 1; i++)
					{
						enemies[i].setblood(0);
						enemies[i].setlife(0);
					}
					flagl5 = 0;
					//boss关初始化完毕
					flagl4 = 1;
					//第五关进入待初始化状态
				}
				break;
			}
			}
			switch (Temp[i][j])
			{
			default:
				break;

			case 0:
				putimage(j * BLOCK_SIZE, i * BLOCK_SIZE, &fl);
				break;
			case 1:
				putimage(j * BLOCK_SIZE, i * BLOCK_SIZE, &wall);
				break;
			case 2:
				putimage(j * BLOCK_SIZE, i * BLOCK_SIZE, &closewall);
				break;
			case 3:
				putimage(j * BLOCK_SIZE, i * BLOCK_SIZE, &wood);
				break;
			case 4:
				putimage(j * BLOCK_SIZE, i * BLOCK_SIZE, &fl2);
				break;
			}
			//遍历数组，在地图对应坐标绘制方块

		}
	}

}



//玩家类
class Player {
public:
	int p_damage[6] = { 5,5,7,10,10,20 };
	//玩家伤害，与武器一一对应
	int p_energy[6] = { 20,10,20,20,10,15 };
	//武器蓝耗，与武器一一对应
	Player() {};
	void printAttribute(Player& knight);
	void attributeUp(Player& knight);
	//属性升级
	void weaponstore();
	//武器商店界面
	void Energydiscrease() {
		//判定双手武器状态
		if (weaponstate == 0)
		{
			EnergyValue -= p_energy[weapon0];
		}
		else if (weaponstate == 1)
		{
			EnergyValue -= p_energy[weapon1];
		}
	}
	//造成伤害
	void Energyincrease() {
		if (EnergyValue <= 270)
			EnergyValue += 30;
		else EnergyValue = 300;
	}
	//击中怪物后的蓝量增加函数，上限为300
	int getEnergy() { return EnergyValue; }
	void setEnergy(int a) { EnergyValue = a; }
	int getShieldValue() { return ShieldValue; }
	void setShieldValue(int a) { ShieldValue = a; }
	void ShieldDiscrease() { ShieldValue -= 2; }
	void ShieldIncrease() { ShieldValue++; }
	void ShieldBreak() { ShieldValue = 0; }
	int getblood() { return blood; }
	void setblood(int a) { blood = a; }
	void bloodDicrease() { blood -= 2; }
	int getcoins() { return coins; }
	void setcoins(int a) { coins -= a; }
	void Setcoins(int a) { coins = a; }
	void coinsDicrease() { coins--; }
	void coinsIncrease() { coins += 5; }
	~Player() {};
private:
	int blood = 5;
	//血量值
	int ShieldValue = 5;
	//护盾值
	int skillCD = 15;
	//CD
	int EnergyValue = 200;
	//蓝条
	int coins = 10;
	//金币
}knight;



//武器商店
void Player::weaponstore()
{
	cleardevice();
	setbkcolor(BLACK);

	IMAGE _weapon1, _weapon2, _weapon3, _weapon4, _weapon5, _weapon6;
	IMAGE image(140, 50);
	loadimage(&_weapon1, _T("./破旧手枪.png"), 140, 140);
	loadimage(&_weapon2, _T("./火焰之鹰.png"), 140, 140);
	loadimage(&_weapon3, _T("./弹射冲锋枪.png"), 140, 140);
	loadimage(&_weapon4, _T("./冲锋枪M2.png"), 140, 140);
	loadimage(&_weapon5, _T("./仲裁者.png"), 140, 140);
	loadimage(&_weapon6, _T("./火焰机枪.png"), 140, 140);
	settextstyle(20, 0, _T("黑体"));
	putimage(20, 200, &_weapon1);
	outtextxy(20, 300, _T("coins:10"));
	putimage(200, 200, &_weapon2);
	outtextxy(200, 300, _T("coins:30"));
	putimage(380, 200, &_weapon3);
	outtextxy(380, 300, _T("coins:50"));
	putimage(560, 200, &_weapon4);
	outtextxy(560, 300, _T("coins:70"));
	putimage(740, 200, &_weapon5);
	outtextxy(740, 300, _T("coins:100"));
	putimage(920, 200, &_weapon6);
	outtextxy(920, 300, _T("coins:200"));
	TCHAR coin[10];
	_stprintf(coin, _T("%d"), coins);
	outtextxy(700, 40, _T("coins: "));
	outtextxy(900, 40, coin);
	SetWorkingImage(&image);
	setbkcolor(WHITE);
	settextcolor(BLUE);
	outtextxy(60, 10, _T("BUY"));
	SetWorkingImage();
	putimage(20, 400, &image);
	putimage(200, 400, &image);
	putimage(380, 400, &image);
	putimage(560, 400, &image);
	putimage(740, 400, &image);
	putimage(920, 400, &image);

	if (weaponstate == 0)
	{
		settextstyle(40, 0, _T("黑体"));
		outtextxy(20, 20, _T("weapon 1"));
	}
	//主手武器
	else if (weaponstate == 1)
	{
		settextstyle(40, 0, _T("黑体"));
		outtextxy(20, 20, _T("weapon 2"));
	}
	//副手武器
	while (!_kbhit())
	{
		while (MouseHit())
		{
			MOUSEMSG m;
			m = GetMouseMsg();

			if ((m.x > 20) && (m.x < 160) && (m.y < 450) && (m.y > 400) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.getcoins() >= 10)
				{
					knight.setcoins(10);
				}
				if (weaponstate == 0)
				{
					weapon0 = 0;
				}
				else if (weaponstate == 1)
				{
					weapon1 = 0;
				}
				knight.weaponstore();
			}
			//将手上武器切换为武器1
			if ((m.x > 200) && (m.x < 340) && (m.y < 450) && (m.y > 400) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.getcoins() >= 30)
				{
					knight.setcoins(30);
				}
				if (weaponstate == 0)
				{
					weapon0 = 1;
				}
				else if (weaponstate == 1)
				{
					weapon1 = 1;
				}
				knight.weaponstore();
			}
			//将手上武器切换为武器2
			if ((m.x > 380) && (m.x < 520) && (m.y < 450) && (m.y > 400) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.getcoins() >= 50)
				{
					knight.setcoins(50);
				}
				if (weaponstate == 0)
				{
					weapon0 = 2;
				}
				else if (weaponstate == 1)
				{
					weapon1 = 2;
				}
				knight.weaponstore();
			}
			//将手上武器切换为武器3
			if ((m.x > 560) && (m.x < 700) && (m.y < 450) && (m.y > 400) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.getcoins() >= 70)
				{
					knight.setcoins(70);
				}
				if (weaponstate == 0)
				{
					weapon0 = 3;
				}
				else if (weaponstate == 1)
				{
					weapon1 = 3;
				}
				knight.weaponstore();
			}
			//将手上武器切换为武器4
			if ((m.x > 740) && (m.x < 880) && (m.y < 450) && (m.y > 400) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.getcoins() >= 100)
				{
					knight.setcoins(100);
				}
				if (weaponstate == 0)
				{
					weapon0 = 4;
				}
				else if (weaponstate == 1)
				{
					weapon1 = 4;
				}
				knight.weaponstore();
			}
			//将手上武器切换为武器5
			if ((m.x > 920) && (m.x < 1060) && (m.y < 450) && (m.y > 400) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.getcoins() >= 200)
				{
					knight.setcoins(200);
				}
				if (weaponstate == 0)
				{
					weapon0 = 5;
				}
				else if (weaponstate == 1)
				{
					weapon1 = 5;
				}
				knight.weaponstore();
			}
			//将手上武器切换为武器6
		}
	}

}




//属性升级界面
void Player::printAttribute(Player& knight)
{
	//血条显示
	settextstyle(20, 0, _T("黑体"));
	setfillcolor(RED);
	settextcolor(RED);
	fillrectangle(30, 30, 120, 60);
	//蓝条
	setfillcolor(BLUE);
	settextcolor(BLUE);
	fillrectangle(30, 90, 120, 120);
	//护盾
	setfillcolor(RGB(128, 128, 128));
	settextcolor(RGB(128, 128, 128));
	fillrectangle(30, 60, 120, 90);
	TCHAR bl[10], shield[10], Energy[10], CD[10];
	_stprintf(bl, _T("%d/7"), blood);
	_stprintf(shield, _T("%d/7"), ShieldValue);
	_stprintf(Energy, _T("%d/300"), EnergyValue);
	_stprintf(CD, _T("%d/15"), skillCD);
	settextcolor(GREEN);
	outtextxy(35, 35, bl);
	outtextxy(35, 65, shield);
	outtextxy(35, 95, Energy);

}



void Player::attributeUp(Player& knight)
//属性升级函数
{


	cleardevice();
	setbkcolor(BLACK);

	IMAGE image1;
	IMAGE image2(100, 100);

	loadimage(&image1, _T("./骑士正(白底图).png"), 400, 400);
	putimage(640, 20, &image1);
	settextstyle(40, 0, _T("黑体"));
	setfillcolor(RED);
	settextcolor(RED);
	fillroundrect(100, 10, 480, 140, 60, 40);
	outtextxy(60, 60, _T("HP"));
	setfillcolor(RGB(128, 128, 128));
	settextcolor(RGB(128, 128, 128));
	fillroundrect(100, 160, 480, 290, 60, 40);
	outtextxy(60, 210, _T("s"));
	setfillcolor(BLUE);
	settextcolor(BLUE);
	fillroundrect(100, 310, 480, 440, 60, 40);
	outtextxy(60, 360, _T("MP"));
	setfillcolor(WHITE);
	settextcolor(WHITE);
	fillroundrect(100, 460, 480, 590, 60, 40);
	outtextxy(60, 510, _T("CD"));
	setfillcolor(RGB(128, 128, 0));
	fillroundrect(640, 450, 1040, 550, 100, 80);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(155, 40, 100));
	settextstyle(60, 0, _T("宋体"));
	outtextxy(770, 470, _T("Enter"));
	settextcolor(BLACK);
	TCHAR bl[10], shield[10], Energy[10], CD[10], coin[10];
	_stprintf(bl, _T("%d/7"), blood);
	_stprintf(shield, _T("%d/7"), ShieldValue);
	_stprintf(Energy, _T("%d/300"), EnergyValue);
	_stprintf(CD, _T("%d/15"), skillCD);
	_stprintf(coin, _T("%d"), coins);
	//各状态条绘制
	outtextxy(210, 40, bl);
	outtextxy(210, 190, shield);
	outtextxy(210, 340, Energy);
	outtextxy(210, 490, CD);
	outtextxy(700, 40, _T("coins: "));
	outtextxy(900, 40, coin);
	SetWorkingImage(&image2);
	//a加号图形设置
	setfillcolor(RGB(123, 54, 23));
	fillcircle(50, 50, 50);
	line(5, 50, 95, 50);
	line(50, 5, 50, 95);
	SetWorkingImage();
	putimage(520, 50, &image2);
	putimage(520, 200, &image2);
	putimage(520, 350, &image2);
	putimage(520, 500, &image2);

	while (!_kbhit())
	{
		while (MouseHit()) {
			MOUSEMSG m;
			m = GetMouseMsg();

			if ((m.x > 520) && (m.x < 620) && (m.y < 150) && (m.y > 50) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.coins > 0)
				{
					if (knight.blood < 7)
					{
						knight.blood++;
						knight.coinsDicrease();
					}
				}
				//提升血量
				cleardevice();
				setbkcolor(BLACK);
				IMAGE image1;
				IMAGE image2(100, 100);
				loadimage(&image1, _T("./骑士正(白底图).png"), 400, 400);
				putimage(640, 20, &image1);
				settextstyle(40, 0, _T("黑体"));
				setfillcolor(RED);
				settextcolor(RED);
				fillroundrect(100, 10, 480, 140, 60, 40);
				outtextxy(60, 60, _T("HP"));
				setfillcolor(RGB(128, 128, 128));
				settextcolor(RGB(128, 128, 128));
				fillroundrect(100, 160, 480, 290, 60, 40);
				outtextxy(60, 210, _T("s"));
				setfillcolor(BLUE);
				settextcolor(BLUE);
				fillroundrect(100, 310, 480, 440, 60, 40);
				outtextxy(60, 360, _T("MP"));
				setfillcolor(WHITE);
				settextcolor(WHITE);
				fillroundrect(100, 460, 480, 590, 60, 40);
				outtextxy(60, 510, _T("CD"));
				setfillcolor(RGB(128, 128, 0));
				fillroundrect(640, 450, 1040, 550, 100, 80);
				setbkmode(TRANSPARENT);
				settextcolor(RGB(155, 40, 100));
				settextstyle(60, 0, _T("宋体"));
				outtextxy(770, 470, _T("Enter"));
				settextcolor(BLACK);
				TCHAR bl[10], shield[10], Energy[10], CD[10], coin[10];
				_stprintf(bl, _T("%d/7"), blood);
				_stprintf(shield, _T("%d/7"), ShieldValue);
				_stprintf(Energy, _T("%d/300"), EnergyValue);
				_stprintf(CD, _T("%d/15"), skillCD);
				_stprintf(coin, _T("%d"), coins);
				outtextxy(210, 40, bl);
				outtextxy(210, 190, shield);
				outtextxy(210, 340, Energy);
				outtextxy(210, 490, CD);
				outtextxy(700, 40, _T("coins: "));
				outtextxy(900, 40, coin);
				SetWorkingImage(&image2);
				//a加号图形设置
				setfillcolor(RGB(123, 54, 23));
				fillcircle(50, 50, 50);
				line(5, 50, 95, 50);
				line(50, 5, 50, 95);
				SetWorkingImage();
				putimage(520, 50, &image2);
				putimage(520, 200, &image2);
				putimage(520, 350, &image2);
				putimage(520, 500, &image2);
				break;
			}
			//重新绘制图像
			if ((m.x > 520) && (m.x < 620) && (m.y < 300) && (m.y > 200) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.coins > 0)
				{
					if (knight.ShieldValue < 7)
					{
						knight.ShieldValue += 1;
						knight.coinsDicrease();
					}
				}
				//提升护盾值
				cleardevice();
				setbkcolor(BLACK);
				IMAGE image1;
				IMAGE image2(100, 100);
				loadimage(&image1, _T("./骑士正(白底图).png"), 400, 400);
				putimage(640, 20, &image1);
				settextstyle(40, 0, _T("黑体"));
				setfillcolor(RED);
				settextcolor(RED);
				fillroundrect(100, 10, 480, 140, 60, 40);
				outtextxy(60, 60, _T("HP"));
				setfillcolor(RGB(128, 128, 128));
				settextcolor(RGB(128, 128, 128));
				fillroundrect(100, 160, 480, 290, 60, 40);
				outtextxy(60, 210, _T("s"));
				setfillcolor(BLUE);
				settextcolor(BLUE);
				fillroundrect(100, 310, 480, 440, 60, 40);
				outtextxy(60, 360, _T("MP"));
				setfillcolor(WHITE);
				settextcolor(WHITE);
				fillroundrect(100, 460, 480, 590, 60, 40);
				outtextxy(60, 510, _T("CD"));
				setfillcolor(RGB(128, 128, 0));
				fillroundrect(640, 450, 1040, 550, 100, 80);
				setbkmode(TRANSPARENT);
				settextcolor(RGB(155, 40, 100));
				settextstyle(60, 0, _T("宋体"));
				outtextxy(770, 470, _T("Enter"));
				settextcolor(BLACK);
				TCHAR bl[10], shield[10], Energy[10], CD[10], coin[10];
				_stprintf(bl, _T("%d/7"), blood);
				_stprintf(shield, _T("%d/7"), ShieldValue);
				_stprintf(Energy, _T("%d/300"), EnergyValue);
				_stprintf(CD, _T("%d/15"), skillCD);
				_stprintf(coin, _T("%d"), coins);
				outtextxy(210, 40, bl);
				outtextxy(210, 190, shield);
				outtextxy(210, 340, Energy);
				outtextxy(210, 490, CD);
				outtextxy(700, 40, _T("coins: "));
				outtextxy(900, 40, coin);
				SetWorkingImage(&image2);//a加号图形设置
				setfillcolor(RGB(123, 54, 23));
				fillcircle(50, 50, 50);
				line(5, 50, 95, 50);
				line(50, 5, 50, 95);
				SetWorkingImage();
				putimage(520, 50, &image2);
				putimage(520, 200, &image2);
				putimage(520, 350, &image2);
				putimage(520, 500, &image2);
				break;
			}
			//重新绘制图像
			if ((m.x > 520) && (m.x < 620) && (m.y < 450) && (m.y > 350) && (m.uMsg == WM_LBUTTONDOWN))
			{
				if (knight.coins > 0) {
					if (knight.EnergyValue <= 275)
					{
						knight.EnergyValue += 25;
						knight.coinsDicrease();
					}
					else if (knight.EnergyValue > 275 && knight.EnergyValue < 300)
					{
						knight.EnergyValue = 300;
						knight.coinsDicrease();
					}
				}
				//提升能量值
				cleardevice();
				setbkcolor(BLACK);
				IMAGE image1;
				IMAGE image2(100, 100);
				loadimage(&image1, _T("./骑士正(白底图).png"), 400, 400);
				putimage(640, 20, &image1);
				settextstyle(40, 0, _T("黑体"));
				setfillcolor(RED);
				settextcolor(RED);
				fillroundrect(100, 10, 480, 140, 60, 40);
				outtextxy(60, 60, _T("HP"));
				setfillcolor(RGB(128, 128, 128));
				settextcolor(RGB(128, 128, 128));
				fillroundrect(100, 160, 480, 290, 60, 40);
				outtextxy(60, 210, _T("s"));
				setfillcolor(BLUE);
				settextcolor(BLUE);
				fillroundrect(100, 310, 480, 440, 60, 40);
				outtextxy(60, 360, _T("MP"));
				setfillcolor(WHITE);
				settextcolor(WHITE);
				fillroundrect(100, 460, 480, 590, 60, 40);
				outtextxy(60, 510, _T("CD"));
				setfillcolor(RGB(128, 128, 0));
				fillroundrect(640, 450, 1040, 550, 100, 80);
				setbkmode(TRANSPARENT);
				settextcolor(RGB(155, 40, 100));
				settextstyle(60, 0, _T("宋体"));
				outtextxy(770, 470, _T("Enter"));
				settextcolor(BLACK);
				TCHAR bl[10], shield[10], Energy[10], CD[10], coin[10];
				_stprintf(bl, _T("%d/7"), blood);
				_stprintf(shield, _T("%d/7"), ShieldValue);
				_stprintf(Energy, _T("%d/300"), EnergyValue);
				_stprintf(CD, _T("%d/15"), skillCD);
				_stprintf(coin, _T("%d"), coins);
				outtextxy(210, 40, bl);
				outtextxy(210, 190, shield);
				outtextxy(210, 340, Energy);
				outtextxy(210, 490, CD);
				outtextxy(700, 40, _T("coins: "));
				outtextxy(900, 40, coin);
				SetWorkingImage(&image2);//a加号图形设置
				setfillcolor(RGB(123, 54, 23));
				fillcircle(50, 50, 50);
				line(5, 50, 95, 50);
				line(50, 5, 50, 95);
				SetWorkingImage();
				putimage(520, 50, &image2);
				putimage(520, 200, &image2);
				putimage(520, 350, &image2);
				putimage(520, 500, &image2);
				break;
			}
			//重新绘制图像
			if ((m.x > 520) && (m.x < 620) && (m.y < 600) && (m.y > 500) && (m.uMsg == WM_LBUTTONDOWN))
			{
				knight.skillCD--;
				//减少技能CD
				knight.coinsDicrease();
				cleardevice();
				setbkcolor(BLACK);
				IMAGE image1;
				IMAGE image2(100, 100);
				loadimage(&image1, _T("./骑士正(白底图).png"), 400, 400);
				putimage(640, 20, &image1);
				settextstyle(40, 0, _T("黑体"));
				setfillcolor(RED);
				settextcolor(RED);
				fillroundrect(100, 10, 480, 140, 60, 40);
				outtextxy(60, 60, _T("HP"));
				setfillcolor(RGB(128, 128, 128));
				settextcolor(RGB(128, 128, 128));
				fillroundrect(100, 160, 480, 290, 60, 40);
				outtextxy(60, 210, _T("s"));
				setfillcolor(BLUE);
				settextcolor(BLUE);
				fillroundrect(100, 310, 480, 440, 60, 40);
				outtextxy(60, 360, _T("MP"));
				setfillcolor(WHITE);
				settextcolor(WHITE);
				fillroundrect(100, 460, 480, 590, 60, 40);
				outtextxy(60, 510, _T("CD"));
				setfillcolor(RGB(128, 128, 0));
				fillroundrect(640, 450, 1040, 550, 100, 80);
				setbkmode(TRANSPARENT);
				settextcolor(RGB(155, 40, 100));
				settextstyle(60, 0, _T("宋体"));
				outtextxy(770, 470, _T("Enter"));
				settextcolor(BLACK);
				TCHAR bl[10], shield[10], Energy[10], CD[10], coin[10];
				_stprintf(bl, _T("%d/7"), blood);
				_stprintf(shield, _T("%d/7"), ShieldValue);
				_stprintf(Energy, _T("%d/300"), EnergyValue);
				_stprintf(CD, _T("%d/15"), skillCD);
				_stprintf(coin, _T("%d"), coins);
				outtextxy(210, 40, bl);
				outtextxy(210, 190, shield);
				outtextxy(210, 340, Energy);
				outtextxy(210, 490, CD);
				outtextxy(700, 40, _T("coins: "));
				outtextxy(900, 40, coin);
				SetWorkingImage(&image2);//a加号图形设置
				setfillcolor(RGB(123, 54, 23));
				fillcircle(50, 50, 50);
				line(5, 50, 95, 50);
				line(50, 5, 50, 95);
				SetWorkingImage();
				putimage(520, 50, &image2);
				putimage(520, 200, &image2);
				putimage(520, 350, &image2);
				putimage(520, 500, &image2);
				break;
			}
			//重新绘制图像
		}
	}
}




//初始界面模块
void chushijiemian()
{
	initgraph(1080, 600);
	IMAGE image1;
	loadimage(NULL, _T("./17148b173dbb3499.jpg"), 1080, 600);
	setfillcolor(RGB(128, 64, 0));
	fillroundrect(20, 320, 280, 420, 60, 40);
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(40, 0, _T(""));
	RECT r1 = { 20, 320, 280, 420 };
	drawtext(_T("开始游戏"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	fillroundrect(320, 320, 580, 420, 60, 40);
	RECT r2 = { 320, 320, 580, 420 };
	drawtext(_T("退出游戏"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	ExMessage m;


	while (1) {
		//鼠标按下时判断坐标是否与选择框重合
		m = getmessage(EM_MOUSE);

		if ((m.message == WM_LBUTTONDOWN) && (m.x <= 280) && (m.x >= 20) && (m.y >= 320) && (m.y <= 420)) {
			break;
		}
		else if ((m.message == WM_LBUTTONDOWN) && (m.x <= 580) && (m.x >= 320) && (m.y >= 320) && (m.y <= 420)) {
			flag = 1;
			break;
		}
		else if (_kbhit()) {
			char c = _getch();
			if (c == 27) {
				flag = 1;
				break;
			}
		}
	}
}




//冒险家协会模块 
void showHomeMap() {
	IMAGE image_bk;
	initgraph(1080, 600);
	setfillcolor(BLACK);
	int xp = 350;
	int yp = 280;
	//骑士初始坐标
	loadimage(&hknight12, _T("./骑士正(白底图)大.png"));
	loadimage(&hknight11, _T("./骑士正(遮罩图)大.png"));
	loadimage(&hknight22, _T("./骑士反(白底图)大.png"));
	loadimage(&hknight21, _T("./骑士反(遮罩图)大.png"));
	loadimage(&image_bk, _T("./家.png"), 1080, 600);
	BeginBatchDraw();
	putimage(0, 0, &image_bk);
	putimage(xp, yp, &hknight11, NOTSRCERASE);
	putimage(xp, yp, &hknight12, SRCINVERT);
	EndBatchDraw();
	int flag1 = 0;
	//属性升级
	int flag2 = 0;
	int flag3 = 0;
	//武器购买
acc:if (flag1) 
{
	knight.attributeUp(knight);
	loadimage(&image_bk, _T("./家.png"), 1080, 600);
	putimage(0, 0, &image_bk);
	putimage(xp, yp, &hknight11, NOTSRCERASE);
	putimage(xp, yp, &hknight12, SRCINVERT);
}
ws:if (flag3) 
{
knight.weaponstore();
loadimage(&image_bk, _T("./家.png"), 1080, 600);
putimage(0, 0, &image_bk);
putimage(xp, yp, &hknight11, NOTSRCERASE);
putimage(xp, yp, &hknight12, SRCINVERT);
}
loadimage(&image_bk, _T("./家.png"), 1080, 600);
putimage(0, 0, &image_bk);
putimage(xp, yp, &hknight11, NOTSRCERASE);
putimage(xp, yp, &hknight12, SRCINVERT);

while (1) {

	line(725, 0, 725, 125);
	line(535, 0, 535, 125);

	*flag2ptr = 0;
	char input = _getch();
	if (input == 27) {
		*flag2ptr = 1;
		break;
	}
	else if ((input == ' ') && (xp >= 535) && (xp <= 725) && (yp <= 125) && (yp >= 0)) {
		break;
	}
	//进入游戏
	else if ((input == 'c')) {
		flag1 = 1;
		goto acc;
	}
	//转到属性升级
	else if ((input == 'v')) {
		flag3 = 1;
		goto ws;
	}
	//转到武器购买
	else if (input == 'e')
	{
		weaponstate = 1 - weaponstate;
	}
	//切换武器
	else if ((input == 'a') && (xp >= 0))
	{
		BeginBatchDraw();

		loadimage(NULL, _T("./家.png"), 1080, 600);
		xp = xp - 10;
		putimage(xp, yp, &hknight21, NOTSRCERASE);
		putimage(xp, yp, &hknight22, SRCINVERT);
		EndBatchDraw();
	}
	else if ((input == 'd') && (xp <= 1000))
	{
		BeginBatchDraw();

		loadimage(NULL, _T("./家.png"), 1080, 600);
		xp = xp + 10;
		putimage(xp, yp, &hknight11, NOTSRCERASE);
		putimage(xp, yp, &hknight12, SRCINVERT);
		EndBatchDraw();
	}
	else if ((input == 'w') && (yp >= 10))
	{
		BeginBatchDraw();

		loadimage(NULL, _T("./家.png"), 1080, 600);
		yp = yp - 10;
		putimage(xp, yp, &hknight21, NOTSRCERASE);
		putimage(xp, yp, &hknight22, SRCINVERT);
		EndBatchDraw();
	}
	
	else if ((input == 's') && (yp <= 520))
	{
		BeginBatchDraw();

		loadimage(NULL, _T("./家.png"), 1080, 600);
		yp = yp + 10;
		putimage(xp, yp, &hknight11, NOTSRCERASE);
		putimage(xp, yp, &hknight12, SRCINVERT);
		EndBatchDraw();
	}
	//按下wasd后坐标移动并重新绘制达到移动效果

  }

}



//对敌人造成的伤害的定义
void Enemy::damage()
{
	if (weaponstate == 0)
		blood -= knight.p_damage[weapon0];
	else if (weaponstate == 1)
		blood -= knight.p_damage[weapon1];
}



//返回与玩家最近的怪物的数组下标
int BulletDirection()
{
	int R = 0;
	unsigned long distance[num];

	for (int i = 0; i < num; i++)
	{
		if (enemies[i].getlife() && (xe[i] >= 0) && (xe[i] <= 1080) && (ye[i] >= 0) && (ye[i] <= 600))
			distance[i] = pow(xe[i] - xp, 2) + pow(ye[i] - yp, 2);
		//以两点x.y之差的平方代表距离
		else distance[i] = 20000000;
		unsigned long* ptr = distance;
		if ((*(ptr + R) >= *(ptr + i)) && (enemies[i].getlife()) && (xe[i] >= 0) && (xe[i] <= 1080) && (ye[i] >= 0) && (ye[i] <= 600))
			R = i;
	}
	return R;

}



//角色移动模块
void MoveWithInput()
{
	if (_kbhit())
	{
		movedirection[0] = _getch();
		if (movedirection[0] == 'a')
		{
			xp -= 30;
			mapx = xp / 30;
			mapy = yp / 30;
			if (Temp[mapy][mapx] != 0)
				xp += 30;
			movedirection[1] = movedirection[0];
			int o = BulletDirection();
			if ((enemies[o].getblood() > 0) && (xe[o] >= 0) && (xe[o] <= 1080) && (ye[o] >= 0) && (ye[o] <= 600)) {
				R = BulletDirection();

				m = (xe[R] + 25 - xp) / abs(xe[R] + 25 - xp) * 40;
				n = (ye[R] + 25 - yp) / abs(ye[R] + 25 - yp) * 40 * ((abs(ye[R] + 25 - yp) / abs(xe[R] + 25 - xp)));
			}
		}
		//向左移动
		else if (movedirection[0] == 'd')
		{
			xp += 30;
			mapx = xp / 30;
			mapy = yp / 30;
			if (Temp[mapy][mapx] != 0)
				xp -= 30;
			movedirection[1] = movedirection[0];
			int o = BulletDirection();
			if ((enemies[o].getblood() > 0) && (xe[o] >= 0) && (xe[o] <= 1080) && (ye[o] >= 0) && (ye[o] <= 600)) {
				R = BulletDirection();

				m = (xe[R] + 25 - xp) / abs(xe[R] + 25 - xp) * 40;
				n = (ye[R] + 25 - yp) / abs(ye[R] + 25 - yp) * 40 * ((abs(ye[R] + 25 - yp) / abs(xe[R] + 25 - xp)));
			}
		}
		//向右移动
		else if (movedirection[0] == 'w')
		{
			yp -= 30;
			mapx = xp / 30;
			mapy = yp / 30;
			if (Temp[mapy][mapx] != 0)
				yp += 30;
			movedirection[1] = movedirection[0];
			int o = BulletDirection();
			if ((enemies[o].getblood() > 0) && (xe[o] >= 0) && (xe[o] <= 1080) && (ye[o] >= 0) && (ye[o] <= 600)) {
				R = BulletDirection();

				m = (xe[R] + 25 - xp) / abs(xe[R] + 25 - xp) * 40;
				n = (ye[R] + 25 - yp) / abs(ye[R] + 25 - yp) * 40 * ((abs(ye[R] + 25 - yp) / abs(xe[R] + 25 - xp)));
			}
		}
		//向上移动
		else if (movedirection[0] == 's')
		{
			yp += 30;
			mapx = xp / 30;
			mapy = yp / 30;
			if (Temp[mapy][mapx] != 0)
				yp -= 30;
			movedirection[1] = movedirection[0];
			int o = BulletDirection();
			if ((enemies[o].getblood() > 0) && (xe[o] >= 0) && (xe[o] <= 1080) && (ye[o] >= 0) && (ye[o] <= 600)) {
				R = BulletDirection();

				m = (xe[R] + 25 - xp) / abs(xe[R] + 25 - xp) * 40;
				n = (ye[R] + 25 - yp) / abs(ye[R] + 25 - yp) * 40 * ((abs(ye[R] + 25 - yp) / abs(xe[R] + 25 - xp)));
			}
		}
		//向下移动
		else if (movedirection[0] == 'k') {
			circle(xp, yp, 50);
			FlushBatchDraw();
			for (int i = 0; i < num; i++) {
				double distance[num];
				distance[i] = pow(xe[i] - xp, 2) + pow(ye[i] - yp, 2);
				if (distance[i] <= 2500) {
					enemies[i].damage();
					knight.Energyincrease();

				}
			}
		}
		//近战攻击
		else if (movedirection[0] == 'j')
		{
			if (knight.getEnergy() >= 5)
			{
				knight.Energydiscrease();
				xb = xp;
				yb = yp;

				int o = BulletDirection();
				if ((enemies[o].getblood() > 0) && (xe[o] >= 0) && (xe[o] <= 1080) && (ye[o] >= 0) && (ye[o] <= 600)) {
					R = BulletDirection();

					m = (xe[R] + 25 - xp) / abs(xe[R] + 25 - xp) * 40;
					n = (ye[R] + 25 - yp) / abs(ye[R] + 25 - yp) * 40 * ((abs(ye[R] + 25 - yp) / abs(xe[R] + 25 - xp)));
				}
			}
			//发射子弹
			else {
				circle(xp, yp, 50);
				for (int i = 0; i < num; i++) {
					if (enemies[i].getlife() == 1 && enemies[i].getblood() > 0)
					{
						double distance[num];
						distance[i] = pow(xe[i] - xp, 2) + pow(ye[i] - yp, 2);
						if (distance[i] <= 2500) {
							enemies[i].damage();
							knight.Energyincrease();

						}
					}
				}
			}
		}
		else if (movedirection[0] == ' ')
		{
			bool x = 1;
			for (int i = 0; i < num; i++)
			{
				if (enemies[i].getlife() == 1)
					x = 0;
			}
			if (x && (xp >= 1000) && (yp <= 390) && (yp >= 210)) {
				k++;
				xp = 60;
				yp = 300;
				p = 1;
				if (k == 6) {
					*winflagptr = 1;
				}
			}
			//闪现
			else if ((xp <= 0) && (yp <= 390) && (yp >= 210)) {
				if (k != 0) {
					k--;
					xp = 1000;
					yp = 300;
				}
			}
			//切换关卡
			/*
			switch (movedirection[1])
			{
			case 'a':xp -= 60; break;
			case 'd':xp += 60; break;
			case 'w':yp -= 60; break;
			case 's':yp += 60; break;
			default:break;
			}*/

			Sleep(100);
		}
		else if (movedirection[0] == 'e')
		{
			weaponstate = 1 - weaponstate;
		}
		//切换武器
		else if (movedirection[0] == 'u')
		{
			for (int i = 0; i <= num - 1; i++)
			{
				//秒杀外挂
				enemies[i].setblood(0);
				//按下P血量归零
				enemies[i].setlife(0);
				//生命状态为死亡

			}
		}
	}
}




//怪物移动函数
void moveEnermy()
{
	srand(time(NULL));
	//随机生成怪物坐标
	for (int i = 0; i < num; i++)
	{
		if (enemies[i].getboss() == 0 && (enemies[i].getlife() == 1) && enemies[i].getblood() > 0) {
			int state = 1;
			if (fabs(xe[i] - xp) < 200 && fabs(xe[i] - xp) > 100 && fabs(ye[i] - yp) > 100 && fabs(ye[i] - yp) < 200)
				state = 2;
			switch (state)
			{
			case 1: {
				if ((xe[i] > 50) && (xe[i] < 1000) && (ye[i] > 50) && (ye[i] < 550)) {
					int move[5] = { 3,-1,1,0,-3 };
					int p = rand() % 5;
					int q = rand() % 5;
					xe[i] += move[p];
					ye[i] += move[q];
					break;
				}

			}
			case 2: {
				if ((xe[i] > 50) && (xe[i] < 1000) && (ye[i] > 50) && (ye[i] < 550)) {
					xe[i] -= fabs(xe[i] - xp) / (xe[i] - xp) * 5;
					ye[i] -= fabs(ye[i] - yp) / (ye[i] - yp) * 5;
					break;
				}
			}
			default:
				break;
			}


		}

		else if (k == 5) {
			//boss关单独执行函数逻辑
			int state = 1;
			if (enemies[0].getblood() <= 100)
				state = 2;
			static int waitindexboss = 0;
			waitindexboss++;
			switch (state)
			{
			case 1: {

				xe[0] = 440;
				ye[0] = 200;

				break;

			}
			case 2: {


				int move[3] = { 3,0,-3 };
				int p = rand() % 3;
				int q = rand() % 3;
				xe[0] += move[p];
				ye[0] += move[q];

				if (fabs(xe[0] - xp) < 400 && fabs(xe[0] - xp) > 100 && fabs(ye[0] - yp) < 400 && fabs(ye[0] - yp) > 100 && waitindexboss == 10) {
					xe[0] -= fabs(xe[0] - xp) / (xe[0] - xp) * 5;
					ye[0] -= fabs(ye[0] - yp) / (ye[0] - yp) * 5;
					break;
				}
			}
			default:
				break;
			}
			if ((xe[i] < 50))
			{
				xe[i] = 50;
			}
			else if ((xe[i] > 1000))
				xe[i] = 1000;

			else if ((ye[i] < 50)) {
				ye[i] = 50;
			}
			else if ((ye[i] > 550)) {
				ye[i] = 550;
			}
		}
	}
}




//子弹移动函数
void BulletMove()
{

	xb += m;
	yb += n;
	if (k == 5) {
		for (int i = 0; i < 8; i++) {
			xbsbu[i] += mb[i];
			ybsbu[i] += nb[i];
		}
	}
	//boss关独立逻辑
	for (int i = 0; i < num; i++)
	{

		if (k != 5)
		{
			xeb[i] += me[i];
			yeb[i] += ne[i];
		}
		//一般关卡逻辑
	}
}




//怪物行为模块
void MoveWithoutInput()
{
	static int waitIndex1 = 1;

	static int waitIndex2 = 1;

	static int waitIndex3[num] = { 1 };

	static int waitIndex4 = 1;
	waitIndex1++;

	waitIndex2++;
	for (int i = 0; i < num; i++)

		waitIndex3[i]++;

	waitIndex4++;

	if (waitIndex1 == 20)
	{
		BulletMove();
		waitIndex1 = 1;
	}
	//每刷新一次程序waitIndex1自增，改变if中的数值以改变子弹速度
	if (waitIndex2 == 40)
	{
		moveEnermy();
		waitIndex2 = 1;
	}
	//每刷新一次程序waitIndex2自增，改变if中的数值以改变怪物速度
	if (waitIndex4 == 500) {
		for (int j = 0; j < 8; j++) {
			xbsbu[j] = xe[0];
			ybsbu[j] = ye[0];
			mb[j] = 10 * cos(j * (pi / 4));
			nb[j] = 10 * sin(j * (pi / 4));
		}
		waitIndex4 = 1;
	}
	//每刷新一次程序waitIndex4自增，改变if中的数值以改变boss速度
	for (int i = 0; i < num; i++)
	{

		if ((waitIndex3[i] == 600 - i * 60) && (enemies[i].getboss() == 0))
		{
			xeb[i] = xe[i];
			yeb[i] = ye[i];
			me[i] = (xp - xe[i]) / abs(xe[i] - xp) * 10;
			ne[i] = (yp - ye[i]) / abs(ye[i] - yp) * 10 * ((abs(ye[i] - yp) / abs(xe[i] - xp)));
			waitIndex3[i] = 1;
		}
	}
}




//图片刷新
void show()
{
	cleardevice();
	printmap();
	knight.printAttribute(knight);
	//重新绘制地图与角色新坐标
	if (k != 5) {
		for (int i = 0; i < num; i++)
		{
			for (int j = i + 1; j < num; j++)
			{
				if (fabs(xe[i] - xe[j]) < width * 0.1)
					xe[j] += width * 0.4;
			}

			if (enemies[i].getlife() == 1 && enemies[i].getblood() > 0) {
				putimage(xe[i], ye[i], &enermy2[i], NOTSRCERASE);
				putimage(xe[i], ye[i], &enermy1[i], SRCINVERT);
			}

		}
	}


	else if (k == 5) {

		if (enemies[0].getlife() == 1 && (enemies[0].getboss() == 1)) {

			putimage(xe[0], ye[0], &boss2, NOTSRCERASE);
			putimage(xe[0], ye[0], &boss1, SRCINVERT);

		}
	}
	//boss关绘制boss

	if (weaponstate == 0)
		putimage(xb, yb, &bullet1[weapon0]);
	else if (weaponstate == 1)
		putimage(xb, yb, &bullet1[weapon1]);

	if (k == 5 && enemies[0].getblood() > 0)
	{
		for (int i = 0; i < 8; i++) {
			putimage(xbsbu[i], ybsbu[i], &bullet2);
		}
	}
	//boss子弹绘制
	for (int i = 0; i < num; i++)
	{
		if (enemies[i].getlife() == 1 && enemies[i].getblood() > 0) {
			putimage(xeb[i], yeb[i], &bullet2);
		}

	}

	putimage(xp, yp, &knight11, NOTSRCERASE);
	putimage(xp, yp, &knight12, SRCINVERT);
	int flag = 1;
	int* flagptr = &flag;
	for (int i = 0; i < num; i++) {

		if (enemies[i].getblood() > 0 && enemies[i].getlife() == 1) {
			*flagptr = 0;
		}


	}
	if (flag) {
		settextcolor(WHITE);
		settextstyle(50, 0, _T("黑体"));
		outtextxy(400, 250, _T("stage clear "));
	}
	FlushBatchDraw();
}




//怪物受击判断
void hitJudge()
{


	for (int i = 0; i < num; i++)
	{


		//manhitenemy
		if (enemies[i].getlife() == 1 && enemies[i].getblood() > 0 && enemies[i].getboss() == 0)
		{
			if (((double)xe[i] < xb) && ((double)xe[i]+50 > xb ) && ((double)ye[i] < yb) && (double)ye[i] +50>yb )
			{
				enemies[i].damage();
				xb = 10000;
				yb = 10000;
				//将子弹移走以免导致怪物重复扣血
				knight.Energyincrease();
				//击中怪物恢复能量
				knight.coinsIncrease();
				//击中怪物获得金钱
			}
			if (enemies[i].getblood() <= 0)
			{
				enemies[i].setlife(0);
				//怪物状态变为死亡
				enemies[i].setblood(0);
				//怪物血量清零
			}
		}



		//manhitboss
		if (enemies[0].getlife() == 1 && enemies[0].getblood() > 0 && enemies[0].getboss() == 1)
		{
			if ((xe[0] < xb) && (xe[0] + 100 > xb) && (ye[0] < yb) && ye[0] + 100 > yb)
			{
				enemies[0].damage();
				xb = 10000;
				yb = 10000;
				knight.Energyincrease();
				knight.coinsIncrease();
			}
			if (enemies[0].getblood() <= 0)
			{
				enemies[0].setlife(0);
				enemies[0].setblood(0);
			}
		}



		//bosshitman
		if (enemies[0].getlife() == 1 && enemies[0].getblood() > 0 && k == 5 && enemies[0].getboss()) {
			for (int j = 0; j < 8; j++) {
				if ((xp > xbsbu[j]) && (xp < xbsbu[j] + 100) && (yp > ybsbu[j]) && (yp < ybsbu[j] + 100))
				{
					xbsbu[j] = 1000000;
					ybsbu[j] = 1000000;
					//boss击中玩家后移走boss子弹以免导致玩家重复扣血
					if (knight.getShieldValue() > 0)
					{
						knight.ShieldDiscrease();
						//骑士受击优先扣除护盾值
						if (knight.getShieldValue() < 0)
						{
							knight.ShieldBreak();
							//护盾被打破
						}
					}
					else
						knight.bloodDicrease();
					//打破护盾后扣除生命值
				}
			}
		}


		//enemyhitman
		else if ((enemies[i].getlife() == 1 && enemies[i].getblood() > 0) && k < 5)
		{
			if ((xp > xeb[i]) && (xp < xeb[i] + 50) && (yp > yeb[i]) && (yp < yeb[i] + 50))
			{
				xeb[i] = 1000000;
				yeb[i] = 1000000;
				//怪物击中玩家后移走怪物子弹以免导致玩家重复扣血
				if (knight.getShieldValue() > 0)
				{
					knight.ShieldDiscrease();
					//骑士受击优先扣除护盾值
					if (knight.getShieldValue() < 0)
					{
						knight.ShieldBreak();
					}
					//护盾被打破
				}
				else
					knight.bloodDicrease();
				//打破护盾后扣除生命值
			}
		}
	}
}



//护盾回复设置
void ShieldRecover()
{
	static int waitIndex = 1;
	waitIndex++;
	if (waitIndex == 1000)
	{
		if (knight.getShieldValue() < 7)
			knight.ShieldIncrease();
		waitIndex = 1;
	}
	//程序刷新1000次以后回复一点护盾值，改变waitIndex可改变恢复速率
}



//战斗模块
void battlemap() {
	int xp = 60, yp = 300;

	IMAGE wall, closewall, fl, wood, fl2;//fl 0 wall 1 closewall 2 wood 3 fl2 4
	loadimage(&knight12, _T("./骑士正(白底图).png"), 30, 30);
	loadimage(&knight11, _T("./骑士正(遮罩图).png"), 30, 30);
	loadimage(&knight22, _T("./骑士反(白底图).png"), 30, 30);
	loadimage(&knight21, _T("./骑士反(遮罩图).png"), 30, 30);
	loadimage(&boss1, _T("./boss白底图.jpg"));
	loadimage(&boss2, _T("./boss遮罩图.jpg"));

	while (1) {

		if (p) {
			BeginBatchDraw();
			printmap();
			show();
			putimage(xp, yp, &knight11, NOTSRCERASE);
			putimage(xp, yp, &knight12, SRCINVERT);
			EndBatchDraw();
		}
		if (*winflagptr)
			break;
		loadimage(&bullet1[0], _T("./散弹子弹.png"), 20, 20);
		loadimage(&bullet1[1], _T("./熔岩子弹.png"), 20, 20);
		loadimage(&bullet1[2], _T("./法球.png"), 20, 20);
		loadimage(&bullet1[3], _T("./次次时代子弹.png"), 20, 20);
		loadimage(&bullet1[4], _T("./冰川.png"), 20, 20);
		loadimage(&bullet1[5], _T("./火焰机枪子弹.png"), 20, 20);
		loadimage(&bullet2, _T("./子弹.png"), 15, 15);
		srand(time(NULL));
		//载入各种子弹
		for (int i = 0; i < num; i++)
		{
			loadimage(&enermy1[i], _T("./幽灵白底.jpg"), 30, 30);
			loadimage(&enermy2[i], _T("./幽灵遮罩.jpg"), 30, 30);
			xe[i] = rand() % 1000;
			ye[i] = rand() % 500;
		}

		show();
		BeginBatchDraw();
		while (true)
		{
			MoveWithoutInput();
			MoveWithInput();
			hitJudge();
			ShieldRecover();
			show();
			if (knight.getblood() <= 0)
				flag3 = 1;
			if (flag3)
				break;
			if (*winflagptr)
				break;
		}
		if (*winflagptr)
			break;
		if (flag3)
			break;
		EndBatchDraw();


	}
}



int main() {
	//数据保存
	FILE* fp;

	int _blood, _energy, _shield, _weapon0, _weapon1, _coin;

	fp = fopen("./游戏数据.txt", "r");
	if (fp) {
		fscanf(fp, "%d \n %d \n %d \n %d \n %d \n %d \n", &_blood, &_energy, &_shield, &_weapon0, &_weapon1, &_coin);
	}
	//将数据写入txt文件

	knight.setblood(_blood);
	knight.setEnergy(_energy);
	knight.setShieldValue(_shield);
	knight.Setcoins(_coin);
	weapon0 = _weapon0;
	weapon1 = _weapon1;
	//血量，蓝量，shied value,weapon0,weapon1,coins,
	fclose(fp);
chushijiemian:


	chushijiemian();
	if (flag) {
		goto quit;
	}
home:

	showHomeMap();
	//绘制基地
	if (*flag2ptr) {
		goto chushijiemian;
	}
	k = 0;
	//通关后将k赋值0以保证下一次从第一关开始
	battlemap();
	if (flag3) {
		flag3 = 0;
		knight.setblood(1);
		goto home;
	}
	if (*winflagptr) {
		*winflagptr = 0;
		//返回基地
		goto home;
	}
quit:
	ofstream ofs;
	ofs.open("./游戏数据.txt");
	ofs << knight.getblood() << endl

		<< knight.getEnergy() << endl

		<< knight.getShieldValue() << endl

		<< weapon0 << endl

		<< weapon1 << endl

		<< knight.getcoins() << endl;


	//血量，蓝量，shied value,weapon0,weapon1,coins,
	ofs.close();
	return 0;
}
