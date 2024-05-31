#include "booking.h"
#include "HighRail.h"
#include "Date.h"
#include "Menu.h"
Status ReadFromBooking(BList& blist, HRailList& hrList, const char* file) {//从文件中读取信息
    FILE* fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return ERROR;
    }
    if (InitList_Book(blist) != OK) {
        perror("Error initializing rail list");
        return ERROR;
    }
    // 文件可正常扫描读取
    int InsertP = 1;
    BookData bData;//fscanf的方式读取不会错读
    while (fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %d %lf %s",
        bData.Order_Num, bData.Boarding_Date, bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
        bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, &bData.SeatNum, &bData.ticketPrice, bData.BookingDate)==14) {

        
        // 从文件中读取订票信息.
        
        /***********************************************************************************************************************/
        HRailList pr = hrList->nextRail;
          while (pr)//遍历列车单链表
        {
            if (!strcmp(pr->data.DepartureDate, bData.Boarding_Date) && !strcmp(pr->data.Train_Number, bData.TrainNumber))//匹配发车日期和车次号
            {
                int flag1 = 0;//设置标志记录起点站
                int flag2 = 0;//设置标志记录终点站
                int i;
                for (i = 0; i < pr->data.SqSS.Num; i++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[i].Station_Name, bData.StartingStation))
                    {
                        flag1 = 1;//找到起点站
                        break;
                    }

                }
                int j;
                for (j = i + 1; j < pr->data.SqSS.Num; j++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[j].Station_Name, bData.TerminalStation))
                    {
                        flag2 = 1;//找到终点站
                        break;
                    }
                }
                if (flag1 && flag2)//起点站和终点站同时找到
                {
                    // 在起点站和终点站之间查找座位并标记为已预订
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
                        pr->data.SqSS.SSList[k].seats[NUM].isBooked = 1;//初始化占座
                    }
                    break;
                }
            }
            pr = pr->nextRail;
        }
        /***********************************************************************************************************************/
        // 把读取数据插入高铁链表
        if (ListInsert_BookInitial(blist, InsertP++, bData) != OK) {
            perror("Error inserting data into rail list");// 如果插入失败，打印错误信息
            return ERROR;// 返回错误状态
        }


    }
    fclose(fp);// 关闭文件
}
Status WriteBooking(BList& blist, const char* file) {
    FILE* fp1 = fopen(file, "w");
    BList p = blist->nextBooking;
    while (p != NULL)//遍历链表将所有信息从头至尾录入文件
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
    printf("请选择您需要的查找方式:\n");
    printf("1.姓名\n");
    printf("2.证件号\n");
    printf("3.乘车日期\n");
    printf("4.车次\n");
    int s_choice;
    scanf("%d", &s_choice);//输入选择
    clearScreen();//清空屏幕
    switch (s_choice)
    {
    case 1: {
        int flag1 = 0;
        printf("请输入您想要查询的乘客姓名：\n");
        char t_pname[20];
        scanf("%s", t_pname);//通过乘客姓名匹配
        clearScreen();
        BList p = blist->nextBooking;
        while (p)//遍历链表
        {
            if (!strcmp(p->data.P_Name, t_pname))//找到匹配的乘客姓名
            {
                BookData bData = p->data;
                printf("订单号:%s\n出发日期:",
                    bData.Order_Num
                );
                DATE t_date = stringToDate(bData.Boarding_Date);//将字符串转化为DATE结构体以便输出
                printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
                printf("乘坐车次:%s 起点站:%s 终点站:%s\n证件类型:%s 证件号:%s 乘客姓名:%s\n发车时间:%s 到达时间:%s\n%s:%d号 票价:%.2lf元",
                    bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                    bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
                );
                DATE t_date1 = stringToDate(bData.BookingDate);//将字符串转化为DATE结构体以便输出
                printf("\n订票日期:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
                printf("\n");
                flag1++;
            }
            p = p->nextBooking;
        }
        if (!flag1)
        {
            printf("暂无相关信息!!!\n");
        }
        break;
    }
    case 2: {
        int flag1 = 0;
        printf("请输入您想要查询的乘客证件号：\n");
        char t_pid[20];
        scanf("%s", t_pid);//通过乘客ID匹配
        clearScreen();
        BList p = blist->nextBooking;
        while (p)//遍历链表
        {
            if (!strcmp(p->data.id, t_pid))//找到匹配的乘客ID
            {
                BookData bData = p->data;
                printf("订单号:%s\n出发日期:",
                    bData.Order_Num
                );
                DATE t_date = stringToDate(bData.Boarding_Date);//将字符串转化为DATE结构体以便输出
                printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
                printf("乘坐车次:%s 起点站:%s 终点站:%s\n证件类型:%s 证件号:%s 乘客姓名:%s\n发车时间:%s 到达时间:%s\n%s:%d号 票价:%.2lf元",
                    bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                    bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
                );
                DATE t_date1 = stringToDate(bData.BookingDate);//将字符串转化为DATE结构体以便输出
                printf("\n订票日期:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
                printf("\n");
                flag1++;
            }
            p = p->nextBooking;
        }
        if (!flag1)
        {
            printf("暂无相关信息!!!\n");
        }
        break;
    }
    case 3: {
        int flag1 = 0;
        printf("请输入您想要查询的乘车日期：\n");
        char t_date[20];
        scanf("%s", t_date);//通过乘车日期匹配
        clearScreen();
        BList p = blist->nextBooking;
        while (p)//遍历链表
        {
            if (!strcmp(p->data.Boarding_Date, t_date))//找到匹配的乘车日期
            {
                BookData bData = p->data;
                printf("订单号:%s\n出发日期:",
                    bData.Order_Num
                );
                DATE t_date = stringToDate(bData.Boarding_Date);//将字符串转化为DATE结构体以便输出
                printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
                printf("乘坐车次:%s 起点站:%s 终点站:%s\n证件类型:%s 证件号:%s 乘客姓名:%s\n发车时间:%s 到达时间:%s\n%s:%d号 票价:%.2lf元",
                    bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                    bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
                );
                DATE t_date1 = stringToDate(bData.BookingDate);//将字符串转化为DATE结构体以便输出
                printf("\n订票日期:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
                printf("\n");
                flag1++;
            }
            p = p->nextBooking;
        }
        if (!flag1)
        {
            printf("暂无相关信息!!!\n");
        }
        break;
    }
    case 4: {
        int flag1 = 0;
        printf("请输入您想要查询的车次：\n");
        char t_num[20];
        scanf("%s", t_num);//通过车次匹配
        clearScreen();
        BList p = blist->nextBooking;
        while (p)//遍历链表
        {
            if (!strcmp(p->data.TrainNumber, t_num))//找到匹配的车次
            {
                BookData bData = p->data;
                printf("订单号:%s\n出发日期:",
                    bData.Order_Num
                );
                DATE t_date = stringToDate(bData.Boarding_Date);//将字符串转化为DATE结构体以便输出
                printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
                printf("乘坐车次:%s 起点站:%s 终点站:%s\n证件类型:%s 证件号:%s 乘客姓名:%s\n发车时间:%s 到达时间:%s\n%s:%d号 票价:%.2lf元",
                    bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                    bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
                );
                DATE t_date1 = stringToDate(bData.BookingDate);//将字符串转化为DATE结构体以便输出
                printf("\n订票日期:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
                printf("\n");
                flag1++;
            }
            p = p->nextBooking;
        }
        if (!flag1)
        {
            printf("暂无相关信息!!!\n");
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
    printf("请输入您想要查询的列车日期：\n");// 提示用户输入列车日期
    char t_Date1[10];// 定义一个字符数组来存储输入的日期
    scanf("%s", t_Date1);// 读取用户输入的日期
    int flag_ret = 0; // 标志变量，用于表示是否找到匹配的列车
    HRailList p = railList->nextRail;// 获取高铁链表的下一个节点
    clearScreen();// 清屏
    // 遍历高铁链表，寻找与输入日期匹配的列车
    while (p != NULL)
    {
        HRData hrData = p->data;// 获取当前节点的列车数据
        // 检查列车的发车日期是否与输入日期匹配
        if (!strcmp(hrData.DepartureDate, t_Date1)) {
            // 如果匹配，打印列车信息
            printf("列车车次:%s 始发站:%s 终点站:%s 总里程:%.0lf公里 运行情况:%s\n",
                hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                hrData.mileage, hrData.Condition);
            printf("发车时间:%s  终到时间:%s 发车日期:", hrData.time_Departure,
                hrData.time_Arrival);
            DATE t_Date = stringToDate(hrData.DepartureDate);// 将字符串日期转换为DATE类型
            printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);// 打印日期

            // 打印列车的所有停靠站信息
            for (int i = 0; i < hrData.StoppingStationNum; i++) {
                StoppingStation station = hrData.SqSS.SSList[i];
                // 读取每个经停站数据
                printf("停靠站%d:%s 到达时间:%s 发车时间:%s 里程:%.1lf公里\n",
                    i + 1, station.Station_Name, station.ArrivalT,
                    station.DepartureT, station.mileage_s);

            }
            flag_ret = 1;// 设置标志变量表示找到了匹配的列车
            printf("\n");

        }
        p = p->nextRail;// 移动到链表中的下一个节点
    }
    if (!flag_ret)
    {
        // 如果没有找到匹配的列车，打印提示信息并返回错误
        printf("未查询到您想要预订的列车信息!!!\n请重试!!!\n");

        return ERROR;
    }
    printf("1.按车次查询\n");// 提示用户选择查询方式
    printf("2.按起点站，终点站查询\n");
    HRailList pr = railList->nextRail;
    int t_button;
    scanf("%d", &t_button);// 定义一个整数变量来存储用户的选择
    switch (t_button)
    {
    case 1:
    {
        // 提示用户输入列车车次
        printf("请输入列车车次:");
        char t_Tnum[10];
        scanf("%s", t_Tnum);
        // 提示用户输入起始站和终点站
        printf("请输入您想查询的起始站与终点站\n");
        char t_Start[20];
        char t_Ending[20];
        printf("起点站:");
        scanf("%s", t_Start);
        printf("终点站:");
        scanf("%s", t_Ending);
        // 遍历链表以查找匹配的列车
        while (pr)
        {
            // 检查发车日期和车次号是否匹配
            if (!strcmp(pr->data.DepartureDate, t_Date1) && !strcmp(pr->data.Train_Number, t_Tnum))
            {
                int flag1 = 0;// 标志位，检测起始站是否找到
                int flag2 = 0;// 标志位，检测终点站是否找到
                int i;
                // 遍历所有停靠站以找到起始站
                for (i = 0; i < pr->data.SqSS.Num; i++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[i].Station_Name, t_Start))
                    {
                        flag1 = 1;// 找到起始站
                        break;
                    }

                }
                int j;
                // 从找到的起始站之后继续遍历，以找到终点站
                for (j = i + 1; j < pr->data.SqSS.Num; j++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[j].Station_Name, t_Ending))
                    {
                        flag2 = 1;// 找到终点站
                        break;
                    }
                }
                // 如果起始站和终点站都找到
                if (flag1 && flag2)
                {
                    int flag3 = 0;
                    int Mark1 = 0;
                    int Mark2 = 0;
                    double Price = 0;
                    int k;
                    int CountRest = 0;// 用于计算剩余座位的计数器
                    // 遍历所有座位以检查剩余座位数
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        // 检查特定座位类别（商务座、一等座、二等座）的剩余座位
                        for (k = i; k < j; k++)//只管起点站，终点不取
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "商务座"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "商务座"))
                            {
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;// 只要找到一个被预订的座位即可停止当前循环
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                         
                        }

                    }
                    printf("剩商务座%d张！\n",CountRest);
                    CountRest = 0;
                    // 检查特定座位类别（商务座、一等座、二等座）的剩余座位
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        for (k = i; k < j; k++)//只管起点站，终点不取
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "一等座"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "一等座"))
                            {
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;// 只要找到一个被预订的座位即可停止当前循环
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                         
                        }

                    }
                    printf("剩一等座%d张！\n", CountRest);
                    CountRest = 0;
                    // 检查特定座位类别（商务座、一等座、二等座）的剩余座位
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        for (k = i; k < j; k++)//只管起点站，终点不取
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "二等座"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "二等座"))
                            {
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;// 只要找到一个被预订的座位即可停止当前循环
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                        
                        }

                    }
                    printf("剩二等座%d张！\n",CountRest);
                    CountRest = 0;

                    break;
                }
               
            }
            pr = pr->nextRail;// 移动到下一个链表元素
            
        }
        if (!pr)
        {
            printf("无法查询到你所查找的列车信息!!!\n");
        }
        break;
    }
    case 2:
    {
        // 提示用户输入列车起点站和终点站
        printf("请输入列车起点站和终点站\n");
        char t_Start[20];
        char t_Ending[20];
        printf("起点站:\n");
        scanf("%s", t_Start);
        printf("终点站:\n");
        scanf("%s", t_Ending);
        // 遍历链表以查找匹配的列车
        while (pr)
        {
            int flag1 = 0;// 标志位，检测起始站是否找到
            int flag2 = 0;// 标志位，检测终点站是否找到
            // 检查发车日期是否匹配
            if (!strcmp(pr->data.DepartureDate, t_Date1))
            {

                int i;
                // 遍历所有停靠站以找到起始站
                for (i = 0; i < pr->data.SqSS.Num; i++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[i].Station_Name, t_Start))
                    {
                        flag1 = 1;// 找到起始站
                        break;
                    }

                }
                int j;
                // 从找到的起始站之后继续遍历，以找到终点站
                for (j = i + 1; j < pr->data.SqSS.Num; j++)
                {
                    if (!strcmp(pr->data.SqSS.SSList[j].Station_Name, t_Ending))
                    {
                        flag2 = 1;// 找到终点站
                        break;
                    }
                }
                // 如果起始站和终点站都找到
                if (flag1 && flag2)
                {
                    int flag3 = 0;
                    int Mark1 = 0;
                    int Mark2 = 0;
                    double Price = 0;
                    int k;
                    int CountRest = 0;// 用于计算剩余座位的计数器
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        // 检查特定座位类别（商务座、一等座、二等座）的剩余座位
                        for (k = i; k < j; k++)//只管起点站，终点不取
                        {
                            // 遍历起点站到终点站之间的所有站点
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "商务座"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "商务座"))
                            {       // 检查座位是否未被预订
                                if (pr->data.SqSS.SSList[k].seats[CountS].isBooked == 1)
                                {
                                    flag3 = 1;
                                    break;// 只要找到一个被预订的座位即可停止当前循环
                                }
                            }

                        }
                        if (k == j) {
                            Mark1 = k;
                            Mark2 = CountS;
                            CountRest++;
                            
                        }

                    }
                    printf("剩商务座%d张！\n", CountRest);
                    CountRest = 0;// 重复以上逻辑以检查一等座和二等座的剩余座位数，相应地调整座位类别和输出语句
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        for (k = i; k < j; k++)//只管起点站，终点不取
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "一等座"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "一等座"))
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
                    printf("剩一等座%d张！\n",CountRest);
                    CountRest = 0;
                    for (int CountS = 0; CountS < pr->data.totalSeats; CountS++)
                    {
                        int k;
                        for (k = i; k < j; k++)//只管起点站，终点不取
                        {
                            if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "二等座"))
                            {
                                break;
                            }
                            if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "二等座"))
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
                    printf("剩二等座%d张！\n",CountRest);
                    CountRest = 0;
                    break;
                }
             
            }
            pr = pr->nextRail;// 移动到下一个链表元素
            
           
        }
        if (!pr)
        {
            printf("无法查询到你所查找的列车信息!!!\n");
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
    char orderNumber[50]; // 足够大以存储完整的订单号
    int CountB = 0;
    while (tempB)
    {
        if (!strcmp(tempB->data.TrainNumber, BData.TrainNumber))
        {
            CountB++;
        }
        tempB = tempB->nextBooking;
    }
    // 提取列车号中的数字部分
    int trainNum = atoi(BData.TrainNumber + 1); // 假设列车号的格式始终为一个字母后跟数字

    // 格式化列车号和座位号
    sprintf(trainNumStr, "%04d", trainNum);
    sprintf(seatStr, "%03d", ++CountB);
    // 组合字符串
    sprintf(orderNumber, "%s-%s-%s", BData.Boarding_Date, trainNumStr, seatStr);
    strcpy(BData.Order_Num, orderNumber);
    return OK;
}
Status AddBooking(BList & blist, HRailList& railList,const char* fileRail, const char* file)   
{

        clearScreen();// 清理屏幕以开始新的输入操作
        BookData BData_i;
        printf("请输入乘车日期\n");// 提示用户输入乘车日期
        // 从文件中读取高铁信息.
        scanf("%s",
            BData_i.Boarding_Date);
        clearScreen();
        int flag_ret = 0;// 用于标记是否找到了匹配的列车
        HRailList p = railList->nextRail;// 从列车列表的头节点开始遍历
        
        while (p != NULL)// 遍历所有列车，寻找符合指定日期的列车
        {
            HRData hrData = p->data;// 获取当前列车的数据
            if (!strcmp(hrData.DepartureDate, BData_i.Boarding_Date)) {// 如果匹配，打印列车的详细信息
                printf("列车车次:%s 始发站:%s 终点站:%s 总里程:%.0lf公里 运行情况:%s\n",
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("发车时间:%s  终到时间:%s 发车日期:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);// 将字符串形式的日期转换为日期结构
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                // 遍历并打印每个经停站的信息
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // 读取每个经停站数据
                    printf("停靠站%d:%s 到达时间:%s 发车时间:%s 里程:%.1lf公里\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                flag_ret = 1;
                printf("\n");
                
            }
            p = p->nextRail;// 移动到下一个列车节点
        }
        if (!flag_ret)
        {
            printf("未查询到您想要预订的列车信息!!!\n请重试!!!\n");

            return ERROR;
        }
        
        printf("请输入起点站:");
        // 提示用户输入起点站
        scanf("%s",
             BData_i.StartingStation);// 从用户处获取起点站
        
        printf("\n请输入终点站:");
        // 提示用户输入终点站
        scanf("%s",
             BData_i.TerminalStation);// 从用户处获取终点站
        clearScreen();
        HRailList p_temp = railList->nextRail;// 重置指针，开始新的遍历
        while (p_temp)// 遍历列车列表，寻找匹配起点站和终点站的列车
        {
            int flag1 = 0;// 标记起点站是否找到
            double record1 = 0;// 记录起点站里程
            double record2 = 0;// 记录终点站里程
            int flag2 = 0;// 标记终点站是否找到
            if (!strcmp(p_temp->data.DepartureDate, BData_i.Boarding_Date))
            {

                int i;
                for (i = 0; i < p_temp->data.SqSS.Num; i++)// 遍历停靠站，寻找起点站
                {
                    if (!strcmp(p_temp->data.SqSS.SSList[i].Station_Name, BData_i.StartingStation))
                    {
                        flag1 = 1;// 找到起点站
                        record1 = p_temp->data.SqSS.SSList[i].mileage_s;// 记录里程
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
                if (flag1 && flag2)// 如果起点站和终点站都找到
                
                {
                    break;
                }
                
            }
            p_temp = p_temp->nextRail; // 移动到下一个列车节点
        }
        if (!p_temp)// 如果没有找到匹配的列车
        {
            printf("未查询到您想要预订的列车信息!!!\n请重试!!!\n");
            
            return ERROR;// 返回错误状态
        }
        int Alongwith = 0;// 同行人数
        printf("请输入同行人数\n");
        // 从文件中读取高铁信息.
        scanf("%d",&Alongwith);// 从用户处获取同行人数
        clearScreen();
        if (Alongwith > 2 || Alongwith < 0)// 检查同行人数是否符合规定
        {
            if (Alongwith > 2)
                printf("同行人数不得多于两人!!!\n");// 超出同行人数限制
            else
            {
                printf("同行人数有误请重试!!!\n");// 同行人数输入错误
            }
            return ERROR;
        }
        else
        {
            // 为每个乘客（包括预订者和同行人）处理预订信息
            for (int along = 0; along < Alongwith + 1; along++)
            {
                BookData BData;// 创建一个用于存储每个乘客的预订信息的结构体
                // 复制共享的预订信息（起点站、终点站、乘车日期）
                strcpy(BData.StartingStation, BData_i.StartingStation);
                strcpy(BData.TerminalStation, BData_i.TerminalStation);
                strcpy(BData.Boarding_Date, BData_i.Boarding_Date);

                // 提示用户输入每个乘客的个人信息（证件号、姓名、证件类型、坐席等级）
                printf("请输入证件号,姓名,证件类型,坐席等级\n");
                
                scanf("%s %s %s %s",
                    BData.id, BData.P_Name, BData.id_type, BData.SeatClass);
                DATE now = Get_Sys_Time();//订票日期
                char t_bkt[10];
                dateToString(now, t_bkt);
                strcpy(BData.BookingDate, t_bkt);
                DATE BoardTime = stringToDate(BData.Boarding_Date);//乘车日期
                // 计算当前日期与乘车日期之间的天数差
                int differ = daysBetweenDates(now, BoardTime);
                // 检查是否在订票时间范围内（两个月内）
                if (differ > 60)
                {
                    printf("现在还未到订票时间，只能预订两个月内的车票!!!\n");
                    return ERROR;
                }
                HRailList pr = railList->nextRail;
                // 遍历列车列表，寻找匹配的列车并处理座位预订逻辑
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
                            if (!strcmp(BData.SeatClass, "商务座"))
                            {
                                Price = (record2 - record1) * 1.2;//商务座价格
                                BData.ticketPrice = Price;
                                int CountS;
                                for ( CountS = 0; CountS < pr->data.totalSeats; CountS++)
                                {
                                    int k;
                                    for (k = i; k < j; k++)//只管起点站，终点不取
                                    {
                                        if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "商务座"))
                                        {
                                            break;
                                        }
                                        if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "商务座"))
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
                                    printf("商务座票已订完，请重新订票!!!\n");
                                    return ERROR;
                                }
                                for (int Cc = i; Cc < j; Cc++)
                                {
                                    pr->data.SqSS.SSList[Cc].seats[Mark2].isBooked = 1;//开始在每个经停站占座。
                                }
                                BData.SeatNum = pr->data.SqSS.SSList[i].seats[Mark2].seatNumber;
                                GenerateOrderNum(blist, BData);//生成订单号
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
                            if (!strcmp(BData.SeatClass, "一等座"))
                            {
                                Price = (record2 - record1) * 0.6;//一等座价格
                                BData.ticketPrice = Price;
                                int CountS;
                                for (CountS = 0; CountS < pr->data.totalSeats; CountS++)
                                {
                                    int k;
                                    for (k = i; k < j; k++)//只管起点站，终点不取
                                    {
                                        if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "一等座"))
                                        {
                                            break;
                                        }
                                        if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "一等座"))
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
                                    printf("一等座票已订完，请重新订票!!!\n");
                                    return ERROR;
                                }
                                for (int Cc = i; Cc < j; Cc++)
                                {
                                    pr->data.SqSS.SSList[Cc].seats[Mark2].isBooked = 1;//开始在每个经停站占座。
                                }
                                BData.SeatNum = pr->data.SqSS.SSList[i].seats[Mark2].seatNumber;
                                GenerateOrderNum(blist, BData);//生成订单号
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
                            if (!strcmp(BData.SeatClass, "二等座"))
                            {
                                Price = (record2 - record1) * 0.46;//二等座价格
                                BData.ticketPrice = Price;
                                int CountS;
                                for ( CountS= 0; CountS < pr->data.totalSeats; CountS++)
                                {
                                    int k;
                                    for (k = i; k < j; k++)//只管起点站，终点不取
                                    {
                                        if (strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "二等座"))
                                        {
                                            break;
                                        }
                                        if (!strcmp(pr->data.SqSS.SSList[k].seats[CountS].seatClass, "二等座"))
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
                                    printf("二等座票已订完，请重新订票!!!\n");
                                    return ERROR;
                                }
                                for (int Cc = i; Cc < j; Cc++)
                                {
                                    pr->data.SqSS.SSList[Cc].seats[Mark2].isBooked = 1;//开始在每个经停站占座。
                                }
                                BData.SeatNum = pr->data.SqSS.SSList[i].seats[Mark2].seatNumber;
                                GenerateOrderNum(blist, BData);//生成订单号
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
                        printf("输入信息错误,订票失败!!!\n");
                    }
                    pr = pr->nextRail;

                }
            }
        }
        
        clearScreen();// 清理屏幕
        printCentered("订票成功!!");// 打印订票成功
        WriteFile(railList, fileRail);
        WriteBooking(blist, file);
        return OK;

}

Status DeleteBooking(BList& blist, const char* file) {//退票退钱
    BookData BData;// 创建一个结构体存储预订数据
    printf("请输入证件号:");
    // 提示用户输入证件号
    scanf("%s",
        BData.id);// 获取用户输入的证件号
    clearScreen();
    printf("请输入姓名:");
    // 提示用户输入姓名.
    scanf("%s",
        BData.P_Name);
    clearScreen();
    /***********************************************************/
    
    int flag1 = 0;// 用于标记是否找到匹配的预订信息
    BList p1 = blist->nextBooking;// 指向预订列表的头节点
    while (p1)// 遍历预订列表查找匹配的预订
    {
        if (!strcmp(p1->data.P_Name, BData.P_Name)&& !strcmp(p1->data.id, BData.id))
        {
            BookData bData = p1->data;// 获取匹配的预订数据
            // 打印预订信息
            printf("订单号:%s\n出发日期:",
                bData.Order_Num
            );
            DATE t_date = stringToDate(bData.Boarding_Date);// 将字符串形式的日期转换为日期结构
            printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
            printf("乘坐车次:%s 起点站:%s 终点站:%s\n证件类型:%s 证件号:%s 乘客姓名:%s\n发车时间:%s 到达时间:%s\n%s:%d号 票价:%.2lf元",
                bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
                bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
            );
            DATE t_date1 = stringToDate(bData.BookingDate);// 将字符串形式的日期转换为日期结构
            printf("\n订票日期:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
            printf("\n");
            flag1++;
        }
        p1 = p1->nextBooking;
    }
    if (!flag1)
    {
        printf("暂无相关信息!!!\n");
        return ERROR;
    }
    /***********************************************************/
    printf("请输入您想要退订的车票订单号:\n");//提示输入退订车票订单号
    char tmp_order[25];
    scanf("%s", tmp_order);
    clearScreen();
    BList p = blist;
    int flag_t = 0;
    while (p->nextBooking)//遍历单链表
    {

        BookData bData = p->nextBooking->data;
        if (!strcmp(bData.Order_Num, tmp_order))
        {
            BList p2 = p->nextBooking;
            p->nextBooking = p2->nextBooking;
            /*******************分时间段退钱*********************/
            DATE now = Get_Sys_Time();
            DATE BoadrTime = stringToDate(bData.Boarding_Date);
            int B_m;
            int N_m;
            sscanf(bData.DepartureTime, "%2d%*c%2d", &BoadrTime.hour, &BoadrTime.min);
            int M_sub = timeToMin(BoadrTime) - timeToMin(now);
            if (BoadrTime.year > now.year || (BoadrTime.year == now.year && BoadrTime.month > now.month) || (BoadrTime.year == now.year && BoadrTime.month == now.month && BoadrTime.day > now.day)
                || (BoadrTime.year == now.year && BoadrTime.month == now.month && BoadrTime.day == now.day && M_sub > 120))//判断是否是在发车两个小时前退票
            {
                printf("退票成功!!!\n已退款：%.2lf 元", bData.ticketPrice);//全款退票
                printf("\n");
            }
            else
            {
                printf("退票成功!!!\n已退款：%.2lf 元", bData.ticketPrice*0.95);//收取%5退票费
                printf("\n");
            }
            free(p2);//释放内存
            flag_t = 1;
            break;
        }
                p = p->nextBooking;//寻找下一节点
    }
    if (!flag_t)
    {
        printf("查找不到您的订单信息，无法退票!!!\n");//输出错误提示
    }
    WriteBooking(blist, file);//重新写入文件
    return OK;
}


Status PrintBookingInfo(BList& blist) {//输出所有车票信息

    BList p = blist->nextBooking;
    while (p != NULL)//遍历单链表
    {
        BookData bData = p->data;
        printf("订单号:%s\n出发日期:",
            bData.Order_Num
        );
        DATE t_date = stringToDate(bData.Boarding_Date);//将字符串转化为Date结构体
        printf("%4d/%02d/%02d ", t_date.year, t_date.month, t_date.day);
        printf("乘坐车次:%s 起点站:%s 终点站:%s\n证件类型:%s 证件号:%s 乘客姓名:%s\n发车时间:%s 到达时间:%s\n%s:%d号 票价:%.2lf元",
            bData.TrainNumber, bData.StartingStation, bData.TerminalStation, bData.id_type,
            bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.SeatClass, bData.SeatNum, bData.ticketPrice
        );
        DATE t_date1 = stringToDate(bData.BookingDate);//将字符串转化为Date结构体
        printf("\n订票日期:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
        printf("\n");
        p = p->nextBooking;//找到下一结点
    }
    return OK;
}


Status PrintTicketInfo(BList& blist) {

    FILE* file = fopen("ticket.txt", "w");  // 打开文件用于写入
    if (file == NULL) {
        perror("Error opening file");
        return ERROR;  // 返回 ERROR 状态
    }
    printf("请输入您的证件号：\n");//提示输入
    char t_id[25];
    scanf("%s", t_id);
    printf("请输入您的姓名：\n");//提示输入
    char t_name[25];
    scanf("%s", t_name);
    clearScreen();
    BList p = blist->nextBooking;//找到首元结点
    int flag = 0;//设置标志位
    while (p != NULL)//遍历单链表
    {
        
        BookData bData = p->data;
        if (!strcmp(t_id, bData.id)&& !strcmp(t_name, bData.P_Name))//进行姓名和ID匹配
        {

            printf("出发日期:"
            );
            DATE t_date = stringToDate(bData.Boarding_Date);//将字符串转化为Date结构体
            printf("%4d/%02d/%02d\n", t_date.year, t_date.month, t_date.day);
            printf("起点站:%s 终点站:%s\n证件类型:%s 证件号:%s 乘客姓名:%s\n发车时间:%s 到达时间:%s\n乘坐车次:%s %s:%d号 票价:%.2lf元",
                  bData.StartingStation, bData.TerminalStation, bData.id_type,
                bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.TrainNumber, bData.SeatClass, bData.SeatNum, bData.ticketPrice
            );
            DATE t_date1 = stringToDate(bData.BookingDate);//将字符串转化为Date结构体
            printf("\n订票日期:%4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
            printf("订单号:%s\n",
                bData.Order_Num
            );
            printf("\n");
            
            flag++;//标志位更新
        }
        
        p = p->nextBooking;//找到下一节点
    }
    if (!flag)
    {
        printf("查询不到您的订单，请订票!!!\n");//输出错误提示
        fprintf(file, "查询不到您的订单，请订票!!!\n");//打印错误提示到文件
        fclose(file);
        return ERROR;//返回错误状态
    }
    printf("请输入您想要打印的车票订单号:\n");//提示输入
    char t_order[25];
    int flag_order = 0;//设置标志位
    scanf("%s", t_order);//输入订单号以供打印
    clearScreen();//清屏
    p = blist->nextBooking;
    while (p != NULL)//遍历单链表
    {

        BookData bData = p->data;
        if (!strcmp(t_order, bData.Order_Num) )//匹配订单号
        {

           
            DATE t_date = stringToDate(bData.Boarding_Date);//将字符串转化为Date结构体
           
            DATE t_date1 = stringToDate(bData.BookingDate);//将字符串转化为Date结构体
           
            // 写入文件而不是打印到控制台
            fprintf(file, "出发日期: %4d/%02d/%02d\n", t_date.year, t_date.month, t_date.day);
            fprintf(file, "起点站: %s 终点站: %s\n证件类型: %s 证件号: %s 乘客姓名: %s\n发车时间: %s 到达时间: %s\n乘坐车次: %s %s: %d号 票价: %.2lf元\n",
                bData.StartingStation, bData.TerminalStation, bData.id_type,
                bData.id, bData.P_Name, bData.DepartureTime, bData.ArrivalTime, bData.TrainNumber, bData.SeatClass, bData.SeatNum, bData.ticketPrice);
            fprintf(file, "订票日期: %4d/%02d/%02d \n", t_date1.year, t_date1.month, t_date1.day);
            fprintf(file, "订单号: %s\n\n", bData.Order_Num);
            printf("车票打印成功,请在文件夹中查看!!!\n\n", flag + 1);
            flag_order++;//标志位更新
            break;
        }

        p = p->nextBooking;
    }
    if (!flag_order)
    {
        printf("查询不到您的订单，请确认订单号!!!\n");//输出错误信息
        fprintf(file, "查询不到您的订单，请确认订单号!!!\n");//打印错误信息
    }
    fclose(file);  // 关闭文件
    return OK;
}