#include "HighRail.h"
#include"Menu.h"
#include"Date.h"
Status WriteFile(HRailList& railList, const char* file) {
    // ���ļ�����д�룬����ļ��������򴴽�
    FILE *fp1 = fopen(file, "w");
    // ��ȡ�г�������
    int n = railList->HighRail_Num;
    // ָ������б�ĵ�һ���ڵ�
    HRailList p = railList->nextRail;
    fprintf(fp1, "%d\n", n);// ���г�����д���ļ�
    while (p != NULL) // �������������б�
    {
        HRData hrData = p->data;// ��ȡ��ǰ�ڵ������
        fprintf(fp1, "%s %s %s %.0lf %s %s %s %d %d %d %d %s",
            hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
            hrData.mileage, hrData.Condition, hrData.time_Departure,
            hrData.time_Arrival, hrData.StoppingStationNum, hrData.SuperlativeSeat,
            hrData.FirstClassSeat, hrData.SecondClassSeat,hrData.DepartureDate);// ���г��Ļ�����Ϣд���ļ�
        for (int i = 0; i < hrData.StoppingStationNum; i++) { // �����г���ÿ��ͣ��վ��д������ϸ��Ϣ
            StoppingStation station= hrData.SqSS.SSList[i];
            // ��ȡÿ����ͣվ����
            fprintf(fp1," %s %s %s %.1lf",
                station.Station_Name, station.ArrivalT,
                station.DepartureT, station.mileage_s);// ��ͣ��վ����Ϣд���ļ�
      
        }
        fprintf(fp1, "\n");// ���У�׼��д����һ���г�����Ϣ
        p = p->nextRail;// �ƶ��������е���һ���ڵ�
    }
    fclose(fp1);
    return OK; // ���ز����ɹ���״̬
}
Status AddTrain(HRailList& railList, const char* file) {
    HRData hrData;
    printf("�����복�Σ�ʼ��վ���յ�վ������̣�����״��������ʱ�䣬��վʱ��\n");//�����ʾ
   
    scanf("%s %s %s %lf %s %s %s",
        hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
        &hrData.mileage, hrData.Condition, hrData.time_Departure,
        hrData.time_Arrival);//�����ݶ���洢�ṹ
    printf("��ͣվ����������������һ��������������������,��������\n");//�����ʾ
   
    scanf("%d %d %d %d %s",
        &hrData.StoppingStationNum, &hrData.SuperlativeSeat,
        &hrData.FirstClassSeat, &hrData.SecondClassSeat, hrData.DepartureDate);//�����ݶ���洢�ṹ
    clearScreen();//����

    if (hrData.StoppingStationNum > 0) {
        if (InitList_Sq(hrData.SqSS, hrData.StoppingStationNum) != OK) {
            perror("Error initializing stopping station list");//���������Ϣ
            return ERROR;//���ش���״̬
        }

        for (int i = 0; i < hrData.StoppingStationNum; i++) {
            StoppingStation station;

            printf("�����뾭ͣվ��������ʱ�䣬�뿪ʱ�䣬���\n");//�����ʾ
            scanf("%s %s %s %lf",
                station.Station_Name, station.ArrivalT,
                station.DepartureT, &station.mileage_s);//��ȡվ����Ϣ
            hrData.SqSS.SSList[i] = station;//����վ��
        }
    }
    // �Ѷ�ȡ���ݲ����������
    if (ListInsert_Rail(railList, railList->HighRail_Num+1, hrData) != OK) {
        perror("Error inserting data into rail list");//���������Ϣ
        return ERROR;//���ش���״̬
    }
    WriteFile(railList, file);//д���ļ�
    return OK;//����OK״̬
}
Status StopTrain(HRailList& railList, const char* file) {
    char temp[20];
    printf("��Ҫͣ�˵ĳ��Σ�\n");//��ʾ����
    scanf("%s", temp);
    HRailList p = railList->nextRail;//��ȡ��Ԫ���
    while (p != NULL)//����������
    {
        HRData hrData = p->data;
        if (!strcmp(hrData.Train_Number, temp)) {//���κ�ƥ��
            strcpy(p->data.Condition, "ͣ��");//״̬�޸�
            
            printf("�ɹ�ͣ��һ���г�!!!\n");//ͣ�˳ɹ�
            break;
        }
        p = p->nextRail;//Ѱ����һ�ڵ�
    }
    if (!p) {
        printf("��ѯ��������Ҫͣ�˵ĳ��Σ�����\n");//���������Ϣ
        return ERROR;//���ش���״̬
    }
    WriteFile(railList, file);//д���ļ�
    return OK;//����OK״̬
}
Status SearchTrain(HRailList& railList) {
    char temp[20];// ����һ���ַ��������ڴ洢�û�����
    int SearchWay;// ����һ�����ͱ������ڴ洢�û�ѡ��Ĳ�ѯ��ʽ
    printf("��ѯ��ʽ��\n");// ��ӡ��ѯ��ʽ����ʾ��Ϣ
    // �ṩ��ͬ�Ĳ�ѯ��ʽѡ��
    printf("1.����\n");
    printf("2.���վ\n");
    printf("3.�յ�վ\n");
    printf("4.����ʱ��\n");
    printf("5.ͣ��վ\n");
    scanf("%d", &SearchWay);// ��ȡ�û�����Ĳ�ѯ��ʽ
    clearScreen();// ������Ļ
    switch (SearchWay)// ʹ��switch�������û���ѡ��ִ�в�ͬ�Ĳ�ѯ����
    {
    case 1: {// ���β�ѯ
        printf("����Ҫ��ѯ�ĳ����ǣ�\n");
        scanf("%s", temp);// ��ȡ�û�����ĳ���
        HRailList p = railList->nextRail; // ��ȡ�����б��ͷ�ڵ�
        while (p != NULL)// ���������б�
        {
            HRData hrData = p->data;// ��ȡ��ǰ�ڵ������
            if (!strcmp(hrData.Train_Number, temp)) {// ��鳵���Ƿ�ƥ��
                printf("�г�����:%s ʼ��վ:%s �յ�վ:%s �����:%.0lf���� �������:%s\n",// ���ƥ�䣬���ӡ���г�����Ϣ
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("����ʱ��:%s  �յ�ʱ��:%s ��������:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                printf("��λ��:\n������:%d  һ����:%d ������:%d\n", hrData.SuperlativeSeat,
                    hrData.FirstClassSeat, hrData.SecondClassSeat);
                printf("��ͣվ��:%d\n", hrData.StoppingStationNum);
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // ��ȡÿ����ͣվ����
                    printf("ͣ��վ%d:%s ����ʱ��:%s ����ʱ��:%s ���:%.1lf����\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                printf("\n");
                break;
            }
            p = p->nextRail; // �ƶ�����һ���ڵ�
        }
        if (!p) {// ���û���ҵ�ƥ��ĳ���
            printf("��������Ҫ���ҵĳ�����Ϣ������\n");
            return ERROR;// ���ش���״̬
        }
        break;

    }
    case 2: {// ���վ��ѯ
        printf("����Ҫ��ѯ�����վ�ǣ�\n");
        scanf("%s", temp);// ��ȡ�û���������վ
        HRailList p = railList->nextRail;// ��ȡ�����б��ͷ�ڵ�
        int flag_nn = 0;
        while (p != NULL)// ���������б�
        {
            HRData hrData = p->data;// ��ȡ��ǰ�ڵ������
            if (!strcmp(hrData.Departure_Station, temp)) {// ������վ�Ƿ�ƥ��
                printf("�г�����:%s ʼ��վ:%s �յ�վ:%s �����:%.0lf���� �������:%s\n",// ���ƥ�䣬���ӡ���г�����Ϣ
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("����ʱ��:%s  �յ�ʱ��:%s ��������:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                printf("��λ��:\n������:%d  һ����:%d ������:%d\n", hrData.SuperlativeSeat,
                    hrData.FirstClassSeat, hrData.SecondClassSeat);
                printf("��ͣվ��:%d\n", hrData.StoppingStationNum);
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // ��ȡÿ����ͣվ����
                    printf("ͣ��վ%d:%s ����ʱ��:%s ����ʱ��:%s ���:%.1lf����\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                printf("\n");
                flag_nn++;
            }
            p = p->nextRail;// �ƶ�����һ���ڵ�
        }
        if (!flag_nn) {// ���û���ҵ�ƥ��ĳ���
            printf("��������Ҫ���ҵĳ�����Ϣ������\n");
            return ERROR;// ���ش���״̬
        }
        break;

    }
    case 3: {// �յ�վ��ѯ
        printf("����Ҫ��ѯ���յ�վ�ǣ�\n");
        scanf("%s", temp);// ��ȡ�û�������յ�վ
        HRailList p = railList->nextRail;// ��ȡ�����б��ͷ�ڵ�
        int flag_mm = 0;
        while (p != NULL)// ���������б�
        {
            HRData hrData = p->data;// ��ȡ��ǰ�ڵ������
            if (!strcmp(hrData.Terminal_Station, temp)) {// ����յ�վ�Ƿ�ƥ��
                printf("�г�����:%s ʼ��վ:%s �յ�վ:%s �����:%.0lf���� �������:%s\n",// ���ƥ�䣬���ӡ���г�����Ϣ
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("����ʱ��:%s  �յ�ʱ��:%s ��������:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                printf("��λ��:\n������:%d  һ����:%d ������:%d\n", hrData.SuperlativeSeat,
                    hrData.FirstClassSeat, hrData.SecondClassSeat);
                printf("��ͣվ��:%d\n", hrData.StoppingStationNum);
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // ��ȡÿ����ͣվ����
                    printf("ͣ��վ%d:%s ����ʱ��:%s ����ʱ��:%s ���:%.1lf����\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                printf("\n");
                flag_mm++;
            }
            p = p->nextRail;// �ƶ�����һ���ڵ�
        }
        if (!flag_mm) {// ���û���ҵ�ƥ��ĳ���
            printf("��������Ҫ���ҵĳ�����Ϣ������\n");
            return ERROR;// ���ش���״̬
        }
        break;

    }
    case 4: {// ����ʱ���ѯ
        printf("����Ҫ��ѯ�ķ���ʱ���ǣ�\n");
        scanf("%s", temp);// ��ȡ�û�����ķ���ʱ��
        HRailList p = railList->nextRail;// ��ȡ�����б��ͷ�ڵ�
        int flag1 = 0;
        while (p != NULL)// ���������б�
        {
            HRData hrData = p->data;// ��ȡ��ǰ�ڵ������
            if (!strcmp(hrData.time_Departure, temp)) {// ��鷢��ʱ���Ƿ�ƥ��
                printf("�г�����:%s ʼ��վ:%s �յ�վ:%s �����:%.0lf���� �������:%s\n",// ���ƥ�䣬���ӡ���г�����Ϣ
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("����ʱ��:%s  �յ�ʱ��:%s ��������:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                printf("��λ��:\n������:%d  һ����:%d ������:%d\n", hrData.SuperlativeSeat,
                    hrData.FirstClassSeat, hrData.SecondClassSeat);
                printf("��ͣվ��:%d\n", hrData.StoppingStationNum);
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // ��ȡÿ����ͣվ����
                    printf("ͣ��վ%d:%s ����ʱ��:%s ����ʱ��:%s ���:%.1lf����\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                printf("\n");
                flag1++;
            }
            p = p->nextRail;// �ƶ�����һ���ڵ�
        }
        if (!flag1) {// ���û���ҵ�ƥ��ĳ���
            printf("��������Ҫ���ҵĳ�����Ϣ������\n");
            return ERROR;// ���ش���״̬
        }
        break;

    }
    case 5: {// ͣ��վ��ѯ
        printf("����Ҫ��ѯ��ͣ��վ�ǣ�\n");
        scanf("%s", temp);// ��ȡ�û������ͣ��վ
        HRailList p = railList->nextRail;// ��ȡ�����б��ͷ�ڵ�
        int flag = 0;//�ж��������
        while (p != NULL)// ���������б�
        {
            HRData hrData = p->data;// ��ȡ��ǰ�ڵ������
            for (int i = 0; i < hrData.SqSS.Num; i++) {

                if (!strcmp(hrData.SqSS.SSList[i].Station_Name, temp)) {// ���ͣ��վ�Ƿ�ƥ��
                    flag++;
                    printf("�г�����:%s ʼ��վ:%s �յ�վ:%s �����:%.0lf���� �������:%s\n",// ���ƥ�䣬���ӡ���г�����Ϣ
                        hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                        hrData.mileage, hrData.Condition);
                    printf("����ʱ��:%s  �յ�ʱ��:%s ��������:", hrData.time_Departure,
                        hrData.time_Arrival);
                    DATE t_Date = stringToDate(hrData.DepartureDate);
                    printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                    printf("��λ��:\n������:%d  һ����:%d ������:%d\n", hrData.SuperlativeSeat,
                        hrData.FirstClassSeat, hrData.SecondClassSeat);
                    printf("��ͣվ��:%d\n", hrData.StoppingStationNum);
                    for (int i = 0; i < hrData.StoppingStationNum; i++) {
                        StoppingStation station = hrData.SqSS.SSList[i];
                        // ��ȡÿ����ͣվ����
                        printf("ͣ��վ%d:%s ����ʱ��:%s ����ʱ��:%s ���:%.1lf����\n",
                            i + 1, station.Station_Name, station.ArrivalT,
                            station.DepartureT, station.mileage_s);

                    }
                    printf("\n");
                    break;
                }
            }
            p = p->nextRail;// �ƶ�����һ���ڵ�
        }
        if (!flag) {// ���û���ҵ�ƥ��ĳ���
            printf("��������Ҫ���ҵĳ�����Ϣ������\n");
            return ERROR;// ���ش���״̬
        }
        break;

    }
    default:
        break;
    }
    return OK;// ����OK״̬
}
Status ModifyTrain(HRailList& railList, const char* file) {
    printf("����Ҫ�޸ĵĳ��Σ�\n");
    char temp[20];// ����һ���ַ��������ڴ洢�û�����ĳ���
    int flag = 0;// ���ڱ���Ƿ��ҵ�ƥ��ĳ���
    scanf("%s", temp);// ��ȡ�û�����ĳ���
    HRailList p = railList->nextRail;// ��ȡ�����б��ͷ�ڵ�
    while (p != NULL) // ���������б�
    {
        HRData hrData = p->data;// ��ȡ��ǰ�ڵ������
        if (!strcmp(hrData.Train_Number, temp)) {// ��鳵���Ƿ�ƥ��
            flag++;// ����ҵ�ƥ��ĳ���
            int ModiInfo;// ����һ�����ͱ������ڴ洢�û�ѡ����޸���Ϣ����
            printf("����Ҫ�޸ĵ���Ϣ��\n");// �ṩ��ͬ���޸���Ϣ����ѡ��
            printf("1.���վ\n");
            printf("2.�յ�վ\n");
            printf("3.����ʱ��\n");
            printf("4.ͣ��վ\n");
            printf("5.�г�״̬\n");
            printf("6.ȫ����Ϣ\n");
            scanf("%d", &ModiInfo);// ��ȡ�û�������޸���Ϣ����
            clearScreen();// ������Ļ
            switch (ModiInfo)
            {// ʹ��switch�������û���ѡ��ִ�в�ͬ���޸Ĳ���
            case 1: {
                printf("����Ҫ�����վ�޸ĳɣ�\n");// �޸����վ
                scanf("%s", temp);
                strcpy(p->data.Departure_Station, temp);
                strcpy(p->data.SqSS.SSList[0].Station_Name,temp);
                break;

            }
            case 2: {
                printf("����Ҫ���յ�վ�޸ĳɣ�\n");// �޸��յ�վ
                scanf("%s", temp);
                strcpy(p->data.Terminal_Station, temp);
                strcpy(p->data.SqSS.SSList[p->data.SqSS.Num-1].Station_Name, temp);
                break;

            }
            case 3: {
                printf("����Ҫ������ʱ���޸ĳɣ�\n");// �޸ķ���ʱ��
                scanf("%s", temp);
                strcpy(p->data.time_Departure, temp);
                break;

            }
            case 4: {
                printf("����Ҫ�޸ĵ�ͣ��վ�ǣ�\n");// �޸�ͣ��վ
                scanf("%s", temp);
                char temp1[20];
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // ��ȡÿ����ͣվ����
                    if (!strcmp(station.Station_Name, temp))
                    {
                        printf("����Ҫ��%s�޸�Ϊ��\n",temp);
                        scanf("%s", temp1);
                        strcpy(p->data.SqSS.SSList[i].Station_Name, temp1);
                        if (!strcmp(hrData.Departure_Station, temp1))
                        {
                            strcpy(hrData.Departure_Station, temp1);
                        }
                        if (!strcmp(hrData.Terminal_Station, temp1))
                        {
                            strcpy(hrData.Terminal_Station, temp1);
                        }
                        break;
                    }
                }
                break;

            }
            case 5: {
                char temp1[20];
                printf("����Ҫ��״̬�޸ĳɣ�\n");// �޸��г�״̬
                scanf("%s", temp1);
                strcpy(p->data.Condition, temp1);
                break;

            }
            case 6: {// �޸�ȫ����Ϣ
                printf("����Ҫ��ʼ��վ�޸ĳɣ�\n");
                scanf("%s", temp);
                strcpy(p->data.Departure_Station, temp);
                printf("����Ҫ���յ�վ�޸ĳɣ�\n");
                scanf("%s", temp);
                strcpy(p->data.Terminal_Station, temp);
                printf("����Ҫ����������޸ĳɣ�\n");
                scanf("%s", temp);
                strcpy(p->data.Condition, temp);
                clearScreen();
                printf("����Ҫ������ʱ���޸ĳɣ�\n");
                scanf("%s", temp);
                strcpy(p->data.time_Departure, temp);
                printf("����Ҫ���յ�ʱ���޸ĳɣ�\n");
                scanf("%s", temp);
                strcpy(p->data.time_Arrival, temp);
                double mile;
                printf("����Ҫ��������޸ĳɣ�\n");
                scanf("%lf", &mile);
                p->data.mileage = mile;
                int tempi;
                clearScreen();
                printf("����Ҫ�������������޸ĳɣ�\n");
                scanf("%d", &tempi);
                p->data.SuperlativeSeat = tempi;
                printf("����Ҫ��һ���������޸ĳɣ�\n");
                scanf("%d", &tempi);
                p->data.FirstClassSeat = tempi;
                printf("����Ҫ�������������޸ĳɣ�\n");
                scanf("%d", &tempi);
                p->data.SecondClassSeat = tempi;
                clearScreen();
                printf("����Ҫ����ͣվ�����޸ĳɣ�\n");
                scanf("%d", &tempi);
                p->data.StoppingStationNum = tempi;
                for (int i = 0; i < tempi; i++)
                {
                    StoppingStation station;
                    // ��ȡÿ����ͣվ����
                    printf("��ͣվ%d�޸���Ϣ��\n",i+1);
                    printf("��ͣվ����:");
                    scanf("%s",
                        station.Station_Name);
                    printf("����ʱ��:");
                    scanf("%s",
                         station.ArrivalT);
                    printf("�뿪ʱ��:");
                    scanf("%s",
                        station.DepartureT);
                    printf("�����:");
                    scanf("%lf",
                         &station.mileage_s);
                    p->data.SqSS.SSList[i] = station;
                }
                break;

            }
            default:
                break;
            }
            WriteFile(railList, file);// ���޸ĺ������д���ļ�
            printf("�޸ĳɹ�!!!\n");
            return OK;// ���ز����ɹ���״̬
        }
        p = p->nextRail;// �ƶ��������е���һ���ڵ�
    }
    if (!flag) {// ���û���ҵ�ƥ��ĳ���
        printf("��������Ҫ�޸ĵĳ�����Ϣ������\n");
        return ERROR;// ���ش���״̬
    }
}
Status ReadTrainFromFile(HRailList& railList, const char* file) {
    FILE* fp = fopen(file, "r");//���ļ����ж���
    if (fp == NULL) {
        perror("Error opening file");//�������
        return ERROR;//���ش���״̬
    }
    if (InitList_Rail(railList) != OK) {//��ʼ���ɹ�
        perror("Error initializing rail list");//�������
        return ERROR;//���ش���״̬
    }
    fscanf(fp, "%d", &railList->HighRail_Num);
    // �ļ�������ɨ���ȡ
    int InsertP = 1;//�����־λ��¼
    HRData hrData;
    while (fscanf(fp, "%s %s %s %lf %s %s %s %d %d %d %d %s",
        hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
        &hrData.mileage, hrData.Condition, hrData.time_Departure,
        hrData.time_Arrival, &hrData.StoppingStationNum, &hrData.SuperlativeSeat,
        &hrData.FirstClassSeat, &hrData.SecondClassSeat, hrData.DepartureDate)==12) {//!feof(fp)
        // ���ļ��ж�ȡ������Ϣ.
        // ��ʼ��˳���
        if (hrData.StoppingStationNum > 0) {
            if (InitList_Sq(hrData.SqSS, hrData.StoppingStationNum) != OK) {//��ʼ���ɹ�
                perror("Error initializing stopping station list");//�������
                return ERROR;//���ش���״̬
            }

            for (int i = 0; i < hrData.StoppingStationNum; i++) {
                StoppingStation station;
                // ��ȡÿ����ͣվ����
                fscanf(fp, "%s %s %s %lf",
                    station.Station_Name, station.ArrivalT,
                    station.DepartureT, &station.mileage_s);
                hrData.SqSS.SSList[i] = station;
            }
        }
        hrData.totalSeats = hrData.SuperlativeSeat + hrData.SecondClassSeat + hrData.FirstClassSeat;//��λ��������
        for (int Stop = 0; Stop < hrData.StoppingStationNum; Stop++) {
            if (InitList_SqSeat(hrData.SqSS.SSList[Stop].seats, hrData.totalSeats) != OK) {//��ʼ���ɹ�
                perror("Error initializing stopping station list");//�������
                return ERROR;//���ش���״̬
            }
            int count = 0;
            for (int i = 0; i < hrData.SuperlativeSeat; i++) {
                hrData.SqSS.SSList[Stop].seats[count].isBooked = 0;
                strcpy(hrData.SqSS.SSList[Stop].seats[count].seatClass, "������");//��λ��ʼ��
                hrData.SqSS.SSList[Stop].seats[count].seatNumber = i + 1;
                count++;
            }
            for (int i = 0; i < hrData.SecondClassSeat; i++) {
                hrData.SqSS.SSList[Stop].seats[count].isBooked = 0;
                strcpy(hrData.SqSS.SSList[Stop].seats[count].seatClass, "������");//��λ��ʼ��
                hrData.SqSS.SSList[Stop].seats[count].seatNumber = i + 1;
                count++;
            }
            for (int i = 0; i < hrData.FirstClassSeat; i++) {
                hrData.SqSS.SSList[Stop].seats[count].isBooked = 0;
                strcpy(hrData.SqSS.SSList[Stop].seats[count].seatClass, "һ����");//��λ��ʼ��
                hrData.SqSS.SSList[Stop].seats[count].seatNumber = i + 1;
                count++;
            }
        }
            
            // �Ѷ�ȡ���ݲ����������
        if (ListInsert_RailInitial(railList, InsertP++, hrData) != OK) {
            perror("Error inserting data into rail list");//�������
            return ERROR;//���ش���״̬
        }


    }
    fclose(fp);//�ر��ļ�
}
Status PrintTrainInfo(HRailList& railList) {
    int n = railList->HighRail_Num;// ��ȡ�г�������
    HRailList p = railList->nextRail;// ָ������б�ĵ�һ���ڵ�
    while (p != NULL)//������������
    {
        HRData hrData = p->data;// ��ȡ��ǰ�ڵ������
        printf( "�г�����:%s ʼ��վ:%s �յ�վ:%s �����:%.0lf���� �������:%s\n",
            hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
            hrData.mileage, hrData.Condition);
        printf("����ʱ��:%s  �յ�ʱ��:%s ��������:", hrData.time_Departure,
            hrData.time_Arrival);
        DATE t_Date = stringToDate(hrData.DepartureDate);//���ַ�������ת��ΪDATE����
        printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
        printf("��λ��:\n������:%d  һ����:%d ������:%d\n", hrData.SuperlativeSeat,
            hrData.FirstClassSeat, hrData.SecondClassSeat);
        printf("��ͣվ��:%d\n", hrData.StoppingStationNum);
        for (int i = 0; i < hrData.StoppingStationNum; i++) {
            StoppingStation station = hrData.SqSS.SSList[i];
            // ��ȡÿ����ͣվ����
            printf("ͣ��վ%d:%s ����ʱ��:%s ����ʱ��:%s ���:%.1lf����\n",
                i+1,station.Station_Name, station.ArrivalT,
                station.DepartureT, station.mileage_s);

        }
        printf("\n");
        p = p->nextRail;//��ȡ��һ���
    }
    return OK;//����OK״̬
}