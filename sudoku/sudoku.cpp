// sudoku.cpp: 定义控制台应用程序的入口点。
//

//测试输出终局：-c 20
//测试熟读求解：-s shuduceshi.txt
#include "stdafx.h"
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<ctime>
#include<cmath>
#include<fstream>
#include<algorithm>
using namespace std;

//输出终局
ofstream output("sudoku.txt");
int cnt, cmp, need;
char sortline[15] = { '1','2','3','4','5','7','8','9','6' };//第一排的顺序 
char store[180000000];//存储数据，一次写入，速度会快很多
int three1[3][5] = { {0,3,6},{0,6,3} };
int three2[7][5] = { {2,5,8},{2,8,5},{5,2,8},{5,8,2},{8,2,5},{8,5,2} };
int three3[7][5] = { {1,4,7},{1,7,4},{4,1,7},{4,7,1},{7,1,4},{7,4,1} };//不同的顺序 

//解数独
ofstream solve_output("sudoku.txt");
char judge[3][10][10];//用于判断当前位置数字是否与行列和九宫格冲突
char flagma[9][9];
char chout[500];

int sudokuproducer(int p)
{
	while (next_permutation(sortline, sortline + 8))
	{
		for (int x = 0;x < 2;x++)
		{
			for (int y = 0;y < 6;y++)
			{
				for (int z = 0;z < 6;z++)//三重循环分别对应three1（前三行）、three2（中间三行）、three3（最后三行）
				{
					for (int i = 0;i < 3;i++) //生成前三行
					{
						store[cnt++] = sortline[(8 + three1[x][i]) % 9];
						for (int j = 1;j < 17;j++) {
							store[cnt++] = ' ';
							j++;
							store[cnt++] = sortline[((16 - j) / 2 + three1[x][i]) % 9];
						}
						store[cnt++] = '\n';
					}
					for (int i = 0;i < 3;i++) //生成中间三行
					{
						store[cnt++] = sortline[(8 + three2[y][i]) % 9];
						for (int j = 1;j < 17;j++) {
							store[cnt++] = ' ';
							j++;
							store[cnt++] = sortline[((16 - j) / 2 + three2[y][i]) % 9];
						}
						store[cnt++] = '\n';
					}
					for (int i = 0;i < 3;i++) //生成最后三行
					{
						store[cnt++] = sortline[(8 + three3[z][i]) % 9];
						for (int j = 1;j < 17;j++) {
							store[cnt++] = ' ';
							j++;
							store[cnt++] = sortline[((16 - j) / 2 + three3[z][i]) % 9];
						}
						store[cnt++] = '\n';
					}
					cmp++;
					if (cmp == p)//满足数量
					{
						return 1;
					}
					else store[cnt++] = '\n';
				}
			}
		}
	}
	return 0;
}

bool findflag = false, flag = true;

int sudokusolver(int row, int column)
{
	bool searchflag = false;
	while (flagma[row][column] != '0') 
	{
		if (column < 8) {
			column++;
		}
		else {
			column = 0;
			row++;
		}
		if (row == 9) {
			findflag = true;
			return 1;
		}
	}
	for (int i = 1;i <= 9;i++)
	{
		//如果这个数在行列九宫格中都没有被填过
		if (judge[0][row][i] == 0 && judge[1][column][i] == 0 && judge[2][row / 3 * 3 + column / 3][i] == 0)
		{
			searchflag = true;
			judge[0][row][i] = 1;
			judge[1][column][i] = 1;
			judge[2][row / 3 * 3 + column / 3][i] = 1;
			flagma[row][column] = i + '0';
			sudokusolver(row, column);//递归
		}
		if (searchflag == true)//是否在递归中
		{
			searchflag = false;
			if (findflag == false)//回溯并重置当前值
			{
				judge[0][row][i] = 0;
				judge[1][column][i] = 0;
				judge[2][row / 3 * 3 + column / 3][i] = 0;
				flagma[row][column] = '0';
			}
			else//已经找完所有空格
			{
				return 1;
			}
		}
	}
	return 0;
}

void outputsudoku()
{
	memset(chout, 0x0, sizeof(chout));//不初始化会烫
	int pout = 0;
	for (int i = 0;i < 9;i++)
	{
		for (int j = 0;j < 9;j++)
		{
			chout[pout++] = flagma[i][j];
			if ((pout + 1) % 18 == 0) {
				chout[pout++] = '\n';
			}
			else {
				chout[pout++] = ' ';
			}
		}
	}
}

int main(int argc,char*argv[])
{
	int len;
	FILE *fp1;
	fopen_s(&fp1,argv[2], "r");
	if (argc == 3 && strcmp(argv[1], "-c") == 0)
	{
		len = strlen(argv[2]);
		for (int i = 0;i < len;i++)
		{
			if (argv[2][i] >= '0'&&argv[2][i] <= '9')
			{
				need = need + ((argv[2][i] - '0')*(int)pow(10, len - i - 1));
			}
			else
			{
				cout << "输入有误！\n" << endl;
				return 0;
			}
		}
		while (cmp < need)
		{
			sudokuproducer(need);
		}
		output << store;
	}
	else if (argc == 3 && strcmp(argv[1], "-s") == 0)
	{
		int p = 0;	//是否满9行
		char ch[100];
		while (fgets(ch, 20, fp1))
		{
			//判别空行
			if (strcmp(ch, "\n") == 0) {
				continue;
			}
			//负责读入
			for (int i = 0;i < 17;i++) 
			{
				if (i % 2 == 0) {
					int cha = ch[i] - '0';
					flagma[p][i / 2] = ch[i];
					judge[0][p][cha] = 1;
					judge[1][i / 2][cha] = 1;
					judge[2][p / 3 * 3 + i / 6][cha] = 1;
				}
			}
			p++;
			if (p == 9) 
			{
				if (flag == false) {
					solve_output << endl;
				}
				else {
					flag = false;
				}
				findflag = false;
				sudokusolver(0, 0);
				outputsudoku();
				solve_output << chout;
				p = 0;
				memset(judge, 0, sizeof(judge));
			}
		}
	}
	else
	{
		cout << "输入有误！\n" << endl;
		return 0;
	}
}
