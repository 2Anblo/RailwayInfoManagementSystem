#include"Date.h"
void dateToString(DATE date, char* dateStr) {
	sprintf(dateStr, "%04d%02d%02d", date.year, date.month, date.day);
}
DATE stringToDate(char* dateStr) {
	DATE date;
	sscanf(dateStr, "%4d%2d%2d", &date.year, &date.month, &date.day);
	return date;
}
DATE Get_Sys_Time() //���ص�ǰϵͳʱ��
{
	struct tm today; //���ʱ��Ľṹ��
	time_t one; //���ʱ�������
	DATE now;
	one = time(&one); //���ϵͳʱ��
	today = *(gmtime(&one)); //�� time_t ��ʽϵͳʱ��תΪ struct tm ��ʽ
	now.year = today.tm_year - 100 + 2000; //2011 �귵�� 111
	now.month = today.tm_mon + 1; //9 �·��� 8;
	now.day = today.tm_mday;
    now.min = today.tm_min;
    now.hour = (today.tm_hour + 8) % 24;//�й���UTC+8ʱ��
	return now;
}
// ����Ƿ�Ϊ����
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// ����ĳ���ж�����
int daysInMonth(int year, int month) {
    int daysOfMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return daysOfMonth[month - 1];
}

// ������ת��Ϊ�ӹ�Ԫ1��1��1�տ�ʼ������
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
// ������������֮���������
int daysBetweenDates(DATE date1, DATE date2) {
    return (dateToDays(date2) - dateToDays(date1));
}
