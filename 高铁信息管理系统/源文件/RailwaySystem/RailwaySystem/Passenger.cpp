#include"Passenger.h"
#include"Menu.h"
Status WriteFilePass(PassList& PList, const char* file) {
    FILE* fp1 = fopen(file, "w");// ���ļ�����д�룬����ļ��������򴴽�
    CountPassenger(PList);// ���˿͵�����
    int n = PList->Passenger_Num;// ��ȡ�˿͵�����
    PassList p = PList->nextP;// ָ��˿��б�ĵ�һ���ڵ�
    while (p != NULL)// ���������˿��б�
    {
        PassData PData = p->data;// ��ȡ��ǰ�ڵ������
        fprintf(fp1, "%s %s %s %s %s %s",
            PData.ID,PData.Name, PData.ID_type, PData.PhoneNumber, PData.Emergency, PData.EmerPhone);
        fprintf(fp1, "\n");
        p = p->nextP;// �ƶ��������е���һ���ڵ�
    }
    fclose(fp1);//�ر��ļ�
    return OK;// ���ز����ɹ���״̬
}
Status AddPassenger(PassList& PList, const char* file) {
    PassData PData;//�������������Ա��ȡ
    printf("������֤����,����,֤������,��ϵ�绰,������ϵ��,��ϵ�˵绰\n");
    // ���ļ��ж�ȡ������Ϣ.
    scanf("%s %s %s %s %s %s",
        PData.ID, PData.Name, PData.ID_type, PData.PhoneNumber, PData.Emergency, PData.EmerPhone);

    // �Ѷ�ȡ���ݲ����������
    if (ListInsert_Passenger(PList, PList->Passenger_Num + 1, PData) != OK) {
        perror("Error inserting data into rail list");//���������Ϣ
        return ERROR;//���ش���״̬
    }
    WriteFilePass(PList, file);//д���ļ�
    return OK;//����OK״̬
}
Status DeletePassenger(PassList& PList, const char* file) {
    printf("����Ҫɾ�����û���֤����Ϊ��\n");
    PassList L = PList;// ����һ��ָ��˿��б�ͷ�ڵ��ָ��
    char temp1[25];// ����һ���ַ��������ڴ洢�û������֤����
    int flag = 0;// ���ڱ���Ƿ��ҵ�ƥ����û�
    scanf("%s", temp1);// ��ȡ�û������֤����
    clearScreen();// ������Ļ
    while (L->nextP)// �����˿��б�
    {
        if (!strcmp(temp1, L->nextP->data.ID))// ���֤�����Ƿ�ƥ��
        {
            printCentered("����Ҫɾ�����û��ǣ�\n");// ��ӡƥ���û�����Ϣ
            printf("֤����:%s\n֤������:%s\n����:%s ��ϵ�绰:%s\n������ϵ��:%s ������ϵ�˵绰:%s\n", L->nextP->data.ID, L->nextP->data.ID_type, L->nextP->data.Name, L->nextP->data.PhoneNumber, L->nextP->data.Emergency, L->nextP->data.EmerPhone);
            printf("\n");
            int flag1 = 0;

        A:   
            printCentered("1.ȷ��   2.ȡ��");// ����һ�����ͱ������ڴ洢�û���ȷ�ϲ���
            printf("��ȷ�ϣ�");
            scanf("%d", &flag1);
            if (flag1 == 1)
            {
                // �û�ȷ��ɾ��
                PassList tmp = L->nextP;// ���浱ǰƥ��ڵ�
                L->nextP = tmp->nextP;
                free(tmp);// �ͷ��ڴ�
                flag = 1;// ���ɾ���ɹ�
                printCentered("ɾ���ɹ�!!!");
                break;
            }
            if (flag1 == 2)
            {
                flag = 1;//  ���ɾ�������Ѵ���
                printCentered("����ȡ��ɾ��!!!");
                break;
            }
            clearScreen();
            printCentered("��������Ч����!!!");
            goto A;// ���������û�����ȷ�ϲ���
            
        }
        L = L->nextP;// �ƶ��������е���һ���ڵ�
    }
    if (!flag) {// ���û���ҵ�ƥ����û�
        printf("����Ҫɾ�����û�������!!!\n");
        return ERROR;// ���ش���״̬
    }
    WriteFilePass(PList, file);// ���޸ĺ������д���ļ�
    return OK;// ���ز����ɹ���״̬
}
Status SearchPassenger(PassList& PList) {
    char temp[20];// ���ڴ洢�û�����Ĳ�ѯ��Ϣ
    int SearchWay;// ����ѡ���ѯ��ʽ
    printf("��ѯ��ʽ��\n");
    printf("1.����\n");
    printf("2.֤����\n");
    printf("3.��ϵ�绰\n");
    printf("4.������ϵ��\n");
    printf("5.������ϵ�˵绰\n");
    scanf("%d", &SearchWay);// ��ȡ�û�ѡ��Ĳ�ѯ��ʽ
    clearScreen();// ������Ļ
    switch (SearchWay)// �����û�ѡ��Ĳ�ѯ��ʽ���в�ͬ�Ĵ���
    {
    case 1: {// ����������ѯ
        printf("����Ҫ��ѯ���û������ǣ�\n");
        scanf("%s", temp);// ��ȡ�û����������
        PassList p = PList->nextP;// ��ȡ�˿��б��ͷ�ڵ�
        int flag = 0;// ��־���������ڼ���Ƿ��ҵ�ƥ����
        while (p != NULL)// �����˿��б�
        {
            PassData pData = p->data;// ��ȡ��ǰ�ڵ�ĳ˿�����
            if (!strcmp(pData.Name, temp)) {// ��������Ƿ�ƥ��
                flag++;// ����ҵ�ƥ������ӱ�־����
                printf("֤����:%s\n֤������:%s\n����:%s ��ϵ�绰:%s\n������ϵ��:%s ������ϵ�˵绰:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// ��ӡƥ��˿͵���Ϣ
               
            }
            p = p->nextP;// �ƶ�����һ���ڵ�
        }
        if (!flag) { // ���û���ҵ�ƥ����
            printf("��������Ҫ���ҵ��û���Ϣ������\n");
            return ERROR;//���ش���״̬
        }
        break;

    }
    case 2: {// ����֤���Ų�ѯ
        printf("����Ҫ��ѯ���û�֤�����ǣ�\n");
        scanf("%s", temp);// ��ȡ�û������֤����
        PassList p = PList->nextP;;// ��ȡ�˿��б��ͷ�ڵ�
        while (p != NULL)// �����˿��б�
        {
            PassData pData = p->data;// ��ȡ��ǰ�ڵ�ĳ˿�����
            if (!strcmp(pData.ID, temp)) {// ���֤�����Ƿ�ƥ��
                printf("֤����:%s\n֤������:%s\n����:%s ��ϵ�绰:%s\n������ϵ��:%s ������ϵ�˵绰:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// ��ӡƥ��˿͵���Ϣ
                break;
            }
            p = p->nextP;// �ƶ�����һ���ڵ�
        }
        if (!p) {// ���û���ҵ�ƥ����
            printf("��������Ҫ���ҵ��û���Ϣ������\n");
            return ERROR;//���ش���״̬
        }
        break;
    }
    case 3: {// ������ϵ�绰��ѯ
        printf("����Ҫ��ѯ����ϵ�绰�ǣ�\n");
        scanf("%s", temp);// ��ȡ�û��������ϵ�绰
        PassList p = PList->nextP;// ��ȡ�˿��б��ͷ�ڵ�
        while (p != NULL)// �����˿��б�
        {
            PassData pData = p->data;// ��ȡ��ǰ�ڵ�ĳ˿�����
            if (!strcmp(pData.PhoneNumber, temp)) {// �����ϵ�绰�Ƿ�ƥ��
                printf("֤����:%s\n֤������:%s\n����:%s ��ϵ�绰:%s\n������ϵ��:%s ������ϵ�˵绰:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// ��ӡƥ��˿͵���Ϣ
                break;
            }
            p = p->nextP;// �ƶ�����һ���ڵ�
        }
        if (!p) {// ���û���ҵ�ƥ����
            printf("��������Ҫ���ҵ��û���Ϣ������\n");
            return ERROR;//���ش���״̬
        }
        break;
    }
    case 4: {// ���ݽ�����ϵ��������ѯ
        printf("����Ҫ��ѯ�Ľ�����ϵ�������ǣ�\n");
        scanf("%s", temp);// ��ȡ�û����������
        int flag = 0;
        PassList p = PList->nextP;// ��ȡ�˿��б��ͷ�ڵ�
        while (p != NULL)// �����˿��б�
        {
            PassData pData = p->data;// ��ȡ��ǰ�ڵ�ĳ˿�����
            if (!strcmp(pData.Emergency, temp)) {// ��������ϵ�������Ƿ�ƥ��
                flag++;// ����ҵ�ƥ������ӱ�־����
                printf("֤����:%s\n֤������:%s\n����:%s ��ϵ�绰:%s\n������ϵ��:%s ������ϵ�˵绰:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// ��ӡƥ��˿͵���Ϣ
                break;
            }
            p = p->nextP;// �ƶ�����һ���ڵ�
        }
        if (!flag) {// ���û���ҵ�ƥ����
            printf("��������Ҫ���ҵ��û���Ϣ������\n");
            return ERROR;//���ش���״̬
        }
        break;
    }
    case 5: {// ���ݽ�����ϵ�˵绰��ѯ
        printf("����Ҫ��ѯ�Ľ�����ϵ�˵绰�ǣ�\n");
        scanf("%s", temp);// ��ȡ�û��������ϵ�绰
        PassList p = PList->nextP;// ��ȡ�˿��б��ͷ�ڵ�
        while (p != NULL)// �����˿��б�
        {
            PassData pData = p->data;// ��ȡ��ǰ�ڵ�ĳ˿�����
            if (!strcmp(pData.EmerPhone, temp)) {// ��������ϵ�˵绰�Ƿ�ƥ��
                printf("֤����:%s\n֤������:%s\n����:%s ��ϵ�绰:%s\n������ϵ��:%s ������ϵ�˵绰:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// ��ӡƥ��˿͵���Ϣ
                break;
            }
            p = p->nextP;// �ƶ�����һ���ڵ�
        }
        if (!p) {// ���û���ҵ�ƥ����
            printf("��������Ҫ���ҵ��û���Ϣ������\n");
            return ERROR;//���ش���״̬
        }
        break;
    }
    default:
        break;
    }
    return OK;
}
Status ModifyPassenger(PassList& PList, const char* file) {
    printf("����Ҫ�޸ĵ��û�֤����Ϊ��\n");
    char temp[25];// �洢�û������֤����
    scanf("%s", temp);// ��ȡ�û������֤����
    PassList pl = PList->nextP;// ��ȡ�˿��б�ĵ�һ��Ԫ��
    while (pl != NULL)// �����˿��б����ҵ�ƥ���֤��
    {
        if (!strcmp(pl->data.ID, temp))// ����ҵ���ƥ���֤���ţ�����ѭ��
        {
            break;
        }
        pl = pl->nextP;// �ƶ�����һ���˿�
    }
    if (!pl) {// ���û���ҵ�ƥ���֤���ţ����ش���
        printf("��ѯ�����������޸ĵ��û�֤����!!!\n");
        return ERROR;
    }
    clearScreen();// ����
    int ModifyWay;// �û�ѡ����޸ķ�ʽ
    printf("�޸���Ϣ���ࣺ\n");
    printf("1.��ϵ�绰\n");
    printf("2.������ϵ�˼���绰\n");
    scanf("%d", &ModifyWay);// ��ȡ�û�ѡ����޸ķ�ʽ
    clearScreen();// ����
    switch (ModifyWay)
    {
    case 1: {// �޸���ϵ�绰
        PassList pl = PList->nextP;// ��ȡ�˿��б�ĵ�һ��Ԫ��
        while (pl != NULL)
        {
            if (!strcmp(pl->data.ID, temp))// �ҵ�ƥ���֤����
            {
                printf("����Ҫ����ϵ�绰�޸�Ϊ��\n");
                char t_phone[20];// �洢�µĵ绰����
                scanf("%s", t_phone);// ��ȡ�µĵ绰����
                strcpy(pl->data.PhoneNumber, t_phone);// ���µ绰����
                printf("�޸ĳɹ�!!!\n");
                break;
            }
            pl = pl->nextP;// �ƶ�����һ���˿�
        }
        if (!pl) {
            printf("��ѯ�����������޸ĵ��û�֤����!!!\n");
        }
        break;
    }
    case 2: { // �޸Ľ�����ϵ�˼���绰
        PassList pl = PList->nextP;// ��ȡ�˿��б�ĵ�һ��Ԫ��
        while (pl != NULL)
        {
            if (!strcmp(pl->data.ID, temp))// �ҵ�ƥ���֤����
            {
                printf("����Ҫ��������ϵ���޸�Ϊ��\n");
                char t_Emer[25];// �洢�µĽ�����ϵ������
                char t_Emerphone[20];// �洢�µĽ�����ϵ�˵绰����
                scanf("%s", t_Emer);// ��ȡ�µĽ�����ϵ������
                strcpy(pl->data.Emergency, t_Emer);// ���½�����ϵ������
                printf("������ϵ�˵绰�޸�Ϊ��\n");
                scanf("%s", t_Emerphone); // ��ȡ�µĽ�����ϵ�˵绰����
                strcpy(pl->data.EmerPhone, t_Emerphone);// ���½�����ϵ�˵绰����
                printf("�޸ĳɹ�!!!\n");
                break;
            }
            pl = pl->nextP;// �ƶ�����һ���˿�
        }
        if (!pl) {
            printf("��ѯ�����������޸ĵ��û�֤����!!!\n");
        }
        break;
    }
    default:{
              break;
          }
    }
    WriteFilePass(PList, file);// ���޸ĺ�ĳ˿��б�д���ļ�
    return OK;// ���سɹ�״̬
}
Status ReadPassengersFromFile(PassList& PList, const char* file) {
    FILE* fp = fopen(file, "r");//���ļ����ж���
    if (fp == NULL) {
        perror("Error opening file");//�������
        return ERROR;//���ش���״̬
    }
    if (InitList_Pass(PList) != OK) {//��ʼ������
        perror("Error initializing rail list");//�������
        return ERROR;//���ش���״̬
    }
    // �ļ�������ɨ���ȡ
    int InsertP = 1;//�����־λ��¼
    PassData pData;
    while (fscanf(fp, "%s %s %s %s %s %s",
        pData.ID, pData.Name, pData.ID_type, pData.PhoneNumber, pData.Emergency, pData.EmerPhone)==6) {
        
       
        // ���ļ��ж�ȡ������Ϣ.
       
        // �Ѷ�ȡ���ݲ����������
        if (ListInsert_PassInitial(PList, InsertP++, pData) != OK) {
            perror("Error inserting data into rail list");//�������
            return ERROR;//���ش���״̬
        }
        PList->Passenger_Num = InsertP - 1;//���³˿���

    }
    fclose(fp);//�ر��ļ�
}
Status PrintPassengerInfo(PassList& PList) {
    PassList pl = PList->nextP;//�ҵ���Ԫ���
    while (pl)//��������
    {
        printf("֤����:%s\n֤������:%s\n����:%s ��ϵ�绰:%s\n������ϵ��:%s ������ϵ�˵绰:%s\n", pl->data.ID, pl->data.ID_type, pl->data.Name,  pl->data.PhoneNumber, pl->data.Emergency, pl->data.EmerPhone);
        printf("\n");//����˿���Ϣ
        
        pl = pl->nextP;//�ҵ���һ�ڵ�
    }
    return OK;
}