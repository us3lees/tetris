#pragma once
#include "header.h"
#include "Screen_Class.cpp"
#include "Print_Class.cpp"
#include "define.h"
using namespace std;
/// <summary>
/// �������� ����� �������� ����.
/// </summary>
class Tetris {
private:
	// ���� ������ �������� ��� ������ �������
	int screen[SIZEX][SIZEY];    //������ ������
	int map[SIZE_MAP][SIZE_MAP]; //������
	int px, py; //���������� ������.
	int score, nextmap; //����������� ����� � ��������� ������
	const char* GAME_TITLE =
		"###########  #########  ###########  ######## ####    ####  #########  \n"
		"##   ##  ##  ##         ##   ##  ##  ##    ##  ##    ####   ##     ##  \n"
		"##   ##  ##  ##         ##   ##  ##  ##    ##  ##   ## ##   ##         \n"
		"     ##      #########       ##      ########  ##  ##  ##   ##         \n"
		"     ##      ##              ##      ##        ## ##   ##   ##         \n"
		"     ##      ##              ##      ##        ####    ##   ##     ##  \n"
		"   ######    #########     ######   ####      ####    ####  #########  \n\n";


private:
	int valnewpos(int x, int y) //������������� �������� ������ ����. ���� ������� TRUE �� ��������� ����.����� ���.
	{
		int i, j;
		if (x < 0) return FALSE; // ��������� �� ����.
		for (i = 0; i < 4; i++)// ���������� ��������
		{
			for (j = 0; j < 4; j++)
			{
				if (map[j][i])
				{
					if ((j + x >= SIZEX) || (i + y >= SIZEY)) return FALSE;//-�������� �� ����� �� ������ �� ������� ������ ������.
					if (screen[j + x][i + y])
					{
						return FALSE;//-���� �� �� ������ "����"
					}
				}
			}
		}
		return TRUE;//-���� ��� ���������� "���" - ������ �������� ����.
	}
	
	void moveDownStep(int px, int py){// ��������� ���� �� ���� ���.( ����������)
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				if (map[j][i]) screen[px + j][py + i] = 1;
			}
		}
	}
	void moveDownFast(int screen[SIZEX][SIZEY]){// ��������� ������ �� ������ �����. ���� ��������� valnewpos()
		for (; valnewpos(px, py + 1); py++);
		moveDownStep(px, py);
		
	}
	void rotatemap(void) //������� ������
	{
		int _map[4][4]; // ��������( ��������������) ������ ��� ������� � map  
		int i, j, sx = 4, sy = 4;

		for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			_map[j][i] = map[j][i];//-�������� ����� ������,��� ���� ��� �� ������� �������������� ���.
			if (map[j][i])//� �������� ���� - ������ ����� ���� ,�� 
			{
				if (i < sx) sx = i;//�������� �� ������� ���������� ����� ���������� �
				if (inv(j) < sy) sy = inv(j);//����� ���������� �
			}
			map[j][i] = 0;//-�������� ������� � �������
		}
		// ������� ����� �� �������������� ������
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				if (_map[inv(i)][j]) map[j - sx][i - sy] = 1;//������ ����������
				
		if (!valnewpos(px, py))
			for (i = 0; i < 4; i++) // ���� ��������� ��� ������
				for (j = 0; j < 4; j++)
					map[j][i] = _map[j][i];//���������� ������� �� ����������� �������
	}
	void deleteline(int screen[SIZEX][SIZEY]) //����� ��������� �����
	{
		int i, j, k, flag;
		System s; // ������� ������� ������ System
		Print print;// ������� ������ ������ Print ��� ������ �� ����� (������� �� �������� �����)
		for (i = SIZEY - 1; i >= 0; i--)
		{
			flag = 1;
			for (j = 0, flag = 1; j < SIZEX; j++)
			{
				if (!screen[j][i]) flag = 0; //����������� �� ���� �������� � ��������� �� �� ������������.
			}
			if (flag) // ���� ��� ��� � �������� ������ 1 �� �������������� ���� ����, ������� �����. � ��������� ����
			{
				print.gotoxy(0, i);
				for (k = 0; k < SIZEX; k++) putchar('_'), s.sleep(20);
				/* --------- */

				score += (((i * (-1)) + SIZEY) * 10);// ��������� ����

				for (k = i; k > 0; k--)
				{
					for (j = 0; j < SIZEX; j++)
					{
						screen[j][k] = screen[j][k - 1];
					}
				}
				i++;
				print.print(screen, map, px, py, score);
			}
		}
	}
	void createmap(void) //�������� ������
	{
		
		System s; // ������� ������ System
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				map[j][i] = fmap[nextmap][j][i]; 
		py = 0;
		px = SIZEX / 2;

		Print print;// ������ ����������
		nextmap = s.random(FMAP_COUNTS - 1);
		print.nextmap(fmap, nextmap);
	}
	void startGame(void){
		int i, j, c;
		time_t tm;

		system("cls"); // ������� ��� ������� 
		System s;
		Print print;
		px = SIZEX / 2;//�������� ��� ������� ������ �� �,����� �� ������
		py = 0;
		score = 0;//���� � ������ ����

		tm = clock();// �������� �����. ����� ��� ������� ������

		nextmap = s.random(FMAP_COUNTS - 1);//��������� ������ ���������� �� 6 
		createmap();//�������� �������
		
		while (TRUE)
		{
			System s;
			c = s.getkey(); // ���������� ����� ������ System getKey()

			switch (c)
			{
			case KEY_UP:
				rotatemap();//�������
				break;
			case KEY_SPACE:
				rotatemap();//�������
				break;
			case KEY_DOWN://�������� ����
				moveDownFast(screen); //�������� ����, ��� ������� ������� ����
				print.print(screen, map, px, py, score);
				deleteline(screen);//������ �� ������� �������� ����������� �� ����� � � ��������
				createmap();//����� ������
				break;
			case KEY_LEFT:
				if (valnewpos(px - 1, py)) px--;//�������� ����� ,��������� �������� ���� �� �
				break;
			case KEY_RIGHT:
				if (valnewpos(px + 1, py)) px++;//�������� ������ ,����������� �������� ���� �� �
				break;
			case 'p'://�����
				_getch();
				break;
			case KEY_ESC://�����
				return;
			}


			if ((clock() - tm) > 720)//-����� ������� ������ 
			{
				tm = clock();

				if (!(valnewpos(px, py + 1)))
				{
					moveDownStep(px, py); // ���� ���� ���� ������, �� ��������� ����. 
					createmap();
					deleteline(screen);//  � �������� �������� �� ������������ �������.
				}
				else py++;//������� ����
			}

			print.print(screen, map, px, py, score); //������ ������

			for (i = 0; i < SIZEX; i++)
			{
				if (screen[i][0])//���� ������� � � � ������ ������� � ����� 0,�� ����� ���� ,���� ����������� �� �����
				{
					system("cls");
					print.gotoxy(2, 8);
					printf("����� ����! :(");
					return;
				}
			}
		}
	}

public:	 // �������� ������ ������, ��� ��
	/// <summary>
	/// 
	/// </summary>
	void gameMenu() //������� ����
	{
		Print print;
		Screen scr;
		int p = 1, c = 0;
		const char* GAME_MENU =
			"                     +===============================+\n"
			"                     |  1. �����                     |\n"
			"                     +===============================+\n"
			"                     |  2. �����(�����.�������)      |\n"
			"                     +===============================+\n"
			"                     |  3. ����������                |\n"
			"                     +===============================+\n"
			"                     |  4. �����                     |\n "
			"                    +===============================+";
		system("cls");
		printf("%s%s", GAME_TITLE, GAME_MENU);
		while (TRUE) { //��������� �� ����
			c = _getch();
			printf("\a");
			switch (c){
			case '1':
			case '2':
			case '3':
			case '4':
				p = c - '0'; //���������� ����. ����� ������� �� ������� �������. ������� ������������ �� ������
			case KEY_ENTER:
				switch (p)
				{
				case 1: // ������� = 1
					scr.clear(screen);  
					startGame();
					print.gotoxy(0, SIZEY); 
					printf("����� ESC ��� ������ � ������� ����...\n \a");  while (_getch() != KEY_ESC);
					break;
				case 2:
					scr.clear(screen); // ������� ������
					scr.createRandom(screen); // �������� ���������� ���������� ������
					startGame(); // ������ ����
					print.gotoxy(0, SIZEY);
					printf("����� ESC ��� ������ � ������� ����...\n \a");  while (_getch() != KEY_ESC);
					break;
				case 3:
					system("cls");
					printf("%s%s", GAME_TITLE,
						"+=======+=======+\n"
						"|\x1B      |�����  |\n"
						"|\x1A      |������ |\n"
						"|\x19      |����   |\n"
						"|\x18/Space|�������|\n"
						"|P      |�����  |\n"
						"|ESC    |�����  |\n"
						"+=======+=======+\n\n"
						"����� �������...\n");
					_getch();
					printf("\a");
					if (_kbhit())
						_getch();
					break;

				case 4: return;
				}

				system("cls");
				printf("%s%s", GAME_TITLE, GAME_MENU);
				p = 1;
				break;
			case KEY_UP: // ��� ������� �����
				if (p > 1) p--; // ��������� ��������
				break;
			case KEY_DOWN: // ��� ������� ����
				if (p < 4) p++;
				break;
			case KEY_ESC:
				return;
			}

		}
	}
	void gameTitle() { // ������ ����� ��������� ��� ������� ����. ���������� ���� ��� �� ������� ������� main()
		printf("%s", GAME_TITLE);
		printf("              ������� ����� ������� ��� �����������");
		_getch();
		printf("\a");
		if (_kbhit()) _getch(); // ���� ������� �������
	}
};
