#include <stdio.h>
#include <string.h>
#include "account.h"
// TODO:新增,修改与删除账号
// TODO:录入信息的函数需要加上参数，把scanf放到main里，多次调用
//管理员可以添加其他人的信息，老师可以修改成绩，所有人都可以修改密码
void manager(int task_num){
    switch (task_num)
    {
    case 1:
        printf("这是录入学生信息的界面.\n");
        break;
    case 2:
        printf("这是修改学生信息的界面.\n");
        break;
    case 3:
        printf("这是删除学生信息的界面.\n");
        break;
    case 4:
        printf("这是浏览学生信息的界面.\n");
        break;
    case 5:
        printf("这是统计学生信息的界面.\n");
        break;
    case 6:
        printf("这是汇总报表的界面.\n");
        break;
    }
}

void class_teacher(int task_num){
    switch (task_num)
    {
    case 1:
        printf("这是修改本班学生信息的界面.\n");
        break;
    case 2:
        printf("这是删除本班学生信息的界面.\n");
        break;
    case 3:
        printf("这是添加本班学生信息的界面.\n");
        break;
    case 4:
        printf("这是浏览本班学生信息的界面.\n");
        break;
    }
}

void instructor(int task_num){
    switch (task_num)
    {
    case 1:
        printf("这是修改本学院学生信息的界面.\n");
        break;
    case 2:
        printf("这是删除本学院学生信息的界面.\n");
        break;
    case 3:
        printf("这是添加本学院学生信息的界面.\n");
        break;
    case 4:
        printf("这是浏览本学院学生信息的界面.\n");
        break;
    }
}

void student(int task_num){
    switch (task_num)
    {
    case 1:
        printf("这是浏览本班学生信息的界面.\n");
        break;
    case 2:
        printf("这是查询本班部分学生信息的界面.\n");
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
        return;
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
    int choice_num, role_num, task, role;
    char AccountName[20],PassWord[20];
    int result;
    // int AccountIdx = 1;
    //登录
    printf("你好，请输入账号和密码：\n");
    scanf("%s",AccountName);
    scanf("%s",PassWord);
    result = log_in(AccountName, PassWord, role, PassWord);
    if (result == 0)
        printf("恭喜，登录成功!\n");
    if (result == 1)
        printf("姓名/角色/密码错误，请重新输入(默认为12345)。\n");
    // if (result == 2)
    //     printf("账号不存在，请重新输入。\n");

    //选择角色+任务
    scanf("%d",&role);
    while (role != 1 && role != 2 && role != 3 && role != 4){
        printf("输入错误\n请选择1-超级管理员\n2-班导师\n3-辅导员\n4-学生\n");
        scanf("%d",&role);
    }
    // role_num = ChooseRole(role);
    switch (role){
        case 1:
            printf("你好，超级管理员\n");
            printf("请选择：\n1-录入全部学生信息\n2-修改学生信息\n3-删除学生信息\n4-浏览学生信息\n5-统计学生信息\n6-汇总报表\n");
            while (scanf("%d", &task), task != 1 && task != 2 && task != 3 && task != 4 && task != 5 && task != 6 ){
                 printf("无效的任务编号，请重新选择：");
            }
            manager(task);
            break; 
        case 2:
            printf("你好，班导师\n");
            printf("请选择：\n1-修改本班学生信息\n2-删除本班学生信息\n3-添加本班学生信息\n4-浏览本学院学生信息\n");      
            while (scanf("%d", &task), task != 1 && task != 2 && task != 3 && task != 4){
                printf("无效的任务编号，请重新选择：");
            }
            class_teacher(task);
            break;
        case 3:
            printf("你好，辅导员\n");
            printf("请选择：\n1-修改本学院学生信息\n2-删除本学院学生信息\n3-添加本学院学生信息\n4-浏览全部学生信息\n");     
            while (scanf("%d", &task), task != 1 && task != 2 && task != 3 && task != 4){
                printf("无效的任务编号，请重新选择：");
            }
            instructor(task);
            break;
        case 4:
            printf("你好，学生\n");
            printf("请选择：\n1-浏览本班学生信息\n2-查询本班某些学生信息\n");
            while (scanf("%d", &task), task != 1 && task != 2){
                printf("无效的任务编号，请重新选择：");
            }
            student(task);
            break;
    }
    // task = ChooseTask(role);
    return 0;
}
