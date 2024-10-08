#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>//区域设置
#include <stdlib.h>
#include <fcntl.h>//汉字显示
#include <stdint.h>

// #include "print_format.h"//控制汉字输出格式
#include "account.h"
#include "store_info.h"
#include "search.h"
#include "modify.h"
#include "delete.h"
#include "statistics.h"
#include "summary.h"
#include "display.h"
#include "manageAccount.h"
#include <io.h>

// TODO:新增,修改与删除账号
// TODO:录入信息的函数需要加上参数，把scanf放到main里，多次调用
//管理员可以添加其他人的信息，老师可以修改成绩，所有人都可以修改密码
// TODO:第二级界面输入错误退到第一级界面，输入正确就继续

void enterBar(int taskLabel){
    switch (taskLabel)
    {
    case 1:
        // char inputID, inputName, inputGender, inputAge, inputProf;
        // gets(inputID);
        
        printf("这是录入学生基本信息的界面。\n");
        enterStu();
        break;
    case 2:
        printf("这是录入课程基本信息的界面。\n");
        enterCourse();
        break;
    case 3:
        printf("这是录入学生成绩的界面。\n");
        enterScore();
        break;   
    default:
        printf("这是无效的任务编号，请重新输入。\n");
        break;
    }
}

void modifyBar(int taskLabel){
    wchar_t id[50], name[50], newInfo[50], idx[50], userName[50], password[50];
    wint_t wc;
    double newGrade;
    int item;
    switch (taskLabel)
    {
    case 1:
        printf("这是修改学生基本信息的界面。\n");
        printf("你可以选择修改1-学号2-姓名3-性别4-年龄5-所在系。\n");
        // scanf("%d", &counter);
        // if (counter > 0 && counter < 11){
        //     for (int i = 0; i < counter ; i ++){
                // printf("这是第%d次修改。\n", counter+1);
        printf("请依次输入需要修改的学生信息的学号、姓名、新信息与修改项。\n");
        // wint_t wc;
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区
        fgetws(id, sizeof(id), stdin);
        id[wcslen(id)-1] = L'\0';
        // if (wcscmp(id, L"exit") == 0)
        //     return;
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name)-1] = L'\0';
        fgetws(newInfo, sizeof(newInfo), stdin);
        newInfo[wcslen(newInfo)-1] = L'\0';

        wscanf(L"%d", &item);
        modify_stu(id, name, newInfo, item);
        break;
    case 2:
        printf("这是修改课程基本信息的界面。\n");
        printf("你可以选择修改1-课号2-课名3-任课老师。\n");
        // scanf("%d", &counter);
        // if (counter > 0 && counter < 11){
        //     for (int i = 0; i < counter ; i ++){
        printf("请依次输入需要修改的课号、课名、新信息与修改项。\n");
        // wint_t wc;
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区
        
        fgetws(idx, sizeof(idx), stdin);  
        idx[wcslen(idx)-1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name)-1] = L'\0';
        fgetws(newInfo, sizeof(newInfo), stdin);
        newInfo[wcslen(newInfo)-1] = L'\0';

        wscanf(L"%d", &item);
        modify_course(idx, name, newInfo, item);
            // }
        break;
    case 3:
        printf("这是修改学生成绩的界面。\n");
        // printf("你可以选择修改1-学号2-姓名3-性别4-年龄5-所在系。\n");
        
        // wscanf(L"%d", &counter);
        // if (counter > 0 && counter < 11){
            // for (int i = 0; i < counter ; i ++){
        printf("修改成绩需要输入你的用户名和密码。\n");
        printf("请依次输入用户名、密码、学号、课号、修改项（1-平时成绩，2-卷面成绩）与新成绩。\n");
        // printf("UserName:\n");
        // wint_t wc;
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区
        // fflush(stdin);
        fgetws(userName, sizeof(userName), stdin);
        userName[wcslen(userName)-1] = L'\0';
        // wprintf(L"username: %ls\n", userName);
        fgetws(password, sizeof(password), stdin);
        password[wcslen(password)-1] = L'\0';
        // wprintf(L"password: %ls\n", password);
        fgetws(id, sizeof(id), stdin);
        id[wcslen(id)-1] = L'\0';
        // wprintf(L"id: %ls\n", id);
        fgetws(idx, sizeof(idx), stdin);
        // wprintf(L"idx: %ls\n", idx);
        // printf("length:%d\n", wcslen(idx));
        idx[wcslen(idx)-1] = L'\0';
        // fflush(stdin);
        wscanf(L"%d", &item);
        wscanf(L"%lf", &newGrade);
        // wscanf(L"%d", &item);
        // wscanf(L"%lf", &newGrade);
        if (item == 1)
            modify_score0(userName, password, id, idx, newGrade);
        else if (item == 2)
            modify_score1(userName, password, id, idx, newGrade);
        else
            printf("修改信息项不存在。\n");
        break;   
    default:
        printf("这是无效的任务编号，请重新选择。\n");
        break;
    }
}

void deleteBar(int taskLabel){
    wchar_t id[50], name[50], idx[50];
    wint_t wc;
    switch (taskLabel)
    {
    case 1:
        printf("这是删除学生基本信息的界面。\n");
        printf("请依次输入需要删除信息的学号与姓名。\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);

        fgetws(id, sizeof(id), stdin);
        id[wcslen(id)-1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name)-1] = L'\0';

        delete_stu(id, name);
        break;
    case 2:
        printf("这是删除课程基本信息的界面。\n");
        printf("请依次输入需要删除信息的课号与课名。\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);

        fgetws(idx, sizeof(idx), stdin);
        idx[wcslen(idx)-1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name)-1] = L'\0';

        delete_course(idx, name);
        break;
    case 3:
        printf("这是删除学生成绩的界面。\n");
        printf("请依次输入需要删除信息的学号与课号。\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);
        
        fgetws(id, sizeof(id), stdin);
        id[wcslen(id)-1] = L'\0';
        fgetws(idx, sizeof(idx), stdin);
        idx[wcslen(idx)-1] = L'\0';

        delete_score(id, idx);
        break;   
    default:
        printf("这是无效的任务编号，请重新输入。\n");
        break;
    }
}

void searchBar(int taskLabel){
    wchar_t id[50], idx[50], name[50], gender[50], profession[50];
    wint_t wc;
    switch (taskLabel)
    {
    case 1:
        printf("这是查询学生基本信息的界面。\n");
        printf("请依次输入学号和姓名：\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区

        fgetws(id, sizeof(id), stdin);
        id[wcslen(id) - 1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name) - 1] = L'\0';

        find_stu(id, name);
        break;
    case 2:
        printf("这是查询课程基本信息的界面。\n");
        printf("请依次输入课号和任课教师：\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区

        fgetws(idx, sizeof(idx), stdin);
        idx[wcslen(idx) - 1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name) - 1] = L'\0';

        find_course(idx, name);
        break;
    case 3:
        printf("这是按性别查询学生基本信息的界面。\n");
        printf("请输入男/女：\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区

        fgetws(gender, sizeof(gender), stdin);
        gender[wcslen(gender) - 1] = L'\0';

        find_gender(gender);
        break;
    case 4:
        printf("这是按系查询学生基本信息的界面。\n");
        printf("请输入学生所在系名称：\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区

        fgetws(profession, sizeof(profession), stdin);
        profession[wcslen(profession) - 1] = L'\0';

        find_profession(profession);
        break;
    case 5:
        printf("这是查询学生所有课程成绩的界面。\n");
        printf("请依次输入学号和姓名：\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区

        fgetws(id, sizeof(id), stdin);
        id[wcslen(id) - 1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name) - 1] = L'\0';

        find_score0(id, name);
        break;
    case 6:
        printf("这是查询课程所有学生成绩的界面。");
        printf("请依次输入课号和课名：\n");
        while ((wc = getwchar()) != L'\n' && wc != WEOF);//清空缓冲区

        fgetws(idx, sizeof(idx), stdin);
        idx[wcslen(idx) - 1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name) - 1] = L'\0';

        find_score1(idx, name);
        break;   
    default:
        printf("这是无效的任务编号，请重新输入。\n");
        // printf("你已经退到上一级。\n");
        // wscanf(L"%d", &taskLabel);//不退出这个界面
        // searchBar(taskLabel);
        break;
        // return; //退出上一级
    }
    // wscanf(L"%d", &taskLabel);//不退出这个界面
    // searchBar(taskLabel);
}

void statBar(int taskLabel){ //统计成绩的选项
    switch (taskLabel)
    {
    case 1:
        printf("这是统计课程卷面成绩的平均分的界面。\n");
        average_exam_grade();
        break;
    case 2:
        printf("这是统计课程综合成绩的平均分的界面。\n");
        average_score();
        break;
    case 3:
        printf("这是统计课程卷面成绩的最高分的界面。\n");
        max_exam_grade();
        break;
    case 4:
        printf("这是统计课程综合成绩的最高分的界面。\n");
        max_score();
        break;
    case 5:
        printf("这是统计课程卷面成绩的分数段的界面。\n");
        exam_statistics();
        break;
    case 6:
        printf("这是统计课程综合成绩的分数段的界面。\n");
        score_statistics();
        break;   
    default:
        printf("这是无效的任务编号，请重新输入。\n");
        break;
    }
}

void sumBar(int taskLabel){
    switch (taskLabel)
    {
    case 1:
        printf("这是显示课程及格情况的界面。\n");
        course_info();
        break;
    case 2:
        printf("这是显示学生成绩及格情况的界面。\n");
        stu_info();
        break;
    default:
        printf("这是无效的任务编号，请重新输入。\n");
        break;
    }
}


void manager(int task_num){
    int task_label;
    wchar_t userName[50], role[50], newPassword[50], name[50];
    wint_t wc;
    switch (task_num)
    {
    case 1:
        printf("这是添加用户信息的界面。\n");
        printf("请依次输入用户名、姓名和角色：\n");
        // while ((wc = getwchar()) != L'\n' && wc != WEOF);

        fgetws(userName, sizeof(userName), stdin);
        userName[wcslen(userName)-1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name)-1] = L'\0';
        fgetws(role, sizeof(role), stdin);
        role[wcslen(role)-1] = L'\0';

        add_info(userName, name, role);
        // return 1;
        break;
    case 2:
        printf("这是修改密码的界面。\n");
        printf("请依次输入用户名、姓名和新密码：\n");
        // while ((wc = getwchar()) != L'\n' && wc != WEOF);

        fgetws(userName, sizeof(userName), stdin);
        userName[wcslen(userName)-1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name)-1] = L'\0';
        fgetws(newPassword, sizeof(newPassword), stdin);
        newPassword[wcslen(newPassword)-1] = L'\0';

        modify_password(userName, name, newPassword);
        // return 2;
        break;
    case 3:
        printf("这是录入学生信息的界面。\n");
        printf("你可以选择输入：\n1-录入学生基本信息\n2-录入课程基本信息\n3-录入成绩信息。\n");
        wscanf(L"%d", &task_label);
        enterBar(task_label);
        break;
        // return 3;
    case 4:
        printf("这是修改学生信息的界面。\n");
        printf("你可以选择输入：\n1-修改学生基本信息\n2-修改课程基本信息\n3-修改成绩信息。\n");
        wscanf(L"%d", &task_label);
        modifyBar(task_label);
        break;
        // return 4;
    case 5:
        printf("这是删除学生信息的界面。\n");
        printf("你可以选择输入：\n1-删除学生基本信息\n2-删除课程基本信息\n3-删除成绩信息。\n");
        wscanf(L"%d", &task_label);
        deleteBar(task_label);
        break;
        // return 5;
    case 6:
        printf("这是查询学生信息的界面。\n");
        printf("你可以选择输入：\n1-查询学生基本信息\n2-查询课程基本信息\n3-按性别查询学生基本信息\n4-按所在系查询学生基本信息\n5-查询学生的课程成绩信息\n6-查询课程的学生成绩信息。\n");
        wscanf(L"%d", &task_label);
        searchBar(task_label);
        break;
        // return 6;
    case 7:
        printf("这是显示全部学生信息的界面.\n");
        display();
        break;
        // return 7;
    case 8:
        printf("这是统计学生成绩的界面。\n");
        printf("你可以选择输入：\n1-统计课程卷面成绩平均分\n2-统计课程综合成绩平均分\n3-统计课程卷面成绩最高分\n4-统计课程综合成绩最高分\n5-统计课程卷面成绩分数段\n6-统计课程综合成绩分数段。\n");
        wscanf(L"%d", &task_label);
        statBar(task_label);
        break;
        // return 8;
    case 9:
        printf("这是汇总报表的界面。\n");
        printf("你可以选择输入：\n1-显示课程成绩及格情况\n2-显示成绩学生及格情况。\n");
        wscanf(L"%d", &task_label);
        sumBar(task_label);
        break;
        // return 9;
    case 10:
        printf("你已经退出系统。\n");
        return;//返回登录界面
        // return 10;
    default:
        printf("这是无效的任务编号，请重新输入。\n");
        break;
    }
    printf("请选择：\n1-添加用户信息\n2-修改密码\n3-录入学生信息\n4-修改学生信息\n5-删除学生信息\n6-查询学生信息\n7-显示学生信息\n8-统计学生成绩\n9-汇总报表\n10-退出系统\n"); //任务提示
    printf("请输入任务编号：\n");
    // wscanf(L"%d", &task_num);
    wscanf(L"%d", &task_num);
    while ((wc = getwchar()) != L'\n' && wc != WEOF);
    // if (task_num != 10)
    manager(task_num);
    
}

void teacher(int task_num){
    int task_label;
    wchar_t userName[50], name[50], newPassword[50];
    wint_t wc;
    switch (task_num)
    {
    case 1:
        printf("这是修改密码的界面.\n");
        printf("请依次输入用户名、姓名和新密码：\n");
        // while ((wc = getwchar()) != L'\n' && wc != WEOF);

        fgetws(userName, sizeof(userName), stdin);
        userName[wcslen(userName)-1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name)-1] = L'\0';
        fgetws(newPassword, sizeof(newPassword), stdin);
        newPassword[wcslen(newPassword)-1] = L'\0';

        modify_password(userName, name, newPassword);
        break;
        // return 1;
    case 2:
        printf("这是修改学生信息的界面.\n");
        printf("你可以选择输入：\n1-修改学生基本信息\n2-修改课程基本信息\n3-修改成绩信息。\n");
        wscanf(L"%d", &task_label);
        modifyBar(task_label);
        break;
        // return 2;
    case 3:
        printf("这是删除学生信息的界面.\n");
        printf("你可以选择输入：\n1-删除学生基本信息\n2-删除课程基本信息\n3-删除成绩信息。\n");
        wscanf(L"%d", &task_label);
        deleteBar(task_label);
        break;
        // return 3;
    case 4:
        printf("这是显示全部学生信息的界面.\n");
        display();
        break;
        // return 4;    
    case 5:
        printf("这是查询学生信息的界面。\n");
        printf("你可以选择输入：\n1-查询学生基本信息\n2-查询课程基本信息\n3-按性别查询学生基本信息\n4-按所在系查询学生基本信息\n5-查询学生的课程成绩信息\n6-查询课程的学生成绩信息。\n");
        wscanf(L"%d", &task_label);
        searchBar(task_label);
        break;
        // return 5;
    case 6:
        printf("这是统计学生成绩的界面。\n");
        printf("你可以选择输入：\n1-统计课程卷面成绩平均分\n2-统计课程综合成绩平均分\n3-统计课程卷面成绩最高分\n4-统计课程综合成绩最高分\n5-统计课程卷面成绩分数段\n6-统计课程综合成绩分数段。\n");
        wscanf(L"%d", &task_label);
        statBar(task_label);
        break;
        // return 6;
    case 7:
        printf("这是汇总报表的界面。\n");
        printf("你可以选择输入：\n1-显示课程成绩及格情况\n2-显示成绩学生及格情况。\n");
        wscanf(L"%d", &task_label);
        sumBar(task_label);
        break;
        // return 7;
    case 8:
        printf("你已经退出系统。\n");
        // return 8;
        return; //返回登录界面
    default:
        printf("这是无效的任务编号，请重新输入。\n");
        break;
    }
    printf("请选择：\n1-修改密码\n2-修改学生信息\n3-删除学生信息\n4-显示学生信息\n5-查询学生信息\n6-统计学生成绩\n7-汇总报表\n8-退出系统\n");
    printf("请输入任务编号：\n");
    wscanf(L"%d", &task_num);
    while ((wc = getwchar()) != L'\n' && wc != WEOF);
    teacher(task_num);
}

void student(int task_num){
    int task_label;
    wchar_t userName[50], name[50], newPassword[50];
    wint_t wc;
    switch (task_num)
    {
    case 1:
        printf("这是修改密码的界面.\n");
        printf("请依次输入用户名、姓名和新密码：\n");
        // while ((wc = getwchar()) != L'\n' && wc != WEOF);
        
        fgetws(userName, sizeof(userName), stdin);
        userName[wcslen(userName)-1] = L'\0';
        fgetws(name, sizeof(name), stdin);
        name[wcslen(name)-1] = L'\0';
        fgetws(newPassword, sizeof(newPassword), stdin);
        newPassword[wcslen(newPassword)-1] = L'\0';
        wprintf(L"new password%ls\n", newPassword);

        modify_password(userName, name, newPassword);
        break;
    case 2:
        printf("这是显示学生信息的界面.\n");
        display();
        break;
        // return 1;
    case 3:
        printf("这是查询学生信息的界面.\n");
        printf("你可以选择输入：\n1-查询学生基本信息\n2-查询课程基本信息\n3-按性别查询学生基本信息\n4-按所在系查询学生基本信息\n5-查询学生的课程成绩信息\n6-查询课程的学生成绩信息。\n");
        wscanf(L"%d", &task_label);
        searchBar(task_label);
        break;
        // return 2;
    case 4:
        printf("这是统计学生成绩的界面。\n");
        printf("你可以选择输入：\n1-统计课程卷面成绩平均分\n2-统计课程综合成绩平均分\n3-统计课程卷面成绩最高分\n4-统计课程综合成绩最高分\n-5统计课程卷面成绩分数段\n6-统计课程综合成绩分数段。\n");
        wscanf(L"%d", &task_label);
        statBar(task_label);
        break;
        // return 3;
    case 5:
        printf("你已经退出系统。\n");
        return;
        // return 4;
    default:
        printf("这是无效的任务编号，请重新输入。\n");
        break;
    }
    //下一个任务
    printf("请选择：\n1-修改密码\n2-显示学生信息\n3-查询学生信息\n4-统计学生成绩\n5-退出系统\n");
    printf("请输入任务编号：\n");
    wscanf(L"%d", &task_num);
    while ((wc = getwchar()) != L'\n' && wc != WEOF);
    student(task_num);
}

int log_in(wchar_t *account_name, wchar_t *name, wchar_t *role, wchar_t *password){ //用户登录
    struct Account account;
    //判断密码是否存在
    // if (strcmp(password, "12345") != 0){
        //printf("password:%s",password);
    //     return 1;
    // }
    //读文件，判断账号是否存在
    char buffer[300];
    wchar_t wbuffer[300];
    int start = 0, end = 0, i, j = 0;
    
    //打开账号文件
    FILE* fp;
    fp = fopen("account_info.txt","r");
    if (fp == NULL){
        printf("文件打开失败\n");
        return 1;
        // exit();
        //exit();
    }

    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^\n]", account.user, account.name, account.role, account.password) == 4){
            if (wcscmp(account_name, account.user) == 0){ //比较其他信息
                if (wcscmp(name, account.name) != 0 || wcscmp(role, account.role) != 0 || wcscmp(password, account.password) != 0){
                    // printf("信息错误!\n");
                    break;
                }else{
                    // printf("登录成功!\n");
                    return 0;
                } 
            }
        }

        // for (i = 0; i < strlen(buffer); i ++){
        //     //不相同字符：
        //     if (buffer[i] != account_name[j] || account_name[j] == ','){
        //         j = 0;//重新开始比较
        //     }
        //     //相同字符：
        //     if (buffer[i] == account_name[j] && account_name[j] != ','){
        //         // printf("buffer:%c,account:%c\n",buffer[i],account_name[j]);      
        //         if (j == 0){
        //             start = i; //record start position
        //             // printf("start:%d\n",start);
        //         }             
        //         if (j == strlen(account_name)-1){
        //             end = i; //record end position
        //             // printf("end:%d\n",end);
        //             break;
        //         }
        //         j ++;
        //     }           
        // }
        // printf("start:%d,end:%d\n",start,end);
        // if (end - start + 1 == strlen(account_name)){
        //     return 0;//账号与密码都存在
        // }
        // j = 0;//重置j
    }
    
    return 1;//账号与其他信息不匹配
    //关闭文件
    fclose(fp);

    // account_idx ++;
    // return account_idx;//返回账号序号
}


int main(){
    setlocale(LC_ALL, "");//区域环境设置
    _setmode( _fileno( stdin ), _O_WTEXT );//输入设置为宽字符

    int choice_num, role_num, task;
    wchar_t AccountName[50], PassWord[50], role[50], Name[50];
    wint_t wc;
    int result;
    // int AccountIdx = 1;
    while (1){ //不关闭界面
        //登录提示
        printf("你好，请依次输入用户名、姓名、角色和密码（中间需要回车）：\n");
    // scanf("%s",AccountName);
        fgetws(AccountName, sizeof(AccountName), stdin);
        AccountName[wcslen(AccountName)-1] = L'\0';

        fgetws(Name, sizeof(Name), stdin);
        Name[wcslen(Name)-1] = L'\0';

        fgetws(role, sizeof(role), stdin);
        role[wcslen(role)-1] = L'\0';
        //TODO:为什么密码不能输入(bug)
        // while ((wc = getwchar()) != L'\n' && wc != WEOF);


        fgetws(PassWord, sizeof(PassWord), stdin);
        PassWord[wcslen(PassWord)-1] = L'\0';
    // scanf("%s",PassWord);
        result = log_in(AccountName, Name, role, PassWord);
    // if (result == 0){
    //     printf("恭喜，登录成功!\n");
    //     if (strcmp(role, "manager") == 0)
    //         role_num = 1;
    //     else if (strcmp(role, "teacher") == 0)
    //         role_num = 2;
    //     else if (strcmp(role, "student") == 0)
    //         role_num = 3;
    // }

        while (result == 1){ //登录失败
            printf("姓名/角色/密码错误或文件打开失败，请重新输入(密码默认为12345)。\n");

            fgetws(AccountName, sizeof(AccountName), stdin);
            AccountName[wcslen(AccountName)-1] = L'\0';

            fgetws(Name, sizeof(Name), stdin);
            Name[wcslen(Name)-1] = L'\0';

            fgetws(role, sizeof(role), stdin);
            role[wcslen(role)-1] = L'\0';

            fgetws(PassWord, sizeof(PassWord), stdin);
            PassWord[wcslen(PassWord)-1] = L'\0';

            result = log_in(AccountName, Name, role, PassWord);
        }
        //登录成功
        printf("恭喜，登录成功!\n");
        if (wcscmp(role, L"管理员") == 0)
            role_num = 1;
        else if (wcscmp(role, L"教师") == 0)
            role_num = 2;
        else if (wcscmp(role, L"学生") == 0)
            role_num = 3;
    // if (result == 2)
    //     printf("账号不存在，请重新输入。\n");

        //选择角色+任务
        switch (role_num){
            case 1:
                printf("你好，管理员。\n");
                printf("请选择：\n1-添加用户信息\n2-修改密码\n3-录入学生信息\n4-修改学生信息\n5-删除学生信息\n6-查询学生信息\n7-显示学生信息\n8-统计学生成绩\n9-汇总报表\n10-退出系统\n");
                wscanf(L"%d", &task);
                while ((wc = getwchar()) != L'\n' && wc != WEOF);
                while (task != 1 && task != 2 && task != 3 && task != 4 && task != 5 && task != 6 && task != 7 && task != 8 && task != 9 && task != 10){
                    printf("无效的任务编号，请重新选择：\n1-添加用户信息\n2-修改密码\n3-录入学生信息\n4-修改学生信息\n5-删除学生信息\n6-查询学生信息\n7-显示学生信息\n8-统计学生成绩\n9-汇总报表\n10-退出系统\n");
                    wscanf(L"%d", &task);
                    while ((wc = getwchar()) != L'\n' && wc != WEOF);
                }
                manager(task);
                break; 
            case 2:
                printf("你好，教师。\n");
                printf("请选择：\n1-修改密码\n2-修改学生信息\n3-删除学生信息\n4-显示学生信息\n5-查询学生信息\n6-统计学生成绩\n7-汇总报表\n8-退出系统\n");
                wscanf(L"%d", &task);
                while ((wc = getwchar()) != L'\n' && wc != WEOF);
                while (task != 1 && task != 2 && task != 3 && task != 4 && task != 5 && task != 6 && task != 7 && task != 8){
                    printf("无效的任务编号，请重新选择：\n1-修改密码\n2-修改学生信息\n3-删除学生信息\n4-显示学生信息\n5-查询学生信息\n6-统计学生成绩\n7-汇总报表\n8-退出系统\n");
                    wscanf(L"%d", &task);
                    while ((wc = getwchar()) != L'\n' && wc != WEOF);
                }
                teacher(task);
                break;
        // case 3:
        //     printf("你好，辅导员\n");
        //     printf("请选择：\n1-修改本学院学生信息\n2-删除本学院学生信息\n3-添加本学院学生信息\n4-浏览全部学生信息\n");     
        //     while (scanf("%d", &task), task != 1 && task != 2 && task != 3 && task != 4){
        //         printf("无效的任务编号，请重新选择：");
        //     }
        //     instructor(task);
        //     break;
            case 3:
                printf("你好，学生。\n");
                printf("请选择：\n1-修改密码\n2-显示学生信息\n3-查询学生信息\n4-统计学生成绩\n5-退出系统\n");
                wscanf(L"%d", &task);
                while ((wc = getwchar()) != L'\n' && wc != WEOF);
                while (task != 1 && task != 2 && task != 3 && task != 4 &&  task != 5){
                    printf("无效的任务编号，请重新选择：\n1-修改密码\n2-显示学生信息\n3-查询学生信息\n4-统计学生成绩\n5-退出系统\n");
                    wscanf(L"%d", &task);
                    while ((wc = getwchar()) != L'\n' && wc != WEOF);
                }
                student(task);
                break;
        }
    }
    //提示已退出系统
    // printf("你已经退出学生成绩管理系统。\n");
    
    //退出系统
    // printf("你好，请输入账号和密码：\n");
    // exit(0);
    // gets(AccountName);
    // gets(Name);
    // gets(role);
    // gets(PassWord);
    // result = log_in(AccountName, Name, role, PassWord);

    // task = ChooseTask(role);
    return 0;
}



// 1录入学生信息 
// 2录入课程信息
// 3录入成绩
// 1修改学生信息
// 2修改课程信息
// 3修改平时成绩
// 4修改卷面成绩

// 1查询学生信息
// 2查询课程信息
// 3查询男女信息
//  4查询系信息
// 5查询学生成绩
// 6查询课程成绩
