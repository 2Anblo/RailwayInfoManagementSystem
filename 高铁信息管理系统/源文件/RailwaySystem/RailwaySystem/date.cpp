#include"Date.h"
void dateToString(DATE date, char* dateStr) {
	sprintf(dateStr, "%04d%02d%02d", date.year, date.month, date.day);
}
DATE stringToDate(char* dateStr) {
	DATE date;
	sscanf(dateStr, "%4d%2d%2d", &date.year, &date.month, &date.day);
	return date;
}
DATE Get_Sys_Time() //返回当前系统时间
{
	struct tm today; //存放时间的结构体
	time_t one; //存放时间的类型
	DATE now;
	one = time(&one); //获得系统时间
	today = *(gmtime(&one)); //将 time_t 格式系统时间转为 struct tm 格式
	now.year = today.tm_year - 100 + 2000; //2011 年返回 111
	now.month = today.tm_mon + 1; //9 月返回 8;
	now.day = today.tm_mday;
    now.min = today.tm_min;
    now.hour = (today.tm_hour + 8) % 24;//中国在UTC+8时区
	return now;
}
// 检查是否为闰年
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 计算某月有多少天
int daysInMonth(int year, int month) {
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return daysOfMonth[month - 1];
}

// 将日期转换为从公元1年1月1日开始的天数
int dateToDays(DATE date) {
    int days = 0;
    for (int y = 1; y < date.year; y++) {
        days += isLeapYear(y) ? 366 : 365;
    }
    for (int m = 1; m < date.month; m++) {
        days += daysInMonth(date.year, m);
    }
    days += date.day;
    return days;
}
int timeToMin(DATE date) {
    int mins = 0;
    for (int y = 0; y < date.hour; y++) {
        mins += 60;
    }
    for (int m = 0; m < date.min; m++) {
        mins ++;
    }
    return mins;
}
// 计算两个日期之间的天数差
int daysBetweenDates(DATE date1, DATE date2) {
    return (dateToDays(date2) - dateToDays(date1));
}
