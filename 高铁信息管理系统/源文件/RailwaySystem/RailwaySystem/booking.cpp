#include "booking.h"
#include "HighRail.h"
#include "Date.h"
#include "Menu.h"
Status ReadFromBooking(BList& blist, HRailList& hrList, const char* file) {//���ļ��ж�ȡ��Ϣ
    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return ERROR;
    }
    if (InitList_Book(blist) != OK) {
        perror("Error initializing rail list");
        return ERROR;
    }
    // �ļ�������ɨ���ȡ
    int InsertP = 1;
    BookData bData;//fscanf�ķ�ʽ��ȡ������
    while (fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %d %lf %s",
        bData.Order_Num, bData.Boarding_Date, bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
        bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, &bData.SeatNum, &bData.ticketPrice, bData.BookingDate)==14) {

        
        // ���ļ��ж�ȡ��Ʊ��Ϣ.
        
        /***********************************************************************************************************************/
        HRailList pr = hrList->nextRail;
          while (pr)//�����г�������
        {
            if (!strcmp(pr->data.DepartureDate, bData.Boarding_Date) && !strcmp(pr->data.Train_Number, bData.TrainNumber))//ƥ�䷢�����ںͳ��κ�
            {
                int flag1 = 0;//���ñ�־��¼���վ
                int flag2 = 0;//���ñ�־��¼�յ�վ
                int i;
                for (i = 0; i < pr->data.SqSS.Num; i++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[i].Station_Name, bData.StartingStation))
                    {
                        flag1 = 1;//�ҵ����վ
                        break;
                    }

                }
                int j;
                for (j = i + 1; j < pr->data.SqSS.Num; j++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[j].Station_Name, bData.TerminalStation))
                    {
                        flag2 = 1;//�ҵ��յ�վ
                        break;
                    }
                }
                if (flag1 && flag2)//���վ���յ�վͬʱ�ҵ�
                {
                    // �����վ���յ�վ֮�������λ�����Ϊ��Ԥ��
                    int flag3 = 0;
                    int Mark1 = 0;
                    int Mark2 = 0;
                    int NUM = 0;
                    int k;
                    int CountRest = 0;
                    for (int temp = 0; temp < pr->data.totalSeats; temp++)
                    {
                        for (k = i; k < j; k++)
                        {
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[temp].seatClass, bData.SeatClass) && pr->data.SqSS.SSList[k].seats[temp].seatNumber == bData.SeatNum)
                            {
                                NUM = temp;
                                break;
                            }
                        }
                        if (k < j)
                        {
                            break;
                        }
                        
                    }
                    for (k = i; k < j; k++)
                    {
                        pr->data.SqSS.SSList[k].seats[NUM].isBooked = 1;//��ʼ��ռ��
                    }
                    break;
                }
            }
            pr = pr->nextRail;
        }
        /***********************************************************************************************************************/
        // �Ѷ�ȡ���ݲ����������
        if (ListInsert_BookInitial(blist, InsertP++, bData) != OK) {
            perror("Error inserting data into rail list");// �������ʧ�ܣ���ӡ������Ϣ
            return ERROR;// ���ش���״̬
        }


    }
    fclose(fp);// �ر��ļ�
}
Status WriteBooking(BList& blist, const char* file) {
    FILE* fp1 = fopen(file, "w");
    BList p = blist->nextBooking;
    while (p != NULL)//��������������Ϣ��ͷ��β¼���ļ�
    {
        BookData bData = p->data;
        fprintf(fp1, "%s %s %s %s %s %s %s %s %s %s %s %d %.2lf %s",
            bData.Order_Num, bData.Boarding_Date, bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
            bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice, bData.BookingDate
            );
        fprintf(fp1, "\n");
        p = p->nextBooking;
    }
    fclose(fp1);
    return OK;
}
Status SearchBookingTicket(BList& blist)
{
    printf("��ѡ������Ҫ�Ĳ��ҷ�ʽ:\n");
    printf("1.����\n");
    printf("2.֤����\n");
    printf("3.�˳�����\n");
    printf("4.����\n");
    int s_choice;
    scanf("%d", &s_choice);//����ѡ��
    clearScreen();//�����Ļ
    switch (s_choice)
    {
    case 1: {
        int flag1 = 0;
        printf("����������Ҫ��ѯ�ĳ˿�������\n");
        char t_pname[20];
        scanf("%s", t_pname);//ͨ���˿�����ƥ��
        clearScreen();
        BList p = blist->nextBooking;
        while (p)//��������
        {
            if (!strcmp(p->data.P_Name, t_pname))//�ҵ�ƥ��ĳ˿�����
            {
                BookData bData = p->data;
                printf("������:%s\n��������:",
                    bData.Order_Num
                );
                DATE t_date = stringToDate(bData.Boarding_Date);//���ַ���ת��ΪDATE�ṹ���Ա����
                printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
                printf("��������:%s ���վ:%s �յ�վ:%s\n֤������:%s ֤����:%s �˿�����:%s\n����ʱ��:%s ����ʱ��:%s\n%s:%d�� Ʊ��:%.2lfԪ",
                    bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                    bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
                );
                DATE t_date1 = stringToDate(bData.BookingDate);//���ַ���ת��ΪDATE�ṹ���Ա����
                printf("\n��Ʊ����:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
                printf("\n");
                flag1++;
            }
            p = p->nextBooking;
        }
        if (!flag1)
        {
            printf("���������Ϣ!!!\n");
        }
        break;
    }
    case 2: {
        int flag1 = 0;
        printf("����������Ҫ��ѯ�ĳ˿�֤���ţ�\n");
        char t_pid[20];
        scanf("%s", t_pid);//ͨ���˿�IDƥ��
        clearScreen();
        BList p = blist->nextBooking;
        while (p)//��������
        {
            if (!strcmp(p->data.id, t_pid))//�ҵ�ƥ��ĳ˿�ID
            {
                BookData bData = p->data;
                printf("������:%s\n��������:",
                    bData.Order_Num
                );
                DATE t_date = stringToDate(bData.Boarding_Date);//���ַ���ת��ΪDATE�ṹ���Ա����
                printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
                printf("��������:%s ���վ:%s �յ�վ:%s\n֤������:%s ֤����:%s �˿�����:%s\n����ʱ��:%s ����ʱ��:%s\n%s:%d�� Ʊ��:%.2lfԪ",
                    bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                    bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
                );
                DATE t_date1 = stringToDate(bData.BookingDate);//���ַ���ת��ΪDATE�ṹ���Ա����
                printf("\n��Ʊ����:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
                printf("\n");
                flag1++;
            }
            p = p->nextBooking;
        }
        if (!flag1)
        {
            printf("���������Ϣ!!!\n");
        }
        break;
    }
    case 3: {
        int flag1 = 0;
        printf("����������Ҫ��ѯ�ĳ˳����ڣ�\n");
        char t_date[20];
        scanf("%s", t_date);//ͨ���˳�����ƥ��
        clearScreen();
        BList p = blist->nextBooking;
        while (p)//��������
        {
            if (!strcmp(p->data.Boarding_Date, t_date))//�ҵ�ƥ��ĳ˳�����
            {
                BookData bData = p->data;
                printf("������:%s\n��������:",
                    bData.Order_Num
                );
                DATE t_date = stringToDate(bData.Boarding_Date);//���ַ���ת��ΪDATE�ṹ���Ա����
                printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
                printf("��������:%s ���վ:%s �յ�վ:%s\n֤������:%s ֤����:%s �˿�����:%s\n����ʱ��:%s ����ʱ��:%s\n%s:%d�� Ʊ��:%.2lfԪ",
                    bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                    bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
                );
                DATE t_date1 = stringToDate(bData.BookingDate);//���ַ���ת��ΪDATE�ṹ���Ա����
                printf("\n��Ʊ����:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
                printf("\n");
                flag1++;
            }
            p = p->nextBooking;
        }
        if (!flag1)
        {
            printf("���������Ϣ!!!\n");
        }
        break;
    }
    case 4: {
        int flag1 = 0;
        printf("����������Ҫ��ѯ�ĳ��Σ�\n");
        char t_num[20];
        scanf("%s", t_num);//ͨ������ƥ��
        clearScreen();
        BList p = blist->nextBooking;
        while (p)//��������
        {
            if (!strcmp(p->data.TrainNumber, t_num))//�ҵ�ƥ��ĳ���
            {
                BookData bData = p->data;
                printf("������:%s\n��������:",
                    bData.Order_Num
                );
                DATE t_date = stringToDate(bData.Boarding_Date);//���ַ���ת��ΪDATE�ṹ���Ա����
                printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
                printf("��������:%s ���վ:%s �յ�վ:%s\n֤������:%s ֤����:%s �˿�����:%s\n����ʱ��:%s ����ʱ��:%s\n%s:%d�� Ʊ��:%.2lfԪ",
                    bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                    bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
                );
                DATE t_date1 = stringToDate(bData.BookingDate);//���ַ���ת��ΪDATE�ṹ���Ա����
                printf("\n��Ʊ����:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
                printf("\n");
                flag1++;
            }
            p = p->nextBooking;
        }
        if (!flag1)
        {
            printf("���������Ϣ!!!\n");
        }
        break;
    }
    default:
        break;
    }
    
    return OK;
}
Status SearchLeftTicket(HRailList& railList)
{
    printf("����������Ҫ��ѯ���г����ڣ�\n");// ��ʾ�û������г�����
    char t_Date1[10];// ����һ���ַ��������洢���������
    scanf("%s", t_Date1);// ��ȡ�û����������
    int flag_ret = 0; // ��־���������ڱ�ʾ�Ƿ��ҵ�ƥ����г�
    HRailList p = railList->nextRail;// ��ȡ�����������һ���ڵ�
    clearScreen();// ����
    // ������������Ѱ������������ƥ����г�
    while (p != NULL)
    {
        HRData hrData = p->data;// ��ȡ��ǰ�ڵ���г�����
        // ����г��ķ��������Ƿ�����������ƥ��
        if (!strcmp(hrData.DepartureDate, t_Date1)) {
            // ���ƥ�䣬��ӡ�г���Ϣ
            printf("�г�����:%s ʼ��վ:%s �յ�վ:%s �����:%.0lf���� �������:%s\n",
                hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                hrData.mileage, hrData.Condition);
            printf("����ʱ��:%s  �յ�ʱ��:%s ��������:", hrData.time_Departure,
                hrData.time_Arrival);
            DATE t_Date = stringToDate(hrData.DepartureDate);// ���ַ�������ת��ΪDATE����
            printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);// ��ӡ����

            // ��ӡ�г�������ͣ��վ��Ϣ
            for (int i = 0; i < hrData.StoppingStationNum; i++) {
                StoppingStation station = hrData.SqSS.SSList[i];
                // ��ȡÿ����ͣվ����
                printf("ͣ��վ%d:%s ����ʱ��:%s ����ʱ��:%s ���:%.1lf����\n",
                    i + 1, station.Station_Name, station.ArrivalT,
                    station.DepartureT, station.mileage_s);

            }
            flag_ret = 1;// ���ñ�־������ʾ�ҵ���ƥ����г�
            printf("\n");

        }
        p = p->nextRail;// �ƶ��������е���һ���ڵ�
    }
    if (!flag_ret)
    {
        // ���û���ҵ�ƥ����г�����ӡ��ʾ��Ϣ�����ش���
        printf("δ��ѯ������ҪԤ�����г���Ϣ!!!\n������!!!\n");

        return ERROR;
    }
    printf("1.�����β�ѯ\n");// ��ʾ�û�ѡ���ѯ��ʽ
    printf("2.�����վ���յ�վ��ѯ\n");
    HRailList pr = railList->nextRail;
    int t_button;
    scanf("%d", &t_button);// ����һ�������������洢�û���ѡ��
    switch (t_button)
    {
    case 1:
    {
        // ��ʾ�û������г�����
        printf("�������г�����:");
        char t_Tnum[10];
        scanf("%s", t_Tnum);
        // ��ʾ�û�������ʼվ���յ�վ
        printf("�����������ѯ����ʼվ���յ�վ\n");
        char t_Start[20];
        char t_Ending[20];
        printf("���վ:");
        scanf("%s", t_Start);
        printf("�յ�վ:");
        scanf("%s", t_Ending);
        // ���������Բ���ƥ����г�
        while (pr)
        {
            // ��鷢�����ںͳ��κ��Ƿ�ƥ��
            if (!strcmp(pr->data.DepartureDate, t_Date1) && !strcmp(pr->data.Train_Number, t_Tnum))
            {
                int flag1 = 0;// ��־λ�������ʼվ�Ƿ��ҵ�
                int flag2 = 0;// ��־λ������յ�վ�Ƿ��ҵ�
                int i;
                // ��������ͣ��վ���ҵ���ʼվ
                for (i = 0; i < pr->data.SqSS.Num; i++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[i].Station_Name, t_Start))
                    {
                        flag1 = 1;// �ҵ���ʼվ
                        break;
                    }

                }
                int j;
                // ���ҵ�����ʼվ֮��������������ҵ��յ�վ
                for (j = i + 1; j < pr->data.SqSS.Num; j++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[j].Station_Name, t_Ending))
                    {
                        flag2 = 1;// �ҵ��յ�վ
                        break;
                    }
                }
                // �����ʼվ���յ�վ���ҵ�
                if (flag1 && flag2)
                {
                    int flag3 = 0;
                    int Mark1 = 0;
                    int Mark2 = 0;
                    double Price = 0;
                    int k;
                    int CountRest = 0;// ���ڼ���ʣ����λ�ļ�����
                    // ����������λ�Լ��ʣ����λ��
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        // ����ض���λ�����������һ����������������ʣ����λ
                        for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                            {
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;// ֻҪ�ҵ�һ����Ԥ������λ����ֹͣ��ǰѭ��
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                         
                        }

                    }
                    printf("ʣ������%d�ţ�\n",CountRest);
                    CountRest = 0;
                    // ����ض���λ�����������һ����������������ʣ����λ
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "һ����"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "һ����"))
                            {
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;// ֻҪ�ҵ�һ����Ԥ������λ����ֹͣ��ǰѭ��
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                         
                        }

                    }
                    printf("ʣһ����%d�ţ�\n", CountRest);
                    CountRest = 0;
                    // ����ض���λ�����������һ����������������ʣ����λ
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                            {
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;// ֻҪ�ҵ�һ����Ԥ������λ����ֹͣ��ǰѭ��
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                        
                        }

                    }
                    printf("ʣ������%d�ţ�\n",CountRest);
                    CountRest = 0;

                    break;
                }
               
            }
            pr = pr->nextRail;// �ƶ�����һ������Ԫ��
            
        }
        if (!pr)
        {
            printf("�޷���ѯ���������ҵ��г���Ϣ!!!\n");
        }
        break;
    }
    case 2:
    {
        // ��ʾ�û������г����վ���յ�վ
        printf("�������г����վ���յ�վ\n");
        char t_Start[20];
        char t_Ending[20];
        printf("���վ:\n");
        scanf("%s", t_Start);
        printf("�յ�վ:\n");
        scanf("%s", t_Ending);
        // ���������Բ���ƥ����г�
        while (pr)
        {
            int flag1 = 0;// ��־λ�������ʼվ�Ƿ��ҵ�
            int flag2 = 0;// ��־λ������յ�վ�Ƿ��ҵ�
            // ��鷢�������Ƿ�ƥ��
            if (!strcmp(pr->data.DepartureDate, t_Date1))
            {

                int i;
                // ��������ͣ��վ���ҵ���ʼվ
                for (i = 0; i < pr->data.SqSS.Num; i++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[i].Station_Name, t_Start))
                    {
                        flag1 = 1;// �ҵ���ʼվ
                        break;
                    }

                }
                int j;
                // ���ҵ�����ʼվ֮��������������ҵ��յ�վ
                for (j = i + 1; j < pr->data.SqSS.Num; j++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[j].Station_Name, t_Ending))
                    {
                        flag2 = 1;// �ҵ��յ�վ
                        break;
                    }
                }
                // �����ʼվ���յ�վ���ҵ�
                if (flag1 && flag2)
                {
                    int flag3 = 0;
                    int Mark1 = 0;
                    int Mark2 = 0;
                    double Price = 0;
                    int k;
                    int CountRest = 0;// ���ڼ���ʣ����λ�ļ�����
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        // ����ض���λ�����������һ����������������ʣ����λ
                        for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                        {
                            // �������վ���յ�վ֮�������վ��
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                            {       // �����λ�Ƿ�δ��Ԥ��
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;// ֻҪ�ҵ�һ����Ԥ������λ����ֹͣ��ǰѭ��
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                            
                        }

                    }
                    printf("ʣ������%d�ţ�\n", CountRest);
                    CountRest = 0;// �ظ������߼��Լ��һ�����Ͷ�������ʣ����λ������Ӧ�ص�����λ����������
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "һ����"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "һ����"))
                            {
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                            
                        }

                    }
                    printf("ʣһ����%d�ţ�\n",CountRest);
                    CountRest = 0;
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                            {
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                            
                        }

                    }
                    printf("ʣ������%d�ţ�\n",CountRest);
                    CountRest = 0;
                    break;
                }
             
            }
            pr = pr->nextRail;// �ƶ�����һ������Ԫ��
            
           
        }
        if (!pr)
        {
            printf("�޷���ѯ���������ҵ��г���Ϣ!!!\n");
        }
        break;
    }
    default:
        break;
    }
    return OK;
    
}
Status GenerateOrderNum(BList& blist, BookData& BData)
{
    BList tempB = blist->nextBooking;
    char trainNumStr[5];
    char seatStr[5];
    char orderNumber[50]; // �㹻���Դ洢�����Ķ�����
    int CountB = 0;
    while (tempB)
    {
        if (!strcmp(tempB->data.TrainNumber, BData.TrainNumber))
        {
            CountB++;
        }
        tempB = tempB->nextBooking;
    }
    // ��ȡ�г����е����ֲ���
    int trainNum = atoi(BData.TrainNumber + 1); // �����г��ŵĸ�ʽʼ��Ϊһ����ĸ�������

    // ��ʽ���г��ź���λ��
    sprintf(trainNumStr, "%04d", trainNum);
    sprintf(seatStr, "%03d", ++CountB);
    // ����ַ���
    sprintf(orderNumber, "%s-%s-%s", BData.Boarding_Date, trainNumStr, seatStr);
    strcpy(BData.Order_Num, orderNumber);
    return OK;
}
Status AddBooking(BList & blist, HRailList& railList,const char* fileRail, const char* file)   
{

        clearScreen();// ������Ļ�Կ�ʼ�µ��������
        BookData BData_i;
        printf("������˳�����\n");// ��ʾ�û�����˳�����
        // ���ļ��ж�ȡ������Ϣ.
        scanf("%s",
            BData_i.Boarding_Date);
        clearScreen();
        int flag_ret = 0;// ���ڱ���Ƿ��ҵ���ƥ����г�
        HRailList p = railList->nextRail;// ���г��б��ͷ�ڵ㿪ʼ����
        
        while (p != NULL)// ���������г���Ѱ�ҷ���ָ�����ڵ��г�
        {
            HRData hrData = p->data;// ��ȡ��ǰ�г�������
            if (!strcmp(hrData.DepartureDate, BData_i.Boarding_Date)) {// ���ƥ�䣬��ӡ�г�����ϸ��Ϣ
                printf("�г�����:%s ʼ��վ:%s �յ�վ:%s �����:%.0lf���� �������:%s\n",
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("����ʱ��:%s  �յ�ʱ��:%s ��������:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);// ���ַ�����ʽ������ת��Ϊ���ڽṹ
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                // ��������ӡÿ����ͣվ����Ϣ
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // ��ȡÿ����ͣվ����
                    printf("ͣ��վ%d:%s ����ʱ��:%s ����ʱ��:%s ���:%.1lf����\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                flag_ret = 1;
                printf("\n");
                
            }
            p = p->nextRail;// �ƶ�����һ���г��ڵ�
        }
        if (!flag_ret)
        {
            printf("δ��ѯ������ҪԤ�����г���Ϣ!!!\n������!!!\n");

            return ERROR;
        }
        
        printf("���������վ:");
        // ��ʾ�û��������վ
        scanf("%s",
             BData_i.StartingStation);// ���û�����ȡ���վ
        
        printf("\n�������յ�վ:");
        // ��ʾ�û������յ�վ
        scanf("%s",
             BData_i.TerminalStation);// ���û�����ȡ�յ�վ
        clearScreen();
        HRailList p_temp = railList->nextRail;// ����ָ�룬��ʼ�µı���
        while (p_temp)// �����г��б�Ѱ��ƥ�����վ���յ�վ���г�
        {
            int flag1 = 0;// ������վ�Ƿ��ҵ�
            double record1 = 0;// ��¼���վ���
            double record2 = 0;// ��¼�յ�վ���
            int flag2 = 0;// ����յ�վ�Ƿ��ҵ�
            if (!strcmp(p_temp->data.DepartureDate, BData_i.Boarding_Date))
            {

                int i;
                for (i = 0; i < p_temp->data.SqSS.Num; i++)// ����ͣ��վ��Ѱ�����վ
                {
                    if (!strcmp(p_temp->data.SqSS.SSList[i].Station_Name, BData_i.StartingStation))
                    {
                        flag1 = 1;// �ҵ����վ
                        record1 = p_temp->data.SqSS.SSList[i].mileage_s;// ��¼���
                        break;
                    }

                }
                int j;
                for (j = i + 1; j < p_temp->data.SqSS.Num; j++)
                {
                    if (!strcmp(p_temp->data.SqSS.SSList[j].Station_Name, BData_i.TerminalStation))
                    {
                        flag2 = 1;
                        record2 = p_temp->data.SqSS.SSList[j].mileage_s;
                        break;
                    }
                }
                if (flag1 && flag2)// ������վ���յ�վ���ҵ�
                
                {
                    break;
                }
                
            }
            p_temp = p_temp->nextRail; // �ƶ�����һ���г��ڵ�
        }
        if (!p_temp)// ���û���ҵ�ƥ����г�
        {
            printf("δ��ѯ������ҪԤ�����г���Ϣ!!!\n������!!!\n");
            
            return ERROR;// ���ش���״̬
        }
        int Alongwith = 0;// ͬ������
        printf("������ͬ������\n");
        // ���ļ��ж�ȡ������Ϣ.
        scanf("%d",&Alongwith);// ���û�����ȡͬ������
        clearScreen();
        if (Alongwith > 2 || Alongwith < 0)// ���ͬ�������Ƿ���Ϲ涨
        {
            if (Alongwith > 2)
                printf("ͬ���������ö�������!!!\n");// ����ͬ����������
            else
            {
                printf("ͬ����������������!!!\n");// ͬ�������������
            }
            return ERROR;
        }
        else
        {
            // Ϊÿ���˿ͣ�����Ԥ���ߺ�ͬ���ˣ�����Ԥ����Ϣ
            for (int along = 0; along < Alongwith + 1; along++)
            {
                BookData BData;// ����һ�����ڴ洢ÿ���˿͵�Ԥ����Ϣ�Ľṹ��
                // ���ƹ����Ԥ����Ϣ�����վ���յ�վ���˳����ڣ�
                strcpy(BData.StartingStation, BData_i.StartingStation);
                strcpy(BData.TerminalStation, BData_i.TerminalStation);
                strcpy(BData.Boarding_Date, BData_i.Boarding_Date);

                // ��ʾ�û�����ÿ���˿͵ĸ�����Ϣ��֤���š�������֤�����͡���ϯ�ȼ���
                printf("������֤����,����,֤������,��ϯ�ȼ�\n");
                
                scanf("%s %s %s %s",
                    BData.id, BData.P_Name, BData.id_type, BData.SeatClass);
                DATE now = Get_Sys_Time();//��Ʊ����
                char t_bkt[10];
                dateToString(now, t_bkt);
                strcpy(BData.BookingDate, t_bkt);
                DATE BoardTime = stringToDate(BData.Boarding_Date);//�˳�����
                // ���㵱ǰ������˳�����֮���������
                int differ = daysBetweenDates(now, BoardTime);
                // ����Ƿ��ڶ�Ʊʱ�䷶Χ�ڣ��������ڣ�
                if (differ > 60)
                {
                    printf("���ڻ�δ����Ʊʱ�䣬ֻ��Ԥ���������ڵĳ�Ʊ!!!\n");
                    return ERROR;
                }
                HRailList pr = railList->nextRail;
                // �����г��б�Ѱ��ƥ����г���������λԤ���߼�
                while (pr)
                {
                    int flag1 = 0;
                    double record1 = 0;
                    double record2 = 0;
                    int flag2 = 0;
                    if (!strcmp(pr->data.DepartureDate, BData.Boarding_Date))
                    {

                        int i;
                        for (i = 0; i < pr->data.SqSS.Num; i++)
                        {
                            if (!strcmp(pr->data.SqSS.SSList[i].Station_Name, BData.StartingStation))
                            {
                                flag1 = 1;
                                record1 = pr->data.SqSS.SSList[i].mileage_s;
                                break;
                            }

                        }
                        int j;
                        for (j = i + 1; j < pr->data.SqSS.Num; j++)
                        {
                            if (!strcmp(pr->data.SqSS.SSList[j].Station_Name, BData.TerminalStation))
                            {
                                flag2 = 1;
                                record2 = pr->data.SqSS.SSList[j].mileage_s;
                                break;
                            }
                        }
                        if (flag1 && flag2)
                        {
                            int flag3 = 0;
                            int Mark1 = 0;
                            int Mark2 = 0;
                            double Price = 0;

                            strcpy(BData.TrainNumber, pr->data.Train_Number);
                            strcpy(BData.DepartureTime, pr->data.SqSS.SSList[i].DepartureT);
                            strcpy(BData.ArrivalTime, pr->data.SqSS.SSList[j].ArrivalT);
                            if (!strcmp(BData.SeatClass, "������"))
                            {
                                Price = (record2 - record1) * 1.2;//�������۸�
                                BData.ticketPrice = Price;
                                int CountS;
                                for ( CountS = 0; CountS < pr->data.totalSeats; CountS++)
                                {
                                    int k;
                                    for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                                    {
                                        if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                                        {
                                            break;
                                        }
                                        if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                                        {
                                            if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                            {
                                                flag3 = 1;
                                                break;
                                            }
                                        }

                                    }
                                    if (k == j) {
                                        Mark1 = k;
                                        Mark2 = CountS;
                                        break;
                                    }

                                }
                                if (CountS >= pr->data.totalSeats)
                                {
                                    printf("������Ʊ�Ѷ��꣬�����¶�Ʊ!!!\n");
                                    return ERROR;
                                }
                                for (int Cc = i; Cc < j; Cc++)
                                {
                                    pr->data.SqSS.SSList[Cc].seats[Mark2].isBooked = 1;//��ʼ��ÿ����ͣվռ����
                                }
                                BData.SeatNum = pr->data.SqSS.SSList[i].seats[Mark2].seatNumber;
                                GenerateOrderNum(blist, BData);//���ɶ�����
                                BList tempB = blist->nextBooking;
                                int CountB = 0;
                                int flag_Insert = 0;
                                while (tempB)
                                {
                                    CountB++;
                                    if (!strcmp(tempB->data.TrainNumber, BData.TrainNumber))
                                    {
                                        ListInsert_BookInitial(blist, CountB, BData);
                                        flag_Insert = 1;
                                        break;
                                    }
                                    tempB = tempB->nextBooking;
                                }
                                if (!flag_Insert)
                                {
                                    ListInsert_BookInitial(blist, CountB+1, BData);
                                }

                            }
                            if (!strcmp(BData.SeatClass, "һ����"))
                            {
                                Price = (record2 - record1) * 0.6;//һ�����۸�
                                BData.ticketPrice = Price;
                                int CountS;
                                for (CountS = 0; CountS < pr->data.totalSeats; CountS++)
                                {
                                    int k;
                                    for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                                    {
                                        if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "һ����"))
                                        {
                                            break;
                                        }
                                        if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "һ����"))
                                        {
                                            if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                            {
                                                flag3 = 1;
                                                break;
                                            }
                                        }

                                    }
                                    if (k == j) {
                                        Mark1 = k;
                                        Mark2 = CountS;
                                        break;
                                    }
                                   
                                }
                                if (CountS >= pr->data.totalSeats)
                                {
                                    printf("һ����Ʊ�Ѷ��꣬�����¶�Ʊ!!!\n");
                                    return ERROR;
                                }
                                for (int Cc = i; Cc < j; Cc++)
                                {
                                    pr->data.SqSS.SSList[Cc].seats[Mark2].isBooked = 1;//��ʼ��ÿ����ͣվռ����
                                }
                                BData.SeatNum = pr->data.SqSS.SSList[i].seats[Mark2].seatNumber;
                                GenerateOrderNum(blist, BData);//���ɶ�����
                                BList tempB = blist->nextBooking;
                                int CountB = 0;
                                int flag_Insert = 0;
                                while (tempB)
                                {
                                    CountB++;
                                    if (!strcmp(tempB->data.TrainNumber, BData.TrainNumber))
                                    {
                                        ListInsert_BookInitial(blist, CountB, BData);
                                        flag_Insert = 1;
                                        break;
                                    }
                                    tempB = tempB->nextBooking;
                                }
                                if (!flag_Insert)
                                {
                                    ListInsert_BookInitial(blist, CountB + 1, BData);
                                }

                            }
                            if (!strcmp(BData.SeatClass, "������"))
                            {
                                Price = (record2 - record1) * 0.46;//�������۸�
                                BData.ticketPrice = Price;
                                int CountS;
                                for ( CountS= 0; CountS < pr->data.totalSeats; CountS++)
                                {
                                    int k;
                                    for (k = i; k < j; k++)//ֻ�����վ���յ㲻ȡ
                                    {
                                        if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                                        {
                                            break;
                                        }
                                        if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "������"))
                                        {
                                            if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                            {
                                                flag3 = 1;
                                                break;
                                            }
                                        }

                                    }
                                    if (k == j) {
                                        Mark1 = k;
                                        Mark2 = CountS;
                                        break;
                                    }

                                }
                                if (CountS >= pr->data.totalSeats)
                                {
                                    printf("������Ʊ�Ѷ��꣬�����¶�Ʊ!!!\n");
                                    return ERROR;
                                }
                                for (int Cc = i; Cc < j; Cc++)
                                {
                                    pr->data.SqSS.SSList[Cc].seats[Mark2].isBooked = 1;//��ʼ��ÿ����ͣվռ����
                                }
                                BData.SeatNum = pr->data.SqSS.SSList[i].seats[Mark2].seatNumber;
                                GenerateOrderNum(blist, BData);//���ɶ�����
                                BList tempB = blist->nextBooking;
                                int CountB = 0;
                                int flag_Insert = 0;
                                while (tempB)
                                {
                                    CountB++;
                                    if (!strcmp(tempB->data.TrainNumber, BData.TrainNumber))
                                    {
                                        ListInsert_BookInitial(blist, CountB, BData);
                                        flag_Insert = 1;
                                        break;
                                    }
                                    tempB = tempB->nextBooking;
                                }
                                if (!flag_Insert)
                                {
                                    ListInsert_BookInitial(blist, CountB + 1, BData);
                                }
                               
                            }
                            break;
                        }

                    }
                    if (!pr)
                    {
                        printf("������Ϣ����,��Ʊʧ��!!!\n");
                    }
                    pr = pr->nextRail;

                }
            }
        }
        
        clearScreen();// ������Ļ
        printCentered("��Ʊ�ɹ�!!");// ��ӡ��Ʊ�ɹ�
        WriteFile(railList, fileRail);
        WriteBooking(blist, file);
        return OK;

}

Status DeleteBooking(BList& blist, const char* file) {//��Ʊ��Ǯ
    BookData BData;// ����һ���ṹ��洢Ԥ������
    printf("������֤����:");
    // ��ʾ�û�����֤����
    scanf("%s",
        BData.id);// ��ȡ�û������֤����
    clearScreen();
    printf("����������:");
    // ��ʾ�û���������.
    scanf("%s",
        BData.P_Name);
    clearScreen();
    /***********************************************************/
    
    int flag1 = 0;// ���ڱ���Ƿ��ҵ�ƥ���Ԥ����Ϣ
    BList p1 = blist->nextBooking;// ָ��Ԥ���б��ͷ�ڵ�
    while (p1)// ����Ԥ���б����ƥ���Ԥ��
    {
        if (!strcmp(p1->data.P_Name, BData.P_Name)&& !strcmp(p1->data.id, BData.id))
        {
            BookData bData = p1->data;// ��ȡƥ���Ԥ������
            // ��ӡԤ����Ϣ
            printf("������:%s\n��������:",
                bData.Order_Num
            );
            DATE t_date = stringToDate(bData.Boarding_Date);// ���ַ�����ʽ������ת��Ϊ���ڽṹ
            printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
            printf("��������:%s ���վ:%s �յ�վ:%s\n֤������:%s ֤����:%s �˿�����:%s\n����ʱ��:%s ����ʱ��:%s\n%s:%d�� Ʊ��:%.2lfԪ",
                bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
            );
            DATE t_date1 = stringToDate(bData.BookingDate);// ���ַ�����ʽ������ת��Ϊ���ڽṹ
            printf("\n��Ʊ����:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
            printf("\n");
            flag1++;
        }
        p1 = p1->nextBooking;
    }
    if (!flag1)
    {
        printf("���������Ϣ!!!\n");
        return ERROR;
    }
    /***********************************************************/
    printf("����������Ҫ�˶��ĳ�Ʊ������:\n");//��ʾ�����˶���Ʊ������
    char tmp_order[25];
    scanf("%s", tmp_order);
    clearScreen();
    BList p = blist;
    int flag_t = 0;
    while (p->nextBooking)//����������
    {

        BookData bData = p->nextBooking->data;
        if (!strcmp(bData.Order_Num, tmp_order))
        {
            BList p2 = p->nextBooking;
            p->nextBooking = p2->nextBooking;
            /*******************��ʱ�����Ǯ*********************/
            DATE now = Get_Sys_Time();
            DATE BoadrTime = stringToDate(bData.Boarding_Date);
            int B_m;
            int N_m;
            sscanf(bData.DepartureTime, "%2d%*c%2d", &BoadrTime.hour, &BoadrTime.min);
            int M_sub = timeToMin(BoadrTime) - timeToMin(now);
            if (BoadrTime.year > now.year || (BoadrTime.year == now.year && BoadrTime.month > now.month) || (BoadrTime.year == now.year && BoadrTime.month == now.month && BoadrTime.day > now.day)
                || (BoadrTime.year == now.year && BoadrTime.month == now.month && BoadrTime.day == now.day && M_sub > 120))//�ж��Ƿ����ڷ�������Сʱǰ��Ʊ
            {
                printf("��Ʊ�ɹ�!!!\n���˿%.2lf Ԫ", bData.ticketPrice);//ȫ����Ʊ
                printf("\n");
            }
            else
            {
                printf("��Ʊ�ɹ�!!!\n���˿%.2lf Ԫ", bData.ticketPrice*0.95);//��ȡ%5��Ʊ��
                printf("\n");
            }
            free(p2);//�ͷ��ڴ�
            flag_t = 1;
            break;
        }
                p = p->nextBooking;//Ѱ����һ�ڵ�
    }
    if (!flag_t)
    {
        printf("���Ҳ������Ķ�����Ϣ���޷���Ʊ!!!\n");//���������ʾ
    }
    WriteBooking(blist, file);//����д���ļ�
    return OK;
}


Status PrintBookingInfo(BList& blist) {//������г�Ʊ��Ϣ

    BList p = blist->nextBooking;
    while (p != NULL)//����������
    {
        BookData bData = p->data;
        printf("������:%s\n��������:",
            bData.Order_Num
        );
        DATE t_date = stringToDate(bData.Boarding_Date);//���ַ���ת��ΪDate�ṹ��
        printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
        printf("��������:%s ���վ:%s �յ�վ:%s\n֤������:%s ֤����:%s �˿�����:%s\n����ʱ��:%s ����ʱ��:%s\n%s:%d�� Ʊ��:%.2lfԪ",
            bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
            bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
        );
        DATE t_date1 = stringToDate(bData.BookingDate);//���ַ���ת��ΪDate�ṹ��
        printf("\n��Ʊ����:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
        printf("\n");
        p = p->nextBooking;//�ҵ���һ���
    }
    return OK;
}


Status PrintTicketInfo(BList& blist) {

    FILE* file = fopen("ticket.txt", "w");  // ���ļ�����д��
    if (file == NULL) {
        perror("Error opening file");
        return ERROR;  // ���� ERROR ״̬
    }
    printf("����������֤���ţ�\n");//��ʾ����
    char t_id[25];
    scanf("%s", t_id);
    printf("����������������\n");//��ʾ����
    char t_name[25];
    scanf("%s", t_name);
    clearScreen();
    BList p = blist->nextBooking;//�ҵ���Ԫ���
    int flag = 0;//���ñ�־λ
    while (p != NULL)//����������
    {
        
        BookData bData = p->data;
        if (!strcmp(t_id, bData.id)&& !strcmp(t_name, bData.P_Name))//����������IDƥ��
        {

            printf("��������:"
            );
            DATE t_date = stringToDate(bData.Boarding_Date);//���ַ���ת��ΪDate�ṹ��
            printf("%4d/%02d/%02d\n", t_date.year, t_date.month, t_date.day);
            printf("���վ:%s �յ�վ:%s\n֤������:%s ֤����:%s �˿�����:%s\n����ʱ��:%s ����ʱ��:%s\n��������:%s %s:%d�� Ʊ��:%.2lfԪ",
                  bData.StartingStation, bData.TerminalStation, bData.id_type,
                bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.TrainNumber, bData.SeatClass, bData.SeatNum, bData.ticketPrice
            );
            DATE t_date1 = stringToDate(bData.BookingDate);//���ַ���ת��ΪDate�ṹ��
            printf("\n��Ʊ����:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
            printf("������:%s\n",
                bData.Order_Num
            );
            printf("\n");
            
            flag++;//��־λ����
        }
        
        p = p->nextBooking;//�ҵ���һ�ڵ�
    }
    if (!flag)
    {
        printf("��ѯ�������Ķ������붩Ʊ!!!\n");//���������ʾ
        fprintf(file, "��ѯ�������Ķ������붩Ʊ!!!\n");//��ӡ������ʾ���ļ�
        fclose(file);
        return ERROR;//���ش���״̬
    }
    printf("����������Ҫ��ӡ�ĳ�Ʊ������:\n");//��ʾ����
    char t_order[25];
    int flag_order = 0;//���ñ�־λ
    scanf("%s", t_order);//���붩�����Թ���ӡ
    clearScreen();//����
    p = blist->nextBooking;
    while (p != NULL)//����������
    {

        BookData bData = p->data;
        if (!strcmp(t_order, bData.Order_Num) )//ƥ�䶩����
        {

           
            DATE t_date = stringToDate(bData.Boarding_Date);//���ַ���ת��ΪDate�ṹ��
           
            DATE t_date1 = stringToDate(bData.BookingDate);//���ַ���ת��ΪDate�ṹ��
           
            // д���ļ������Ǵ�ӡ������̨
            fprintf(file, "��������: %4d/%02d/%02d\n", t_date.year, t_date.month, t_date.day);
            fprintf(file, "���վ: %s �յ�վ: %s\n֤������: %s ֤����: %s �˿�����: %s\n����ʱ��: %s ����ʱ��: %s\n��������: %s %s: %d�� Ʊ��: %.2lfԪ\n",
                bData.StartingStation, bData.TerminalStation, bData.id_type,
                bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.TrainNumber, bData.SeatClass, bData.SeatNum, bData.ticketPrice);
            fprintf(file, "��Ʊ����: %4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
            fprintf(file, "������: %s\n\n", bData.Order_Num);
            printf("��Ʊ��ӡ�ɹ�,�����ļ����в鿴!!!\n\n", flag + 1);
            flag_order++;//��־λ����
            break;
        }

        p = p->nextBooking;
    }
    if (!flag_order)
    {
        printf("��ѯ�������Ķ�������ȷ�϶�����!!!\n");//���������Ϣ
        fprintf(file, "��ѯ�������Ķ�������ȷ�϶�����!!!\n");//��ӡ������Ϣ
    }
    fclose(file);  // �ر��ļ�
    return OK;
}