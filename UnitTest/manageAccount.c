//添加管理员信息
#include <string.h>
#include <stdio.h>
#include "account.h"
#define MAX_LINE_LENGTH 256

void add_info(char* username, char* name, char* role){ //用户名和姓名
    // struct Account account;

    //以追加模式打开文件
    FILE *fp;
    fp = fopen("account_info.txt", "a");
    if (fp == NULL){
        printf("文件打开失败。\n");
        return;
    }

    fprintf(fp, "%s,%s,%s,%s\n", username, name, role, "12345");
    fclose(fp);
}

 //添加学生信息
// void add_stu_info(char* username, char* name){
    
// }


//修改管理员密码
void modify_password(char* username, char* name, char* new_password){

    FILE *fp;
    fp = fopen("account_info.txt", "r");
    if (fp == NULL){
        printf("文件打开失败。\n");
        return;
    }

    //读取文件并创建链表
    //修改链表的节点
    int modified = 0;
    char buffer[MAX_LINE_LENGTH], first_line[MAX_LINE_LENGTH];
    struct Account account;
    struct AccountNode *head = NULL, *last = NULL;

    fgets(first_line, sizeof(first_line), fp);
    while (fgets(buffer, sizeof(buffer), fp)){
        struct AccountNode * new_node = (struct AccountNode *)malloc(sizeof(struct AccountNode)); //创建链表
        if (sscanf(buffer, "%49[^,],%49[^,],%49[^,],%49[^\n]", new_node->account.user, new_node->account.name, new_node->account.role,  new_node->account.password) == 4){
            new_node->next = NULL;
            if (head == NULL) //只有头节点时
                head = new_node;
            else 
                last->next = new_node;//连接新节点
            last = new_node;//更新last指针
            last->next = NULL;

            if (strcmp(username, new_node->account.user) == 0 && strcmp(name, new_node->account.name) == 0){ //用户名和姓名匹配
                strcpy(new_node->account.password, new_password); //修改密码
                modified = 1;//标记修改成功
            }
            if (strcmp(username, new_node->account.user) != 0 && strcmp(name, new_node->account.name) == 0){
                printf("输入的用户名与姓名不一致，请重新输入。\n");
                break;
            }
            if (strcmp(username, new_node->account.user) == 0 && strcmp(name, new_node->account.name) != 0){
                printf("输入的用户名与姓名不一致，请重新输入。\n");
                break;
            }   
        }else{
            free(new_node);//释放多余内存
            break;
        }
    }
    fclose(fp);
    
    //重写文件
    fp = fopen("account_info.txt", "w");
    if (fp == NULL){
        printf("文件打开失败。\n");
        return;
    }
    struct AccountNode * current = head, * temp = NULL;
    fprintf(fp, "%s", first_line); //重写第一行
    while (current != NULL){
        fprintf(fp, "%s,%s,%s,%s\n", current->account.user, current->account.name, current->account.role, current->account.password); //写文件
        struct AccountNode * temp = current;
        current = current->next;
        free(temp); //释放该节点内存
        temp = NULL;
    }
    fclose(fp);

    if (!modified) {
        printf("输入的用户名或姓名错误或用户名与姓名不匹配，请重新输入。\n");
        return;
    }
}

int main(){
    char userName[50], name[50], role[50], newPassword[50], temp_new[50];
    int total; //记录添加信息的条数
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
    for (int i = 0; i < 2; i ++){ //多次输入管理员信息
        // add_info(userName, name, role);
        gets(userName); //老师的用户名为工号，学生的为学号
        gets(name);
        gets(newPassword);//第一次输入新密码
        for (int j = 0; j < strlen(newPassword); j ++){
            if ((newPassword[j] >= 'a' && newPassword[j] <= 'z') || (newPassword[j] >= '0' && newPassword[j] <= '9')){ //密码符合条件
                continue;
            }else{
                printf("密码不符合条件，密码不能含有特殊符号或大写字母。\n");
                return;
            }
        }
        
        modify_password(userName, name, newPassword); //寻找对应的账号
        strcpy(temp_new, newPassword);
        gets(newPassword);//再次输入新密码
        if (strcmp(newPassword, temp_new) == 0)
            printf("修改密码成功！\n");
        else{
            printf("第二次输入错误！\n");
            return;
        }   
    }
    
    return 0;
}