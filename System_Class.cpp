#pragma once //�� google))
#include "header.h"
#include "define.h" // ����������� ������������ ������ ��������� � �����������  
/*
����� System. 
��������� ������ �������, ��������, � �����.
*/
class System {
public:

	int random(int max) //������������
	{
		return (int)(rand() * (max+1) / RAND_MAX);
	}

	void sleep(int milsec) //��������
	{
		clock_t t = clock();
		while (clock() - t < milsec);
	}

	int getkey(void)//-����� �� ����� ����
	{
		int c;
		if (_kbhit()) //���� ������ �������
		{
			if ((c = _getch()) == 224)
				c = _getch();
			//���� ������ ������� p (�����), �� ������ ����� ������� ��� ����������� ����
			return c;
		}
		return 0;
	}
};