#include"Menu.h"
#include"HighRail.h"
#include"Passenger.h"
#include"booking.h"
#include"Date.h"
#define CONSOLE_WIDTH 80  // �������̨���Ϊ80���ַ�

void printCentered(const char* text) {//���д�ӡ
    int length = strlen(text);
    int padding = (CONSOLE_WIDTH - length) / 2;
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}


void clearScreen() {
    // Windows�е���������
    system("cls");
}
void submenu1() {//���ι���ϵͳ
    int choice;
    HRailList railList;
    PassList PList;
    BList blist;
    do {
        clearScreen();
        ReadTrainFromFile(railList, "train.txt");
        printCentered("���ι���ϵͳ\n");
        printCentered("1. ����һ���г�\n");
        printCentered("2. ͣ��һ���г�\n");
        printCentered("3. ����������Ϣ��ѯ\n");
        printCentered("4. �޸��г���Ϣ\n");
        printCentered("5. ������и�����Ϣ\n");
        printCentered("6. �����ϼ��˵�\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            clearScreen();
            AddTrain(railList,"train.txt");//����һ���г�
            printf("�ɹ�����һ���г�!!!\n");
            break;
        case 2:
            clearScreen();
            StopTrain(railList, "train.txt");//ͣ��һ���г�
            break;
        case 3:
            clearScreen();
            SearchTrain(railList);//����������Ϣ��ѯ
            break;
        case 4:
            clearScreen();
            ModifyTrain(railList, "train.txt");//�޸��г���Ϣ
            break;
        case 5:
            //������и�����Ϣ
            clearScreen();
            PrintTrainInfo(railList);//������и�����Ϣ
            break;
        case 6:
            // �������˵�
            break;
        default:
            printf("��Чѡ������������!!!\n");
            break;
        }
        if (choice != 6) {

            printf("\n�����������...");
            while (getchar() != '\n'); // ���������
            getchar(); // �ȴ��û���Enter
        }
    } while (choice != 6);
}

void submenu2() {// �˿���Ϣ����ϵͳ
    int choice;
    HRailList railList;
    PassList PList;
    BList blist;
    do {
        clearScreen();
        printCentered("�˿���Ϣ����ϵͳ\n");
        printCentered("1. ����һ���˿�\n");
        printCentered("2. ɾ��һ���˿�\n");
        printCentered("3. �˿���Ϣ��ѯ\n");//�޸ĳ�����֮�����Ϣ
        printCentered("4. �˿���Ϣ�޸�\n");
        printCentered("5. ������г˿���Ϣ\n");
        printCentered("6. �����ϼ��˵�\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt");//���ļ��ж�ȡ�˿��б���Ϣ
            AddPassenger(PList, "Passenger.txt");//����һ���˿�
            printf("�ɹ�����һ���˿�!!!\n");
            break;
        case 2:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt");//���ļ��ж�ȡ�˿��б���Ϣ
            DeletePassenger(PList, "Passenger.txt");//ɾ��һ���˿�
            break;
        case 3:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt"); //���ļ��ж�ȡ�˿��б���Ϣ
            SearchPassenger(PList);//�˿���Ϣ��ѯ
            break;
        case 4:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt");//���ļ��ж�ȡ�˿��б���Ϣ
            ModifyPassenger(PList, "Passenger.txt");//�˿���Ϣ�޸�
            break;
        case 5:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt"); //���ļ��ж�ȡ�˿��б���Ϣ
            PrintPassengerInfo(PList);//������г˿���Ϣ
            break;
        case 6:
            // �������˵�
            break;
        default:
            printf("��Чѡ������������!!!\n");
            break;
        }
        if (choice != 6) {

            printf("\n�����������...");
            while (getchar() != '\n'); // ���������
            getchar(); // �ȴ��û���Enter
        }
    } while (choice != 6);
}
static void submenu3() {//��Ʊ��Ϣ����ϵͳ
    int choice;
    HRailList railList;
    PassList PList;
    BList blist;
    do {
        clearScreen();
        printf("��Ʊ��Ϣ����ϵͳ\n");
        printf("1. ��Ʊ\n");
        printf("2. ��Ʊ\n");
        printf("3. ��Ʊ��Ϣ��ѯ\n");//�޸ĳ�����֮�����Ϣ
        printf("4. ��Ʊ��ѯ\n");
        printf("5. ������г�Ʊ��Ϣ\n");
        printf("6. ��Ʊ��ӡ\n");
        printf("7. �����ϼ��˵�\n");
        printf("����������ѡ��: ");
        scanf("%d", &choice);
        
        switch (choice) {
        case 1:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//�ļ���ȡ�г���Ϣ
            ReadFromBooking(blist, railList,"booking.txt");//�ļ���ȡ��Ʊ��Ϣ
            AddBooking(blist, railList, "train.txt", "booking.txt");//��Ʊ
           // printf("�ɹ���Ʊ!!!\n");
            break;
        case 2:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//�ļ���ȡ�г���Ϣ
            ReadFromBooking(blist, railList, "booking.txt");//�ļ���ȡ��Ʊ��Ϣ
            DeleteBooking(blist,"booking.txt");//��Ʊ
            break;
        case 3:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//�ļ���ȡ�г���Ϣ
            ReadFromBooking(blist, railList, "booking.txt");//�ļ���ȡ��Ʊ��Ϣ
            SearchBookingTicket(blist);//��Ʊ��Ϣ��ѯ
            break;
        case 4:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//�ļ���ȡ�г���Ϣ
            ReadFromBooking(blist, railList, "booking.txt");//�ļ���ȡ��Ʊ��Ϣ
            SearchLeftTicket(railList);//��Ʊ��ѯ
            break;
        case 5:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//�ļ���ȡ�г���Ϣ
            ReadFromBooking(blist, railList, "booking.txt");//�ļ���ȡ��Ʊ��Ϣ
            PrintBookingInfo(blist);//������г�Ʊ��Ϣ
            break;
        case 6:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//�ļ���ȡ�г���Ϣ
            ReadFromBooking(blist, railList, "booking.txt");//�ļ���ȡ��Ʊ��Ϣ
            PrintTicketInfo(blist);//��Ʊ��ӡ
            break;
        case 7:
            // �������˵�
            break;
        default:
            printf("��Чѡ������������!!!\n");
            break;
        }
        if (choice != 7) {

            printf("\n�����������...");
            while (getchar() != '\n'); // ���������
            getchar(); // �ȴ��û���Enter
        }
    } while (choice != 7);
}
void mainMenu() {
    int choice;
    do {
        clearScreen();
        printCentered("������Ʊϵͳ\n");
        printCentered("1. ���ι���ϵͳ\n");//���ι���ϵͳ
        printCentered("2. �˿���Ϣ����ϵͳ\n");//�˿���Ϣ����ϵͳ
        printCentered("3. ��Ʊ��Ϣ����ϵͳ\n");//��Ʊ��Ϣ����ϵͳ
        printCentered("4. �˳�ϵͳ\n");//Exit
        printf("��������ѡ��:");
       
       
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // ���복�ι���ϵͳ
            submenu1();
            break;
        case 2:
            // ����˿���Ϣ����ϵͳ
            submenu2();
            break;
        case 3:
            // ���붩Ʊ��Ϣ����ϵͳ
            submenu3();
            break;
        case 4:
            clearScreen();
            printCentered("�˳�ϵͳ��...\n");
            break;
        default:
            clearScreen();
            printCentered("��Чѡ��������!!!\n");
            
            
            break;
        }
        if (choice != 4) {

            printf("\n�����������...");
            while (getchar() != '\n'); // ���������
            getchar(); // �ȴ��û���Enter
        }
    } while (choice != 4);
}