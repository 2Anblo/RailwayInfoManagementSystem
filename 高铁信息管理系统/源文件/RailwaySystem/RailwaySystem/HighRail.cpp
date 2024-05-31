#include "HighRail.h"
#include"Menu.h"
#include"Date.h"
Status WriteFile(HRailList& railList, const char* file) {
    // 打开文件用于写入，如果文件不存在则创建
    FILE *fp1 = fopen(file, "w");
    // 获取列车的数量
    int n = railList->HighRail_Num;
    // 指向高铁列表的第一个节点
    HRailList p = railList->nextRail;
    fprintf(fp1, "%d\n", n);// 将列车数量写入文件
    while (p != NULL) // 遍历整个高铁列表
    {
        HRData hrData = p->data;// 获取当前节点的数据
        fprintf(fp1, "%s %s %s %.0lf %s %s %s %d %d %d %d %s",
            hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
            hrData.mileage, hrData.Condition, hrData.time_Departure,
            hrData.time_Arrival, hrData.StoppingStationNum, hrData.SuperlativeSeat,
            hrData.FirstClassSeat, hrData.SecondClassSeat,hrData.DepartureDate);// 将列车的基本信息写入文件
        for (int i = 0; i < hrData.StoppingStationNum; i++) { // 对于列车的每个停靠站，写入其详细信息
            StoppingStation station= hrData.SqSS.SSList[i];
            // 读取每个经停站数据
            fprintf(fp1," %s %s %s %.1lf",
                station.Station_Name, station.ArrivalT,
                station.DepartureT, station.mileage_s);// 将停靠站的信息写入文件
      
        }
        fprintf(fp1, "\n");// 换行，准备写入下一个列车的信息
        p = p->nextRail;// 移动到链表中的下一个节点
    }
    fclose(fp1);
    return OK; // 返回操作成功的状态
}
Status AddTrain(HRailList& railList, const char* file) {
    HRData hrData;
    printf("请输入车次，始发站，终到站，总里程，运行状况，发车时间，到站时间\n");//输出提示
   
    scanf("%s %s %s %lf %s %s %s",
        hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
        &hrData.mileage, hrData.Condition, hrData.time_Departure,
        hrData.time_Arrival);//将内容读入存储结构
    printf("经停站数，商务座数量，一等座数量，二等座数量,发车日期\n");//输出提示
   
    scanf("%d %d %d %d %s",
        &hrData.StoppingStationNum, &hrData.SuperlativeSeat,
        &hrData.FirstClassSeat, &hrData.SecondClassSeat, hrData.DepartureDate);//将内容读入存储结构
    clearScreen();//清屏

    if (hrData.StoppingStationNum > 0) {
        if (InitList_Sq(hrData.SqSS, hrData.StoppingStationNum) != OK) {
            perror("Error initializing stopping station list");//输出错误信息
            return ERROR;//返回错误状态
        }

        for (int i = 0; i < hrData.StoppingStationNum; i++) {
            StoppingStation station;

            printf("请输入经停站名，到达时间，离开时间，里程\n");//输出提示
            scanf("%s %s %s %lf",
                station.Station_Name, station.ArrivalT,
                station.DepartureT, &station.mileage_s);//读取站点信息
            hrData.SqSS.SSList[i] = station;//插入站点
        }
    }
    // 把读取数据插入高铁链表
    if (ListInsert_Rail(railList, railList->HighRail_Num+1, hrData) != OK) {
        perror("Error inserting data into rail list");//输出错误信息
        return ERROR;//返回错误状态
    }
    WriteFile(railList, file);//写入文件
    return OK;//返回OK状态
}
Status StopTrain(HRailList& railList, const char* file) {
    char temp[20];
    printf("想要停运的车次：\n");//提示输入
    scanf("%s", temp);
    HRailList p = railList->nextRail;//获取首元结点
    while (p != NULL)//遍历单链表
    {
        HRData hrData = p->data;
        if (!strcmp(hrData.Train_Number, temp)) {//车次号匹配
            strcpy(p->data.Condition, "停运");//状态修改
            
            printf("成功停运一趟列车!!!\n");//停运成功
            break;
        }
        p = p->nextRail;//寻找下一节点
    }
    if (!p) {
        printf("查询不到您想要停运的车次！！！\n");//输出错误信息
        return ERROR;//返回错误状态
    }
    WriteFile(railList, file);//写入文件
    return OK;//返回OK状态
}
Status SearchTrain(HRailList& railList) {
    char temp[20];// 创建一个字符数组用于存储用户输入
    int SearchWay;// 创建一个整型变量用于存储用户选择的查询方式
    printf("查询方式：\n");// 打印查询方式的提示信息
    // 提供不同的查询方式选项
    printf("1.车次\n");
    printf("2.起点站\n");
    printf("3.终到站\n");
    printf("4.发车时间\n");
    printf("5.停靠站\n");
    scanf("%d", &SearchWay);// 获取用户输入的查询方式
    clearScreen();// 清理屏幕
    switch (SearchWay)// 使用switch语句根据用户的选择执行不同的查询操作
    {
    case 1: {// 车次查询
        printf("您想要查询的车次是：\n");
        scanf("%s", temp);// 获取用户输入的车次
        HRailList p = railList->nextRail; // 获取高铁列表的头节点
        while (p != NULL)// 遍历高铁列表
        {
            HRData hrData = p->data;// 获取当前节点的数据
            if (!strcmp(hrData.Train_Number, temp)) {// 检查车次是否匹配
                printf("列车车次:%s 始发站:%s 终点站:%s 总里程:%.0lf公里 运行情况:%s\n",// 如果匹配，则打印该列车的信息
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("发车时间:%s  终到时间:%s 发车日期:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                printf("座位数:\n商务座:%d  一等座:%d 二等座:%d\n", hrData.SuperlativeSeat,
                    hrData.FirstClassSeat, hrData.SecondClassSeat);
                printf("经停站数:%d\n", hrData.StoppingStationNum);
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // 读取每个经停站数据
                    printf("停靠站%d:%s 到达时间:%s 发车时间:%s 里程:%.1lf公里\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                printf("\n");
                break;
            }
            p = p->nextRail; // 移动到下一个节点
        }
        if (!p) {// 如果没有找到匹配的车次
            printf("暂无您想要查找的车次信息！！！\n");
            return ERROR;// 返回错误状态
        }
        break;

    }
    case 2: {// 起点站查询
        printf("您想要查询的起点站是：\n");
        scanf("%s", temp);// 获取用户输入的起点站
        HRailList p = railList->nextRail;// 获取高铁列表的头节点
        int flag_nn = 0;
        while (p != NULL)// 遍历高铁列表
        {
            HRData hrData = p->data;// 获取当前节点的数据
            if (!strcmp(hrData.Departure_Station, temp)) {// 检查起点站是否匹配
                printf("列车车次:%s 始发站:%s 终点站:%s 总里程:%.0lf公里 运行情况:%s\n",// 如果匹配，则打印该列车的信息
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("发车时间:%s  终到时间:%s 发车日期:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                printf("座位数:\n商务座:%d  一等座:%d 二等座:%d\n", hrData.SuperlativeSeat,
                    hrData.FirstClassSeat, hrData.SecondClassSeat);
                printf("经停站数:%d\n", hrData.StoppingStationNum);
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // 读取每个经停站数据
                    printf("停靠站%d:%s 到达时间:%s 发车时间:%s 里程:%.1lf公里\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                printf("\n");
                flag_nn++;
            }
            p = p->nextRail;// 移动到下一个节点
        }
        if (!flag_nn) {// 如果没有找到匹配的车次
            printf("暂无您想要查找的车次信息！！！\n");
            return ERROR;// 返回错误状态
        }
        break;

    }
    case 3: {// 终到站查询
        printf("您想要查询的终到站是：\n");
        scanf("%s", temp);// 获取用户输入的终到站
        HRailList p = railList->nextRail;// 获取高铁列表的头节点
        int flag_mm = 0;
        while (p != NULL)// 遍历高铁列表
        {
            HRData hrData = p->data;// 获取当前节点的数据
            if (!strcmp(hrData.Terminal_Station, temp)) {// 检查终到站是否匹配
                printf("列车车次:%s 始发站:%s 终点站:%s 总里程:%.0lf公里 运行情况:%s\n",// 如果匹配，则打印该列车的信息
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("发车时间:%s  终到时间:%s 发车日期:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                printf("座位数:\n商务座:%d  一等座:%d 二等座:%d\n", hrData.SuperlativeSeat,
                    hrData.FirstClassSeat, hrData.SecondClassSeat);
                printf("经停站数:%d\n", hrData.StoppingStationNum);
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // 读取每个经停站数据
                    printf("停靠站%d:%s 到达时间:%s 发车时间:%s 里程:%.1lf公里\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                printf("\n");
                flag_mm++;
            }
            p = p->nextRail;// 移动到下一个节点
        }
        if (!flag_mm) {// 如果没有找到匹配的车次
            printf("暂无您想要查找的车次信息！！！\n");
            return ERROR;// 返回错误状态
        }
        break;

    }
    case 4: {// 发车时间查询
        printf("您想要查询的发车时间是：\n");
        scanf("%s", temp);// 获取用户输入的发车时间
        HRailList p = railList->nextRail;// 获取高铁列表的头节点
        int flag1 = 0;
        while (p != NULL)// 遍历高铁列表
        {
            HRData hrData = p->data;// 获取当前节点的数据
            if (!strcmp(hrData.time_Departure, temp)) {// 检查发车时间是否匹配
                printf("列车车次:%s 始发站:%s 终点站:%s 总里程:%.0lf公里 运行情况:%s\n",// 如果匹配，则打印该列车的信息
                    hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                    hrData.mileage, hrData.Condition);
                printf("发车时间:%s  终到时间:%s 发车日期:", hrData.time_Departure,
                    hrData.time_Arrival);
                DATE t_Date = stringToDate(hrData.DepartureDate);
                printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                printf("座位数:\n商务座:%d  一等座:%d 二等座:%d\n", hrData.SuperlativeSeat,
                    hrData.FirstClassSeat, hrData.SecondClassSeat);
                printf("经停站数:%d\n", hrData.StoppingStationNum);
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // 读取每个经停站数据
                    printf("停靠站%d:%s 到达时间:%s 发车时间:%s 里程:%.1lf公里\n",
                        i + 1, station.Station_Name, station.ArrivalT,
                        station.DepartureT, station.mileage_s);

                }
                printf("\n");
                flag1++;
            }
            p = p->nextRail;// 移动到下一个节点
        }
        if (!flag1) {// 如果没有找到匹配的车次
            printf("暂无您想要查找的车次信息！！！\n");
            return ERROR;// 返回错误状态
        }
        break;

    }
    case 5: {// 停靠站查询
        printf("您想要查询的停靠站是：\n");
        scanf("%s", temp);// 获取用户输入的停靠站
        HRailList p = railList->nextRail;// 获取高铁列表的头节点
        int flag = 0;//判断有无输出
        while (p != NULL)// 遍历高铁列表
        {
            HRData hrData = p->data;// 获取当前节点的数据
            for (int i = 0; i < hrData.SqSS.Num; i++) {

                if (!strcmp(hrData.SqSS.SSList[i].Station_Name, temp)) {// 检查停靠站是否匹配
                    flag++;
                    printf("列车车次:%s 始发站:%s 终点站:%s 总里程:%.0lf公里 运行情况:%s\n",// 如果匹配，则打印该列车的信息
                        hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
                        hrData.mileage, hrData.Condition);
                    printf("发车时间:%s  终到时间:%s 发车日期:", hrData.time_Departure,
                        hrData.time_Arrival);
                    DATE t_Date = stringToDate(hrData.DepartureDate);
                    printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
                    printf("座位数:\n商务座:%d  一等座:%d 二等座:%d\n", hrData.SuperlativeSeat,
                        hrData.FirstClassSeat, hrData.SecondClassSeat);
                    printf("经停站数:%d\n", hrData.StoppingStationNum);
                    for (int i = 0; i < hrData.StoppingStationNum; i++) {
                        StoppingStation station = hrData.SqSS.SSList[i];
                        // 读取每个经停站数据
                        printf("停靠站%d:%s 到达时间:%s 发车时间:%s 里程:%.1lf公里\n",
                            i + 1, station.Station_Name, station.ArrivalT,
                            station.DepartureT, station.mileage_s);

                    }
                    printf("\n");
                    break;
                }
            }
            p = p->nextRail;// 移动到下一个节点
        }
        if (!flag) {// 如果没有找到匹配的车次
            printf("暂无您想要查找的车次信息！！！\n");
            return ERROR;// 返回错误状态
        }
        break;

    }
    default:
        break;
    }
    return OK;// 返回OK状态
}
Status ModifyTrain(HRailList& railList, const char* file) {
    printf("您想要修改的车次：\n");
    char temp[20];// 创建一个字符数组用于存储用户输入的车次
    int flag = 0;// 用于标记是否找到匹配的车次
    scanf("%s", temp);// 获取用户输入的车次
    HRailList p = railList->nextRail;// 获取高铁列表的头节点
    while (p != NULL) // 遍历高铁列表
    {
        HRData hrData = p->data;// 获取当前节点的数据
        if (!strcmp(hrData.Train_Number, temp)) {// 检查车次是否匹配
            flag++;// 标记找到匹配的车次
            int ModiInfo;// 创建一个整型变量用于存储用户选择的修改信息类型
            printf("您想要修改的信息：\n");// 提供不同的修改信息类型选项
            printf("1.起点站\n");
            printf("2.终到站\n");
            printf("3.发车时间\n");
            printf("4.停靠站\n");
            printf("5.列车状态\n");
            printf("6.全部信息\n");
            scanf("%d", &ModiInfo);// 获取用户输入的修改信息类型
            clearScreen();// 清理屏幕
            switch (ModiInfo)
            {// 使用switch语句根据用户的选择执行不同的修改操作
            case 1: {
                printf("您想要将起点站修改成：\n");// 修改起点站
                scanf("%s", temp);
                strcpy(p->data.Departure_Station, temp);
                strcpy(p->data.SqSS.SSList[0].Station_Name,temp);
                break;

            }
            case 2: {
                printf("您想要将终到站修改成：\n");// 修改终到站
                scanf("%s", temp);
                strcpy(p->data.Terminal_Station, temp);
                strcpy(p->data.SqSS.SSList[p->data.SqSS.Num-1].Station_Name, temp);
                break;

            }
            case 3: {
                printf("您想要将发车时间修改成：\n");// 修改发车时间
                scanf("%s", temp);
                strcpy(p->data.time_Departure, temp);
                break;

            }
            case 4: {
                printf("您想要修改的停靠站是：\n");// 修改停靠站
                scanf("%s", temp);
                char temp1[20];
                for (int i = 0; i < hrData.StoppingStationNum; i++) {
                    StoppingStation station = hrData.SqSS.SSList[i];
                    // 读取每个经停站数据
                    if (!strcmp(station.Station_Name, temp))
                    {
                        printf("您想要将%s修改为：\n",temp);
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
                printf("您想要将状态修改成：\n");// 修改列车状态
                scanf("%s", temp1);
                strcpy(p->data.Condition, temp1);
                break;

            }
            case 6: {// 修改全部信息
                printf("您想要将始发站修改成：\n");
                scanf("%s", temp);
                strcpy(p->data.Departure_Station, temp);
                printf("您想要将终到站修改成：\n");
                scanf("%s", temp);
                strcpy(p->data.Terminal_Station, temp);
                printf("您想要将运行情况修改成：\n");
                scanf("%s", temp);
                strcpy(p->data.Condition, temp);
                clearScreen();
                printf("您想要将出发时间修改成：\n");
                scanf("%s", temp);
                strcpy(p->data.time_Departure, temp);
                printf("您想要将终到时间修改成：\n");
                scanf("%s", temp);
                strcpy(p->data.time_Arrival, temp);
                double mile;
                printf("您想要将总里程修改成：\n");
                scanf("%lf", &mile);
                p->data.mileage = mile;
                int tempi;
                clearScreen();
                printf("您想要将商务座数量修改成：\n");
                scanf("%d", &tempi);
                p->data.SuperlativeSeat = tempi;
                printf("您想要将一等座数量修改成：\n");
                scanf("%d", &tempi);
                p->data.FirstClassSeat = tempi;
                printf("您想要将二等座数量修改成：\n");
                scanf("%d", &tempi);
                p->data.SecondClassSeat = tempi;
                clearScreen();
                printf("您想要将经停站数量修改成：\n");
                scanf("%d", &tempi);
                p->data.StoppingStationNum = tempi;
                for (int i = 0; i < tempi; i++)
                {
                    StoppingStation station;
                    // 读取每个经停站数据
                    printf("经停站%d修改信息：\n",i+1);
                    printf("经停站名称:");
                    scanf("%s",
                        station.Station_Name);
                    printf("到达时间:");
                    scanf("%s",
                         station.ArrivalT);
                    printf("离开时间:");
                    scanf("%s",
                        station.DepartureT);
                    printf("里程数:");
                    scanf("%lf",
                         &station.mileage_s);
                    p->data.SqSS.SSList[i] = station;
                }
                break;

            }
            default:
                break;
            }
            WriteFile(railList, file);// 将修改后的数据写入文件
            printf("修改成功!!!\n");
            return OK;// 返回操作成功的状态
        }
        p = p->nextRail;// 移动到链表中的下一个节点
    }
    if (!flag) {// 如果没有找到匹配的车次
        printf("暂无您所要修改的车次信息！！！\n");
        return ERROR;// 返回错误状态
    }
}
Status ReadTrainFromFile(HRailList& railList, const char* file) {
    FILE* fp = fopen(file, "r");//打开文件进行读入
    if (fp == NULL) {
        perror("Error opening file");//错误输出
        return ERROR;//返回错误状态
    }
    if (InitList_Rail(railList) != OK) {//初始化成功
        perror("Error initializing rail list");//错误输出
        return ERROR;//返回错误状态
    }
    fscanf(fp, "%d", &railList->HighRail_Num);
    // 文件可正常扫描读取
    int InsertP = 1;//插入标志位记录
    HRData hrData;
    while (fscanf(fp, "%s %s %s %lf %s %s %s %d %d %d %d %s",
        hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
        &hrData.mileage, hrData.Condition, hrData.time_Departure,
        hrData.time_Arrival, &hrData.StoppingStationNum, &hrData.SuperlativeSeat,
        &hrData.FirstClassSeat, &hrData.SecondClassSeat, hrData.DepartureDate)==12) {//!feof(fp)
        // 从文件中读取高铁信息.
        // 初始化顺序表
        if (hrData.StoppingStationNum > 0) {
            if (InitList_Sq(hrData.SqSS, hrData.StoppingStationNum) != OK) {//初始化成功
                perror("Error initializing stopping station list");//错误输出
                return ERROR;//返回错误状态
            }

            for (int i = 0; i < hrData.StoppingStationNum; i++) {
                StoppingStation station;
                // 读取每个经停站数据
                fscanf(fp, "%s %s %s %lf",
                    station.Station_Name, station.ArrivalT,
                    station.DepartureT, &station.mileage_s);
                hrData.SqSS.SSList[i] = station;
            }
        }
        hrData.totalSeats = hrData.SuperlativeSeat + hrData.SecondClassSeat + hrData.FirstClassSeat;//座位数量计算
        for (int Stop = 0; Stop < hrData.StoppingStationNum; Stop++) {
            if (InitList_SqSeat(hrData.SqSS.SSList[Stop].seats, hrData.totalSeats) != OK) {//初始化成功
                perror("Error initializing stopping station list");//错误输出
                return ERROR;//返回错误状态
            }
            int count = 0;
            for (int i = 0; i < hrData.SuperlativeSeat; i++) {
                hrData.SqSS.SSList[Stop].seats[count].isBooked = 0;
                strcpy(hrData.SqSS.SSList[Stop].seats[count].seatClass, "商务座");//座位初始化
                hrData.SqSS.SSList[Stop].seats[count].seatNumber = i + 1;
                count++;
            }
            for (int i = 0; i < hrData.SecondClassSeat; i++) {
                hrData.SqSS.SSList[Stop].seats[count].isBooked = 0;
                strcpy(hrData.SqSS.SSList[Stop].seats[count].seatClass, "二等座");//座位初始化
                hrData.SqSS.SSList[Stop].seats[count].seatNumber = i + 1;
                count++;
            }
            for (int i = 0; i < hrData.FirstClassSeat; i++) {
                hrData.SqSS.SSList[Stop].seats[count].isBooked = 0;
                strcpy(hrData.SqSS.SSList[Stop].seats[count].seatClass, "一等座");//座位初始化
                hrData.SqSS.SSList[Stop].seats[count].seatNumber = i + 1;
                count++;
            }
        }
            
            // 把读取数据插入高铁链表
        if (ListInsert_RailInitial(railList, InsertP++, hrData) != OK) {
            perror("Error inserting data into rail list");//错误输出
            return ERROR;//返回错误状态
        }


    }
    fclose(fp);//关闭文件
}
Status PrintTrainInfo(HRailList& railList) {
    int n = railList->HighRail_Num;// 获取列车的数量
    HRailList p = railList->nextRail;// 指向高铁列表的第一个节点
    while (p != NULL)//遍历高铁链表
    {
        HRData hrData = p->data;// 获取当前节点的数据
        printf( "列车车次:%s 始发站:%s 终点站:%s 总里程:%.0lf公里 运行情况:%s\n",
            hrData.Train_Number, hrData.Departure_Station, hrData.Terminal_Station,
            hrData.mileage, hrData.Condition);
        printf("发车时间:%s  终到时间:%s 发车日期:", hrData.time_Departure,
            hrData.time_Arrival);
        DATE t_Date = stringToDate(hrData.DepartureDate);//将字符串类型转换为DATE类型
        printf("%4d/%02d/%02d\n", t_Date.year, t_Date.month, t_Date.day);
        printf("座位数:\n商务座:%d  一等座:%d 二等座:%d\n", hrData.SuperlativeSeat,
            hrData.FirstClassSeat, hrData.SecondClassSeat);
        printf("经停站数:%d\n", hrData.StoppingStationNum);
        for (int i = 0; i < hrData.StoppingStationNum; i++) {
            StoppingStation station = hrData.SqSS.SSList[i];
            // 读取每个经停站数据
            printf("停靠站%d:%s 到达时间:%s 发车时间:%s 里程:%.1lf公里\n",
                i+1,station.Station_Name, station.ArrivalT,
                station.DepartureT, station.mileage_s);

        }
        printf("\n");
        p = p->nextRail;//获取下一结点
    }
    return OK;//返回OK状态
}