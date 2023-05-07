// UIԴ���룺�¿ɼ� <emil09_chen@126.com>
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

// ���ƺ���

// ����λ�õ���
class seat{
public:
	int i = 0;      // y ����
	int j = 0;      // x ����
	int score = 0; // ����
};

// �������̵���
class box{
public:
	int x = 0;              // x ����
	int y = 0;              // y ����
	int v = -1;         // ֵ�����壺1�����壺0����λ��-1��
	int modle;              // ģʽ
	bool isnew = false;     // �Ƿ���ѡ���
	int score = 0;         // ����
	COLORREF color = WHITE; // ���̱���ɫ
public:
	void draw(){
		COLORREF thefillcolor = getfillcolor(); // ���������ɫ
		setlinestyle(PS_SOLID, 2);              // ����ʽ����
		setfillcolor(color);                    // �����ɫ����
		solidrectangle(x, y, x + 30, y + 30);   // �����ޱ߿��������
		if (isnew){
			// ��������µ�
			// ���Ʊ߿���
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
			// �����ǲ�ͬλ�����̵���ʽ
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
		case 0: // ����
			setfillcolor(WHITE);
			setlinestyle(PS_SOLID, 1);
			fillcircle(x + 15, y + 15, 13);
			break;
		case 1: // ����
			setfillcolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			fillcircle(x + 15, y + 15, 13);
			break;
		}
		setfillcolor(thefillcolor); // ��ԭ���ɫ
	}
};
box BOX[MAX_SIZE][MAX_SIZE];      // ����

// ��������
void draw(int ifdraw=1){
	int modle = 0;  // ������ʽ
	int score = 0; // ���������λ��
					// ���꣨��ֵ��
	TCHAR strnum[MAX_SIZE][3] = { _T("1"),_T("2") ,_T("3") ,_T("4"),_T("5") ,_T("6") ,_T("7"),_T("8"),_T("9"),_T("10"), _T("11"),_T("12") ,_T("13") ,_T("14"),_T("15"),_T("16"),_T("17"),_T("18"),_T("19")  };
	// ���꣨��ĸ��
	TCHAR strabc[MAX_SIZE][3] = { _T("A"),_T("B") ,_T("C") ,_T("D"),_T("E") ,_T("F") ,_T("G"),_T("H"),_T("I"),_T("J"), _T("K"),_T("L") ,_T("M") ,_T("N"),_T("O"),_T("P"),_T("Q"),_T("R"),_T("S")  };
	for (int i = 0, k = 0; i < 570; i += 30)
	{
		for (int j = 0, g = 0; j < 570; j += 30)
		{
			BOX[k][g].color = RGB(255, 205, 150);// ���̵�ɫ
												 // x��y ����
			BOX[k][g].x = 65 + j;
			BOX[k][g].y = 50 + i;
			BOX[k][g].score = 0;// ��ʼ������
								 // ������ʽ���ж�
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
			if(ifdraw)BOX[k][g].draw(); // ����
			if (BOX[k][g].isnew == true)BOX[k][g].isnew = false; // ����һ������λ�õĺڿ����
			g++;
		}
		k++;
	}
	// ������
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

int win = -1;         // ˭Ӯ�ˣ�0�����壬1�����壬2��ƽ�֣�
int nowcnt[2];
int dx[4]{ 1,0,1,1 }; // - | \ / �ĸ�����
int dy[4]{ 0,1,1,-1 };

// �Ծֳ�ʼ��
void init()
{
	win = -1;// ˭Ӯ��
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			BOX[i][j].score = 0;// ����
			BOX[i][j].v = -1;// ֵ
		}
	}
}

// �ж���Ӯ
void isWIN(){
	bool isinit = true; // �Ƿ�ոտ���
	for (int i = 0; i < MAX_SIZE; i++)
		for (int j = 0; j < MAX_SIZE; j++)
			if (BOX[i][j].v != -1){
				// ����ÿ�����ܵ�λ��
				isinit = false;                 // ����У���ô�Ͳ��Ǹոտ���
				int nowcolor = BOX[i][j].v; // ���ڱ���������ɫ
				int length[4] = { 0,0,0,0 };    // �ĸ�����ĳ���
				for (int k = 0; k < 4; k++){
					// ԭ��ͬѰ�����λ��
					int nowi = i,nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].v == nowcolor)length[k]++,nowj += dx[k],nowi += dy[k];
					nowi = i;nowj = j;
					while (nowi <= 18 && nowj <= 18 && nowi >= 0 && nowj >= 0 && BOX[nowi][nowj].v == 1 - nowcolor)length[k]++,nowj -= dx[k],nowi -= dy[k];
				}
				for (int k = 0; k < 4; k++)if (length[k] >= 5)win = nowcolor;// ���������
				if ((!isinit) && nowcnt[0]+nowcnt[1]==MAP_SIZE)win = 2;// ������ǿ������������� ƽ��
			}
}

seat findbestseat(int color){
	if (color==1&&nowcnt[0] + nowcnt[1] == 0) {seat Ans;Ans.i=Ans.j=9;return Ans;}//�ڷ���һ�ӱ�����Ԫ
	// ���ֱ�
	int Score[3][5] = {
		{ 0, 20, 360, 5800, 92840 }, // ����0��
		{ 0, 0, 20, 360, 92840 },    // ����1��
		{ 0, 0, 0, 0, 92840 }        // ����2��
	};
	seat bestseat;              // ���λ��
	int MAXscore[MAP_SIZE] = { 0 }; // ��ѷ����������ж����
	int MAXx[MAP_SIZE] = { 0 };      // ��� x ���꣨�����ж����
	int MAXy[MAP_SIZE] = { 0 };      // ��� y ���꣨�����ж����
	int score = 0;             // ��һ����ѷ�������λ��
	int truescore;             // �������ѷ���λ��
	int nowi = 0;               // ���ڱ�������y����
	int nowj = 0;               // ���ڱ�������x����
	int length[4];              // �ĸ�����ĳ���
	int emeny[4];               // �ĸ�����ĵ���
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (BOX[i][j].v == -1)
			{
				// ����ÿһ�����ܵ�λ��

				// �Լ�
				BOX[i][j].v = color; // ������������
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
					length[k] -= 2; // �жϳ���
					if (length[k] > 4)
					{
						length[k] = 4;
					}
					BOX[i][j].score += Score[emeny[k]][length[k]] * 4 + !(!length[k]) * 20;//�ӷ�ϵͳ
					length[k] = 0;
					emeny[k] = 0;
				}
				// ���ˣ�ԭ��ͬ�ϣ�
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
				// �������߷�����ͬ
				MAXscore[score] = BOX[i][j].score;
				MAXy[score] = i;
				MAXx[score] = j;
				score++;
				// ����һ������������
			}
			if (BOX[i][j].score > MAXscore[0])
			{
				// �������߷�����
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
				// ��������ټ���
			}
		}
	}
	// �������λ��
	truescore = rand() % score;
	bestseat.i = MAXy[truescore];
	bestseat.j = MAXx[truescore];
	bestseat.score = MAXscore[truescore];
	// ����λ��
	return bestseat;
}

namespace SOMETOOLS {
#define Re register int
#define LL long long
#define LD double
#define gettime _GETTIME_
	inline LD gettime() { return (LD)clock() / (LD)CLOCKS_PER_SEC; }//��?????

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
		for (Re O = 0; O < 4; ++O) {//�ĸ�����
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

	//�Կ���������
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

LL score_atk[5][3] = { 0,0,0,//score[i][j]�����Ӻ��γ� ��j��������i������ �ķ���
2  , 1   , 0, //���Ӻ��γ� ��0,1,2�������� 1 ������
1000 , 100  , 0, //���Ӻ��γ� ��0,1,2�������� 2 ������
10000, 990  , 0, //���Ӻ��γ� ��0,1,2�������� 3 ������
1e12 , 9990, 0, //���Ӻ��γ� ��0,1,2�������� 4 ������
};
LL	score_def[5][2] = { 0,0,//score[i][j]�����Ӻ����� ԭ����j��������i������ �ķ���
2   , 1  , //���Ӻ����� ԭ����0,1�������� 1 ������
1000  , 100  , //���Ӻ����� ԭ����0,1�������� 2 ������
10000 , 990 , //���Ӻ����� ԭ����0,1�������� 3 ������
-1  , 1e10, //���Ӻ����� ԭ����0,1�������� 4 ������
};
//�ҷ�һ��ʤ�� ---1e16
//>> ��ֹ�Է�һ��ʤ�� ---1e14
//>> �ҷ��γ�0��4�� ---1e12
//>> ��ֹ�Է��γ�0��4���������Է�ԭ0��3���� ---1e10
//>> �ҷ��γ�0��3�� >= �ҷ��γ�1��4�� ---1000,900
//>> ��ֹ�Է��γ�0��3���������Է�ԭ0��2���� ---500
namespace MY_AI_0 {
	inline LL calc_atk(Re color, Re i, Re j) {//���������Է��ĵ÷֣�
		LL ans = 0; Re d_color = (color ^ 1);
		for (Re O = 0; O < 4; ++O) {//�ĸ�����
			Re t = 1, du = 0;

			Re nx = i, ny = j, wx = dx[O], wy = dy[O];
			while (Inmap(nx + wx, ny + wy)&&col[nx + wx][ny + wy] == color)nx += wx, ny += wy, ++t;
			if (!Inmap(nx + wx, ny + wy)||col[nx + wx][ny + wy] == d_color)du++;

			nx = i, ny = j;
			while (Inmap(nx - wx, ny - wy)&&col[nx - wx][ny - wy] == color)nx -= wx, ny -= wy, ++t;
			if (!Inmap(nx - wx, ny - wy)||col[nx - wx][ny - wy] == d_color)du++;

			if (t >= 5)return 1e16;//�ҷ�һ��ʤ��
			//t<=4:
			ans += score_atk[t][du];
		}
		return ans;
	}
	inline LL calc_def(Re color, Re i, Re j) {//�����¶Է�˫�ߵĵ÷֣�
		LL ans = 0; Re d_color = (color ^ 1);
		for (Re O = 0; O < 4; ++O) {//�ĸ�����
			Re t = 1, du=0;

			Re nx = i, ny = j, wx = dx[O], wy = dy[O];
			while (Inmap(nx + wx, ny + wy)&&col[nx + wx][ny + wy] == d_color)nx += wx, ny += wy, ++t;
			if (!Inmap(nx + wx, ny + wy)||col[nx + wx][ny + wy] == color)du++;

			nx = i, ny = j;
			while (Inmap(nx - wx, ny - wy)&&col[nx - wx][ny - wy] == d_color)nx -= wx, ny -= wy, ++t;
			if (!Inmap(nx - wx, ny - wy)||col[nx - wx][ny - wy] == color)du++;

			if (t >= 5)return 1e14;//��ֹ�Է�һ��ʤ��
			//t<=4:
			if(t==4&&!du)return 1e10;//��ֹ�Է��γ�0��4���������Է�ԭ0��3����
			if(du<2)ans += score_def[t][du];

		}
		return ans;
	}
	struct AI_0 {//��������
		int color;
		LL rate[5] = { 0,3,4,2,1 };
		int Qt; QAQ Qs[361 + 3];
		int ILp, IRp, JLp, JRp;//ÿ�ξֲ�������Ĳ��ҷ�Χ
		struct MERGE {//���鼯�Ż�����ö���ٶ�
			int fa[19 + 3];
			inline int find(Re x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
		}T1[19 + 3];
		QAQ my_AI() {//Ѱ��������λ��
			Qt = 0;
			for (Re i = ILp; i <= IRp; ++i)
				for (Re j = T1[i].find(JLp); j <= JRp; j = T1[i].find(j + 1)) {
					LL ss0 = calc_atk(color, i, j)*rate[1] + calc_def(color, i, j)*rate[2] + calc_atk(color ^ 1, i, j)*rate[3] + calc_def(color ^ 1, i, j)*rate[4];//�ҹ�+�ҷ�+����+����
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
			ILp = IRp = JLp = JRp = 10;//�ڷ���һ�ӱ�����Ԫ
			for (Re i = 1; i <= 19; ++i)
				for (Re j = 1; j <= 19 + 1; ++j)
					T1[i].fa[j] = j;
		}
	}my_ai_0;
}
using MY_AI_0::calc_atk;
using MY_AI_0::calc_def;
namespace MY_AI{
	const int MAX_DEEP_N=6+5;//MAX_DEEP:����������
	const int MAX_WIDE_N=10+5;//MAX_POINT������ÿ����

	const LL dfs_inf=1e17;
	struct AI_1 {//Ԥ�Ծ���
		struct CALC_ {
			LL rate[2][5] = { 
				0,3,4,2,1,
				0,3,4,2,1,
			};
			int MAX_deep,MAX_wide;
			int Qt; QAQ Qs[3610 + 3];
			int ILp, IRp, JLp, JRp;//ÿ�ξֲ�������Ĳ��ҷ�Χ
			struct MERGE {//���鼯�Ż�����ö���ٶ�
				int fa[190 + 3];
				inline int find(Re x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
			}T1[190 + 3];

			inline void find_goodpoint(Re color,Re &last_Qt,QAQ last_Qs[]) {//Ѱ��������λ��
				Qt = 0;
				for (Re i = ILp; i <= IRp; ++i)
					for (Re j = T1[i].find(JLp); j <= JRp; j=T1[i].find(j+1))if(col[i][j]==-1){
						LL ss0 = calc_atk(color, i, j)*rate[color][1] + calc_def(color, i, j)*rate[color][2]
							+calc_atk(color ^ 1, i, j)*rate[color][3] + calc_def(color ^ 1, i, j)*rate[color][4];//�ҹ�+�ҷ�+����+����
						if (!Qt || ss0 > Qs[1].v)Qs[Qt = 1] = QAQ(i, j, ss0);
						else if (ss0 == Qs[Qt].v)Qs[++Qt] = QAQ(i, j, ss0);
					}
				if(Qt>MAX_wide){//����ÿ����������
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
				ILp = IRp = JLp = JRp = 10;//�ڷ���һ�ӱ�����Ԫ
				for (Re i = 1; i <= 19; ++i)
					for (Re j = 1; j <= 19 + 1; ++j)
						T1[i].fa[j] = j;
			}
		}calc_score;
		int AI_1_color,MAX_deep,MAX_wide;
		LL ppp;
		inline LL findmin(Re deep,LL alpha,Re op) {//���������Ҿ���С
			//cleardevice();
			//TCHAR text[500];_stprintf(text, _T("min:ballcnt=(%d,%d) deep=%d op=%d ppp=%d"), ballcnt[0],ballcnt[1],deep,op,++ppp);
			//outtextxy(150, 650, text);
			if(MY_TOOLS::dfs_judge_win())return dfs_inf;//��Ӯ��

			if(ballcnt[0]+ballcnt[1]==MAP_SIZE)return 0;//ƽ��
			if(deep>MAX_deep)return 0;//�����������

			QAQ to;LL ans=dfs_inf;//׼��һ�����ڶ�����˵���������߷֣�

			int Qt;QAQ Qs[MAX_WIDE_N+1]; calc_score.find_goodpoint(op,Qt,Qs);

			for(Re i=1;i<=Qt;++i){
				QAQ to=Qs[i];
				calc_score.dfs_luozi(to.x,to.y),MY_TOOLS::dfs_luo(op,to.x,to.y);//��̽����

				ans=min(ans,-to.v+findmax(deep+1,ans+to.v,op^1));//����һ��

				calc_score.dfs_luozi_back(),MY_TOOLS::dfs_luo_back();//��������

				if(ans<=alpha)return ans;
			}
			return ans;
		}
		inline LL findmax(Re deep,LL beta,Re op) {//���뾡����
			if(MY_TOOLS::dfs_judge_win())return -dfs_inf;//����Ӯ��

			if(ballcnt[0]+ballcnt[1]==MAP_SIZE)return 0;//ƽ��
			if(deep>MAX_deep)return 0;//�����������
			QAQ to;LL ans=-dfs_inf;//׼��һ����������˵���������ͷ֣�
			int Qt;QAQ Qs[MAX_WIDE_N+1]; calc_score.find_goodpoint(op,Qt,Qs);

			for(Re i=1;i<=Qt;++i){
				QAQ to=Qs[i];
				calc_score.dfs_luozi(to.x,to.y),MY_TOOLS::dfs_luo(op,to.x,to.y);//��̽����
				
				ans=max(ans,to.v+findmin(deep+1,ans-to.v,op^1));//����һ��
				
				calc_score.dfs_luozi_back(),MY_TOOLS::dfs_luo_back();//��������
				
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
				calc_score.dfs_luozi(to.x,to.y),MY_TOOLS::dfs_luo(AI_1_color,to.x,to.y);//��̽����
				LL s=findmin(1,ans.v-to.v,AI_1_color^1);//����һ��
				if(to.v+s > ans.v)ans=QAQ(to.x,to.y,to.v+s);//�Ƚϴ�С
				calc_score.dfs_luozi_back(),MY_TOOLS::dfs_luo_back();//��������
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
		2,4,//����
		1,9,//����
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
	const int Test_cnt=500;//���ľ���
	const int Show_game = 0;//�Ƿ�չʾ���Ĺ���
	int My_AI_color = 0;
	int gamecnt,wincnt[3];
	void print_game_result() {//���Test_cnt�ֶ��ĵĽ��
		TCHAR text[500];
		_stprintf(text, _T("��ʤ%d�Σ���ʤ%d�Σ�ƽ%d��"), wincnt[0], wincnt[1], wincnt[2]);
		outtextxy(150, 650, text);
	}
	inline void my_luozi(Re whoplay,Re bx,Re by) {
		MY_TOOLS::luo(whoplay,bx,by);
		MY_AI::luozi_update(bx, by);
	}
	void gamestart() {//��������
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

			BOX[best.i][best.j].v = whoplay,BOX[best.i][best.j].isnew = true;//����AI����

			my_luozi(whoplay, best.i + 1, best.j + 1);//�ҵ�AI����

			++nowcnt[whoplay];

			Judge_win(whoplay,best.i+1, best.j+1);//�ж϶Ծ��Ƿ����
			
			whoplay^=1;

			if (win == -1) {draw(Show_game);if (Show_game)Sleep(500);}//�Ծ���δ����
			else {//�Ծֽ���
				draw(Show_game);

				++wincnt[win]; ++gamecnt;//ͳ�ƶ��Ľ��
				
				if (Show_game) {//����Ļ��������ֽ��
					settextcolor(RGB(0, 255, 0));
					if (win == 0)outtextxy(320, 320, _T("��ʤ"));
					if (win == 1)outtextxy(320, 320, _T("��ʤ"));
					if (win == 2)outtextxy(320, 320, _T("ƽ��"));
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
	void battle_start() {//����Test_cnt��
		MvM_init();

		while (gamecnt < Test_cnt) {
			init(); // ����ĳ�ʼ��

			Setseed(rand());
			gamestart(); // ��Ϸ��ʼ

			cleardevice();

			setfillcolor(RGB(255, 205, 150)); settextstyle(30, 15, 0, 0, 0, 1000, false, false, false); settextcolor(BLACK);
			//print_game_result();

			if (gamecnt == Test_cnt) {
				solidrectangle(40, 25, 645, 630);
				draw(1);
			}
			if (gamecnt == Test_cnt) {
				settextcolor(RGB(0, 255, 0));
				if (win == 0)outtextxy(320, 320, _T("��ʤ"));
				if (win == 1)outtextxy(320, 320, _T("��ʤ"));
				if (win == 2)outtextxy(320, 320, _T("ƽ��"));
			}
			//Sleep(1);
		}
		setfillcolor(RGB(255, 205, 150)); settextstyle(30, 15, 0, 0, 0, 1000, false, false, false); settextcolor(BLACK);
		
	}
	const int print_file=1;
	inline void find_best_rate() {//Ѱ����ѹ����Ȳ���
		if(print_file)open_file_id(1);//��ӡ���ζ������ݵ��ļ�

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
						_stprintf(text, _T("%d,%d,%d,%d,��%d�Σ���%d�Σ�ƽ%d��"), i1, i2, i3, i4, wincnt[0], wincnt[1], wincnt[2]);
						outtextxy(150, 650, text);
						system("pause");
					}
				}
		if(print_file)close_file();
	}
	inline void find_best_dw() {//Ѱ��������Ȳ���
		if(print_file)open_file_id(1);//��ӡ���ζ������ݵ��ļ�

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
						_stprintf(text, _T("%d,%d_vs_ckj: ��%d�Σ���%d�Σ�ƽ%d��"), i1, i2,  wincnt[0], wincnt[1], wincnt[2]);
						//_stprintf(text, _T("2,5_vs_%d,%d: ��%d�Σ���%d�Σ�ƽ%d��"), i1, i2,  wincnt[0], wincnt[1], wincnt[2]);
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

			//��¼���ζ�������
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

		draw(1); // ����

				 // ��һ�����ͣ������
		int oldi = 0, oldj = 0;
		// ���Ʊ���
		setfillcolor(RGB(255, 205, 150)); solidrectangle(40, 25, 645, 630); settextstyle(30, 15, 0, 0, 0, 1000, false, false, false); settextcolor(BLACK);


		// �����ʾ��
		TCHAR text[500];
		if (playercolor == 0) _stprintf(text, _T("No.%d ���ִ�׺��У�����ִ������"), gamecnt+1);
		else _stprintf(text, _T("No.%d ���ִ�ں��У�����ִ������"), gamecnt+1);
		
		outtextxy(150, 650, text);
		
		draw(1); // ����
		while (1) {
			if (whoplay == playercolor) {
				// �������
				int flag = 1;
				while (flag) {
					MOUSEMSG mouse = GetMouseMsg(); // ��ȡ�����Ϣ

					for (int i = 0; i < MAX_SIZE&&flag; i++)for (int j = 0; j < MAX_SIZE; j++)
						if (mouse.x > BOX[i][j].x && mouse.x<BOX[i][j].x + 30 && mouse.y>BOX[i][j].y && mouse.y < BOX[i][j].y + 30 && BOX[i][j].v == -1) {
							if (mouse.mkLButton) {// ���������
								BOX[i][j].v = playercolor; // ����
								BOX[i][j].isnew = true;        // ��λ�ø���

								my_luozi(whoplay, i + 1, j + 1);
								++nowcnt[whoplay];
								Judge_win(whoplay, i + 1, j + 1);

								oldi = -1; oldj = -1;
								flag = 0;
								break;
							}
							// ����ѡ���
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

				BOX[best.i][best.j].v = whoplay;//�������λ��
				BOX[best.i][best.j].isnew = true;

				my_luozi(whoplay, best.i + 1, best.j + 1);
				++nowcnt[whoplay];
				Judge_win(whoplay, best.i + 1, best.j + 1);
			}

			whoplay ^= 1;

			if (win == -1) {// ���û����ʤ��
				draw(1); Sleep(500);
			}
			else {
				draw(1);
				++gamecnt;
				if(AI_id==0)++wincnt_AI0[My_AI_color][win]; 
				else ++wincnt_AI1[My_AI_color][win]; 
				if (1) {
					settextcolor(RGB(0, 255, 0));
					if (win == 0)outtextxy(320, 320, _T("��ʤ"));
					if (win == 1)outtextxy(320, 320, _T("��ʤ"));
					if (win == 2)outtextxy(320, 320, _T("ƽ��"));
					if (gamecnt == Test_cnt) {
						using Machine_Learning::print_number;
						//��¼���ζ�������
						Machine_Learning::open_file_id(1);

						//AI0���֣��ף��ڣ�ƽ
						print_number(wincnt_AI0[0][0]); putchar(','); putchar(' '); print_number(wincnt_AI0[0][1]); putchar(','); putchar(' '); print_number(wincnt_AI0[0][2]);
						putchar(' ');
						//AI0���֣��ף��ڣ�ƽ
						print_number(wincnt_AI0[1][0]); putchar(','); putchar(' '); print_number(wincnt_AI0[1][1]); putchar(','); putchar(' '); print_number(wincnt_AI0[1][2]);
						putchar(' ');
						
						//AI1���֣��ף��ڣ�ƽ
						print_number(wincnt_AI1[0][0]); putchar(','); putchar(' '); print_number(wincnt_AI1[0][1]); putchar(','); putchar(' '); print_number(wincnt_AI1[0][2]);
						putchar(' ');
						//AI1���֣��ף��ڣ�ƽ
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
			init(); // ����ĳ�ʼ��

			game_player_vs_my_AI_game(); // ��Ϸ��ʼ

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