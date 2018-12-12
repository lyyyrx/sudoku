// sudoku.cpp: 定义控制台应用程序的入口点。
//

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
char store[180000000];//存储数据，一次写入
char three1[3][5] = { "036","063" }, three2[7][5] = { "258","285","528","582","825","852" }, three3[7][5] = { "147","174","417","471","714","741" };//不同的顺序 

//解数独
ofstream solve_output("sudoku.txt");
char judge[3][10][10];
char flagma[10][10];

void sudokuproducer()
{
	while (next_permutation(sortline, sortline + 8))
	{
		for (int x = 0;x < 2;x++)
		{
			for (int y = 0;y < 6;y++)
			{
				for (int z = 0;z < 6;z++)//三重循环分别对应three1、three2、three3
				{
					for (int i = 0;i < 3;i++) {
						store[cnt++] = sortline[(8 + three1[x][i] - '0') % 9];
						for (int j = 1;j < 17;j++) {
							store[cnt++] = ' ';
							j++;
							store[cnt++] = sortline[((16 - j) / 2 + three1[x][i] - '0') % 9];
						}
						store[cnt++] = '\n';
					}

					for (int i = 0;i < 3;i++) {
						store[cnt++] = sortline[(8 + three2[y][i] - '0') % 9];
						for (int j = 1;j < 17;j++) {
							store[cnt++] = ' ';
							j++;
							store[cnt++] = sortline[((16 - j) / 2 + three2[y][i] - '0') % 9];
						}
						store[cnt++] = '\n';
					}

					for (int i = 0;i < 3;i++) {
						store[cnt++] = sortline[(8 + three3[z][i] - '0') % 9];
						for (int j = 1;j < 17;j++) {
							store[cnt++] = ' ';
							j++;
							store[cnt++] = sortline[((16 - j) / 2 + three3[z][i] - '0') % 9];
						}
						store[cnt++] = '\n';
					}
					
					store[cnt++] = '\n';

					if (++cmp == need)
					{
						return;
					}
				}
			}
		}
	}
}
bool findflag = false, flag = true;
void sudokusolver(int row, int column)
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
			return;
		}
	}
	for (int i = 1;i <= 9;i++)
	{
		if (judge[0][row][i] == 0 && judge[1][column][i] == 0 && judge[2][row / 3 * 3 + column / 3][i] == 0)
		{
			searchflag = true;
			judge[0][row][i] = 1;
			judge[1][column][i] = 1;
			judge[2][row / 3 * 3 + column / 3][i] = 1;
			flagma[row][column] = i + '0';
			sudokusolver(row, column);
		}
		if (searchflag == true)
		{
			searchflag = false;
			if (findflag == true)
			{
				return;
			}
			else
			{
				judge[0][row][i] = 0;
				judge[1][column][i] = 0;
				judge[2][row / 3 * 3 + column / 3][i] = 0;
				flagma[row][column] = '0';
			}
		}
	}
}

void outputsudoku()
{
	char chout[1000];
	memset(chout, 0x0, sizeof(chout));
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
	solve_output << chout;
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
			sudokuproducer();
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
			//负责输入
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
				p = 0;
				//输出递归的数组
				outputsudoku();
				memset(judge, 0, sizeof(judge));
			}
		}
	}
	else
	{
		cout << "输入有误！\n" << endl;
	}
}
