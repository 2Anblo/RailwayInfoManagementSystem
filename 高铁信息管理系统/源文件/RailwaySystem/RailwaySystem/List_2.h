#pragma once
#include"List_1.h"
//֤�����֤���š��������ֻ��š�������ϵ�ˣ�������ϵ�˵绰
typedef struct PassData {
    char ID_type[10];//֤�����
    char ID[25];//֤����
    char Name[25];//����
    char PhoneNumber[20];//�ֻ���
    char Emergency[25];//������ϵ��
    char EmerPhone[20];//������ϵ�˵绰
};
typedef struct Passenger {
    int Passenger_Num;//�˿�����(��)
    PassData data;//�˿���Ϣ
    Passenger* nextP;
}Passenger,*PassList;
static Status CountPassenger(PassList& L)//�����˿�����
{
    PassList p = L->nextP;
    int i = 0;
    while (p) {//��������
        p = p->nextP;
        i++;
    }
    L->Passenger_Num = i;
    return OK;
}
static Status InitList_Pass(PassList& L)
{ //����һ���յ�����LΪ��ͷ���ĵ������ͷָ��.
    L = (PassList)malloc(sizeof(Passenger));   //����ͷ���
    if (!L) return ERROR;
    L->nextP = NULL;
    return OK;
} //InitList_Pass

static Status ListInsert_PassInitial(PassList& L, int i, PassData e)
{//�ڴ�ͷ���ĵ���������L�е�i��λ��֮ǰ����Ԫ��e
    PassList p, s;
    int j;
    p = L; j = 0;
    while (p && j < i - 1)
    {
        p = p->nextP; j++;
    }                     //Ѱ�ҵ�i-1�����
    if (!p || j > i - 1)  return ERROR;     //i С��1���ߴ��ڱ�
    s = (PassList)malloc(sizeof(Passenger));   //�����½��
    s->data = e;
    s->nextP = p->nextP;                 //����L��
    p->nextP = s;

    return OK;
}//ListInsert(La,i,e);   
static Status ListInsert_Passenger(PassList& L, int i, PassData e)
{//�ڴ�ͷ���ĵ���������L�е�i��λ��֮ǰ����Ԫ��e
    PassList p, s;
    int j;
    p = L; j = 0;
    while (p && j < i - 1)
    {
        p = p->nextP; j++;
    }                     //Ѱ�ҵ�i-1�����
    if (!p || j > i - 1)  return ERROR;     //i С��1���ߴ��ڱ�
    s = (PassList)malloc(sizeof(Passenger));   //�����½��
    s->data = e;
    s->nextP = p->nextP;                 //����L��
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
    if (!p || j > i)  return ERROR;          //��i��Ԫ�ز�����
    e = p->data;                                               //ȡ��i��Ԫ��
    return OK;
}
