#include "header.h"

void gotoxy(int x, int y){
 COORD Pos = {x -1, y-1};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}
void textcolor(int color_num)
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),color_num);
}
unsigned __stdcall tagger(void *arg)
{
	srand(time(NULL));
	while(1)
	{
	
	//gotoxy(180,10);
	objimage(160,10,L"./Áøºó ¼ú·©1.bmp",200,300);
	Sleep(3000-((rand()%3)*1000));
	m_count=0;
	d_count=0;
	rand_col=color_num[rand()%5];
	
		if(rand_col==color_num[0])
		{
			gotoxy(150,5);
			textcolor(9); //ÆÄ¶û;
			printf("¡á\n");
			objimage(160,10,L"./Áøºó ¼ú·©2.bmp",200,300);
			
		}
		else if(rand_col==color_num[1])
		{
			gotoxy(150,5);
			textcolor(10);//ÃÊ·Ï
			printf("¡á\n");
			objimage(160,10,L"./Áøºó ¼ú·©2.bmp",200,300);
		}
		else if(rand_col==color_num[2])
		{
			gotoxy(150,5);
			textcolor(11);//¹ÎÆ®
			printf("¡á\n");
			objimage(160,10,L"./Áøºó ¼ú·©2.bmp",200,300);
		}
		else if(rand_col==color_num[3])
		{
			//gotoxy(0,10);
			//printf("ÇÇ¾ú½À´Ï´Ù!");
			gotoxy(150,5);
			textcolor(12);//»¡°­
			printf("¡á\n");
			objimage(160,10,L"./Áøºó ¼ú·©2.bmp",160,320);
			
		}
		else if(rand_col==color_num[4])
		{
			gotoxy(150,5);
			textcolor(14);//³ë¶û
			printf("¡á\n");
			objimage(160,10,L"./Áøºó ¼ú·©2.bmp",160,320);
		}
		Sleep(1000);
		if((m_count==0 && rand_col==9) || (rand_col==11 && m_count<2))//ÆÄ¶û ¹ÎÆ®»öÀÏ¶§ ¿òÁ÷ÀÌÁö ¾ÊÀ»½Ã °ÔÀÓ¿À¹ö
		{
			gameover();
			exit(0);
		}
		gotoxy(150,5);
		textcolor(15);
		printf(" ");
		rand_col=0;
		
	}
}

void move(int x_b, int y_b)
{
	user_x=x;
	user_y=y;
	key=_getch();
	switch(key)
	{
	case 72:
		gotoxy(x+1,y+1);printf("    ");
		gotoxy(x+1,y+2);printf("    "); 
		y=y-2;
		m_count+=1;
		
		if(map[y/2][x/4]==1)
			y=y+2;
		break;
	case 75:
		gotoxy(x+1,y+1);printf("    ");
		gotoxy(x+1,y+2);printf("    ");
		x=x-4;
		m_count+=1;
		
		if(map[y/2][x/4]==1)
			x=x+4;
		break;
	case 77:
		gotoxy(x+1,y+1);printf("    ");
		gotoxy(x+1,y+2);printf("    "); 
		x=x+4;
		m_count+=1;
		
		if(map[y/2][x/4]==1)
			x=x-4;
		break;
	case 80:
		gotoxy(x+1,y+1);printf("    ");
		gotoxy(x+1,y+2);printf("    "); 
		y=y+2;
		m_count+=1;
		
		if(map[y/2][x/4]==1)
			y=y-2;
		break;
	}
	//Sleep(100);
	
}


void objimage(int x, int y, wchar_t* temp ,int m_x,int m_y)
{
   x = 8 * x;
   y = 16 * y;
   HWND myconsole = GetConsoleWindow();
   //Get a handle to device context
   HDC mydc = GetDC(myconsole);

   HBITMAP hImage, hOldBitmap;
   HDC hMemDC = CreateCompatibleDC(mydc);

   // ÀÌ¹ÌÁö ·Îµå
   hImage = (HBITMAP)LoadImage(NULL,      temp,      IMAGE_BITMAP,      0,      0,      LR_LOADFROMFILE | LR_CREATEDIBSECTION);
   // ÀÌ¹ÌÁö Ãâ·Â ºÎºÐ
   hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
   BitBlt(mydc, x, y, m_x, m_y, hMemDC, 0, 0, SRCCOPY);

   // °¢Á¾ ¸Þ¸ð¸® ÇØÁ¦ 
   SelectObject(hMemDC, hOldBitmap);
   DeleteObject(hImage);
   DeleteDC(hMemDC);
   ReleaseDC(myconsole, mydc);
}
