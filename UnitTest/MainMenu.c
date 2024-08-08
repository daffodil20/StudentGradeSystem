#include <stdio.h>
#include <string.h>
#include "account.h"
// TODO:新增,修改与删除账号
// TODO:录入信息的函数需要加上参数，把scanf放到main里，多次调用
//管理员可以添加其他人的信息，老师可以修改成绩，所有人都可以修改密码

void enterBar(int taskLabel){ 
    switch (taskLabel)
    {
    case 1:
        printf("这是录入学生基本信息的界面。");
        break;
    case 2:
        printf("这是录入课程基本信息的界面。");
        break;
    case 3:
        printf("这是录入学生成绩的界面。");
        break;   
    default:
        printf("无效的任务编号");
        break;
    }
}

void modifyBar(int taskLabel){
    switch (taskLabel)
    {
    case 1:
        printf("这是修改学生基本信息的界面。");
        break;
    case 2:
        printf("这是修改课程基本信息的界面。");
        break;
    case 3:
        printf("这是修改学生成绩的界面。");
        break;   
    default:
        printf("无效的任务编号");
        break;
    }
}

void deleteBar(int taskLabel){
    switch (taskLabel)
    {
    case 1:
        printf("这是删除学生基本信息的界面。");
        break;
    case 2:
        printf("这是删除课程基本信息的界面。");
        break;
    case 3:
        printf("这是删除学生成绩的界面。");
        break;   
    default:
        printf("无效的任务编号");
        break;
    }
}

void searchBar(int taskLabel){
    switch (taskLabel)
    {
    case 1:
        printf("这是查询学生基本信息的界面。");
        break;
    case 2:
        printf("这是查询课程基本信息的界面。");
        break;
    case 3:
        printf("这是按性别查询学生基本信息的界面。");
        break;
    case 4:
        printf("这是按系查询学生基本信息的界面。");
        break;
    case 5:
        printf("这是查询学生所有课程成绩的界面。");
        break;
    case 6:
        printf("这是查询课程所有学生成绩的界面。");
        break;   
    default:
        printf("无效的任务编号");
        break;
    }
}

void statBar(int taskLabel){ //统计成绩的选项
    switch (taskLabel)
    {
    case 1:
        printf("这是查询课程卷面成绩的平均分的界面。");
        break;
    case 2:
        printf("这是查询课程综合成绩的平均分的界面。");
        break;
    case 3:
        printf("这是查询课程卷面成绩的最高分的界面。");
        break;
    case 4:
        printf("这是查询课程综合成绩的最高分的界面。");
        break;
    case 5:
        printf("这是查询课程卷面成绩的分数段的界面。");
        break;
    case 6:
        printf("这是查询课程综合成绩所的分数段的界面。");
        break;   
    default:
        printf("无效的任务编号");
        break;
    }
}

void sumBar(int taskLabel){
    switch (taskLabel)
    {
    case 1:
        printf("这是显示课程及格情况的界面。");
        break;
    case 2:
        printf("这是显示学生成绩情况的界面。");
        break;
    default:
        printf("无效的任务编号");
        break;
    }
}


void manager(int task_num){
    int task_label;
    switch (task_num)
    {
    case 1:
        printf("这是添加用户信息的界面。\n");
        // return 1;
        break;
    case 2:
        printf("这是修改密码的界面。\n");
        // return 2;
        break;
    case 3:
        printf("这是录入学生信息的界面。\n");
        scanf("%d", &task_label);
        enterBar(task_label);
        break;
        // return 3;
    case 4:
        printf("这是修改学生信息的界面。\n");
        scanf("%d", &task_label);
        modifyBar(task_label);
        break;
        // return 4;
    case 5:
        printf("这是删除学生信息的界面。\n");
        scanf("%d", &task_label);
        deleteBar(task_label);
        break;
        // return 5;
    case 6:
        printf("这是查询学生信息的界面。\n");
        scanf("%d", &task_label);
        searchBar(task_label);
        break;
        // return 6;
    case 7:
        printf("这是显示全部学生信息的界面.\n");
        break;
        // return 7;
    case 8:
        printf("这是统计学生成绩的界面。\n");
        scanf("%d", &task_label);
        statBar(task_label);
        break;
        // return 8;
    case 9:
        printf("这是汇总报表的界面。\n");
        scanf("%d", &task_label);
        sumBar(task_label);
        break;
        // return 9;
    case 10:
        printf("这是退出系统的界面。\n");
        break;
        // return 10;
    default:
        printf("无效的任务编号\n");
        break;
    }
}

void teacher(int task_num){
    int task_label;
    switch (task_num)
    {
    case 1:
        printf("这是修改密码的界面.\n");
        break;
        // return 1;
    case 2:
        printf("这是修改学生信息的界面.\n");
        scanf("%d", &task_label);
        modifyBar(task_label);
        break;
        // return 2;
    case 3:
        printf("这是删除学生信息的界面.\n");
        scanf("%d", &task_label);
        deleteBar(task_label);
        break;
        // return 3;
    case 4:
        printf("这是显示全部学生信息的界面.\n");
        break;
        // return 4;    
    case 5:
        printf("这是查询学生信息的界面。\n");
        scanf("%d", &task_label);
        searchBar(task_label);
        break;
        // return 5;
    case 6:
        printf("这是统计学生成绩的界面。\n");
        scanf("%d", &task_label);
        statBar(task_label);
        break;
        // return 6;
    case 7:
        printf("这是汇总报表的界面。\n");
        scanf("%d", &task_label);
        sumBar(task_label);
        break;
        // return 7;
    case 8:
        printf("这是退出系统的界面。\n");
        // return 8;
        break;
    default:
        printf("无效的任务编号\n");
        break;
    }
}

// void instructor(int task_num){
//     switch (task_num)
//     {
//     case 1:
//         printf("这是修改本学院学生信息的界面.\n");
//         break;
//     case 2:
//         printf("这是删除本学院学生信息的界面.\n");
//         break;
//     case 3:
//         printf("这是添加本学院学生信息的界面.\n");
//         break;
//     case 4:
//         printf("这是浏览本学院学生信息的界面.\n");
//         break;
//     }
// }

void student(int task_num){
    int task_label;
    switch (task_num)
    {
    case 1:
        printf("这是显示本班学生信息的界面.\n");
        break;
        // return 1;
    case 2:
        printf("这是查询学生信息的界面.\n");
        scanf("%d", &task_label);
        searchBar(task_label);
        break;
        // return 2;
    case 3:
        printf("这是统计学生成绩的界面。\n");
        scanf("%d", &task_label);
        statBar(task_label);
        break;
        // return 3;
    case 4:
        printf("这是退出系统的界面。\n");
        break;
        // return 4;
    default:
        printf("无效的任务编号\n");
        break;
    }
}

int log_in(char *account_name, char *name, char *role, char *password){ //用户登录
    struct Account account;
    //判断密码是否存在
    // if (strcmp(password, "12345") != 0){
        //printf("password:%s",password);
    //     return 1;
    // }
    //读文件，判断账号是否存在
    char buffer[300];
    int start = 0, end = 0, i, j = 0;
    
    //打开账号文件
    FILE* fp;
    fp = fopen("account_info.txt","r");
    if (fp == NULL){
        printf("文件打开失败\n");
        // exit();
        //exit();
    }

    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        if (sscanf(buffer, "%49[^,],%49[^,],%49[^,],%49[^\n]", account.user, account.name, account.role, account.password) == 4){
            if (strcmp(account_name, account.user) == 0){ //比较其他信息
                if (strcmp(name, account.name) != 0 || strcmp(role, account.role) != 0 || strcmp(password, account.password) != 0){
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
    int choice_num, role_num, task;
    char AccountName[50],PassWord[50], role[50], Name[50];
    int result;
    // int AccountIdx = 1;
    //登录
    printf("你好，请输入账号和密码：\n");
    // scanf("%s",AccountName);
    gets(AccountName);
    gets(Name);
    gets(role);
    gets(PassWord);
    // scanf("%s",PassWord);
    result = log_in(AccountName, Name, role, PassWord);
    if (result == 0){
        printf("恭喜，登录成功!\n");
        if (strcmp(role, "manager") == 0)
            role_num = 1;
        else if (strcmp(role, "teacher") == 0)
            role_num = 2;
        else if (strcmp(role, "student") == 0)
            role_num = 3;
    }
    if (result == 1)
        printf("姓名/角色/密码错误，请重新输入(默认为12345)。\n");
    // if (result == 2)
    //     printf("账号不存在，请重新输入。\n");

    //选择角色+任务
    // scanf("%d",&role_num);
    // while (role_num != 1 && role_num != 2 && role_num != 3){
    //     printf("输入错误\n请选择1-超级管理员\n2-老师\n3-学生\n");
    //     scanf("%d",&role_num);
    // }
    // role_num = ChooseRole(role);
    switch (role_num){
        case 1:
            printf("你好，超级管理员\n");
            printf("请选择：\n1-添加用户信息\n2-修改密码\n3-录入学生信息\n4-修改学生信息\n5-删除学生信息\n6-查询学生信息\n7-显示学生信息\n8-统计学生成绩\n9-汇总报表\n10-退出系统\n");
            while (scanf("%d", &task), task != 1 && task != 2 && task != 3 && task != 4 && task != 5 && task != 6 && task != 7 && task != 8 && task != 9 && task != 10){
                 printf("无效的任务编号，请重新选择：");
            }
            manager(task);
            break; 
        case 2:
            printf("你好，老师\n");
            printf("请选择：\n1-修改密码\n2-修改学生信息\n3-删除学生信息\n4-查询学生信息\n5-显示学生信息\n6-统计学生成绩\n7-汇总报表\n8-退出系统\n");      
            while (scanf("%d", &task), task != 1 && task != 2 && task != 3 && task != 4 && task != 5 && task != 6 && task != 7 && task != 8){
                printf("无效的任务编号，请重新选择：");
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
            printf("你好，学生\n");
            printf("请选择：\n1-修改密码\n2-查询学生信息\n3-显示学生信息\n4-统计学生成绩\n5-退出系统\n");
            while (scanf("%d", &task), task != 1 && task != 2 && task != 3 && task != 4 &&  task != 5){
                printf("无效的任务编号，请重新选择：");
            }
            student(task);
            break;
    }
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
