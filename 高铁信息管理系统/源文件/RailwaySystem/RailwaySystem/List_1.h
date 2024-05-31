#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK 1
#define OVERFLOW -2
#define ERROR 0
typedef struct Seat {
    int seatNumber;    // 座位号
    int isBooked;      // 座位是否已被预订，0表示未预订，1表示已预订
    char seatClass[15];// 座位类别（商务座、一等座、二等座）
} Seat,*SeatList;
typedef struct StoppingStation {
    char Station_Name[20];//经停站名
    char ArrivalT[10];//到达时间
    char DepartureT[10];//出发时间
    double mileage_s;//里程
    SeatList seats;       // 指向座位数组的指针
}StoppingStation;
typedef struct SqListStoppingStation {
    int Num;//经停站数目
    StoppingStation* SSList;//经停站表
};
typedef struct HRData
{
    char Train_Number[6];//车次号
    char Departure_Station[20];//始发站
    char Terminal_Station[20];//终到站
    double mileage;//KiloMeter总里程
    char Condition[10];//正常 or 停运
    char time_Departure[10];//发车时间
    char time_Arrival[10];//终到时间
    char DepartureDate[10];//发车日期
    int StoppingStationNum;//经停站数
    int SuperlativeSeat;//特等、商务座数量
    int FirstClassSeat;//一等座数量
    int SecondClassSeat;//二等座数量
    int totalSeats;    // 总座位数
    SqListStoppingStation SqSS;//经停站表
}HRData;

typedef struct HighRail
{
    int HighRail_Num;//列车总趟数，放在头节点里
    HRData data;//每趟列车数据
    HighRail* nextRail;//下一趟列车的指针域
}HighRail,*HRailList;

typedef  HRData ElemType;//元素类型为HRData

typedef int Status;
static Status InitList_Rail(HRailList& L)
{ //建立一个空的链表，L为带头结点的单链表的头指针.
    L = (HRailList)malloc(sizeof(HighRail));   //生成头结点
    if (!L) return ERROR;
    L->nextRail = NULL;
    return OK;
} //InitList_Rail

static Status ListInsert_RailInitial(HRailList& L, int i, ElemType e)
{//在带头结点的单线性链表L中第i个位置之前插入元素e
    HRailList p, s;
    int j;
    p = L; j = 0;
    while (p && j < i - 1)
    {
        p = p->nextRail; j++;
    }                     //寻找第i-1个结点
    if (!p || j > i - 1)  return ERROR;     //i 小于1或者大于表长
    s = (HRailList)malloc(sizeof(HighRail));   //生成新结点
    s->data = e;
    s->nextRail = p->nextRail;                 //插入L中
    p->nextRail = s;

    return OK;
}//ListInsert(La,i,e);   
static Status ListInsert_Rail(HRailList& L, int i, ElemType e)
{//在带头结点的单线性链表L中第i个位置之前插入元素e
    HRailList p, s;
    int j;
    p = L; j = 0;
    while (p && j < i - 1)
    {
        p = p->nextRail; j++;
    }                     //寻找第i-1个结点
    if (!p || j > i - 1)  return ERROR;     //i 小于1或者大于表长
    s = (HRailList)malloc(sizeof(HighRail));   //生成新结点
    s->data = e;
    s->nextRail = p->nextRail;                 //插入L中
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
    if (!p || j > i)  return ERROR;          //第i个元素不存在
    e = p->data;                                               //取第i个元素
    return OK;
}

static Status InitList_Sq(SqListStoppingStation& L, int current) {
    L.Num = current;
    L.SSList = (StoppingStation*)malloc(sizeof(StoppingStation) * (L.Num));
    if (!L.SSList) exit(OVERFLOW);
    return OK;
}
static Status InitList_SqSeat(SeatList& L, int current) {//current参数传totalSeat
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