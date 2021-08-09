#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <math.h>

#define ENTER 0x0d

#define PLAYER_X 74
#define PLAYER_Y 0

#define ENEMY_X 74
#define ENEMY_Y 28

#define HOLD_X 30
#define HOLD_Y 15

#define DELAY 50
#define ENEMY_DELAY 1

#define PRINT_DELAY 50 // 대화창에 관한 정의
#define LINE_LEN 100

#define COIN_DELAY 50
#define COIN_MAX 10

#define COLOR_KIND 14
#define CHANGE_TERM 0.5

#define INITSTATE 0
#define BLOCKSTATE 1
#define VITORY 2
#define DEFEAT 3
#define EXITSTATE 4

#pragma comment(lib, "winmm.lib")
typedef struct co coi;
struct co {
	int x;
	int y;
	int val;
};
coi coin[COIN_MAX];
int coin_num = 0;

enum {
	BLACK,
	D_BLUE,
	D_GREEN,
	D_SKYBLUE,
	D_RED,
	D_VIOLET,
	D_YELLOW,
	GRAY,
	D_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

void SetColor(int backcolor, int fontcolor);
void img(int x, int y, int mx, int my, wchar_t *temp);
void print_at(int x, int y, char *str);
int get_key();
void gotoxy(int x, int y);
void intro();
void print_SW();
void print_LOADING(int x, int y);
void print_fill(int x, int y);
void print_instr(int x, int y);
void print_str(char *name, char *str, int Player_x, int Player_y, int Enemy_x, int Enemy_y, int sel);
void erase_cursor(void);
void get_out(int Player_x, int Player_y, int *Enemy_x, int *Enemy_y, int *chase_sw);
int check_obs(int x, int y);
void print_all(int Player_x, int Player_y);
void check_deg(int *bef_key, int key, int *deg_key);
void print_character(int deg_key, int Player_x, int Player_y, int key);
void print_enemy(int deg_key, int Player_x, int Player_y, int key);
void enemy_xy(int Player_x, int Player_y, int *Enemy_x, int *Enemy_y, int *chase_sw, int *en_key);
void meet_NPC(int Player_x, int Player_y, int Enemy_x, int Enemy_y, int *tutorial, int amount);
int game_play();
void print_blank();
void print_blank_fill(char *str);
void print_DEFEAT(int x, int y);
void print_VICTORY(int x, int y);
int check_obs_coin(int x, int y);
void set_coin();
void print_coin();
void get_coin(int Player_x, int Player_y, int *amount);
void clear_coin();

void main()
{
	system("title 두근두근 SW");		// 콘솔 창 제목
	system("mode con:cols=160 lines=40");		// 콘솔 창 크기

	int state = INITSTATE;
	time_t start = time(0);
	int sound_sw = 1;
	int load = 27;
	int ready = 0;
	int victory;
	
	erase_cursor();
	system("color F0");	// 흰 배경에 검은색 텍스트 기본 설정
	srand((unsigned int)time(NULL));	// 난수 시드 설정
	intro();			// 인트로 화면 1번 출력
	PlaySound(L"./Sound/Intro.wav", NULL, SND_FILENAME | SND_ASYNC ); // 인트로 BGM 시작

	while (state != EXITSTATE)
	{/*
		key = get_key();	*/	
		if ((GetAsyncKeyState(VK_ADD) < 0) && sound_sw == 0)
		{			
			PlaySound(L"./Sound/Intro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			sound_sw = 1;
		}
		if ((GetAsyncKeyState(VK_SUBTRACT) & 0x0001) && sound_sw == 1)
		{
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			sound_sw = 0;
		}

		switch (state)
		{
		case INITSTATE:
			if (GetAsyncKeyState(VK_RETURN) < 0)
			{
				system("cls");
				print_LOADING(24, 12);
				state = BLOCKSTATE;				
			}

			else if(time(0) > start + CHANGE_TERM)
			{
				start = time(0);
				print_SW();		// 인트로의 SW 글자 재출력					
			}
			break;

		case BLOCKSTATE:
			if ((GetAsyncKeyState(VK_RETURN) < 0) && ready == 1)
			{
				system("cls");				
				PlaySound(L"./Sound/Sweet.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				victory = game_play();
				
				if (victory)
				{
					print_VICTORY(47, 15);
					return;
				}
				else
				{						
					PlaySound(L"./Sound/scream.wav", NULL, SND_FILENAME );
					print_DEFEAT(36, 14);
					return;
				}
			}

			else if (load < 126)
			{			
				print_fill(load, 24);
				Sleep((rand() % 50) > 42 ? pow(rand() % 25,2) : rand() % 20);
				load ++;				
			}

			else if (load == 126 && ready == 0)
			{
				ready = 1;
				SetColor(BLACK, WHITE);
				print_at(60, 25, "게임을 시작하려면 ENTER키를 누르세요.");
				SetColor(WHITE, BLACK);
				gotoxy(0, 0);
			}
			break;
		}
	}
}

int game_play()
{
	int amount = 0;

	int bef_key = 0;
	int deg_key = 0;
	int Player_x = PLAYER_X;
	int Player_y = PLAYER_Y;
	int sound_sw = 1;

	int en_bef_key = 0;
	int en_deg_key = 0;
	int en_key;
	int Enemy_x = ENEMY_X, Enemy_y = ENEMY_Y;
	int chase_sw = 0;
	int moving_delay = 0;
	int wallet_sw = 0;

	int coin_delay = 0;

	int temp_x;
	int temp_y;
	int dest_x;
	int dest_y;
	int key;

	int tutorial = 0;
	int npc_num = 0;
	int i;

	srand((unsigned int)time(NULL));
	print_all(Player_x, Player_y);

	img(Player_x, Player_y, 43, 57, L"./image/Boy/down0.bmp");
	img(0, 0, 43, 57, L"./image/NPC/NPC2.bmp");
	img(84, 0, 32, 18, L"./image/Wallet.bmp");

	if (!tutorial)
	{
		print_str("현우", "              /아 오늘은 기대하던 예지 생일이다!!!/좋은 선물 사줘야지~~♬", Player_x, Player_y, Enemy_x, 50, 0);
		print_str("현우", "어??...??...!!??..../뭐지???..왜 돈이 모자라지???...", Player_x, Player_y, Enemy_x, 50, 0);
		print_str("현우", "꼭 선물 사줘야 하는데 어떻게 하지??.../하... 큰일이다...", Player_x, Player_y, Enemy_x, 50, 0);
		print_str("현우", "오!! 저기 저 사람 진빈이형 같은데?/왜 여기에 있는거지?/돈 좀 뜯을 수 있으려나??...", Player_x, Player_y, Enemy_x, 50, 0);

		for (i = 0; i < 33; i++)
		{
			check_deg(&bef_key, VK_LEFT, &deg_key);
			Player_x -= 2;
			print_character(deg_key, Player_x, Player_y, VK_LEFT);
			Sleep(70);
		}

		Player_x -= 2;
		print_character(0, Player_x, Player_y, VK_LEFT);
		meet_NPC(Player_x, Player_y, Enemy_x, Enemy_y, &tutorial, amount);
	}
	img(Enemy_x, Enemy_y, 43, 57, L"./image/Girl/up0.bmp");

	while (1)
	{
		//key = get_key();

		npc_num %= 50;
		if (npc_num < 25)
			img(0, 0, 43, 57, L"./image/NPC/NPC2.bmp");
		else
			img(0, 0, 43, 57, L"./image/NPC/NPC1.bmp");
		npc_num++;

		if (abs(Enemy_x - Player_x) < 7 && abs(Enemy_y - Player_y) < 4)
		{
			print_str("예지", "너 지금 뭐하는 거야???....", Player_x, Player_y, Enemy_x, Enemy_y, 1);
			print_str("현우", "응??...", Player_x, Player_y, Enemy_x, Enemy_y, 0);
			print_str("예지", "너 설마 지금 그 돈을 가지려고 한거야???...", Player_x, Player_y, Enemy_x, Enemy_y, 1);
			print_str("현우", "...으?...응???;.. 그게 난;;...", Player_x, Player_y, Enemy_x, Enemy_y, 0);
			print_str("예지", "됬어... 나 집이나 갈래... 연락하지마!!", Player_x, Player_y, Enemy_x, Enemy_y, 1);
			print_str("현우", "어?!!??!?!?...응???;....", Player_x, Player_y, Enemy_x, Enemy_y, 0);

			dest_x = 146;
			dest_y = 8;
			PlaySound(L"./Sound/Step.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			while (Enemy_x != 146 || Enemy_y != 8)
			{
				temp_x = Enemy_x;
				temp_y = Enemy_y;

				enemy_xy(dest_x, dest_y, &Enemy_x, &Enemy_y, &chase_sw, &en_key);
				if (!en_key)
					continue;
				check_deg(&en_bef_key, en_key, &en_deg_key);
				print_coin();
				print_character(0, Player_x, Player_y, VK_RIGHT);
				print_enemy(en_deg_key, Enemy_x, Enemy_y, en_key);

				if (temp_x == Enemy_x && temp_y == Enemy_y)
				{
					if (dest_y)
						dest_y--;
					if (Enemy_x == 146)
						dest_y = 8;
				}
				
				Sleep(30);
			}
			img(Enemy_x, Enemy_y, 43, 57, L"./image/Map/erase.bmp");
			PlaySound(L"./Sound/Door.wav", NULL, SND_FILENAME | SND_ASYNC);
			Sleep(1000);
			return 0;
		}

		if ((GetAsyncKeyState(VK_ADD) < 0) && sound_sw == 0)
		{
			PlaySound(L"./Sound/Sweet.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			sound_sw = 1;
		}

		if ((GetAsyncKeyState(VK_SUBTRACT) < 0) && sound_sw == 1)
		{
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			sound_sw = 0;
		}

		if ((GetAsyncKeyState('p') < 0))
		{
			PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC);
			img(0, 29, 270, 1280, L"./image/Puase.bmp");
			SetColor(GRAY, WHITE);
			print_at(132, 37, "        PRESS 'ANY KEY'");
			SetColor(WHITE, BLACK);

			getch();

			img(0, 0, 1280, 720, L"./image/Map/Map1280.bmp");
			img(84, 0, 32, 18, L"./image/Wallet.bmp");
			print_character(deg_key, Player_x, Player_y, key);
			print_enemy(en_deg_key, Enemy_x, Enemy_y, en_key);
			print_coin();

			if (sound_sw == 1)
				PlaySound(L"./Sound/Sweet.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}
		
		if ((GetAsyncKeyState(VK_UP) < 0) || (GetAsyncKeyState(VK_DOWN) < 0) || (GetAsyncKeyState(VK_LEFT) < 0) || (GetAsyncKeyState(VK_RIGHT) < 0))
		{
			if (GetAsyncKeyState(VK_UP) < 0)
			{
				key = VK_UP;
				check_deg(&bef_key, key, &deg_key);
				Player_y--;

				if (check_obs(Player_x, Player_y) == 1)
					Player_y++;

				else if (check_obs(Player_x, Player_y) == 2)
				{
					Player_y++;
					meet_NPC(Player_x, Player_y, Enemy_x, Enemy_y, &tutorial, amount);
				}

				else if (check_obs(Player_x, Player_y) == 3)
				{					
					chase_sw = 2;					
					wallet_sw = 1;
					amount += 300;
					Player_y++;
					print_str("예지", "현우야?!?!... 그거 누구 꺼야 봐봐!!!", Player_x, Player_y, Enemy_x, Enemy_y, 1);
					print_str("현우", "아... 아;;..?!.../아무것도 아니야!!...", Player_x, Player_y, Enemy_x, Enemy_y, 0);
				}					
			}

			else if (GetAsyncKeyState(VK_DOWN) < 0)
			{
				key = VK_DOWN;
				check_deg(&bef_key, key, &deg_key);
				Player_y++;

				if (check_obs(Player_x, Player_y))
					Player_y--;
			}

			else if (GetAsyncKeyState(VK_LEFT) < 0)
			{
				key = VK_LEFT;
				check_deg(&bef_key, key, &deg_key);
				Player_x -= 2;

				if (check_obs(Player_x, Player_y) == 1)
					Player_x += 2;

				else if (check_obs(Player_x, Player_y) == 2)
				{
					Player_x += 2;
					meet_NPC(Player_x, Player_y, Enemy_x, Enemy_y, &tutorial, amount);
				}

				else if (check_obs(Player_x, Player_y) == 3)
				{					
					chase_sw = 2;
					wallet_sw = 1;
					amount += 300;
					Player_x += 2;
					print_str("예지", "현우야?!?!... 그거 누구 꺼야 봐봐!!!", Player_x, Player_y, Enemy_x, Enemy_y, 1);
					print_str("현우", "아... 아;;..?!.../아무것도 아니야!!...", Player_x, Player_y, Enemy_x, Enemy_y, 0);
				}
									
				
			}

			else 
			{
				key = VK_RIGHT;
				check_deg(&bef_key, key, &deg_key);
				Player_x += 2;
				if ((Player_x == 148 && Player_y == 8) && (chase_sw || tutorial == 2))
				{
					if (tutorial == 2)
					{
						clear_coin();

						Player_x = 74;
						Player_y= 15;
						Enemy_x = 74;
						Enemy_y = 17;

						print_all(Player_x, Player_y);
						img(Enemy_x, Enemy_y, 43, 57, L"./image/Girl/up0.bmp");
						img(0, 0, 43, 57, L"./image/NPC/NPC2.bmp");
						img(84, 0, 32, 18, L"./image/Wallet.bmp");						

						print_str("현우", "예지야!...", Player_x, Player_y, Enemy_x, Enemy_y, 0);
						print_str("예지", "응? 왜???", Player_x, Player_y, Enemy_x, Enemy_y, 1);
						print_str("현우", "생일 축하해!!/이건  선물이야!!/우리 오래오래 가자!!!/사랑해...♥", Player_x, Player_y, Enemy_x, Enemy_y, 0);
						print_str("예지", "오... 정말 고마워.../비싼건데 무슨 돈으로 산거지??.../암튼 정말 고마워 잘쓸게/현우야 사랑해!!!", Player_x, Player_y, Enemy_x, Enemy_y, 1);
						PlaySound(L"./Sound/Kiss.wav", NULL, SND_FILENAME );
						return 1; //승리함
					}

					get_out(Player_x - 2, Player_y, &Enemy_x, &Enemy_y, &chase_sw);
					wallet_sw = 0;
					Player_x = 146;

					Sleep(DELAY);
					key = VK_LEFT;
					continue;
				}
				if (check_obs(Player_x, Player_y) == 1)				
					Player_x -= 2;
				else if (check_obs(Player_x, Player_y) == 3)
				{
					Player_x -= 2;
					print_str("예지", "현우야?!?!... 그거 누구 꺼야 봐봐!!!", Player_x, Player_y, Enemy_x, Enemy_y, 1);
					print_str("현우", "아... 아;;..?!.../아무것도 아니야!!...", Player_x, Player_y, Enemy_x, Enemy_y, 0);
					chase_sw = 2;
					wallet_sw = 1;
					amount += 300;
				}				
			}			
			get_coin(Player_x, Player_y, &amount);
			print_character(deg_key, Player_x, Player_y, key);

		}
		print_coin();
		if (coin_delay == COIN_DELAY)
		{
			set_coin();
			coin_delay = 0;
		}
		else
			coin_delay++;

		if (moving_delay == ENEMY_DELAY || wallet_sw)
		{
			moving_delay = 0;
			enemy_xy(Player_x, Player_y, &Enemy_x, &Enemy_y, &chase_sw, &en_key);
			if (!en_key)
				continue;
			check_deg(&en_bef_key, en_key, &en_deg_key);
			print_enemy(en_deg_key, Enemy_x, Enemy_y, en_key);
		}

		else
			moving_delay++;

		Sleep(DELAY);
	}
}

void intro()
{

	puts("                                                                                                  ");
	puts("");
	puts("");
	puts("");
	puts("                                                  ■■■■■■■■■■                                 ■■■■■■■■■■");
	puts("                        ■■■■■■■■■■      ■■■■■■■■■■       ■■■■■■■■■■      ■■■■■■■■■■  ");
	puts("                      ■■■                                   ■■■      ■■■■                                 ■■■  ");
	puts("                      ■■■■■■■■■■■                  ■■■       ■■■■■■■■■■■                  ■■■  ");
	puts("                                                            ■■■                                               ■■■    ");
	puts("                                            ■■■■■■■■■■■■■                           ■■■■■■■■■■■■■  ");
	puts("                  ■■■■■■■■■■■■■                           ■■■■■■■■■■■■■                      ");
	puts("                          ■■■                                               ■■■                                  ");
	puts("                          ■■■                ■■■■                       ■■■                ■■■■                ");
	puts("                          ■■■               ■■■                          ■■■               ■■■                  ");
	puts("                         ■■■               ■■■■■■■■■■            ■■■               ■■■■■■■■■■    ");
	puts("                                                                                                  ");

	puts("");

	print_SW();
	print_at(70, 36, "PRESS 'ENTER'");

	gotoxy(0, 0);
}

void print_SW()
{
	gotoxy(0, 18);
	SetColor(WHITE, (rand() % COLOR_KIND) + 1);

	puts("                                                                                                                                ");
	puts("                                                               ■■■■※                                        ■■■※");
	puts("                                                            ■■■■■■■※                                      ■■■※");
	puts("                                                          ■■■※    ■■■※                                     ■■■※");
	puts("                                                        ■■■※        ■■※      ■■■※                        ■■■※");
	puts("                                                        ■■※                       ■■■※        ■■■※       ■■■※");
	puts("                                                        ■■※                        ■■■※       ■■■※       ■■■※");
	puts("                                                        ■■※          ■■■■※    ■■■※        ■■■※      ■■■※");
	puts("                                                          ■■■※ ■■■■■■■■※   ■■■※      ■■■※      ■■■※");
	puts("                                                            ■■■■■■※    ■■■※    ■■■※    ■■■■※    ■■■※");
	puts("                                                               ■■■          ■■■※    ■■■■※  ■■■■■※■■■※");
	puts("                                                                               ■■■※      ■■■■※■■■■■■■■■※");
	puts("                                                                              ■■■※        ■■■■■■■※  ■■■■※");
	puts("                                                              ■■■■※   ■■■■※           ■■■■■※      ■■※");
	puts("                                                                ■■■■■■■■※                ■■■※");
	puts("                                                                    ■■■■※");

	SetColor(WHITE, BLACK);
	gotoxy(0, 0);
}

void print_fill(int x, int y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	print_at(x, y++, "  ");
	print_at(x, y++, "  ");
	print_at(x, y++, "  ");

	SetColor(WHITE, BLACK);

}

void print_LOADING(int x, int y)
{
	SetColor(WHITE, VIOLET);
	print_at(x, y++, "  ■                ■■■              ■        ■■■■        ■    ■■        ■        ■■■■    ");
	print_at(x, y++, "  ■              ■      ■            ■        ■      ■      ■    ■■        ■      ■        ■  ");
	print_at(x, y++, "  ■            ■          ■        ■  ■      ■        ■    ■    ■  ■      ■    ■              ");
	print_at(x, y++, "  ■            ■          ■        ■  ■      ■        ■    ■    ■  ■      ■    ■              ");
	print_at(x, y++, "  ■            ■          ■      ■      ■    ■        ■    ■    ■    ■    ■    ■    ■■■■  ");
	print_at(x, y++, "  ■            ■          ■      ■      ■    ■        ■    ■    ■    ■    ■    ■          ■  ");
	print_at(x, y++, "  ■            ■          ■      ■■■■■    ■        ■    ■    ■      ■  ■    ■          ■  ");
	print_at(x, y++, "  ■            ■          ■    ■          ■  ■        ■    ■    ■      ■  ■    ■          ■  ");
	print_at(x, y++, "  ■              ■      ■      ■          ■  ■      ■      ■    ■        ■■      ■      ■■  ");
	print_at(x, y++, "  ■■■■■■      ■■■        ■          ■  ■■■■        ■    ■        ■■        ■■■  ■  ");
	SetColor(WHITE, BLACK);

	print_at(x, ++y, "  ┌─────────────────────────────────────────────────┐  ");
	print_at(x, ++y, "  │                                                                                                  │  ");
	print_at(x, ++y, "  │                                                                                                  │  ");
	print_at(x, ++y, "  │                                                                                                  │  ");
	print_at(x, ++y, "  └─────────────────────────────────────────────────┘  ");

	print_instr(x, y);
	gotoxy(0, 0);
}

void print_instr(int x, int y)
{
	y += 2;

	print_at(x + 28, y + 2, "  ▲   : Up");
	print_at(x + 28, y + 3, "◀  ▶ : Left | Right");
	print_at(x + 28, y + 4, "  ▼   : Down");

	print_at(x + 66, y + 2, "+  : BGM On");
	print_at(x + 66, y + 3, "P  : PAUSE");
	print_at(x + 66, y + 4, "-  : BGM Off");	
}

void print_coin()
{
	int i;

	for (i = 0; i < coin_num; i++)
		if (coin[i].x != 0 || coin[i].y != 0)
			img(coin[i].x, coin[i].y, 32, 36, L"./image/Coin.bmp");
	return;
}

void print_DEFEAT(int x, int y) //	print_DEFEAT(36, 14); 라고 쓰면 됨
{
	int i;
	int rand_num;

	srand((unsigned int)time(NULL));
	PlaySound(L"./Sound/Defeat.wav", NULL, SND_FILENAME | SND_ASYNC);

	for (i = 0; i < 250; i++)
	{
		rand_num = rand() % 16 - 7;

		SetColor(D_RED, rand() % 16);
		system("cls");
		print_at(x + rand_num, y, "■■■■        ■■■■■■    ■■■■■■  ■■■■■■          ■        ■■■■■■■  ");
		print_at(x + rand_num, y + 1, "■      ■      ■              ■            ■                    ■              ■        ");
		print_at(x + rand_num, y + 2, "■        ■    ■              ■            ■                  ■  ■            ■        ");
		print_at(x + rand_num, y + 3, "■        ■    ■              ■            ■                  ■  ■            ■        ");
		print_at(x + rand_num, y + 4, "■        ■    ■■■■■■    ■■■■■    ■■■■■■      ■      ■          ■        ");
		print_at(x + rand_num, y + 5, "■        ■    ■              ■            ■                ■      ■          ■        ");
		print_at(x + rand_num, y + 6, "■        ■    ■              ■            ■                ■■■■■          ■        ");
		print_at(x + rand_num, y + 7, "■        ■    ■              ■            ■              ■          ■        ■        ");
		print_at(x + rand_num, y + 8, "■      ■      ■              ■            ■              ■          ■        ■        ");
		print_at(x + rand_num, y + 9, "■■■■        ■■■■■■    ■            ■■■■■■    ■          ■        ■        ");
		Sleep(200);
		if (GetAsyncKeyState(VK_RETURN) < 0)
			break;
	}

	SetColor(WHITE, BLACK);
	gotoxy(0, 0);

	return;
}

void print_VICTORY(int x, int y) //print_VICTORY(47, 15); 라고 쓰면 됨
{
	int i;
	int rand_num;

	srand((unsigned int)time(NULL));
	PlaySound(L"./Sound/VICTORY.wav", NULL, SND_FILENAME | SND_ASYNC);

	for (i = 0; i < 250; i++)
	{
		rand_num = rand() % 16 - 7;

		SetColor(VIOLET, rand() % 16);
		system("cls");
		if (i % 2)
		{
			print_at(x + rand_num, y, "      ■■      ■■                            ■■      ■■      ");
			print_at(x + rand_num, y + 1, "    ■    ■  ■    ■      ■■  ■■        ■    ■  ■    ■    ");
			print_at(x + rand_num, y + 2, "  ■        ■        ■  ■■■■■■■    ■        ■        ■  ");
			print_at(x + rand_num, y + 3, "  ■                  ■  ■■■■■■■    ■                  ■  ");
			print_at(x + rand_num, y + 3, "  ■                  ■  ■■■■■■■    ■                  ■  ");
			print_at(x + rand_num, y + 4, "    ■              ■      ■■■■■        ■              ■    ");
			print_at(x + rand_num, y + 5, "    ■              ■      ■■■■■        ■              ■    ");
			print_at(x + rand_num, y + 6, "      ■          ■          ■■■            ■          ■      ");
			print_at(x + rand_num, y + 7, "        ■      ■              ■                ■      ■        ");
			print_at(x + rand_num, y + 8, "          ■  ■                ■                  ■  ■          ");
			print_at(x + rand_num, y + 9, "            ■                                        ■            ");
		}
		else
		{
			print_at(x + rand_num + 2, y, "                        ■■      ■■                      ");
			print_at(x + rand_num + 2, y + 1, "    ■■  ■■        ■    ■  ■    ■      ■■  ■■    ");
			print_at(x + rand_num + 2, y + 2, "  ■■■■■■■    ■        ■        ■  ■■■■■■■  ");
			print_at(x + rand_num + 2, y + 3, "  ■■■■■■■    ■                  ■  ■■■■■■■  ");
			print_at(x + rand_num + 2, y + 4, "  ■■■■■■■    ■                  ■  ■■■■■■■  ");
			print_at(x + rand_num + 2, y + 5, "    ■■■■■        ■              ■      ■■■■■    ");
			print_at(x + rand_num + 2, y + 6, "    ■■■■■        ■              ■      ■■■■■    ");
			print_at(x + rand_num + 2, y + 7, "      ■■■            ■          ■          ■■■      ");
			print_at(x + rand_num + 2, y + 8, "        ■                ■      ■              ■        ");
			print_at(x + rand_num + 2, y + 9, "        ■                  ■  ■                ■        ");
			print_at(x + rand_num + 2, y + 9, "                              ■                            ");

		}
		Sleep(130);
		if (GetAsyncKeyState(VK_RETURN) < 0)
			return;
	}

	SetColor(WHITE, BLACK);
	gotoxy(0, 0);

	return;
}

void print_blank_fill(char *str)
{
	int i;
	for (i = 0; str[i]; i++)
	{
		if (str[i] == -95)
		{
			print_blank();
			i++;
		}
		else
			printf(" ");
	}
	puts("");
	SetColor(WHITE, BLACK);
}

void print_blank()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("  ");
	SetColor(WHITE, BLACK);
}

void print_all(int Player_x, int Player_y)
{
	img(0, 0, 1280, 720, L"./image/Map/Map1280.bmp");
	img(Player_x, Player_y, 1280, 720, L"./image/Boy/down0.bmp");
}

void print_enemy(int deg_key, int Player_x, int Player_y, int key)
{
	if (key == VK_UP)
	{
		img(Player_x, Player_y + 1, 43, 57, L"./image/Map/erase.bmp");
		if (deg_key % 4 == 1)
			img(Player_x, Player_y, 43, 57, L"./image/Girl/up1.bmp");
		else if (deg_key % 4 == 3)
			img(Player_x, Player_y, 43, 57, L"./image/Girl/up2.bmp");
		else
			img(Player_x, Player_y, 43, 57, L"./image/Girl/up0.bmp");
		return;
	}

	else if (key == VK_DOWN)
	{
		img(Player_x, Player_y - 1, 43, 57, L"./image/Map/erase.bmp");
		if (deg_key % 4 == 1)
			img(Player_x, Player_y, 43, 57, L"./image/Girl/down1.bmp");
		else if (deg_key % 4 == 3)
			img(Player_x, Player_y, 43, 57, L"./image/Girl/down2.bmp");
		else
			img(Player_x, Player_y, 43, 57, L"./image/Girl/down0.bmp");
		return;
	}

	else if (key == VK_LEFT)
	{
		img(Player_x + 2, Player_y, 43, 57, L"./image/Map/erase.bmp");
		if (deg_key % 4 == 1)
			img(Player_x, Player_y, 43, 57, L"./image/Girl/left1.bmp");
		else if (deg_key % 4 == 3)
			img(Player_x, Player_y, 43, 57, L"./image/Girl/left2.bmp");
		else
			img(Player_x, Player_y, 43, 57, L"./image/Girl/left0.bmp");
		return;
	}

	else
	{
		img(Player_x - 2, Player_y, 43, 57, L"./image/Map/erase.bmp");
		if (deg_key % 4 == 1)
			img(Player_x, Player_y, 43, 57, L"./image/Girl/right1.bmp");
		else if (deg_key % 4 == 3)
			img(Player_x, Player_y, 43, 57, L"./image/Girl/right2.bmp");
		else
			img(Player_x, Player_y, 43, 57, L"./image/Girl/right0.bmp");
		return;
	}
}

void print_character(int deg_key, int Player_x, int Player_y, int key)
{
	if (key == VK_UP)
	{
		img(Player_x, Player_y + 1, 43, 57, L"./image/Map/erase.bmp");
		if (deg_key % 4 == 1)
			img(Player_x, Player_y, 43, 57, L"./image/Boy/up1.bmp");
		else if (deg_key % 4 == 3)
			img(Player_x, Player_y, 43, 57, L"./image/Boy/up2.bmp");
		else
			img(Player_x, Player_y, 43, 57, L"./image/Boy/up0.bmp");
		return;
	}

	else if (key == VK_DOWN)
	{
		img(Player_x, Player_y - 1, 43, 57, L"./image/Map/erase.bmp");
		if (deg_key % 4 == 1)
			img(Player_x, Player_y, 43, 57, L"./image/Boy/down1.bmp");
		else if (deg_key % 4 == 3)
			img(Player_x, Player_y, 43, 57, L"./image/Boy/down2.bmp");
		else
			img(Player_x, Player_y, 43, 57, L"./image/Boy/down0.bmp");
		return;
	}

	else if (key == VK_LEFT)
	{
		img(Player_x + 2, Player_y, 43, 57, L"./image/Map/erase.bmp");
		if (deg_key % 4 == 1)
			img(Player_x, Player_y, 43, 57, L"./image/Boy/left1.bmp");
		else if (deg_key % 4 == 3)
			img(Player_x, Player_y, 43, 57, L"./image/Boy/left2.bmp");
		else
			img(Player_x, Player_y, 43, 57, L"./image/Boy/left0.bmp");
		return;
	}

	else
	{
		img(Player_x - 2, Player_y, 43, 57, L"./image/Map/erase.bmp");
		if (deg_key % 4 == 1)
			img(Player_x, Player_y, 43, 57, L"./image/Boy/right1.bmp");
		else if (deg_key % 4 == 3)
			img(Player_x, Player_y, 43, 57, L"./image/Boy/right2.bmp");
		else
			img(Player_x, Player_y, 43, 57, L"./image/Boy/right0.bmp");
		return;
	}
}

void print_str(char *name, char *str, int Player_x, int Player_y, int Enemy_x, int Enemy_y, int sel)
{
	int i;
	int slash_num = 0;
	int key;
	int skip = 0;

	SetColor(GRAY, WHITE);

	img(0, 29, 270, 1280, L"./image/Background.bmp");

	if (sel == 0)
		img(50, 32, 270, 1280, L"./image/Boy/HY.bmp");
	else if (sel == 1)
		img(50, 32, 270, 1280, L"./image/Girl/YJ.bmp");
	else
		img(50, 32, 270, 1280, L"./image/NPC/JB.bmp");

	print_at(51, 36, name);
	print_at(132, 37, "TO SKIP PRESS 'ENTER'");
	gotoxy(80, 32);
	for (i = 0; str[i]; i++) {
		key = get_key();
		if (str[i] == '/')
		{
			slash_num++;
			gotoxy(80, 32 + slash_num);
			continue;
		}

		if ((str[i] & 0x80) == 0x80)
		{
			printf("%c%c", str[i], str[i + 1]); //한글이면 2byte 출력
			i++;
		}
		else
			printf("%c", str[i]); //아니면 그냥 출력				

		if (key == ENTER) skip = 1;
		if (!skip)
			Sleep(PRINT_DELAY);
	}	
	print_at(132, 37, "        PRESS 'ANY KEY'");
	SetColor(WHITE, BLACK);
	getch();

	img(0, 0, 1280, 720, L"./image/Map/Map1280.bmp");
	img(84, 0, 32, 18, L"./image/Wallet.bmp");
	print_coin();
	img(0, 0, 43, 57, L"./image/NPC/NPC2.bmp");
	img(Player_x, Player_y, 43, 57, L"./image/Boy/down0.bmp");
	img(Enemy_x, Enemy_y, 43, 57, L"./image/Girl/up0.bmp");

	return;
}

void print_at(int x, int y, char *str) {
	gotoxy(x, y);
	printf("%s", str);
}

void img(int x, int y, int mx, int my, wchar_t *temp)
{
	x = 8 * x;
	y = 18 * y;
	mx = 8 * mx;
	my = 18 * my;

	HWND myconsole = GetConsoleWindow();
	//Get a handle to device context
	HDC mydc = GetDC(myconsole);

	HBITMAP hImage, hOldBitmap;
	HDC hMemDC = CreateCompatibleDC(mydc);

	//이미지 로드
	hImage = (HBITMAP)LoadImage(NULL, temp, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	//이미지 출력 부분
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);
	BitBlt(mydc, x, y, mx, my, hMemDC, 0, 0, SRCCOPY);

	//각종 메모리 해제
	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hImage);
	DeleteDC(hMemDC);
	ReleaseDC(myconsole, mydc);
}

int check_obs_coin(int x, int y)
{
	if (146 < x || x < 0 || 38 < y || y < 0)					return 1; //벽의 영역

	else if (x < 6 && y < 3)									return 2; //npc의 영역

	else if ((78 < x && x < 88) && y < 1)						return 3; //지갑을 줍는다.

	else if ((22 < x && x < 44) && (4 < y && y < 11))			return 1;
	else if ((22 < x && x < 44) && (15 < y && y < 22))			return 1;
	else if ((22 < x && x < 44) && (27 < y && y < 33))			return 1;

	else if ((50 < x && x < 72) && (4 < y && y < 11))			return 1;
	else if ((50 < x && x < 72) && (15 < y && y < 22))			return 1;
	else if ((50 < x && x < 72) && (27 < y && y < 33))			return 1;

	else if ((78 < x && x < 98) && (4 < y && y < 11))			return 1;
	else if ((78 < x && x < 98) && (15 < y && y < 22))			return 1;
	else if ((78 < x && x < 98) && (27 < y && y < 33))			return 1;

	else if ((106 < x && x < 126) && (4 < y && y < 11))			return 1;
	else if ((106 < x && x < 126) && (15 < y && y < 22))		return 1;
	else if ((106 < x && x < 126) && (27 < y && y < 33))		return 1;

	return 0;
}

void set_coin()
{
	int rand_x;
	int rand_y;
	int i;
	int same = 0;

	srand((unsigned int)time(NULL));

	if (coin_num == COIN_MAX)
		return;

	while (1)
	{
		rand_x = rand() % 147;
		rand_y = rand() % 39;
		if (!check_obs_coin(rand_x, rand_y))
		{
			for (i = 0; i < coin_num; i++)
				if (coin[i].x == rand_x && coin[i].y == rand_y)
				{
					same = 1;
					break;
				}

			if (!same)
			{
				coin[i].x = rand_x;
				coin[i].y = rand_y;
				coin[i].val = (rand() % 5 + 5) * 10;
				coin_num++;
				return;
			}
		}
	}
	return;
}

void get_coin(int Player_x, int Player_y, int *amount)
{
	int i;

	for (i = 0; i < coin_num; i++)
		if ((coin[i].x - 4 < Player_x) && (Player_x < coin[i].x + 4) && (coin[i].y - 3 < Player_y) && (Player_y < coin[i].y + 2))
		{
			(*amount) += coin[i].val;
			img(coin[i].x, coin[i].y, 32, 36, L"./image/Coin_Erase.bmp");
			coin[i].x = coin[coin_num - 1].x;
			coin[i].y = coin[coin_num - 1].y;
			coin[i].val = coin[coin_num - 1].val;
			coin_num--;
			return; //동전을 먹음
		}
	return;
}

void clear_coin()
{
	coin_num = 0;
	return;
}

void check_deg(int *bef_key, int key, int *deg_key)
{
	if (*bef_key == key)
		(*deg_key)++;
	else
		(*deg_key) = 0;

	*bef_key = key;

	return;
}

int check_obs(int x, int y)
{
	if (x < 0 || 146 < x || y < 0 || 37 < y)					return 1; //벽의 영역

	else if (x < 6 && y < 3)									return 2; //npc의 영역

	else if ((78 < x && x < 88) && y < 1)						return 3; //지갑을 줍는다.

	else if ((22 < x && x < 44) && (3 < y && y < 11))			return 1;
	else if ((22 < x && x < 44) && (14 < y && y < 22))			return 1;
	else if ((22 < x && x < 44) && (26 < y && y < 33))			return 1;

	else if ((50 < x && x < 72) && (3 < y && y < 11))			return 1;
	else if ((50 < x && x < 72) && (14 < y && y < 22))			return 1;
	else if ((50 < x && x < 72) && (26 < y && y < 33))			return 1;

	else if ((78 < x && x < 98) && (3 < y && y < 11))			return 1;
	else if ((78 < x && x < 98) && (14 < y && y < 22))			return 1;
	else if ((78 < x && x < 98) && (26 < y && y < 33))			return 1;

	else if ((106 < x && x < 126) && (3 < y && y < 11))			return 1;
	else if ((106 < x && x < 126) && (14 < y && y < 22))		return 1;
	else if ((106 < x && x < 126) && (26 < y && y < 33))		return 1;

	return 0;
}

void meet_NPC(int Player_x, int Player_y, int Enemy_x, int Enemy_y, int *tutorial, int amount)
{
	char jb[60] = "지금 총    원을 모았어/아직은 부족해!!/좀더 주워!!!!";
	int sw = 0;

	if (!(*tutorial))
	{
		print_str("현우", "진빈이형!! 뭐해 여기서???", Player_x, Player_y, Enemy_x, Enemy_y, 0);
		print_str("진빈", "쉿!....", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "응??...", Player_x, Player_y, Enemy_x, Enemy_y, 0);
		print_str("진빈", "어허... 쉿!!", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "????..../새로운 정신병인가??...", Player_x, Player_y, Enemy_x, Enemy_y, 0);

		print_str("진빈", "흠.../너 지금 예지 선물 살 돈이 없어서 그러는 거지??", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "형이 그걸 어떻게??....", Player_x, Player_y, Enemy_x, Enemy_y, 0);
		print_str("진빈", "척보면 척이지!!/그런데 말이야 여기 308 강의실에는/사람들이 흘리고 가버린 동전들이 정말 많아/그러니 조용히 하라고!", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "아 진짜??/마침 내가 딱 1000원이 모자랐는데/주울 수 있으려나??", Player_x, Player_y, Enemy_x, Enemy_y, 0);

		print_str("진빈", "당연하지!", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "근데 예지가 남의 돈을 주우면/굉장히 싫어할텐데??......", Player_x, Player_y, Enemy_x, Enemy_y, 0);
		print_str("진빈", "그래.../그게 가장 큰 문제지.../게다가 예지가 아까 부터 308강의실에서 서성이고 있어/오른쪽에 있는 문으로 잠시 나가면 주의를 돌릴 수 있을거야", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "오!!! 그런 좋은 방법이..../역시 형이야!!", Player_x, Player_y, Enemy_x, Enemy_y, 0);
		print_str("진빈", "동전을 줍다가 얼마나 주웠는지 알고 싶으면/나한테와 그럼 알려줄게", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "형 도와줘서 정말 고마워!!/빨리 주워볼게!!", Player_x, Player_y, Enemy_x, Enemy_y, 0);

		print_str("진빈", "아!! 맞다 그리고 아까 도윤이형이 흘리고 간 지갑이/강의실 앞에 있어 도윤이형 지갑엔 비록 300원 밖에 없어 /하지만 나갔다 들어오면 누군가 채워 넣더라고!", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "오 좋은데?!!", Player_x, Player_y, Enemy_x, Enemy_y, 0);
		print_str("진빈", "하지만 예지가 지갑의 존재를 알고 있기 때문에/널 2배의 속도로 바로 쫓아올거야!", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		print_str("현우", "그건 좀 무서운데??...", Player_x, Player_y, Enemy_x, Enemy_y, 0);
		
		print_str("현우", "알겠어 형 고마워! 바로 시작해 볼게!!", Player_x, Player_y, Enemy_x, Enemy_y, 0);
		(*tutorial) = 1;
	}

	else if (amount < 1000)
	{
		if (amount / 100)
		{
			jb[8] = amount / 100 + 48;
			amount %= 100;
			sw = 1;
		}

		if (amount / 10 || sw)
		{
			jb[9] = amount / 10 + 48;
			amount %= 10;
			sw = 1;
		}
		jb[10] = amount + 48;
		print_str("진빈", jb, Player_x, Player_y, Enemy_x, Enemy_y, 2);
	}

	else
	{
		print_str("진빈", "드디어 필요한 돈을 다 모았어!!/예지에게 들키기 전에 어서 나가서 선물을 사와!!", Player_x, Player_y, Enemy_x, Enemy_y, 2);
		(*tutorial) = 2;
	}

	return;
}

void get_out(int Player_x, int Player_y, int *Enemy_x, int *Enemy_y, int *chase_sw)
{
	(*chase_sw) = 0;

	img(Player_x, Player_y, 43, 57, L"./image/Map/erase.bmp");
	print_str("예지", "현우야 어디 간거야??..../칫 나혼자 놀거야...ㅠㅠ", Player_x, 50, *Enemy_x, *Enemy_y, 1);
	img(*Enemy_x, *Enemy_y, 43, 57, L"./image/Map/erase.bmp");
	(*Enemy_x) = ENEMY_X;
	(*Enemy_y) = ENEMY_Y;
	img(Player_x, Player_y, 43, 57, L"./image/Boy/left0.bmp");
	print_str("현우", "휴 살았다.../들키지 않아서 정말 다행이야...", Player_x, 50, *Enemy_x, *Enemy_y, 0);
	img(Player_x, Player_y, 43, 57, L"./image/Boy/left0.bmp");
	img(*Enemy_x, *Enemy_y, 43, 57, L"./image/Girl/up0.bmp");

	return;
}

void enemy_xy(int Player_x, int Player_y, int *Enemy_x, int *Enemy_y, int *chase_sw, int *en_key)
{
	int gap_x;
	int gap_y;
	int rand_num;
	int temp_x;
	int temp_y;
	int temp_rand;

	gap_x = Player_x - *Enemy_x;
	gap_y = Player_y - *Enemy_y;

	if (*chase_sw)
	{
		if ((*chase_sw) == 1)
		{
			print_str("예지", "현우야 지금 뭐하는 거야??!!?!?!", Player_x, Player_y, *Enemy_x, *Enemy_y, 1);
			print_str("현우", "아... 아;;..?!.../아무것도 아니야!!...", Player_x, Player_y, *Enemy_x, *Enemy_y, 0);
		}

		rand_num = temp_rand = rand() % 2;
		(*chase_sw)++;

		while (1)
		{
			if (rand_num || gap_y == 0)
			{
				if (gap_x > 0)
				{
					(*Enemy_x) += 2;
					(*en_key) = VK_RIGHT;

					if (!check_obs(*Enemy_x, *Enemy_y))
						return;

					(*Enemy_x) -= 2;
				}
				else if (gap_x < 0)
				{
					(*Enemy_x) -= 2;
					(*en_key) = VK_LEFT;

					if (!check_obs(*Enemy_x, *Enemy_y))
						return;

					(*Enemy_x) += 2;
				}
			}
			if (gap_y > 0)
			{
				(*Enemy_y)++;
				(*en_key) = VK_DOWN;

				if (!check_obs(*Enemy_x, *Enemy_y))
					return;

				(*Enemy_y)--;
			}
			else if (gap_y < 0)
			{
				(*Enemy_y)--;
				(*en_key) = VK_UP;

				if (!check_obs(*Enemy_x, *Enemy_y))
					return;

				(*Enemy_y)++;
			}
			if (rand_num == temp_rand)
				rand_num = !rand_num;
			else
				break;
		}
		return;
	}


	else
	{
		do {
			temp_x = *Enemy_x;
			temp_y = *Enemy_y;
			rand_num = rand() % 4;

			if (rand_num == 0)
				temp_x += 2;
			else if (rand_num == 1)
				temp_x -= 2;
			else if (rand_num == 2)
				temp_y++;
			else
				temp_y--;

			if (!check_obs(temp_x, temp_y))
				break;
		} while (1);
		*Enemy_x = temp_x;
		*Enemy_y = temp_y;

		if (abs(gap_x) < HOLD_X && abs(gap_y) < HOLD_Y)
			(*chase_sw) = 1;

		if (rand_num == 0)
			(*en_key) = VK_RIGHT;
		else if (rand_num == 1)
			(*en_key) = VK_LEFT;
		else if (rand_num == 2)
			(*en_key) = VK_DOWN;
		else
			(*en_key) = VK_UP;
		return;
	}
}

void erase_cursor(void)
{
	CONSOLE_CURSOR_INFO CurInfo;

	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void SetColor(int backcolor, int fontcolor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor * 16 + fontcolor);
}

int get_key()
{
	int key = 0;
	if (_kbhit())
	{
		key = _getch();
		if (key == 0xe0)
			key = _getch();
	}
	return key;
}

void gotoxy(int x, int y)
{
	COORD CursorPosition = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}