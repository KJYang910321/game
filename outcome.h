#include<iostream>

using namespace std;

int outcome(int copy_press, int copy_digit, int value_t, int value_s, int rank)
{
	if(rank == 1)//choose teacher
	{
		if(copy_press == value_t)//�I�W 
		{
			if(copy_digit == value_s)//�W��
			{
				return 0;//�� 
			}
			else
				return 1;//Ĺ 
		}
		else//���I�W 
		{
			if(copy_digit == value_s)//�W��
				return 1;//Ĺ 
			else
				return -1;//���� 
		}
	}
	else if(rank == 2)
	{
		if(copy_press == value_s)//�W��
		{
			if(copy_digit == value_t)//�I�W
				return 1;//Ĺ
			else
				return 0;//�� 
		} 
		else//¼�� 
		{
			if(copy_digit == value_t)//�I�W
				return 0;//�� 
			else//���I�W
				return -1;//���� 
		}
	}
}
