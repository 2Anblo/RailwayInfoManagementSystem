#pragma once
#include"List_1.h"
//证件类别、证件号、姓名、手机号、紧急联系人，紧急联系人电话
typedef struct PassData {
    char ID_type[10];//证件类别
    char ID[25];//证件号
    char Name[25];//姓名
    char PhoneNumber[20];//手机号
    char Emergency[25];//紧急联系人
    char EmerPhone[20];//紧急联系人电话
};
typedef struct Passenger {
    int Passenger_Num;//乘客数量(总)
    PassData data;//乘客信息
    Passenger* nextP;
}Passenger,*PassList;
static Status CountPassenger(PassList& L)//数出乘客数量
{
    PassList p = L->nextP;
    int i = 0;
    while (p) {//遍历链表
        p = p->nextP;
        i++;
    }
    L->Passenger_Num = i;
    return OK;
}
static Status InitList_Pass(PassList& L)
{ //建立一个空的链表，L为带头结点的单链表的头指针.
    L = (PassList)malloc(sizeof(Passenger));   //生成头结点
    if (!L) return ERROR;
    L->nextP = NULL;
    return OK;
} //InitList_Pass

static Status ListInsert_PassInitial(PassList& L, int i, PassData e)
{//在带头结点的单线性链表L中第i个位置之前插入元素e
    PassList p, s;
    int j;
    p = L; j = 0;
    while (p && j < i - 1)
    {
        p = p->nextP; j++;
    }                     //寻找第i-1个结点
    if (!p || j > i - 1)  return ERROR;     //i 小于1或者大于表长
    s = (PassList)malloc(sizeof(Passenger));   //生成新结点
    s->data = e;
    s->nextP = p->nextP;                 //插入L中
    p->nextP = s;

    return OK;
}//ListInsert(La,i,e);   
static Status ListInsert_Passenger(PassList& L, int i, PassData e)
{//在带头结点的单线性链表L中第i个位置之前插入元素e
    PassList p, s;
    int j;
    p = L; j = 0;
    while (p && j < i - 1)
    {
        p = p->nextP; j++;
    }                     //寻找第i-1个结点
    if (!p || j > i - 1)  return ERROR;     //i 小于1或者大于表长
    s = (PassList)malloc(sizeof(Passenger));   //生成新结点
    s->data = e;
    s->nextP = p->nextP;                 //插入L中
    p->nextP = s;
    L->Passenger_Num++;
    return OK;
}//ListInsert(La,i,e); 
static Status GetElem_HR(PassList L, int i, PassData& e)
{
    PassList p;
    int j;
    p = L->nextP;
    j = 1;
    while (p && j < i)
    {
        p = p->nextP; j++;
    }
    if (!p || j > i)  return ERROR;          //第i个元素不存在
    e = p->data;                                               //取第i个元素
    return OK;
}
