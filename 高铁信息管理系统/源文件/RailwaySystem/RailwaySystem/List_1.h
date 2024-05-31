#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define OVERFLOW -2
#define ERROR 0
typedef struct Seat {
    int seatNumber;    // ��λ��
    int isBooked;      // ��λ�Ƿ��ѱ�Ԥ����0��ʾδԤ����1��ʾ��Ԥ��
    char seatClass[15];// ��λ�����������һ��������������
} Seat,*SeatList;
typedef struct StoppingStation {
    char Station_Name[20];//��ͣվ��
    char ArrivalT[10];//����ʱ��
    char DepartureT[10];//����ʱ��
    double mileage_s;//���
    SeatList seats;       // ָ����λ�����ָ��
}StoppingStation;
typedef struct SqListStoppingStation {
    int Num;//��ͣվ��Ŀ
    StoppingStation* SSList;//��ͣվ��
};
typedef struct HRData
{
    char Train_Number[6];//���κ�
    char Departure_Station[20];//ʼ��վ
    char Terminal_Station[20];//�յ�վ
    double mileage;//KiloMeter�����
    char Condition[10];//���� or ͣ��
    char time_Departure[10];//����ʱ��
    char time_Arrival[10];//�յ�ʱ��
    char DepartureDate[10];//��������
    int StoppingStationNum;//��ͣվ��
    int SuperlativeSeat;//�صȡ�����������
    int FirstClassSeat;//һ��������
    int SecondClassSeat;//����������
    int totalSeats;    // ����λ��
    SqListStoppingStation SqSS;//��ͣվ��
}HRData;

typedef struct HighRail
{
    int HighRail_Num;//�г�������������ͷ�ڵ���
    HRData data;//ÿ���г�����
    HighRail* nextRail;//��һ���г���ָ����
}HighRail,*HRailList;

typedef  HRData ElemType;//Ԫ������ΪHRData

typedef int Status;
static Status InitList_Rail(HRailList& L)
{ //����һ���յ�����LΪ��ͷ���ĵ������ͷָ��.
    L = (HRailList)malloc(sizeof(HighRail));   //����ͷ���
    if (!L) return ERROR;
    L->nextRail = NULL;
    return OK;
} //InitList_Rail

static Status ListInsert_RailInitial(HRailList& L, int i, ElemType e)
{//�ڴ�ͷ���ĵ���������L�е�i��λ��֮ǰ����Ԫ��e
    HRailList p, s;
    int j;
    p = L; j = 0;
    while (p && j < i - 1)
    {
        p = p->nextRail; j++;
    }                     //Ѱ�ҵ�i-1�����
    if (!p || j > i - 1)  return ERROR;     //i С��1���ߴ��ڱ�
    s = (HRailList)malloc(sizeof(HighRail));   //�����½��
    s->data = e;
    s->nextRail = p->nextRail;                 //����L��
    p->nextRail = s;

    return OK;
}//ListInsert(La,i,e);   
static Status ListInsert_Rail(HRailList& L, int i, ElemType e)
{//�ڴ�ͷ���ĵ���������L�е�i��λ��֮ǰ����Ԫ��e
    HRailList p, s;
    int j;
    p = L; j = 0;
    while (p && j < i - 1)
    {
        p = p->nextRail; j++;
    }                     //Ѱ�ҵ�i-1�����
    if (!p || j > i - 1)  return ERROR;     //i С��1���ߴ��ڱ�
    s = (HRailList)malloc(sizeof(HighRail));   //�����½��
    s->data = e;
    s->nextRail = p->nextRail;                 //����L��
    p->nextRail = s;
    L->HighRail_Num++;
    return OK;
}//ListInsert(La,i,e); 
static Status GetElem_HR(HRailList L, int i, ElemType& e)
{
    HRailList p;
    int j;
    p = L->nextRail;
    j = 1;
    while (p && j < i)
    {
        p = p->nextRail; j++;
    }
    if (!p || j > i)  return ERROR;          //��i��Ԫ�ز�����
    e = p->data;                                               //ȡ��i��Ԫ��
    return OK;
}

static Status InitList_Sq(SqListStoppingStation& L, int current) {
    L.Num = current;
    L.SSList = (StoppingStation*)malloc(sizeof(StoppingStation) * (L.Num));
    if (!L.SSList) exit(OVERFLOW);
    return OK;
}
static Status InitList_SqSeat(SeatList& L, int current) {//current������totalSeat
    L = (SeatList)malloc(sizeof(Seat) * current);
    if (!L) exit(OVERFLOW);
    return OK;
}

static Status GetElem_Sq(SqListStoppingStation L, int i, StoppingStation& e) {
    if (i<1 || i>L.Num) return ERROR;
    e = L.SSList[i - 1];
    return OK;
}

static int LocateElem_Sq(SqListStoppingStation L, StoppingStation e, Status(*compare)(ElemType, ElemType)) {
    StoppingStation* p;
    p = L.SSList;
    int i = 0;
    while (i <= L.Num - 1 &&strcmp(p++->Station_Name,L.SSList[i].Station_Name))i++;
    if (i > L.Num - 1)return 0;
    else return i + 1;
}