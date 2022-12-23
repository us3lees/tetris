#pragma once
#include "define.h"
#include "header.h"

/* ����� Print ��������� ������ ��� ������ � ������� �� �����.
	
*/
class Print { 
public :
	void print(int screen[SIZEX][SIZEY],int map[SIZE_MAP][SIZE_MAP], int px, int py, int score) //������
	{
		int i, j;
		int buff[SIZEX][SIZEY];

		for (i = 0; i < SIZEY; i++) for (j = 0; j < SIZEX; j++) buff[j][i] = screen[j][i]; //����� �� ������ �� �����
		for (i = 0; i < 4; i++) for (j = 0; j < 4; j++) if (map[j][i]) buff[j + px][i + py] = 1; //���� ����� ������, �� � ������ ���������� 1

		gotoxy(0, 0); //������� � ����� � ������������ 0, 0
		for (i = 0; i < SIZEY; i++)
		{
			for (j = 0; j < SIZEX; j++)
			{
				putchar(buff[j][i] == 0 ? SCR_SP : SCR_OB); //���� ������� � ������ �� ����� ������, �� ��������� �����
			}
			putchar('\n');
		}

		gotoxy(SIZEX + 1, 0); //���� ����
		printf("����������� �����: %i", score); //������� ���������� �����, ���������� � ���� ����
	}
	void gotoxy(int xpos, int ypos) //����������� ������� �������� �������� � ����� � ������������ xpos, ypos
	{
		COORD scrn;
		HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);//�������� "�����" ��� ������ �� ����� ������� ������ � ������� 
		scrn.X = xpos; scrn.Y = ypos;//-�������� ��������
		SetConsoleCursorPosition(hOuput, scrn);//-������ ������,�� ������ �������.
	}
	void nextmap(const int fmap[FMAP_COUNTS][4][4], int nextmap) //���������� ��������� ������ ������ � ���� c�����
	{
		int i, j;
		gotoxy(SIZEX + 1, 2); //������� � ����� � ������������ SIZE+x,2
		printf("���������: ");

		for (i = 0; i < 4; i++) 
		{
			gotoxy(SIZEX + 2, i + 3);//������� � ����� � ������������ SIZE+2,i+3
			for (j = 0; j < 4; j++)
			{
				putchar(fmap[nextmap][j][i] == 0 ? ' ' : SCR_OB); //���� �� ����� ������, �� ��������� ���������, ����� ��������� �������
			}
		}
	}
};