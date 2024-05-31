#include"Passenger.h"
#include"Menu.h"
Status WriteFilePass(PassList& PList, const char* file) {
    FILE* fp1 = fopen(file, "w");// 打开文件用于写入，如果文件不存在则创建
    CountPassenger(PList);// 清点乘客的数量
    int n = PList->Passenger_Num;// 获取乘客的数量
    PassList p = PList->nextP;// 指向乘客列表的第一个节点
    while (p != NULL)// 遍历整个乘客列表
    {
        PassData PData = p->data;// 获取当前节点的数据
        fprintf(fp1, "%s %s %s %s %s %s",
            PData.ID,PData.Name, PData.ID_type, PData.PhoneNumber, PData.Emergency, PData.EmerPhone);
        fprintf(fp1, "\n");
        p = p->nextP;// 移动到链表中的下一个节点
    }
    fclose(fp1);//关闭文件
    return OK;// 返回操作成功的状态
}
Status AddPassenger(PassList& PList, const char* file) {
    PassData PData;//创建数据类型以便获取
    printf("请输入证件号,姓名,证件类型,联系电话,紧急联系人,联系人电话\n");
    // 从文件中读取高铁信息.
    scanf("%s %s %s %s %s %s",
        PData.ID, PData.Name, PData.ID_type, PData.PhoneNumber, PData.Emergency, PData.EmerPhone);

    // 把读取数据插入高铁链表
    if (ListInsert_Passenger(PList, PList->Passenger_Num + 1, PData) != OK) {
        perror("Error inserting data into rail list");//输出错误信息
        return ERROR;//返回错误状态
    }
    WriteFilePass(PList, file);//写入文件
    return OK;//返回OK状态
}
Status DeletePassenger(PassList& PList, const char* file) {
    printf("您想要删除的用户的证件号为：\n");
    PassList L = PList;// 创建一个指向乘客列表头节点的指针
    char temp1[25];// 创建一个字符数组用于存储用户输入的证件号
    int flag = 0;// 用于标记是否找到匹配的用户
    scanf("%s", temp1);// 获取用户输入的证件号
    clearScreen();// 清理屏幕
    while (L->nextP)// 遍历乘客列表
    {
        if (!strcmp(temp1, L->nextP->data.ID))// 检查证件号是否匹配
        {
            printCentered("您所要删除的用户是：\n");// 打印匹配用户的信息
            printf("证件号:%s\n证件类型:%s\n姓名:%s 联系电话:%s\n紧急联系人:%s 紧急联系人电话:%s\n", L->nextP->data.ID, L->nextP->data.ID_type, L->nextP->data.Name, L->nextP->data.PhoneNumber, L->nextP->data.Emergency, L->nextP->data.EmerPhone);
            printf("\n");
            int flag1 = 0;

        A:   
            printCentered("1.确认   2.取消");// 创建一个整型变量用于存储用户的确认操作
            printf("请确认：");
            scanf("%d", &flag1);
            if (flag1 == 1)
            {
                // 用户确认删除
                PassList tmp = L->nextP;// 保存当前匹配节点
                L->nextP = tmp->nextP;
                free(tmp);// 释放内存
                flag = 1;// 标记删除成功
                printCentered("删除成功!!!");
                break;
            }
            if (flag1 == 2)
            {
                flag = 1;//  标记删除操作已处理
                printCentered("您已取消删除!!!");
                break;
            }
            clearScreen();
            printCentered("请输入有效数字!!!");
            goto A;// 重新请求用户输入确认操作
            
        }
        L = L->nextP;// 移动到链表中的下一个节点
    }
    if (!flag) {// 如果没有找到匹配的用户
        printf("您想要删除的用户不存在!!!\n");
        return ERROR;// 返回错误状态
    }
    WriteFilePass(PList, file);// 将修改后的数据写入文件
    return OK;// 返回操作成功的状态
}
Status SearchPassenger(PassList& PList) {
    char temp[20];// 用于存储用户输入的查询信息
    int SearchWay;// 用于选择查询方式
    printf("查询方式：\n");
    printf("1.姓名\n");
    printf("2.证件号\n");
    printf("3.联系电话\n");
    printf("4.紧急联系人\n");
    printf("5.紧急联系人电话\n");
    scanf("%d", &SearchWay);// 获取用户选择的查询方式
    clearScreen();// 清理屏幕
    switch (SearchWay)// 根据用户选择的查询方式进行不同的处理
    {
    case 1: {// 根据姓名查询
        printf("您想要查询的用户姓名是：\n");
        scanf("%s", temp);// 获取用户输入的姓名
        PassList p = PList->nextP;// 获取乘客列表的头节点
        int flag = 0;// 标志变量，用于检查是否找到匹配项
        while (p != NULL)// 遍历乘客列表
        {
            PassData pData = p->data;// 获取当前节点的乘客数据
            if (!strcmp(pData.Name, temp)) {// 检查姓名是否匹配
                flag++;// 如果找到匹配项，增加标志计数
                printf("证件号:%s\n证件类型:%s\n姓名:%s 联系电话:%s\n紧急联系人:%s 紧急联系人电话:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// 打印匹配乘客的信息
               
            }
            p = p->nextP;// 移动到下一个节点
        }
        if (!flag) { // 如果没有找到匹配项
            printf("暂无您想要查找的用户信息！！！\n");
            return ERROR;//返回错误状态
        }
        break;

    }
    case 2: {// 根据证件号查询
        printf("您想要查询的用户证件号是：\n");
        scanf("%s", temp);// 获取用户输入的证件号
        PassList p = PList->nextP;;// 获取乘客列表的头节点
        while (p != NULL)// 遍历乘客列表
        {
            PassData pData = p->data;// 获取当前节点的乘客数据
            if (!strcmp(pData.ID, temp)) {// 检查证件号是否匹配
                printf("证件号:%s\n证件类型:%s\n姓名:%s 联系电话:%s\n紧急联系人:%s 紧急联系人电话:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// 打印匹配乘客的信息
                break;
            }
            p = p->nextP;// 移动到下一个节点
        }
        if (!p) {// 如果没有找到匹配项
            printf("暂无您想要查找的用户信息！！！\n");
            return ERROR;//返回错误状态
        }
        break;
    }
    case 3: {// 根据联系电话查询
        printf("您想要查询的联系电话是：\n");
        scanf("%s", temp);// 获取用户输入的联系电话
        PassList p = PList->nextP;// 获取乘客列表的头节点
        while (p != NULL)// 遍历乘客列表
        {
            PassData pData = p->data;// 获取当前节点的乘客数据
            if (!strcmp(pData.PhoneNumber, temp)) {// 检查联系电话是否匹配
                printf("证件号:%s\n证件类型:%s\n姓名:%s 联系电话:%s\n紧急联系人:%s 紧急联系人电话:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// 打印匹配乘客的信息
                break;
            }
            p = p->nextP;// 移动到下一个节点
        }
        if (!p) {// 如果没有找到匹配项
            printf("暂无您想要查找的用户信息！！！\n");
            return ERROR;//返回错误状态
        }
        break;
    }
    case 4: {// 根据紧急联系人姓名查询
        printf("您想要查询的紧急联系人姓名是：\n");
        scanf("%s", temp);// 获取用户输入的姓名
        int flag = 0;
        PassList p = PList->nextP;// 获取乘客列表的头节点
        while (p != NULL)// 遍历乘客列表
        {
            PassData pData = p->data;// 获取当前节点的乘客数据
            if (!strcmp(pData.Emergency, temp)) {// 检查紧急联系人姓名是否匹配
                flag++;// 如果找到匹配项，增加标志计数
                printf("证件号:%s\n证件类型:%s\n姓名:%s 联系电话:%s\n紧急联系人:%s 紧急联系人电话:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// 打印匹配乘客的信息
                break;
            }
            p = p->nextP;// 移动到下一个节点
        }
        if (!flag) {// 如果没有找到匹配项
            printf("暂无您想要查找的用户信息！！！\n");
            return ERROR;//返回错误状态
        }
        break;
    }
    case 5: {// 根据紧急联系人电话查询
        printf("您想要查询的紧急联系人电话是：\n");
        scanf("%s", temp);// 获取用户输入的联系电话
        PassList p = PList->nextP;// 获取乘客列表的头节点
        while (p != NULL)// 遍历乘客列表
        {
            PassData pData = p->data;// 获取当前节点的乘客数据
            if (!strcmp(pData.EmerPhone, temp)) {// 检查紧急联系人电话是否匹配
                printf("证件号:%s\n证件类型:%s\n姓名:%s 联系电话:%s\n紧急联系人:%s 紧急联系人电话:%s\n", pData.ID, pData.ID_type, pData.Name, pData.PhoneNumber, pData.Emergency, pData.EmerPhone);
                printf("\n");// 打印匹配乘客的信息
                break;
            }
            p = p->nextP;// 移动到下一个节点
        }
        if (!p) {// 如果没有找到匹配项
            printf("暂无您想要查找的用户信息！！！\n");
            return ERROR;//返回错误状态
        }
        break;
    }
    default:
        break;
    }
    return OK;
}
Status ModifyPassenger(PassList& PList, const char* file) {
    printf("您想要修改的用户证件号为：\n");
    char temp[25];// 存储用户输入的证件号
    scanf("%s", temp);// 读取用户输入的证件号
    PassList pl = PList->nextP;// 获取乘客列表的第一个元素
    while (pl != NULL)// 遍历乘客列表以找到匹配的证件
    {
        if (!strcmp(pl->data.ID, temp))// 如果找到了匹配的证件号，跳出循环
        {
            break;
        }
        pl = pl->nextP;// 移动到下一个乘客
    }
    if (!pl) {// 如果没有找到匹配的证件号，返回错误
        printf("查询不到你所想修改的用户证件号!!!\n");
        return ERROR;
    }
    clearScreen();// 清屏
    int ModifyWay;// 用户选择的修改方式
    printf("修改信息种类：\n");
    printf("1.联系电话\n");
    printf("2.紧急联系人及其电话\n");
    scanf("%d", &ModifyWay);// 读取用户选择的修改方式
    clearScreen();// 清屏
    switch (ModifyWay)
    {
    case 1: {// 修改联系电话
        PassList pl = PList->nextP;// 获取乘客列表的第一个元素
        while (pl != NULL)
        {
            if (!strcmp(pl->data.ID, temp))// 找到匹配的证件号
            {
                printf("您想要将联系电话修改为：\n");
                char t_phone[20];// 存储新的电话号码
                scanf("%s", t_phone);// 读取新的电话号码
                strcpy(pl->data.PhoneNumber, t_phone);// 更新电话号码
                printf("修改成功!!!\n");
                break;
            }
            pl = pl->nextP;// 移动到下一个乘客
        }
        if (!pl) {
            printf("查询不到你所想修改的用户证件号!!!\n");
        }
        break;
    }
    case 2: { // 修改紧急联系人及其电话
        PassList pl = PList->nextP;// 获取乘客列表的第一个元素
        while (pl != NULL)
        {
            if (!strcmp(pl->data.ID, temp))// 找到匹配的证件号
            {
                printf("您想要将紧急联系人修改为：\n");
                char t_Emer[25];// 存储新的紧急联系人姓名
                char t_Emerphone[20];// 存储新的紧急联系人电话号码
                scanf("%s", t_Emer);// 读取新的紧急联系人姓名
                strcpy(pl->data.Emergency, t_Emer);// 更新紧急联系人姓名
                printf("紧急联系人电话修改为：\n");
                scanf("%s", t_Emerphone); // 读取新的紧急联系人电话号码
                strcpy(pl->data.EmerPhone, t_Emerphone);// 更新紧急联系人电话号码
                printf("修改成功!!!\n");
                break;
            }
            pl = pl->nextP;// 移动到下一个乘客
        }
        if (!pl) {
            printf("查询不到你所想修改的用户证件号!!!\n");
        }
        break;
    }
    default:{
              break;
          }
    }
    WriteFilePass(PList, file);// 将修改后的乘客列表写入文件
    return OK;// 返回成功状态
}
Status ReadPassengersFromFile(PassList& PList, const char* file) {
    FILE* fp = fopen(file, "r");//打开文件进行读入
    if (fp == NULL) {
        perror("Error opening file");//错误输出
        return ERROR;//返回错误状态
    }
    if (InitList_Pass(PList) != OK) {//初始化链表
        perror("Error initializing rail list");//错误输出
        return ERROR;//返回错误状态
    }
    // 文件可正常扫描读取
    int InsertP = 1;//插入标志位记录
    PassData pData;
    while (fscanf(fp, "%s %s %s %s %s %s",
        pData.ID, pData.Name, pData.ID_type, pData.PhoneNumber, pData.Emergency, pData.EmerPhone)==6) {
        
       
        // 从文件中读取高铁信息.
       
        // 把读取数据插入高铁链表
        if (ListInsert_PassInitial(PList, InsertP++, pData) != OK) {
            perror("Error inserting data into rail list");//错误输出
            return ERROR;//返回错误状态
        }
        PList->Passenger_Num = InsertP - 1;//更新乘客数

    }
    fclose(fp);//关闭文件
}
Status PrintPassengerInfo(PassList& PList) {
    PassList pl = PList->nextP;//找到首元结点
    while (pl)//遍历链表
    {
        printf("证件号:%s\n证件类型:%s\n姓名:%s 联系电话:%s\n紧急联系人:%s 紧急联系人电话:%s\n", pl->data.ID, pl->data.ID_type, pl->data.Name,  pl->data.PhoneNumber, pl->data.Emergency, pl->data.EmerPhone);
        printf("\n");//输出乘客信息
        
        pl = pl->nextP;//找到下一节点
    }
    return OK;
}