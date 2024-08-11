// #include <stdio.h>
// // void RecordPassWord(){
// //     FILE *fp;
// //     fp = fopen("account_info.txt","a+");
// //     if (fp == NULL)
// //         printf("文件不存在");
// //     char password[20], account[20];
// //     //输入账号和密码
// //     scanf("%s",account);
// //     scanf("%s",password);
// //     fprintf(fp, "account:%s|password:%s\n", account, password);//写文件
// //     fprintf(fp, L"账号密码");
// //     fclose(fp);

// // }
// // int main(){
// //     RecordPassWord();
    
// //     return 0;
// // }

// void modify_course0(int item, char* idx, char* new_info){ //修改课程信息,total是修改课程哪个item的标记
//     #define MAX_LINE_LENGTH 256
//     FILE *fp;
//     char buffer[MAX_LINE_LENGTH];
//     char *lines[MAX_LINE_LENGTH];
//     int line_count = 0;

//     // 读取文件内容到内存
//     fp = fopen("course.txt", "r");
//     if (fp == NULL) {
//         printf("文件打开失败\n");
//         return;
//     }

//     while (fgets(buffer, sizeof(buffer), fp) != NULL) {    
//         lines[line_count] = strdup(buffer); // 保存每一行到内存
//         line_count++;
//     }
//     fclose(fp);

//     // 打开文件以修改数据
//     fp = fopen("course.txt", "w");
//     if (fp == NULL) {
//         printf("文件打开失败\n");
//         return;
//     }

//     int modified = 0;
//     //逐行读文件，比较学号
//     for (int i = 0; i < line_count; i ++){
//         char course_idx[50];
//         sscanf(lines[i], "%49[^,]", course_idx);//读取新学号到字符串
//         if (strcmp(idx, course_idx) == 0){
//             char* rest_of_line = strchr(lines[i], ',');
//             if (item == 1){
//                 // char* rest_of_line = strchr(lines[i], ','); // 找到逗号的位置
//                 if (rest_of_line){
//                     rest_of_line++; // 移动到逗号后面的第一个字符
//                     char new_line[MAX_LINE_LENGTH];
//                     snprintf(new_line, sizeof(new_line), "%s,%s", new_info, rest_of_line); // 构造新的行
//                 }
//                     // if (rest_of_line) {
//                     //     rest_of_line++; // 移动到逗号后面的第一个字符
//                     //     char new_line[MAX_LINE_LENGTH];
//                     //     snprintf(new_line, sizeof(new_line), "%s,%s", new_info, rest_of_line); // 构造新的行
//                     //     free(lines[i]); // 释放旧行的内存
//                     //     lines[i] = strdup(new_line); // 用新行替换
//                     //     modified = 1; // 设置修改标记
//                     // }
//             }else{
//                 // char* rest_of_line = strchr(lines[i], ','); // 找到逗号的位置
//                 if (rest_of_line) {
//                     for (i = 0; i < item - 1; i ++)
//                         rest_of_line = strchr(rest_of_line + 1, ',');
//                     rest_of_line++; // 移动到逗号后面的第一个字符
//                     char new_line[MAX_LINE_LENGTH];
//                     if (item == 2)
//                         snprintf(new_line, sizeof(new_line), "%s,%s,%s", idx, new_info, rest_of_line); // 构造新的行
//                     if (item == 3)
//                         fscanf()
//                         snprintf(new_line, sizeof(new_line), "%s,%s,%s", idx, new_info);
//                         // char new_line[MAX_LINE_LENGTH];
//                         // snprintf(new_line, sizeof(new_line), "%s,%s", new_info, rest_of_line); // 构造新的行
//                         // free(lines[i]); // 释放旧行的内存
//                         // lines[i] = strdup(new_line); // 用新行替换
//                         // modified = 1; // 设置修改标记
//                 }
//             }
//             // rest_of_line ++; // 移动到逗号后面的第一个字符
            
//             free(lines[i]); // 释放旧行的内存
//             lines[i] = strdup(new_line); // 用新行替换
//             modified = 1; // 设置修改标记                             
//         }       
//     }
    
//     //查找失败
//     if (!modified){
//         printf("输入的课号不存在，请重新输入。\n");
//         return;
//     }

//     //将内存写回文件
//     for (int i = 0; i < line_count; i ++){
//         fprintf(fp, "%s", lines[i]);
//         free(lines[i]);//释放内存
//     }
//     fclose(fp);
// }

// int main(){
//     int i;
//     char idx[50], NewInfo[100];
//     scanf("%d", &i);
//     gets(NewInfo);
//     modify_course0(i, idx, NewInfo);

//     return 0;
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "score.h"  // 假设你有一个 "score.h" 头文件

// #define MAX_LINE_LENGTH 256

// void modify_course0(int item, char* idx, char* new_info) {
//     FILE *fp;
//     char buffer[MAX_LINE_LENGTH];
//     char *lines[MAX_LINE_LENGTH];
//     int line_count = 0;

//     // 读取文件内容到内存
//     fp = fopen("course.txt", "r");
//     if (fp == NULL) {
//         printf("文件打开失败\n");
//         return;
//     }

//     while (fgets(buffer, sizeof(buffer), fp) != NULL) {
//         lines[line_count] = strdup(buffer); // 保存每一行到内存
//         line_count++;
//     }
//     fclose(fp);

//     // 打开文件以修改数据
//     fp = fopen("course.txt", "w");
//     if (fp == NULL) {
//         printf("文件打开失败\n");
//         return;
//     }

//     int modified = 0;
//     for (int i = 0; i < line_count; i++) {
//         char course_idx[50];
//         sscanf(lines[i], "%49[^,]", course_idx); // 读取课程编号
//         if (strcmp(idx, course_idx) == 0) {
//             char *token;
//             char *tokens[10];
//             int token_count = 0;

//             // 分割行并存储各列数据
//             token = strtok(lines[i], ",");
//             while (token != NULL && token_count < 10) {
//                 tokens[token_count++] = token;
//                 token = strtok(NULL, ",");
//             }

//             // 确保item在范围内
//             if (item < 1 || item > token_count) {
//                 printf("指定的项不存在\n");
//                 return;
//             }

//             // 替换指定的项
//             tokens[item - 1] = new_info;

//             // 重新构建行数据
//             char new_line[MAX_LINE_LENGTH] = "";
//             for (int j = 0; j < token_count; j++) {
//                 strcat(new_line, tokens[j]);
//                 if (j < token_count - 1) {
//                     strcat(new_line, ",");
//                 }
//             }
//             strcat(new_line, "\n");

//             // 替换旧行
//             free(lines[i]);
//             lines[i] = strdup(new_line);

//             modified = 1;
//             break;
//         }
//     }

//     if (!modified) {
//         printf("输入的课号不存在，请重新输入。\n");
//     } else {
//         // 将内存写回文件
//         for (int i = 0; i < line_count; i++) {
//             fprintf(fp, "%s", lines[i]);
//             free(lines[i]); // 释放内存
//         }
//     }
//     fclose(fp);
// }

// int main() {
//     int item;
//     char idx[50], new_info[50];
//     printf("请输入要修改的项号（例如：1 2 3 4）以及课程编号和新的信息（中间用空格隔开）：\n");
    
//     gets(idx);
//     gets(new_info);
//     scanf("%d", &item);
//     modify_course0(item, idx, new_info);

//     return 0;
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "course.h"
// #include "score.h"  // 假设你有一个 "score.h" 头文件
// #include "account.h"

// #define MAX_LINE_LENGTH 256

// void modify_course0(char* idx, char* new_info, int item) {
//     FILE *fp;
//     char buffer[MAX_LINE_LENGTH];
//     char *lines[MAX_LINE_LENGTH];
//     int line_count = 0;

//     // 读取文件内容到内存
//     fp = fopen("course.txt", "w+");
//     if (fp == NULL) {
//         printf("文件打开失败\n");
//         return;
//     }

//     // while (fgets(buffer, sizeof(buffer), fp) != NULL) {
//     //     lines[line_count] = strdup(buffer); // 保存每一行到内存
//     //     line_count++;
//     // }
//     // fclose(fp);

//     // 打开文件以修改数据
//     // fp = fopen("course.txt", "w");
//     // if (fp == NULL) {
//     //     printf("文件打开失败\n");
//     //     return;
//     // }
//     int line_counter = 0, modified = 0;
//     struct Course course;
//     struct CourseNode *head = NULL, *p = NULL, *last = NULL;
//     // struct CourseNode *CurP = head;//头指针 current pointer
//     // CurrentP = head;

//     //创建链表
    
//     // while (1){
//     //     p = (struct CourseNode *)malloc(sizeof(struct CourseNode));
        
//     // }
//     //创建链表、逐行读文件并修改
//     while (fscanf(fp, "%s,%s,%s", course.index, course.name, course.teacher) == 3){
//         line_counter ++;
//         if (line_counter > 1){
//             p = (struct CourseNode *)malloc(sizeof(struct CourseNode));
//             strcpy(p->course[0], course.index);
//             strcpy(p->course[1], course.name);
//             strcpy(p->course[2], course.teacher);
//             p->next = NULL; //初始化新的节点

//             if (last == NULL)//只有一个节点
//                 head = p;
//             else
//                 last->next = p;//加入新节点
//             last = p;//更新末尾节点的值

//             if (strcmp(course.index, idx) == 0){ //修改数据
//                 strcpy(p->course[item], new_info);
//                 modified = 1;
//             }

//             //写回文件
//             fprintf(fp, "%s,%s,%s\n", p->course[0], p->course[1], p->course[2]);
//         }
//     }

//     //修改
//     // int modified = 0;
//     // while (CurP != NULL){
//     //     if (CurP->course[0] == idx){
//     //         CurP->course[item] = new_info;//修改课程数据
//     //         modified = 1;//修改标记
//     //         break;
//     //     }
//     //     CurP = CurP->next;
//     // }
    

//     // int modified = 0;
//     // for (int i = 0; i < line_count; i++) {
//     //     char course_idx[50];
//     //     sscanf(lines[i], "%49[^,]", course_idx); // 读取课程编号
//     //     if (strcmp(idx, course_idx) == 0) {
//     //         char *token;
//     //         char *tokens[10];
//     //         int token_count = 0;

//     //         // 分割行并存储各列数据，去除末尾换行符
//     //         token = strtok(lines[i], ",\n");
//     //         while (token != NULL && token_count < 10) {
//     //             tokens[token_count++] = token;
//     //             token = strtok(NULL, ",\n");
//     //         }

//     //         // 确保item在范围内
//     //         if (item < 1 || item > token_count) {
//     //             printf("指定的项不存在\n");
//     //             return;
//     //         }

//     //         // 替换指定的项
//     //         tokens[item - 1] = new_info;

//     //         // 重新构建行数据
//     //         char new_line[MAX_LINE_LENGTH] = "";
//     //         for (int j = 0; j < token_count; j++) {
//     //             strcat(new_line, tokens[j]);
//     //             if (j < token_count - 1) {
//     //                 strcat(new_line, ",");
//     //             }
//     //         }
//     //         strcat(new_line, "\n");

//     //         // 替换旧行
//     //         free(lines[i]);
//     //         lines[i] = strdup(new_line);

//     //         modified = 1;
//     //         break;
//     //     }
//     // }

//     // if (!modified) {
//     //     printf("输入的课号不存在，请重新输入。\n");
//     // } else {
//     //     // 将内存写回文件
//     //     for (int i = 0; i < line_count; i++) {
//     //         fprintf(fp, "%s", lines[i]);
//     //         free(lines[i]); // 释放内存
//     //     }
//     // }
//     fclose(fp);
// }

// int main() {
//     int item;
//     char idx[50], new_info[50];
//     printf("请输入要修改的项号（例如：1 2 3 4）以及课程编号和新的信息（中间用空格隔开）：\n");
    
    
//     gets(idx);
//     gets(new_info);
//     scanf("%d", &item);
//     modify_course0(idx, new_info, item);

//     return 0;
// }

// 修改课程数据的函数
// void modify_course0(char* idx, char* new_info, int item) {
//     FILE *fp;
//     struct CourseNode *head = NULL, *last = NULL;
//     int modified = 0;

//     // 读取文件内容到链表
//     fp = fopen("course.txt", "r");
//     if (fp == NULL) {
//         printf("文件打开失败\n");
//         return;
//     }

//     // 跳过第一行
//     char first_line[MAX_LINE_LENGTH];
//     if (fgets(first_line, sizeof(first_line), fp) == NULL) {
//         printf("无法读取文件或文件为空\n");
//         fclose(fp);
//         return;
//     }

//     // 逐行读取文件并创建链表
//     char line[MAX_LINE_LENGTH];
//     while (fgets(line, sizeof(line), fp)) {
//         struct CourseNode *new_node = (struct CourseNode *)malloc(sizeof(struct CourseNode));
//         if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", 
//                    new_node->course.index, 
//                    new_node->course.name, 
//                    new_node->course.teacher) == 3) {
//             new_node->next = NULL;
//             if (head == NULL) {
//                 head = new_node;
//             } else {
//                 last->next = new_node;
//             }
//             last = new_node;
//             printf("index:%s name:%s teacher:%s\n", new_node->course.index, 
//                    new_node->course.name, 
//                    new_node->course.teacher);
//             // 查找并修改数据
//             if (strcmp(new_node->course.index, idx) == 0) {
//                 if (item == 1) strcpy(new_node->course.index, new_info);
//                 else if (item == 2) strcpy(new_node->course.name, new_info);
//                 else if (item == 3) strcpy(new_node->course.teacher, new_info);
//                 else printf("修改项不存在\n");
//                 modified = 1;
//             }
//         } else {
//             free(new_node); // 释放未用的内存
//             break; // 结束循环
//         }
//     }
//     fclose(fp);

//     // 写回文件
//     fp = fopen("course.txt", "w");
//     if (fp == NULL) {
//         printf("文件打开失败\n");
//         return;
//     }

//     // 重新写入第一行
//     fprintf(fp, "%s", first_line);

//     struct CourseNode *current = head;
//     while (current != NULL) {
//         fprintf(fp, "%s,%s,%s\n", 
//                 current->course.index, 
//                 current->course.name, 
//                 current->course.teacher);
//         struct CourseNode *temp = current;
//         current = current->next;
//         free(temp); // 释放节点内存
//         temp = NULL;
//     }
//     fclose(fp);

//     if (!modified) {
//         printf("输入的课号不存在，请重新输入。\n");
//     }
// }

// int log_in(char *account_name, char *name, char *role, char *password){ //用户登录
//     struct Account account;
//     //判断密码是否存在
//     // if (strcmp(password, "12345") != 0){
//         //printf("password:%s",password);
//     //     return 1;
//     // }
//     //读文件，判断账号是否存在
//     char buffer[300];
//     int start = 0, end = 0, i, j = 0;
    
//     //打开账号文件
//     FILE* fp;
//     fp = fopen("account_info.txt","r");
//     if (fp == NULL){
//         printf("文件打开失败\n");
//         return;
//         //exit();
//     }

//     fgets(buffer, sizeof(buffer), fp);
//     while (fgets(buffer, sizeof(buffer), fp) != NULL){
//         if (sscanf(buffer, "%49[^,],%49[^,],%49[^,],%49[^\n]", account.user, account.name, account.role, account.password) == 4){
//             if (strcmp(account_name, account.user) == 0){ //比较其他信息
//                 if (strcmp(name, account.name) != 0 || strcmp(role, account.role) != 0 || strcmp(password, account.password) != 0){
//                     printf("信息错误!\n");
//                     break;
//                 }else{
//                     printf("登录成功!\n");
//                     return 0;
//                 } 
//             }
//         }

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
    // }
    
    // return 1;//账号与其他信息不匹配
    //关闭文件
    // fclose(fp);

    // account_idx ++;
    // return account_idx;//返回账号序号
// }


#include <stdlib.h>
#include <string.h>
#include "course.h"
#include "score.h"  // 假设你有一个 "score.h" 头文件
#include "account.h"
#include <stdio.h>
#include "modify.h"
#include "search.h"
int main() {
    char idx[50], new_info[50], id[50], gender[50], profession[50];
    char account[50], name[50], role[50], password[50];
    // char space = ' ';
    int item;
    double newGrade;
    // printf("请输入课程编号、新信息和要修改的项（1: 课号, 2: 名称，3：老师）：\n");
    // gets(account);
    // gets(password);
    // scanf("%d ", &item);
    // gets(id);
    gets(idx);
    gets(name);
    // gets(profession);
    // gets(new_info);
    // scanf("%lf", &newGrade);
    
    // scanf("%d", &item);
    // modify_course0(idx, new_info, item);
    // scanf("%d ", &item);
    // gets(space);
    // gets(account);
    // printf("%d\n", item);
    // printf("%s", account);
    // modify_course(idx, name, new_info, item);
    // modify_score0(account, password, id, idx, newGrade);
    // find_stu(id, name);
    // find_course(idx, name);
    // find_gender(gender);
    // find_profession(profession);
    // find_score0(id, name);
    find_score1(idx, name);
    // gets(name);
    // gets(role);
    // gets(password);
    // log_in(account, name, role, password);
    
    return 0;
}