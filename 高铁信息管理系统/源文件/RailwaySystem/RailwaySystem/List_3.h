#pragma once
#include "List_2.h"
typedef struct BookData {
	char Order_Num[25];//������
	char P_Name[25];//�˳�������
	char TrainNumber[20];//���κ�
	char Boarding_Date[15];//�˳�����
	char StartingStation[20];//���վ
	char TerminalStation[20];//�յ�վ
	char id_type[20];//֤������
	char id[20];//֤����
	char DepartureTime[10];//����ʱ��
	char ArrivalTime[10];//����ʱ��
	double ticketPrice;//Ʊ��
	int SeatNum;//��λ��
	char BookingDate[15];//��Ʊ����
	char SeatClass[15];//��ϯ�ȼ�
}BookData;
typedef struct Book {
	BookData data;//��Ʊ��Ϣ
	Book* nextBooking;
}Book,*BList;
static Status InitList_Book(BList& L)
{ //����һ���յ�����LΪ��ͷ���ĵ������ͷָ��.
	L = (BList)malloc(sizeof(Book));   //����ͷ���
	if (!L) return ERROR;
	L->nextBooking = NULL;
	return OK;
} //InitList_Pass
static Status ListInsert_BookInitial(BList& L, int i, BookData e)
{//�ڴ�ͷ���ĵ���������L�е�i��λ��֮ǰ����Ԫ��e
	BList p, s;
	int j;
	p = L; j = 0;
	while (p && j < i - 1)
	{
		p = p->nextBooking; j++;
	}                     //Ѱ�ҵ�i-1�����
	if (!p || j > i - 1)  return ERROR;     //i С��1���ߴ��ڱ�
	s = (BList)malloc(sizeof(Book));   //�����½��
	s->data = e;
	s->nextBooking = p->nextBooking;                 //����L��
	p->nextBooking = s;

	return OK;
}//ListInsert(La,i,e);   