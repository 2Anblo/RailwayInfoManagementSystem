#pragma once
#include"List_3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct date
{
	int year, month, day, min, hour;
}DATE; //�������ڽṹ��
void dateToString(DATE date, char* dateStr);
DATE stringToDate(char* dateStr);
DATE Get_Sys_Time(); //���ص�ǰϵͳʱ��
// ����Ƿ�Ϊ����
int isLeapYear(int year);

// ����ĳ���ж�����
int daysInMonth(int year, int month);

// ������ת��Ϊ�ӹ�Ԫ1��1��1�տ�ʼ������
int dateToDays(DATE date);

// ������������֮���������
int daysBetweenDates(DATE date1, DATE date2);

int timeToMin(DATE date);