#include"Menu.h"
#include"HighRail.h"
#include"Passenger.h"
#include"booking.h"
#include"Date.h"
#define CONSOLE_WIDTH 80  // 假设控制台宽度为80个字符

void printCentered(const char* text) {//居中打印
    int length = strlen(text);
    int padding = (CONSOLE_WIDTH - length) / 2;
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}


void clearScreen() {
    // Windows中的清屏命令
    system("cls");
}
void submenu1() {//车次管理系统
    int choice;
    HRailList railList;
    PassList PList;
    BList blist;
    do {
        clearScreen();
        ReadTrainFromFile(railList, "train.txt");
        printCentered("车次管理系统\n");
        printCentered("1. 增开一趟列车\n");
        printCentered("2. 停开一趟列车\n");
        printCentered("3. 高铁车次信息查询\n");
        printCentered("4. 修改列车信息\n");
        printCentered("5. 输出所有高铁信息\n");
        printCentered("6. 返回上级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            clearScreen();
            AddTrain(railList,"train.txt");//增开一趟列车
            printf("成功增开一趟列车!!!\n");
            break;
        case 2:
            clearScreen();
            StopTrain(railList, "train.txt");//停开一趟列车
            break;
        case 3:
            clearScreen();
            SearchTrain(railList);//高铁车次信息查询
            break;
        case 4:
            clearScreen();
            ModifyTrain(railList, "train.txt");//修改列车信息
            break;
        case 5:
            //输出所有高铁信息
            clearScreen();
            PrintTrainInfo(railList);//输出所有高铁信息
            break;
        case 6:
            // 返回主菜单
            break;
        default:
            printf("无效选择，请重新输入!!!\n");
            break;
        }
        if (choice != 6) {

            printf("\n按任意键继续...");
            while (getchar() != '\n'); // 清除缓冲区
            getchar(); // 等待用户按Enter
        }
    } while (choice != 6);
}

void submenu2() {// 乘客信息管理系统
    int choice;
    HRailList railList;
    PassList PList;
    BList blist;
    do {
        clearScreen();
        printCentered("乘客信息管理系统\n");
        printCentered("1. 增加一个乘客\n");
        printCentered("2. 删除一个乘客\n");
        printCentered("3. 乘客信息查询\n");//修改除车次之外的信息
        printCentered("4. 乘客信息修改\n");
        printCentered("5. 输出所有乘客信息\n");
        printCentered("6. 返回上级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt");//从文件中读取乘客列表信息
            AddPassenger(PList, "Passenger.txt");//增加一个乘客
            printf("成功增加一名乘客!!!\n");
            break;
        case 2:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt");//从文件中读取乘客列表信息
            DeletePassenger(PList, "Passenger.txt");//删除一个乘客
            break;
        case 3:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt"); //从文件中读取乘客列表信息
            SearchPassenger(PList);//乘客信息查询
            break;
        case 4:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt");//从文件中读取乘客列表信息
            ModifyPassenger(PList, "Passenger.txt");//乘客信息修改
            break;
        case 5:
            clearScreen();
            ReadPassengersFromFile(PList, "Passenger.txt"); //从文件中读取乘客列表信息
            PrintPassengerInfo(PList);//输出所有乘客信息
            break;
        case 6:
            // 返回主菜单
            break;
        default:
            printf("无效选择，请重新输入!!!\n");
            break;
        }
        if (choice != 6) {

            printf("\n按任意键继续...");
            while (getchar() != '\n'); // 清除缓冲区
            getchar(); // 等待用户按Enter
        }
    } while (choice != 6);
}
static void submenu3() {//订票信息管理系统
    int choice;
    HRailList railList;
    PassList PList;
    BList blist;
    do {
        clearScreen();
        printf("订票信息管理系统\n");
        printf("1. 订票\n");
        printf("2. 退票\n");
        printf("3. 车票信息查询\n");//修改除车次之外的信息
        printf("4. 余票查询\n");
        printf("5. 输出所有车票信息\n");
        printf("6. 车票打印\n");
        printf("7. 返回上级菜单\n");
        printf("请输入您的选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
        case 1:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//文件读取列车信息
            ReadFromBooking(blist, railList,"booking.txt");//文件读取订票信息
            AddBooking(blist, railList, "train.txt", "booking.txt");//订票
           // printf("成功订票!!!\n");
            break;
        case 2:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//文件读取列车信息
            ReadFromBooking(blist, railList, "booking.txt");//文件读取订票信息
            DeleteBooking(blist,"booking.txt");//退票
            break;
        case 3:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//文件读取列车信息
            ReadFromBooking(blist, railList, "booking.txt");//文件读取订票信息
            SearchBookingTicket(blist);//车票信息查询
            break;
        case 4:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//文件读取列车信息
            ReadFromBooking(blist, railList, "booking.txt");//文件读取订票信息
            SearchLeftTicket(railList);//余票查询
            break;
        case 5:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//文件读取列车信息
            ReadFromBooking(blist, railList, "booking.txt");//文件读取订票信息
            PrintBookingInfo(blist);//输出所有车票信息
            break;
        case 6:
            clearScreen();
            ReadTrainFromFile(railList, "train.txt");//文件读取列车信息
            ReadFromBooking(blist, railList, "booking.txt");//文件读取订票信息
            PrintTicketInfo(blist);//车票打印
            break;
        case 7:
            // 返回主菜单
            break;
        default:
            printf("无效选择，请重新输入!!!\n");
            break;
        }
        if (choice != 7) {

            printf("\n按任意键继续...");
            while (getchar() != '\n'); // 清除缓冲区
            getchar(); // 等待用户按Enter
        }
    } while (choice != 7);
}
void mainMenu() {
    int choice;
    do {
        clearScreen();
        printCentered("高铁订票系统\n");
        printCentered("1. 车次管理系统\n");//车次管理系统
        printCentered("2. 乘客信息管理系统\n");//乘客信息管理系统
        printCentered("3. 订票信息管理系统\n");//订票信息管理系统
        printCentered("4. 退出系统\n");//Exit
        printf("输入您的选择:");
       
       
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // 进入车次管理系统
            submenu1();
            break;
        case 2:
            // 进入乘客信息管理系统
            submenu2();
            break;
        case 3:
            // 进入订票信息管理系统
            submenu3();
            break;
        case 4:
            clearScreen();
            printCentered("退出系统中...\n");
            break;
        default:
            clearScreen();
            printCentered("无效选择，请重试!!!\n");
            
            
            break;
        }
        if (choice != 4) {

            printf("\n按任意键继续...");
            while (getchar() != '\n'); // 清除缓冲区
            getchar(); // 等待用户按Enter
        }
    } while (choice != 4);
}