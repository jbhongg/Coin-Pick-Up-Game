#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>
#include <process.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "winmm")

extern char map[20][39];

extern int color_num[5];//랜덤으로 받을 색
extern int c_x;
extern int c_y;
extern int y;
extern int x;
extern int user_x;
extern int user_y;
extern char key;
extern int x_b;
extern int y_b;
extern int clr;
extern int rand_col;
extern int m_count;
extern int d_count;
void print_map();

void gotoxy(int x, int y);

void textcolor(int color_num);

unsigned __stdcall tagger(void *arg);



void objimage(int x, int y, wchar_t* temp,int m_x,int m_y);

void move(int x_b, int y_b);

void background();

void Start_Screen();

void Menu_Screen();

void Game_Start();

void Rule();

void gameover();