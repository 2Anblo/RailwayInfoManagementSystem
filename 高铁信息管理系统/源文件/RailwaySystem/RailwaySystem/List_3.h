#pragma once
#include "List_2.h"
typedef struct BookData {
	char Order_Num[25];//订单号
	char P_Name[25];//乘车人姓名
	char TrainNumber[20];//车次号
	char Boarding_Date[15];//乘车日期
	char StartingStation[20];//起点站
	char TerminalStation[20];//终点站
	char id_type[20];//证件类型
	char id[20];//证件号
	char DepartureTime[10];//开车时间
	char ArrivalTime[10];//到达时间
	double ticketPrice;//票价
	int SeatNum;//座位号
	char BookingDate[15];//订票日期
	char SeatClass[15];//坐席等级
}BookData;
typedef struct Book {
	BookData data;//订票信息
	Book* nextBooking;
}Book,*BList;
static Status InitList_Book(BList& L)
{ //建立一个空的链表，L为带头结点的单链表的头指针.
	L = (BList)malloc(sizeof(Book));   //生成头结点
	if (!L) return ERROR;
	L->nextBooking = NULL;
	return OK;
} //InitList_Pass
static Status ListInsert_BookInitial(BList& L, int i, BookData e)
{//在带头结点的单线性链表L中第i个位置之前插入元素e
	BList p, s;
	int j;
	p = L; j = 0;
	while (p && j < i - 1)
	{
		p = p->nextBooking; j++;
	}                     //寻找第i-1个结点
	if (!p || j > i - 1)  return ERROR;     //i 小于1或者大于表长
	s = (BList)malloc(sizeof(Book));   //生成新结点
	s->data = e;
	s->nextBooking = p->nextBooking;                 //插入L中
	p->nextBooking = s;

	return OK;
}//ListInsert(La,i,e);   