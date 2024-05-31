#pragma once
#include"List_3.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct date
{
	int year, month, day, min, hour;
}DATE; //定义日期结构体
void dateToString(DATE date, char* dateStr);
DATE stringToDate(char* dateStr);
DATE Get_Sys_Time(); //返回当前系统时间
// 检查是否为闰年
int isLeapYear(int year);

// 计算某月有多少天
int daysInMonth(int year, int month);

// 将日期转换为从公元1年1月1日开始的天数
int dateToDays(DATE date);

// 计算两个日期之间的天数差
int daysBetweenDates(DATE date1, DATE date2);

int timeToMin(DATE date);