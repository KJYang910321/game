#include<iostream>

using namespace std;

int outcome(int copy_press, int copy_digit, int value_t, int value_s, int rank)
{
	if(rank == 1)//choose teacher
	{
		if(copy_press == value_t)//點名 
		{
			if(copy_digit == value_s)//上課
			{
				return 0;//輸 
			}
			else
				return 1;//贏 
		}
		else//不點名 
		{
			if(copy_digit == value_s)//上課
				return 1;//贏 
			else
				return -1;//平手 
		}
	}
	else if(rank == 2)
	{
		if(copy_press == value_s)//上課
		{
			if(copy_digit == value_t)//點名
				return 1;//贏
			else
				return 0;//輸 
		} 
		else//翹課 
		{
			if(copy_digit == value_t)//點名
				return 0;//輸 
			else//不點名
				return -1;//平手 
		}
	}
}
