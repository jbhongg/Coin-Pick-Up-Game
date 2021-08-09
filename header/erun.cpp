#include "header.h"

#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x000e);
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x000c);
#define ORIGINAL SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0007);
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0009);

int color_num[5]={9,10,11,12,14};//랜덤으로 받을 색
int c_x=100;
int c_y=12;
int y=24;
int x=4;
int user_x;
int user_y;
char key;
int x_b=101;
int y_b=25;
int clr;
int rand_col;
int m_count;
int d_count;
int main()
{
	system("mode con: cols=190 lines=43");
	background();
	Start_Screen();
	Menu_Screen();


	

}
//main.c

void background()
{
	gotoxy(5, 2); printf("┌────────────────────────────────────────────────────────────────────────────────────────┐");
	gotoxy(5, 3); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 4); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 5); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 6); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 7); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 8); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 9); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 10); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 11); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 12); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 13); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 14); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 15); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 16); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 17); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 18); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 19); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 20); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 21); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 22); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 23); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 24); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 25); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 26); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 27); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 28); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 29); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 30); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 31); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 32); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 33); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 34); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 35); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 36); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 37); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 38); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 39); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 40); printf("│                                                                                                                                                                                │ ");
	gotoxy(5, 41); printf("└────────────────────────────────────────────────────────────────────────────────────────┘");
	gotoxy(5, 46);
}

void Start_Screen()
{

	gotoxy(0, 0);
	printf("\n");
	gotoxy(40, 5);
	printf("  ■■■  ■■■     ■   ■     ■■ ■■           ■");
	gotoxy(40, 6);
	printf("  ■  ■      ■   ■■■ ■       ■   ■           ■");
	gotoxy(40, 7);
	printf("  ■■■      ■    ■■  ■         ■       ■■   ■");
	gotoxy(40, 8);
	printf("                   ■  ■ ■     ■■■■■  ■  ■  ■");
	gotoxy(40, 9);
	printf("■■■■ ■■■■   ■■   ■■■    ■      ■  ■  ■");
	gotoxy(40, 10);
	printf("   ■        ■      ■   ■      ■■■■    ■■   ■");
	gotoxy(40, 11);
	printf("   ■       ■■  ■■■■■         ■              ■");
	gotoxy(40, 12);
	printf("   ■      ■  ■         ■       ■  ■            ■");
	gotoxy(40, 13);
	printf("   ■       ■■          ■      ■    ■           ■");


	gotoxy(70, 15);
	printf("          ■           ■         ■");
	gotoxy(70, 16);
	printf("          ■           ■       ■  ■           ■        ■");
	gotoxy(70, 17);
	printf("■■■■  ■   ■■    ■      ■    ■   ■     ■ ■■■ ■");
	gotoxy(70, 18);
	printf(" ■ ■    ■  ■  ■ ■■                 ■     ■ ■     ■");
	gotoxy(70, 19);
	printf(" ■ ■    ■   ■■    ■    ■■■■■■ ■     ■ ■     ■■■");
	gotoxy(70, 20);
	printf("■■■■  ■           ■      ■    ■   ■■■ ■ ■■■ ■ ");
	gotoxy(70, 21);
	printf("          ■       ■   ■     ■■■■          ■        ■");
	gotoxy(70, 22);
	printf("          ■     ■ ■ ■ ■   ■    ■          ■        ■");
	gotoxy(70, 23);
	printf("          ■    ■   ■    ■  ■■■■          ■        ■");

	/*gotoxy(70, 24);
	printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  \n");
	*/

	gotoxy(80, 29);
	RED printf("♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡\n"); ORIGINAL
		gotoxy(80, 30);
	RED printf("♡                                  ♡\n"); ORIGINAL
		gotoxy(80, 31);
	RED printf("♡                                  ♡\n"); ORIGINAL
		gotoxy(80, 32);
	RED printf("♡                                  ♡\n"); ORIGINAL
		gotoxy(80, 33);
	RED printf("♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡\n"); ORIGINAL
		while (1)
		{
			gotoxy(85, 31);
			YELLOW printf("<PRESS ENTER KEY TO START>\n"); ORIGINAL
				Sleep(400);
			gotoxy(85, 31);
			printf("                           \n\n\n");
			Sleep(400);

			if (_kbhit())
				break;
		}
}

/*system("cls");
printf("loading...");*/

void Menu_Screen()
{
	int a;

	system("cls");
	background();
	gotoxy(70, 15);
	printf("----------------------------------------");
	gotoxy(70, 16);
	printf("----------------------------------------\n");
	gotoxy(82, 18);
	printf("1. GAME START");
	gotoxy(82, 20);
	printf("2. GAME RULE");
	gotoxy(82, 22);
	printf("3. EXIT\n");
	gotoxy(75, 30);
	printf("원하시는 메뉴버튼을 눌러주세요 : ");
	gotoxy(95, 30);
	scanf("%d", &a);

	switch (a)
	{
	case 1:
		system("cls");
		Game_Start();
		break;
		
	case 2:
		system("cls");
		Rule();
		break;

	case 3:
		system("cls");
		break;

	default:
		system("cls");
		printf("잘못누르셨습니다. 올바른 버튼을 눌러주세요\n");
		break;
	}
}

void Game_Start()
{
	srand(time(NULL));
	//gotoxy(80, c_y);
	//printf("■");
	print_map();
	_beginthreadex(NULL, 0, tagger, 0, 0, NULL);

	while (1)
	{
		gotoxy(x, y);
		textcolor(15);
		objimage(x,y,L"./캐릭터..bmp",32,32);
		/*printf("○○");
		gotoxy(x, y);
		printf("○○");*/



		if (rand_col == 12 && m_count>0)
		{
			gameover();
			return ;
		}
		if (rand_col == 9 && (m_count > 1 || d_count==1)) //파랑색일때 두칸이상 움직이면 쥬금
		{
			gameover();
			return ;
		}
		if (rand_col == 11 && (m_count > 2 || d_count==1))//민트색일때 세칸이상 움직이면 죽음
		{
			gameover();
			return ;
		}
		if (rand_col == 14 && m_count > 0)//노란색일때 움직이면 처음부터 시작
		{
			gotoxy(x+1,y+1);
			printf("    ");
			gotoxy(x+1,y+2);
			printf("    ");
			x=4;
			y=24;
			objimage(x,y,L"./캐릭터..bmp",40,40);

		}

		move(x_b, y_b);

		if (x>156)
		{
			system("cls");
			background(); BLUE
			gotoxy(45, 11); printf(" ■■■■          ■■■          ■■    ■■        ■■■■          ");
			gotoxy(45, 12); printf(" ■               ■    ■         ■ ■  ■ ■        ■             ");
			gotoxy(45, 13); printf(" ■   ■■       ■■■■■        ■  ■■  ■        ■■■■                 ");
			gotoxy(45, 14); printf(" ■    ■        ■      ■        ■        ■        ■            ");
			gotoxy(45, 15); printf(" ■■■■        ■      ■        ■        ■        ■■■■             ");
			gotoxy(40, 20); printf(" ■■■■       ■                ■■■         ■■■■          ■■■■                 ");
			gotoxy(40, 21); printf(" ■             ■               ■    ■        ■                ■    ■                 ");
			gotoxy(40, 22); printf(" ■             ■              ■■■■■       ■■■■          ■■■■               ");
			gotoxy(40, 23); printf(" ■             ■              ■      ■       ■                ■   ■             ");
			gotoxy(40, 24); printf(" ■■■■       ■■■■■      ■      ■       ■■■■          ■    ■           "); ORIGINAL

			return ;

		}


		//Sleep(1000);


		if (key == 27)
			break;
	}
}

void Rule()
{
	char a;
	background();
	gotoxy(90, 10);
	YELLOW printf("<GAME RULE>\n"); ORIGINAL
		gotoxy(65, 11);
	printf("-------------------------------------------------------------");
	gotoxy(75, 12);
	printf("이동 수단 : 방향키 (← ↑ ↓ →)로 이동\n");

	gotoxy(67, 14);
	BLUE printf("■"); ORIGINAL
		gotoxy(69, 14);
	printf(" : 1칸 움직일 수 있습니다. 0번 or 1번 초과 게임 종료\n");

	gotoxy(67, 16);
	RED printf("■"); ORIGINAL
		gotoxy(69, 16); ORIGINAL
		printf(" : 정지하세요. 움직일 시 게임 종료\n");

	gotoxy(67, 18);
	YELLOW printf("■"); ORIGINAL
		gotoxy(69, 18); ORIGINAL
		printf(" : 움직일 시 처음 부터 다시 시작\n");

	gotoxy(67, 20);
	textcolor(10);//초록
	printf("■\n"); ORIGINAL
		gotoxy(69, 20); ORIGINAL
		printf(" : 자유 이동\n");

	gotoxy(67, 22);
	textcolor(11);//민트
	printf("■\n"); ORIGINAL
		gotoxy(69, 22); ORIGINAL
		printf(" : 두칸 움직여야 합니다. 0번 1번 or 2번 초과시 게임 종료\n");
	gotoxy(80,30);
	printf("게임 시작 : enter    종료 : esc");
	
		a=getch();
		if(a==13)
		{
			system("cls");
			Game_Start();
		}
		else if(a==27)
		{
			return ;
		}
}
void gameover()
{
   background(); RED
      gotoxy(45, 11); printf(" ■■■■          ■■■          ■■    ■■        ■■■■          ");
   gotoxy(45, 12); printf(" ■               ■    ■         ■ ■  ■ ■        ■             ");
   gotoxy(45, 13); printf(" ■   ■■       ■■■■■        ■  ■■  ■        ■■■■                 ");
   gotoxy(45, 14); printf(" ■    ■        ■      ■        ■        ■        ■            ");
   gotoxy(45, 15); printf(" ■■■■        ■      ■        ■        ■        ■■■■             ");
   gotoxy(45, 20); printf(" ■■■■        ■      ■          ■■■■          ■■■■                                    ");
   gotoxy(45, 21); printf(" ■    ■        ■      ■          ■                ■    ■                      ");
   gotoxy(45, 22); printf(" ■    ■         ■    ■           ■■■■          ■■■■                               ");
   gotoxy(45, 23); printf(" ■    ■         ■    ■           ■                ■   ■                       ");
   gotoxy(45, 24); printf(" ■■■■          ■■■            ■■■■          ■    ■                                  "); ORIGINAL

}