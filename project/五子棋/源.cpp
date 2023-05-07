// UI源代码：陈可佳 <emil09_chen@126.com>
//
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<map>
#include<set>
#include<ctime>
#include<cmath>
#include<queue>
#include<cctype>
#include<string>
#include<cstdio>
#include<sstream>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include <time.h>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>

const int MAX_SIZE=19,MAP_SIZE=361;

// 绘制函数

// 保存位置的类
class seat{
public:
	int i = 0;      // y 坐标
	int j = 0;      // x 坐标
	int score = 0; // 分数
};

// 保存棋盘的类
class box{
public:
	int x = 0;              // x 坐标
	int y = 0;              // y 坐标
	int v = -1;         // 值（黑棋：1，白棋：0，空位：-1）
	int modle;              // 模式
	bool isnew = false;     // 是否有选择框
	int score = 0;         // 分数
	COLORREF color = WHITE; // 棋盘背景色
public:
	void draw(){
		COLORREF thefillcolor = getfillcolor(); // 备份填充颜色
		setlinestyle(PS_SOLID, 2);              // 线样式设置
		setfillcolor(color);                    // 填充颜色设置
		solidrectangle(x, y, x + 30, y + 30);   // 绘制无边框的正方形
		if (isnew){
			// 如果是新下的
			// 绘制边框线
			setlinecolor(LIGHTGRAY);
			line(x + 1, y + 2, x + 8, y + 2);
			line(x + 2, y + 1, x + 2, y + 8);
			line(x + 29, y + 2, x + 22, y + 2);
			line(x + 29, y + 1, x + 29, y + 8);
			line(x + 2, y + 29, x + 8, y + 29);
			line(x + 2, y + 22, x + 2, y + 29);
			line(x + 29, y + 29, x + 22, y + 29);
			line(x + 29, y + 22, x + 29, y + 29);
		}
		setlinecolor(BLACK);
		switch (modle){
			// 以下是不同位置棋盘的样式
		case 0:
			line(x + 15, y, x + 15, y + 30);
			line(x - 1, y + 15, x + 30, y + 15);
			break;
			//  *
			// ***
			//  *
		case 1:
			line(x + 14, y + 15, x + 30, y + 15);
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y, x + 15, y + 30);
			setlinestyle(PS_SOLID, 2);
			break;
			// *
			// ***
			// *
		case 2:
			line(x - 1, y + 15, x + 15, y + 15);
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y, x + 15, y + 30);
			setlinestyle(PS_SOLID, 2);
			break;
			//   *
			// ***
			//   *
		case 3:
			line(x + 15, y + 15, x + 15, y + 30);
			setlinestyle(PS_SOLID, 3);
			line(x - 1, y + 15, x + 30, y + 15);
			setlinestyle(PS_SOLID, 2);
			break;
			// ***
			//  *
			//  *
		case 4:
			line(x + 15, y, x + 15, y + 15);
			setlinestyle(PS_SOLID, 3);
			line(x - 1, y + 15, x + 30, y + 15);
			setlinestyle(PS_SOLID, 2);
			break;
			//  *
			//  *
			// ***
		case 5:
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y, x + 15, y + 15);
			line(x + 15, y + 15, x + 30, y + 15);
			setlinestyle(PS_SOLID, 2);
			break;
			// *
			// *
			// ***
		case 6:
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y, x + 15, y + 15);
			line(x - 1, y + 15, x + 15, y + 15);
			setlinestyle(PS_SOLID, 2);
			break;
			//   *
			//   *
			// ***
		case 7:
			setlinestyle(PS_SOLID, 3);
			line(x - 1, y + 15, x + 15, y + 15);
			line(x + 15, y + 15, x + 15, y + 30);
			setlinestyle(PS_SOLID, 2);
			break;
			// ***
			//   *
			//   *
		case 8:
			setlinestyle(PS_SOLID, 3);
			line(x + 15, y + 15, x + 30, y + 15);
			line(x + 15, y + 15, x + 15, y + 30);
			setlinestyle(PS_SOLID, 2);
			break;
			// ***
			// *
			// *
		case 9:
			line(x + 15, y, x + 15, y + 30);
			line(x - 1, y + 15, x + 30, y + 15);
			setfillcolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			fillcircle(x + 15, y + 15, 4);
			break;
			//  *
			// *O*
			//  *
		}
		switch (v)
		{
		case 0: // 白棋
			setfillcolor(WHITE);
			setlinestyle(PS_SOLID, 1);
			fillcircle(x + 15, y + 15, 13);
			break;
		case 1: // 黑棋
			setfillcolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			fillcircle(x + 15, y + 15, 13);
			break;
		}
		setfillcolor(thefillcolor); // 还原填充色
	}
};
box BOX[MAX_SIZE][MAX_SIZE];      // 棋盘

// 绘制棋盘
void draw(int ifdraw=1){
	int modle = 0;  // 棋盘样式
	int score = 0; // 坐标输出的位置
					// 坐标（数值）
	TCHAR strnum[MAX_SIZE][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15"),_T("16"),_T("17"),_T("18"),_T("19")  };
	// 坐标（字母）
	TCHAR strabc[MAX_SIZE][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,_T("N"),_T("O"),_T("P"),_T("Q"),_T("R"),_T("S")  };
	for (int i = 0, k = 0; i < 570; i += 30)
	{
		for (int j = 0, g = 0; j < 570; j += 30)
		{
			BOX[k][g].color = RGB(255, 205, 150);// 棋盘底色
												 // x、y 坐标
			BOX[k][g].x = 65 + j;
			BOX[k][g].y = 50 + i;
			BOX[k][g].score = 0;// 初始化分数
								 // 棋盘样式的判断
			if (k == 0 && g == 0)modle = 8;
			else if (k == 0 && g == 18)modle = 7;
			else if (k == 18 && g == 18)modle = 6;
			else if (k == 18 && g == 0)modle = 5;
			else if (k == 0)modle = 3;
			else if (k == 18)modle = 4;
			else if (g == 0)modle = 1;
			else if (g == 18)modle = 2;
			else  if ((k == 3 && g == 3) || (k == 3 && g == 15) || (k == 15 && g == 3) || (k == 15 && g == 15) || (k == 3 && g == 9) || (k == 9 && g == 3) || (k == 15 && g == 9) || (k == 9 && g == 15) || (k == 9 && g == 9))
				modle = 9;
			else modle = 0;
			BOX[k][g].modle = modle;
			if(ifdraw)BOX[k][g].draw(); // 绘制
			if (BOX[k][g].isnew == true)BOX[k][g].isnew = false; // 把上一个下棋位置的黑框清除
			g++;
		}
		k++;
	}
	// 画坐标
	LOGFONT nowstyle;
	gettextstyle(&nowstyle);
	settextstyle(0, 0, NULL);
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if(ifdraw)outtextxy(75 + score, 35, strnum[i]);
		if(ifdraw)outtextxy(53, 55 + score, strabc[i]);
		score += 30;
	}
	settextstyle(&nowstyle);
}

int win = -1;         // 谁赢了（0：白棋，1：黑棋，2：平局）
int nowcnt[2];
int dx[4]{ 1,0,1,1 }; // - | \ / 四个方向
int dy[4]{ 0,1,1,-1 };

// 对局初始化
void init()
{
	win = -1;// 谁赢了
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			BOX[i][j].score = 0;// 分数
			BOX[i][j].v = -1;// 值
		}
	}
}

// 判断输赢
void isWIN(){
	bool isinit = true; // 是否刚刚开局
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
			if (BOX[i][j].v != -1){
				// 遍历每个可能的位置
				isinit = false;                 // 如果有，那么就不是刚刚开局
				int nowcolor = BOX[i][j].v; // 现在遍历到的颜色
				int length[4] = { 0,0,0,0 };    // 四个方向的长度
				for (int k = 0; k < 4; k++){
					// 原理同寻找最佳位置
					int nowi = i,nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].v == nowcolor)length[k]++,nowj += dx[k],nowi += dy[k];
					nowi = i;nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].v == 1 - nowcolor)length[k]++,nowj -= dx[k],nowi -= dy[k];
				}
				for (int k = 0; k < 4; k++)if (length[k] >= 5)win = nowcolor;// 如果满五子
				if ((!isinit) && nowcnt[0]+nowcnt[1]==MAP_SIZE)win = 2;// 如果不是开局且棋盘已满 平局
			}
}

seat findbestseat(int color){
	if (color==1&&nowcnt[0] + nowcnt[1] == 0) {seat Ans;Ans.i=Ans.j=9;return Ans;}//黑方第一子必落天元
	// 评分表
	int Score[3][5] = {
		{ 0, 20, 360, 5800, 92840 }, // 防守0子
		{ 0, 0, 20, 360, 92840 },    // 防守1子
		{ 0, 0, 0, 0, 92840 }        // 防守2子
	};
	seat bestseat;              // 最佳位置
	int MAXscore[MAP_SIZE] = { 0 }; // 最佳分数（可能有多个）
	int MAXx[MAP_SIZE] = { 0 };      // 最佳 x 坐标（可能有多个）
	int MAXy[MAP_SIZE] = { 0 };      // 最佳 y 坐标（可能有多个）
	int score = 0;             // 下一个最佳分数储存位置
	int truescore;             // 输出的最佳分数位置
	int nowi = 0;               // 现在遍历到的y坐标
	int nowj = 0;               // 现在遍历到的x坐标
	int length[4];              // 四个方向的长度
	int emeny[4];               // 四个方向的敌子
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (BOX[i][j].v == -1)
			{
				// 遍历每一个可能的位置

				// 自己
				BOX[i][j].v = color; // 尝试下在这里
				for (int k = 0; k < 4; k++)
				{
					length[k] = 0;
					emeny[k] = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].v == color)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					if (BOX[nowi][nowj].v == 1 - color || nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18)
					{
						emeny[k]++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].v == color)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
					if (BOX[nowi][nowj].v == 1 - color || nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18)
					{
						emeny[k]++;
					}
					length[k] -= 2; // 判断长度
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					BOX[i][j].score += Score[emeny[k]][length[k]] * 4 + !(!length[k]) * 20;//加分系统
					length[k] = 0;
					emeny[k] = 0;
				}
				// 敌人（原理同上）
				BOX[i][j].v = 1 - color;
				for (int k = 0; k < 4; k++)
				{
					length[k] = 0;
					emeny[k] = 0;
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].v == 1 - color)
					{
						length[k]++;
						nowj += dx[k];
						nowi += dy[k];
					}
					if (BOX[nowi][nowj].v == color || nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18)
					{
						emeny[k]++;
					}
					nowi = i;
					nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].v == 1 - color)
					{
						length[k]++;
						nowj -= dx[k];
						nowi -= dy[k];
					}
					if (BOX[nowi][nowj].v == color || nowi < 0 || nowj < 0 || nowi > 18 || nowj > 18)
					{
						emeny[k]++;
					}
					length[k] -= 2;
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					BOX[i][j].score += Score[emeny[k]][length[k]];
					length[k] = 0;
					emeny[k] = 0;
				}
				BOX[i][j].v = -1;
			}
			if (BOX[i][j].score == MAXscore[0])
			{
				// 如果和最高分数相同
				MAXscore[score] = BOX[i][j].score;
				MAXy[score] = i;
				MAXx[score] = j;
				score++;
				// 新增一个分数及坐标
			}
			if (BOX[i][j].score > MAXscore[0])
			{
				// 如果比最高分数高
				for (int k = 0; k < score; k++)
				{
					MAXscore[k] = 0;
					MAXy[k] = 0;
					MAXx[k] = 0;
				}
				score = 0;
				MAXscore[score] = BOX[i][j].score;
				MAXy[score] = i;
				MAXx[score] = j;
				score++;
				// 清空数组再加入
			}
		}
	}
	// 生成随机位置
	truescore = rand() % score;
	bestseat.i = MAXy[truescore];
	bestseat.j = MAXx[truescore];
	bestseat.score = MAXscore[truescore];
	// 返回位置
	return bestseat;
}

namespace SOMETOOLS {
#define Re register int
#define LL long long
#define LD double
#define gettime _GETTIME_
	inline LD gettime() { return (LD)clock() / (LD)CLOCKS_PER_SEC; }//·?????

#define Squre(a) ((a)*(a))
#define Cube(a) ((a)*(a)*(a)) 

#define abs _ABS_
	template<typename T>inline T abs(T a) { return a < 0 ? -a : a; }

#define swap _SWAP_
	template<typename T>inline void swap(T &a, T &b) { T c = a; a = b, b = c; }

#define gcd _GCD_
	template<typename T>inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a%b); }

#define max _MAX_
	template<typename T>inline T max(T a, T b) { return (a > b) ? a : b; }
	template<typename T>inline T max(T a, T b, T c) { return max(max(a, b), c); }
	template<typename T>inline T max(T a, T b, T c, T d) { return max(max(max(a, b), c), d); }
	template<typename T>inline T max(T a, T b, T c, T d, T e) { return max(max(max(max(a, b), c), d), e); }
	template<typename T>inline T max(T a, T b, T c, T d, T e, T f) { return max(max(max(max(a, b), c), d), e); }

#define min _MIN_
	template<typename T>inline T min(T a, T b) { return (a < b) ? a : b; }
	template<typename T>inline T min(T a, T b, T c) { return min(min(a, b), c); }
	template<typename T>inline T min(T a, T b, T c, T d) { return min(min(min(a, b), c), d); }
	template<typename T>inline T min(T a, T b, T c, T d, T e) { return min(min(min(min(a, b), c), d), e); }
	template<typename T>inline T min(T a, T b, T c, T d, T e, T f) { return min(min(min(min(a, b), c), d), e); }
}
using namespace SOMETOOLS;
namespace RANDOM_DATA {
	int index, MT[624]; bool isInit;

	inline void MTsrand_(unsigned int seed) {
		index = 0, isInit = 1, MT[0] = seed;
		for (Re i = 1; i<624; i++) {
			Re t = 1812433253 * (MT[i - 1] ^ (MT[i - 1] >> 30)) + i;
			MT[i] = t & 0xffffffff;
		}
	}
	inline void generate_() {
		for (Re i = 0; i<624; i++) {
			Re y = (MT[i] & 0x80000000) + (MT[(i + 1) % 624] & 0x7fffffff);
			MT[i] = MT[(i + 397) % 624] ^ (y >> 1);
			if (y % 2 == 1)MT[i] ^= 2087483647;
		}
	}
	inline int MTrand_() {
		if (!isInit)MTsrand_((int)time(NULL));
		if (index == 0)generate_();
		Re y = MT[index];
		y = y ^ (y >> 11);
		y = y ^ ((y << 7) & 1969275843);
		y = y ^ ((y << 15) & 2058296471);
		y = y ^ (y >> 18);
		index = (index + 1) % 624;
		return y;
	}
	inline int MTrand(Re a, Re b) {
		if (a>b)swap(a, b);
		return (a == b) ? a : (MTrand_() % (b - a + 1) + a);
	}

	int Flag_Srand;

	inline void Setseed(unsigned int seed) { Flag_Srand = 1, srand(seed), MTsrand_(seed); }
	inline void Setseed() { Flag_Srand = 1, Setseed((unsigned int)(time(int(NULL)))); }

	inline int Rand(Re L, Re R) {
		if (!Flag_Srand)Setseed();
		if (L>R)swap(L, R);
		LL len = R - L;
		if (len <= 32767)return (!len) ? L : (L + rand() % (len + 1));
		else return MTrand(L, R);
	}

	/*------------------------------------------------------------------------------*/
}
using RANDOM_DATA::Rand;
using RANDOM_DATA::Setseed;
namespace MY_TOOLS{

	struct QAQ { 
		int x, y; LL v;
		QAQ(int X = 0, int Y = 0,LL V=0) { x = X, y = Y, v = V; }
		inline bool operator<(const QAQ &O)const {return v<O.v;}
	};
	int ballcnt[2],col[19+3][19+3];
	//QAQ history[2][181+3];
	inline void init() {
		//memset(history, 0, sizeof(history));
		ballcnt[0]=ballcnt[1]=0;
		for (Re i = 0; i <= 20; ++i)
			for (Re j = 0; j <= 20; ++j)
				col[i][j] = -1;
	}
	//inline int Inmap(Re x, Re y) { return x >= 1 && x <= 19 && y >= 1 && y <= 19; }
#define Inmap(x,y) ((x)>=1&&(x)<=19&&(y)>=1&&(y)<=19)
	inline void luo(Re color,Re x,Re y) {
		col[x][y] = color,++ballcnt[color];
		//history[color][ballcnt[color]]=QAQ(x,y);
	}
	inline int judge(Re color, Re i, Re j) {
		for (Re O = 0; O < 4; ++O) {//四个方向
			Re t=1,nx = i, ny = j, wx =dx[O], wy = dy[O];
			while (Inmap(nx + wx, ny + wy) && col[nx + wx][ny + wy] == color)nx += wx, ny += wy, ++t;
			nx=i,ny=j;
			while (Inmap(nx - wx, ny - wy) && col[nx - wx][ny - wy] == color)nx -= wx, ny -= wy, ++t;
			if (t >= 5)return 1;
		}
		return 0;
	}
	inline void Judge_win(Re color,Re i,Re j) {
		if(judge(color,i,j)==1)win=color;
		else if(ballcnt[0]+ballcnt[1]==MAP_SIZE)win=2;
	}

	//对抗搜索工具
	int Qt;QAQ Qs[181+3];
	inline void dfs_luo(Re color, Re i, Re j) {
		Qs[++Qt]=QAQ(i,j,color);//,luo(color,i,j);
		col[i][j] = color;
		++ballcnt[color];
	}
	inline void dfs_luo_back(){
		QAQ tmp=Qs[Qt--];
		col[tmp.x][tmp.y] = -1,
		--ballcnt[tmp.v];
	}
	inline int dfs_judge_win() {
		return judge(Qs[Qt].v,Qs[Qt].x,Qs[Qt].y);
	}
}
using MY_TOOLS::QAQ;
using MY_TOOLS::col;
//using MY_TOOLS::Inmap;
//using MY_TOOLS::history;
using MY_TOOLS::ballcnt;
using MY_TOOLS::Judge_win;

LL score_atk[5][3] = { 0,0,0,//score[i][j]：落子后形成 有j个阻拦的i连区域 的分数
2  , 1   , 0, //落子后形成 有0,1,2个阻拦的 1 连区域
1000 , 100  , 0, //落子后形成 有0,1,2个阻拦的 2 连区域
10000, 990  , 0, //落子后形成 有0,1,2个阻拦的 3 连区域
1e12 , 9990, 0, //落子后形成 有0,1,2个阻拦的 4 连区域
};
LL	score_def[5][2] = { 0,0,//score[i][j]：落子后阻拦 原本有j个阻拦的i连区域 的分数
2   , 1  , //落子后阻拦 原本有0,1个阻拦的 1 连区域
1000  , 100  , //落子后阻拦 原本有0,1个阻拦的 2 连区域
10000 , 990 , //落子后阻拦 原本有0,1个阻拦的 3 连区域
-1  , 1e10, //落子后阻拦 原本有0,1个阻拦的 4 连区域
};
//我方一步胜利 ---1e16
//>> 阻止对方一步胜利 ---1e14
//>> 我方形成0阻4连 ---1e12
//>> 阻止对方形成0阻4连（阻拦对方原0阻3连） ---1e10
//>> 我方形成0阻3连 >= 我方形成1阻4连 ---1000,900
//>> 阻止对方形成0阻3连（阻拦对方原0阻2连） ---500
namespace MY_AI_0 {
	inline LL calc_atk(Re color, Re i, Re j) {//攻（进攻对方的得分）
		LL ans = 0; Re d_color = (color ^ 1);
		for (Re O = 0; O < 4; ++O) {//四个方向
			Re t = 1, du = 0;

			Re nx = i, ny = j, wx = dx[O], wy = dy[O];
			while (Inmap(nx + wx, ny + wy)&&col[nx + wx][ny + wy] == color)nx += wx, ny += wy, ++t;
			if (!Inmap(nx + wx, ny + wy)||col[nx + wx][ny + wy] == d_color)du++;

			nx = i, ny = j;
			while (Inmap(nx - wx, ny - wy)&&col[nx - wx][ny - wy] == color)nx -= wx, ny -= wy, ++t;
			if (!Inmap(nx - wx, ny - wy)||col[nx - wx][ny - wy] == d_color)du++;

			if (t >= 5)return 1e16;//我方一步胜利
			//t<=4:
			ans += score_atk[t][du];
		}
		return ans;
	}
	inline LL calc_def(Re color, Re i, Re j) {//防（堵对方双边的得分）
		LL ans = 0; Re d_color = (color ^ 1);
		for (Re O = 0; O < 4; ++O) {//四个方向
			Re t = 1, du=0;

			Re nx = i, ny = j, wx = dx[O], wy = dy[O];
			while (Inmap(nx + wx, ny + wy)&&col[nx + wx][ny + wy] == d_color)nx += wx, ny += wy, ++t;
			if (!Inmap(nx + wx, ny + wy)||col[nx + wx][ny + wy] == color)du++;

			nx = i, ny = j;
			while (Inmap(nx - wx, ny - wy)&&col[nx - wx][ny - wy] == d_color)nx -= wx, ny -= wy, ++t;
			if (!Inmap(nx - wx, ny - wy)||col[nx - wx][ny - wy] == color)du++;

			if (t >= 5)return 1e14;//阻止对方一步胜利
			//t<=4:
			if(t==4&&!du)return 1e10;//阻止对方形成0阻4连（阻拦对方原0阻3连）
			if(du<2)ans += score_def[t][du];

		}
		return ans;
	}
	struct AI_0 {//单步决策
		int color;
		LL rate[5] = { 0,3,4,2,1 };
		int Qt; QAQ Qs[361 + 3];
		int ILp, IRp, JLp, JRp;//每次局部检查落点的查找范围
		struct MERGE {//并查集优化棋盘枚举速度
			int fa[19 + 3];
			inline int find(Re x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
		}T1[19 + 3];
		QAQ my_AI() {//寻找最大分数位置
			Qt = 0;
			for (Re i = ILp; i <= IRp; ++i)
				for (Re j = T1[i].find(JLp); j <= JRp; j = T1[i].find(j + 1)) {
					LL ss0 = calc_atk(color, i, j)*rate[1] + calc_def(color, i, j)*rate[2] + calc_atk(color ^ 1, i, j)*rate[3] + calc_def(color ^ 1, i, j)*rate[4];//我攻+我防+他攻+他防
					if (!Qt || ss0 > Qs[1].v)Qs[Qt = 1] = QAQ(i, j, ss0);
					else if (ss0 == Qs[Qt].v)Qs[++Qt] = QAQ(i, j, ss0);
				}
			return Qt > 1 ? Qs[Rand(1, Qt)] : Qs[1];
		}
		inline void luozi_update(Re i, Re j) {
			T1[i].fa[j] = T1[i].find(j + 1);
			ILp = min(ILp, max(i - 4, 1));
			IRp = max(IRp, min(i + 4, 19));
			JLp = min(JLp, max(j - 4, 1));
			JRp = max(JRp, min(j + 4, 19));
		}
		inline void init(Re color0) {
			color = color0, Qt = 0;
			//if (color == 1)	rate[1] = 3, rate[2] = 4, rate[3] = 2, rate[4] = 1;
			//else            rate[1] = 3, rate[2] = 4, rate[3] = 2, rate[4] = 1;
			memset(T1, 0, sizeof(T1));
			ILp = IRp = JLp = JRp = 10;//黑方第一子必落天元
			for (Re i = 1; i <= 19; ++i)
				for (Re j = 1; j <= 19 + 1; ++j)
					T1[i].fa[j] = j;
		}
	}my_ai_0;
}
using MY_AI_0::calc_atk;
using MY_AI_0::calc_def;
namespace MY_AI{
	const int MAX_DEEP_N=6+5;//MAX_DEEP:最大搜索深度
	const int MAX_WIDE_N=10+5;//MAX_POINT：搜索每层宽度

	const LL dfs_inf=1e17;
	struct AI_1 {//预言决策
		struct CALC_ {
			LL rate[2][5] = { 
				0,3,4,2,1,
				0,3,4,2,1,
			};
			int MAX_deep,MAX_wide;
			int Qt; QAQ Qs[3610 + 3];
			int ILp, IRp, JLp, JRp;//每次局部检查落点的查找范围
			struct MERGE {//并查集优化棋盘枚举速度
				int fa[190 + 3];
				inline int find(Re x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
			}T1[190 + 3];

			inline void find_goodpoint(Re color,Re &last_Qt,QAQ last_Qs[]) {//寻找最大分数位置
				Qt = 0;
				for (Re i = ILp; i <= IRp; ++i)
					for (Re j = T1[i].find(JLp); j <= JRp; j=T1[i].find(j+1))if(col[i][j]==-1){
						LL ss0 = calc_atk(color, i, j)*rate[color][1] + calc_def(color, i, j)*rate[color][2]
							+calc_atk(color ^ 1, i, j)*rate[color][3] + calc_def(color ^ 1, i, j)*rate[color][4];//我攻+我防+他攻+他防
						if (!Qt || ss0 > Qs[1].v)Qs[Qt = 1] = QAQ(i, j, ss0);
						else if (ss0 == Qs[Qt].v)Qs[++Qt] = QAQ(i, j, ss0);
					}
				if(Qt>MAX_wide){//限制每层的搜索宽度
					for(Re OO=1;OO<=MAX_wide;++OO){
						Re p=Rand(OO,Qt);
						if(p!=OO)swap(Qs[p],Qs[OO]);
					}
					Qt=MAX_wide;
				}
				last_Qt=Qt;
				for(Re i=1;i<=Qt;++i)last_Qs[i]=Qs[i];
			}
			inline void luozi_update(Re i,Re j) {
				T1[i].fa[j]=T1[i].find(j+1);
				ILp=min(ILp,max(i-4,1)),IRp=max(IRp,min(i+4,19)),JLp=min(JLp,max(j-4,1)),JRp=max(JRp,min(j+4,19));
			}
			int Q1234t,Q1[MAX_DEEP_N+2],Q2[MAX_DEEP_N+2],Q3[MAX_DEEP_N+2],Q4[MAX_DEEP_N+2];
			inline void dfs_luozi(Re i, Re j) {
				++Q1234t, Q1[Q1234t]=ILp, Q2[Q1234t]=IRp, Q3[Q1234t]=JLp, Q4[Q1234t]=JRp;
				ILp=min(ILp,max(i-4,1)),IRp=max(IRp,min(i+4,19)),JLp=min(JLp,max(j-4,1)),JRp=max(JRp,min(j+4,19));
			}
			inline void dfs_luozi_back() {
				ILp=Q1[Q1234t], IRp=Q2[Q1234t], JLp=Q3[Q1234t], JRp=Q4[Q1234t]; --Q1234t;
			}
			inline void init(Re color0,Re deep,Re wide) {
				Q1234t=Qt=0,MAX_deep=deep,MAX_wide=wide;
				memset(T1,0,sizeof(T1));
				ILp = IRp = JLp = JRp = 10;//黑方第一子必落天元
				for (Re i = 1; i <= 19; ++i)
					for (Re j = 1; j <= 19 + 1; ++j)
						T1[i].fa[j] = j;
			}
		}calc_score;
		int AI_1_color,MAX_deep,MAX_wide;
		LL ppp;
		inline LL findmin(Re deep,LL alpha,Re op) {//对手想让我尽量小
			//cleardevice();
			//TCHAR text[500];_stprintf(text, _T("min:ballcnt=(%d,%d) deep=%d op=%d ppp=%d"), ballcnt[0],ballcnt[1],deep,op,++ppp);
			//outtextxy(150, 650, text);
			if(MY_TOOLS::dfs_judge_win())return dfs_inf;//我赢了

			if(ballcnt[0]+ballcnt[1]==MAP_SIZE)return 0;//平局
			if(deep>MAX_deep)return 0;//搜索深度限制

			QAQ to;LL ans=dfs_inf;//准备一个对于对手来说的最坏情况（高分）

			int Qt;QAQ Qs[MAX_WIDE_N+1]; calc_score.find_goodpoint(op,Qt,Qs);

			for(Re i=1;i<=Qt;++i){
				QAQ to=Qs[i];
				calc_score.dfs_luozi(to.x,to.y),MY_TOOLS::dfs_luo(op,to.x,to.y);//试探落子

				ans=min(ans,-to.v+findmax(deep+1,ans+to.v,op^1));//搜下一层

				calc_score.dfs_luozi_back(),MY_TOOLS::dfs_luo_back();//撤销落子

				if(ans<=alpha)return ans;
			}
			return ans;
		}
		inline LL findmax(Re deep,LL beta,Re op) {//我想尽量大
			if(MY_TOOLS::dfs_judge_win())return -dfs_inf;//对手赢了

			if(ballcnt[0]+ballcnt[1]==MAP_SIZE)return 0;//平局
			if(deep>MAX_deep)return 0;//搜索深度限制
			QAQ to;LL ans=-dfs_inf;//准备一个对于我来说的最坏情况（低分）
			int Qt;QAQ Qs[MAX_WIDE_N+1]; calc_score.find_goodpoint(op,Qt,Qs);

			for(Re i=1;i<=Qt;++i){
				QAQ to=Qs[i];
				calc_score.dfs_luozi(to.x,to.y),MY_TOOLS::dfs_luo(op,to.x,to.y);//试探落子
				
				ans=max(ans,to.v+findmin(deep+1,ans-to.v,op^1));//搜下一层
				
				calc_score.dfs_luozi_back(),MY_TOOLS::dfs_luo_back();//撤销落子
				
				if(ans>=beta)return ans;
			}
			return ans;
		}
		inline QAQ my_AI() {
			QAQ to,ans=QAQ(0,0,-dfs_inf);
			int Qt;QAQ Qs[MAX_WIDE_N+1]; calc_score.find_goodpoint(AI_1_color,Qt,Qs);
			if(Qt)ans.x=Qs[1].x,ans.y=Qs[1].y;
			else{
				cleardevice(),outtextxy(150, 650, _T("FUCKYOU!!!"));system("pause");
			}
			for(Re i=1;i<=Qt;++i){
				QAQ to=Qs[i];
				calc_score.dfs_luozi(to.x,to.y),MY_TOOLS::dfs_luo(AI_1_color,to.x,to.y);//试探落子
				LL s=findmin(1,ans.v-to.v,AI_1_color^1);//搜下一层
				if(to.v+s > ans.v)ans=QAQ(to.x,to.y,to.v+s);//比较大小
				calc_score.dfs_luozi_back(),MY_TOOLS::dfs_luo_back();//撤销落子
			}
			return ans;
		}
		inline void luozi_update(Re i, Re j) {
			calc_score.luozi_update(i,j);
		}
		inline void init(Re color0,Re deep,Re wide) {
			AI_1_color=color0,MAX_deep=deep,MAX_wide=wide;
			calc_score.init(color0,deep,wide);
		}
	}my_ai_1,my_ai_2;

	const int dw[2][2]={
		2,4,//后手
		1,9,//先手
	};
	int change_deep=1,change_wide=9;
	const int USE_AI_ID=2;
	const int find_bestrate=0;
	const int find_bestdw=0;

	inline void init(Re myAI_color) {
		MY_AI_0::my_ai_0.init(myAI_color^1);
		//my_ai_1.init(myAI_color,change_deep,change_wide);
		//my_ai_1.init(myAI_color^1,change_deep,change_wide);
		my_ai_2.init(myAI_color,dw[myAI_color][0],dw[myAI_color][1]);
	}
	inline void luozi_update(Re i,Re j) {
		MY_AI_0::my_ai_0.luozi_update(i,j);
		//my_ai_1.luozi_update(i,j);
		my_ai_2.luozi_update(i,j);
	}
	inline seat my_AI() {
		QAQ ans;
		//ans=MY_AI_0::my_ai_0.my_AI();
		//ans=my_ai_1.my_AI();
		ans=my_ai_2.my_AI();

		seat Ans; Ans.i = ans.x - 1, Ans.j = ans.y - 1;
		return Ans;
	}
	inline seat my_AI_() {
		QAQ ans;
		ans=MY_AI_0::my_ai_0.my_AI();
		//ans=my_ai_1.my_AI();

		seat Ans; Ans.i = ans.x - 1, Ans.j = ans.y - 1;
		return Ans;
	}
}
using MY_AI::my_AI;
using MY_AI::my_AI_;

namespace Machine_Learning {
	const int Test_cnt=500;//对弈局数
	const int Show_game = 0;//是否展示对弈过程
	int My_AI_color = 0;
	int gamecnt,wincnt[3];
	void print_game_result() {//输出Test_cnt局对弈的结果
		TCHAR text[500];
		_stprintf(text, _T("白胜%d次，黑胜%d次，平%d次"), wincnt[0], wincnt[1], wincnt[2]);
		outtextxy(150, 650, text);
	}
	inline void my_luozi(Re whoplay,Re bx,Re by) {
		MY_TOOLS::luo(whoplay,bx,by);
		MY_AI::luozi_update(bx, by);
	}
	void gamestart() {//单场对弈
		int whoplay = 1; nowcnt[0] = nowcnt[1] = 0;
		MY_TOOLS::init(), MY_AI::init(My_AI_color);

		setfillcolor(RGB(255, 205, 150)); settextstyle(30, 15, 0, 0, 0, 1000, false, false, false); settextcolor(BLACK);
		if(Show_game)solidrectangle(40, 25, 645, 630);
		draw(Show_game); if(Show_game)print_game_result();
		//print_game_result();
		while (1) {
			seat best;
			//best= ( whoplay== My_AI_color ? my_AI(): findbestseat(whoplay));
			best= ( whoplay== My_AI_color ? my_AI(): my_AI_());

			BOX[best.i][best.j].v = whoplay,BOX[best.i][best.j].isnew = true;//它的AI落子

			my_luozi(whoplay, best.i + 1, best.j + 1);//我的AI落子

			++nowcnt[whoplay];

			Judge_win(whoplay,best.i+1, best.j+1);//判断对局是否结束
			
			whoplay^=1;

			if (win == -1) {draw(Show_game);if (Show_game)Sleep(500);}//对局尚未结束
			else {//对局结束
				draw(Show_game);

				++wincnt[win]; ++gamecnt;//统计对弈结果
				
				if (Show_game) {//在屏幕上输出本局结果
					settextcolor(RGB(0, 255, 0));
					if (win == 0)outtextxy(320, 320, _T("白胜"));
					if (win == 1)outtextxy(320, 320, _T("黑胜"));
					if (win == 2)outtextxy(320, 320, _T("平局"));
					system("pause");
				}
				return;
			}
		}
		return;
	}
	inline void open_file_id(int id){
		freopen("CON","r",stdin);
		freopen("CON","w",stdout);
		std::string _id; std::stringstream ss; ss<<id; ss>>_id; 
		std::string filepath="./learningdata/data_"+_id+".txt";
		freopen(filepath.c_str(),"w",stdout);
	}
	inline void close_file(){
		freopen("CON","r",stdin);
		freopen("CON","w",stdout);
	}
	void print_number(int x) {
		if (x / 10)print_number(x / 10);
		putchar('0' + x%10);
	}
	inline void MvM_init() {
		gamecnt = wincnt[0]=wincnt[1] = wincnt[2]=0;
	}
	void battle_start() {//对弈Test_cnt场
		MvM_init();

		while (gamecnt < Test_cnt) {
			init(); // 外面的初始化

			Setseed(rand());
			gamestart(); // 游戏开始

			cleardevice();

			setfillcolor(RGB(255, 205, 150)); settextstyle(30, 15, 0, 0, 0, 1000, false, false, false); settextcolor(BLACK);
			//print_game_result();

			if (gamecnt == Test_cnt) {
				solidrectangle(40, 25, 645, 630);
				draw(1);
			}
			if (gamecnt == Test_cnt) {
				settextcolor(RGB(0, 255, 0));
				if (win == 0)outtextxy(320, 320, _T("白胜"));
				if (win == 1)outtextxy(320, 320, _T("黑胜"));
				if (win == 2)outtextxy(320, 320, _T("平局"));
			}
			//Sleep(1);
		}
		setfillcolor(RGB(255, 205, 150)); settextstyle(30, 15, 0, 0, 0, 1000, false, false, false); settextcolor(BLACK);
		
	}
	const int print_file=1;
	inline void find_best_rate() {//寻找最佳攻防比参数
		if(print_file)open_file_id(1);//打印本次对弈数据到文件

		for (int i1 = 1; i1 <= 4; ++i1)
			for (int i2 = 1; i2 <= 4; ++i2)if (i2 != i1)
				for (int i3 = 1; i3 <= 4; ++i3)if (i3 != i1&&i3 != i2) {
					int i4 = 10 - i1 - i2 - i3;
					MY_AI_0::my_ai_0.rate[1] = i1, MY_AI_0::my_ai_0.rate[2] = i2, MY_AI_0::my_ai_0.rate[3] = i3, MY_AI_0::my_ai_0.rate[4] = i4;
					
					battle_start();
					if(print_file){
						print_number(i1); putchar(','); putchar(' '); 
						print_number(i2); putchar(','); putchar(' '); 
						print_number(i3); putchar(','); putchar(' '); 
						print_number(i4); putchar(','); putchar(' '); 
						print_number(wincnt[0]); putchar(','); putchar(' '); print_number(wincnt[1]); putchar(','); putchar(' '); print_number(wincnt[2]);
						putchar('\n');
					}
					else{
						TCHAR text[500];
						_stprintf(text, _T("%d,%d,%d,%d,白%d次，黑%d次，平%d次"), i1, i2, i3, i4, wincnt[0], wincnt[1], wincnt[2]);
						outtextxy(150, 650, text);
						system("pause");
					}
				}
		if(print_file)close_file();
	}
	inline void find_best_dw() {//寻找最佳深宽比参数
		if(print_file)open_file_id(1);//打印本次对弈数据到文件

		for (int i1 = 1; i1 <= 4; ++i1)
			for (int i2 = 1 ; i2 <= 10; ++i2){
					MY_AI::change_deep=i1,MY_AI::change_wide=i2;
					Setseed(0);
					battle_start();
					if(print_file){

						//print_number(2); putchar(','); 	print_number(5); 
						//putchar('_'); putchar('v'); putchar('s'); putchar('_');
						//print_number(i1); putchar(',');	print_number(i2);  
						
						print_number(i1); putchar(',');	print_number(i2);  
						putchar('_'); putchar('v'); putchar('s'); putchar('_');
						putchar('c'); putchar('k'); 	putchar('j'); 

						putchar(':');putchar(' ');
						print_number(wincnt[0]); putchar(','); putchar(' '); print_number(wincnt[1]); putchar(','); putchar(' '); print_number(wincnt[2]);
						putchar('\n');
					}
					else{
						TCHAR text[500];
						_stprintf(text, _T("%d,%d_vs_ckj: 白%d次，黑%d次，平%d次"), i1, i2,  wincnt[0], wincnt[1], wincnt[2]);
						//_stprintf(text, _T("2,5_vs_%d,%d: 白%d次，黑%d次，平%d次"), i1, i2,  wincnt[0], wincnt[1], wincnt[2]);
						outtextxy(150, 650, text);
						system("pause");
					}
				}
		if(print_file)close_file();
	}
	void game_machine_vs_machine(){

		//find_best_rate();closegraph(),exit(0);

		battle_start(); 

		if (gamecnt == Test_cnt) {
			print_game_result();

			//记录本次对弈数据
			open_file_id(1);
			print_number(wincnt[0]); putchar(','); putchar(' '); print_number(wincnt[1]); putchar(','); putchar(' '); print_number(wincnt[2]);
			close_file();

			system("pause");
		}
					
		closegraph(),exit(0);
	}
}
using Machine_Learning::game_machine_vs_machine;
namespace Player_Vs_My_AI {
	int My_AI_color,gamecnt,AI_id,Test_cnt=40;int wincnt_AI0[2][3],wincnt_AI1[2][3];
	inline void my_luozi(Re whoplay, Re bx, Re by) {
		MY_TOOLS::luo(whoplay, bx, by);
		MY_AI::luozi_update(bx, by);
	}
	void game_player_vs_my_AI_game() {
		nowcnt[0] = nowcnt[1] = 0;
		int whoplay = 1; 
		int playercolor;
		if(gamecnt%4==0)playercolor=0,AI_id=0;
		else if(gamecnt%4==1)playercolor=0,AI_id=1;
		else if(gamecnt%4==2)playercolor=1,AI_id=0;
		else playercolor=1,AI_id=1;

		playercolor=rand()%2;
		AI_id=1;

		My_AI_color = (playercolor ^ 1);
		MY_TOOLS::init();
		MY_AI::init(My_AI_color);

		setfillcolor(RGB(255, 205, 150)); settextstyle(30, 15, 0, 0, 0, 1000, false, false, false); settextcolor(BLACK);
		solidrectangle(40, 25, 645, 630);

		draw(1); // 绘制

				 // 上一个鼠标停的坐标
		int oldi = 0, oldj = 0;
		// 绘制背景
		setfillcolor(RGB(255, 205, 150)); solidrectangle(40, 25, 645, 630); settextstyle(30, 15, 0, 0, 0, 1000, false, false, false); settextcolor(BLACK);


		// 输出标示语
		TCHAR text[500];
		if (playercolor == 0) _stprintf(text, _T("No.%d 玩家执白后行，电脑执黑先行"), gamecnt+1);
		else _stprintf(text, _T("No.%d 玩家执黑后行，电脑执白先行"), gamecnt+1);
		
		outtextxy(150, 650, text);
		
		draw(1); // 绘制
		while (1) {
			if (whoplay == playercolor) {
				// 玩家下棋
				int flag = 1;
				while (flag) {
					MOUSEMSG mouse = GetMouseMsg(); // 获取鼠标信息

					for (int i = 0; i < MAX_SIZE&&flag; i++)for (int j = 0; j < MAX_SIZE; j++)
						if (mouse.x > BOX[i][j].x && mouse.x<BOX[i][j].x + 30 && mouse.y>BOX[i][j].y && mouse.y < BOX[i][j].y + 30 && BOX[i][j].v == -1) {
							if (mouse.mkLButton) {// 如果按下了
								BOX[i][j].v = playercolor; // 下棋
								BOX[i][j].isnew = true;        // 新位置更新

								my_luozi(whoplay, i + 1, j + 1);
								++nowcnt[whoplay];
								Judge_win(whoplay, i + 1, j + 1);

								oldi = -1; oldj = -1;
								flag = 0;
								break;
							}
							// 更新选择框
							BOX[oldi][oldj].isnew = false;
							BOX[oldi][oldj].draw();
							BOX[i][j].isnew = true;
							BOX[i][j].draw();
							oldi = i; oldj = j;
						}
				}
			}
			else {
				seat best = (AI_id==1?my_AI():my_AI_());

				BOX[best.i][best.j].v = whoplay;//下在最佳位置
				BOX[best.i][best.j].isnew = true;

				my_luozi(whoplay, best.i + 1, best.j + 1);
				++nowcnt[whoplay];
				Judge_win(whoplay, best.i + 1, best.j + 1);
			}

			whoplay ^= 1;

			if (win == -1) {// 如果没有人胜利
				draw(1); Sleep(500);
			}
			else {
				draw(1);
				++gamecnt;
				if(AI_id==0)++wincnt_AI0[My_AI_color][win]; 
				else ++wincnt_AI1[My_AI_color][win]; 
				if (1) {
					settextcolor(RGB(0, 255, 0));
					if (win == 0)outtextxy(320, 320, _T("白胜"));
					if (win == 1)outtextxy(320, 320, _T("黑胜"));
					if (win == 2)outtextxy(320, 320, _T("平局"));
					if (gamecnt == Test_cnt) {
						using Machine_Learning::print_number;
						//记录本次对弈数据
						Machine_Learning::open_file_id(1);

						//AI0后手，白：黑：平
						print_number(wincnt_AI0[0][0]); putchar(','); putchar(' '); print_number(wincnt_AI0[0][1]); putchar(','); putchar(' '); print_number(wincnt_AI0[0][2]);
						putchar(' ');
						//AI0先手，白：黑：平
						print_number(wincnt_AI0[1][0]); putchar(','); putchar(' '); print_number(wincnt_AI0[1][1]); putchar(','); putchar(' '); print_number(wincnt_AI0[1][2]);
						putchar(' ');
						
						//AI1后手，白：黑：平
						print_number(wincnt_AI1[0][0]); putchar(','); putchar(' '); print_number(wincnt_AI1[0][1]); putchar(','); putchar(' '); print_number(wincnt_AI1[0][2]);
						putchar(' ');
						//AI1先手，白：黑：平
						print_number(wincnt_AI1[1][0]); putchar(','); putchar(' '); print_number(wincnt_AI1[1][1]); putchar(','); putchar(' '); print_number(wincnt_AI1[1][2]);
						putchar(' ');
						
						Machine_Learning::close_file();

					}
					system("pause");
				}
				return;
			}
		}
	}
	void player_vs_my_AI() {
		gamecnt = 0; 
		while (gamecnt<Test_cnt) {
			init(); // 外面的初始化

			game_player_vs_my_AI_game(); // 游戏开始

			cleardevice();
		}

	}
}
using Player_Vs_My_AI::player_vs_my_AI;
int main(){
	initgraph(700, 700, NOMINIMIZE); setbkcolor(WHITE); cleardevice(); setbkmode(TRANSPARENT);
	Setseed(0);
if(MY_AI::find_bestrate)Machine_Learning::find_best_rate();
if(MY_AI::find_bestdw)Machine_Learning::find_best_dw();
else //game_machine_vs_machine();
player_vs_my_AI();
}