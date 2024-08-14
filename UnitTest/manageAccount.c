//添加管理员信息
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "account.h"
// #include "manageAccount.h"
#include "student.h"
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include "course.h"
#include "score.h"
#include <fcntl.h>
#define MAX_LINE_LENGTH 256

void add_info(wchar_t* username, wchar_t* name, wchar_t* role){ //用户名和姓名
    // struct Account account;

    //以追加模式打开文件
    FILE *fp;
    fp = fopen("account_info.txt", "a");
    if (fp == NULL){
        printf("文件打开失败。\n");
        return;
    }

    fwprintf(fp, L"%ls,%ls,%ls,%ls\n", username, name, role, L"12345");
    fclose(fp);
}

//修改管理员密码
int modify_password(wchar_t* username, wchar_t* name, wchar_t* new_password){
    //判断密码是否符合要求
    if (wcslen(new_password) != 5){
        printf("密码不符合要求，密码长度必须为5。请重新输入用户名、姓名和新密码：\n");
        return 1;
    }

    for (int j = 0; j < wcslen(new_password); j ++){
        if ((new_password[j] >= L'a' && new_password[j] <= L'z') || (new_password[j] >= L'0' && new_password[j] <= L'9')){ //密码符合条件
            continue;
        }else{
            printf("密码不符合要求，密码不能含有特殊符号和大写字母。请重新输入用户名、姓名和新密码：\n");
            return 1;
        }
    }

    FILE *fp;
    fp = fopen("account_info.txt", "r");
    if (fp == NULL){
        printf("文件打开失败。\n");
        return 1;
    }

    //读取文件并创建链表
    //修改链表的节点
    int modified = 0;
    char buffer[MAX_LINE_LENGTH], first_line[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    struct Account account;
    struct AccountNode *head = NULL, *last = NULL;
    
    fgets(buffer, sizeof(buffer), fp);//跳过表头
    while (fgets(buffer, sizeof(buffer), fp)){
        struct AccountNode * new_node = (struct AccountNode *)malloc(sizeof(struct AccountNode)); //创建链表
        mbstowcs(wbuffer, buffer, sizeof(buffer) / sizeof(wchar_t));
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^\n]", new_node->account.user, new_node->account.name, new_node->account.role,  new_node->account.password) == 4){
            new_node->next = NULL;
            if (head == NULL) //只有头节点时
                head = new_node;
            else 
                last->next = new_node;//连接新节点
            last = new_node;//更新last指针
            last->next = NULL;

            if (wcscmp(username, new_node->account.user) == 0 && wcscmp(name, new_node->account.name) == 0){ //用户名和姓名匹配
                wcscpy(new_node->account.password, new_password); //修改密码
                // modified = 1;//标记修改成功
            }
            if (wcscmp(username, new_node->account.user) != 0 && wcscmp(name, new_node->account.name) == 0){
                printf("输入的用户名与姓名不一致，请重新输入用户名、姓名和新密码。\n");
                return 1;
                // break;
            }
            if (wcscmp(username, new_node->account.user) == 0 && wcscmp(name, new_node->account.name) != 0){
                printf("输入的用户名与姓名不一致，请重新输入用户名、姓名和新密码。\n");
                return 1;
                // break;
            }   
        }else{
            free(new_node);//释放多余内存
            break;
        }
    }
    fclose(fp);

    // if (!modified) {
    //     printf("输入的用户名或姓名错误或用户名与姓名不匹配，请重新输入。\n");
    //     return;
    // }
    
    //重写文件
    fp = fopen("account_info.txt", "w");
    if (fp == NULL){
        printf("文件打开失败。\n");
        return 1;
    }
    struct AccountNode * current = head, * temp = NULL;
    fwprintf(fp, L"用户名,姓名,角色,密码\n"); //重写表头
    while (current != NULL){
        fwprintf(fp, L"%ls,%ls,%ls,%ls\n", current->account.user, current->account.name, current->account.role, current->account.password); //写文件
        struct AccountNode * temp = current;
        current = current->next;
        free(temp); //释放该节点内存
        temp = NULL;
    }
    fclose(fp);
    return 0;
}

//TODO:把修改密码时输入密码不符合条件写道函数里，不能在main里
int main(){
    wchar_t userName[50], name[50], role[50], newPassword[50], temp_new[50];
    int total, passLabel; //记录添加信息的条数和是否正确修改密码
    setlocale(LC_ALL, "");
    _setmode( _fileno( stdin ), _O_WTEXT );
    // gets(userName); //老师的用户名为工号，学生的为学号
    // gets(name);
    // gets(newPassword);
    // // gets(role);
    // scanf("%d", &total);
    // fgets(userName, sizeof(userName), stdin);
    // printf("username:%s", userName);
    // fgets(name, sizeof(name), stdin);
    // printf("name:%s", name);
    // fgets(role, sizeof(role), stdin);
    // printf("role:%s", role);
    // scanf("%d ", &total);
    // wscanf(L"用户名,姓名,角色,密码\n");
    fgetws(userName, sizeof(userName), stdin);
    userName[wcslen(userName) - 1] = L'\0';
    fgetws(name, sizeof(name), stdin);
    name[wcslen(name) - 1] = L'\0';
    // fgetws(, sizeof(userName), stdin);
    // fgetws(role, sizeof(role), stdin);
    // role[wcslen(role) - 1] = L'\0';
    fgetws(newPassword, sizeof(newPassword), stdin);
    newPassword[wcslen(newPassword) - 1] = L'\0';

    // FILE *fp;
    // fp = fopen("account_info.txt", "a");
    
    // fwprintf(fp, L"用户名,姓名,角色,密码\n");
    // add_info(userName, name, role);
    modify_password(userName, name, newPassword);
    // fclose(fp);
    // for (int i = 0; i < total; i ++){ //多次输入管理员信息
    //     // add_info(userName, name, role);
    //     gets(userName); //老师的用户名为工号，学生的为学号
    //     gets(name);
    //     gets(newPassword);//第一次输入新密码
    //     //判断密码长度
    //     // for (int j = 0; j < strlen(newPassword); j ++){
    //     //     if ((newPassword[j] >= 'a' && newPassword[j] <= 'z') || (newPassword[j] >= '0' && newPassword[j] <= '9')){ //密码符合条件
    //     //         continue;
    //     //     }else{
    //     //         printf("密码不符合条件，密码不能含有特殊符号或大写字母。请重新输入信息：\n");
    //     //         i --;
    //     //         break;
    //     //     }
    //     // }
    //     passLabel = modify_password(userName, name, newPassword);
    //     if (passLabel == 0){ //寻找对应的账号
    //         strcpy(temp_new, newPassword);
    //         printf("请再次输入新密码以确认：\n");
    //         gets(newPassword);//再次输入新密码
    //         if (strcmp(newPassword, temp_new) == 0)
    //             printf("修改密码成功！\n");
    //         else{
    //             printf("第二次输入错误！请重新输入用户名、姓名和新密码：\n");
    //             i --;
    //         }
    //     }else{
    //        i --;
    //     }   
    // }
    
    return 0;
}