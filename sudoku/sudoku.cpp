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

void sudokuproducer()
{
	do 
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
	} while (next_permutation(sortline, sortline + 8));
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

	}
	else
	{
		cout << "输入有误！\n" << endl;
	}
}

