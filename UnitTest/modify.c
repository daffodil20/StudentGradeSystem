#include <stdio.h>
#include "student.h"
#include <locale.h>
//#include <wchar.h>
#include <string.h>
#include "course.h"
#include "score.h"
#include <stdlib.h>

// TODO: 根据姓名与课名修改
// TODO: (possible)变量全局化
// void modify_stu0(char* old_id, char* new_id){ //修改学生学号
//     //r+打开文件
//     // FILE *fp;
//     // fp = fopen("student.txt", "r+");

//     // //读文件，查找学生
//     // char identity[50];
//     // while (fscanf(fp, "%s", identity) == 1){
//     //     if (strcmp(identity, stu_info) == 0){//匹配成功
//     //         //修改学生信息
//     //         for (int i = 0; i < strlen(identity); i ++){ //清空identity
//     //             identity[i] = ' ';
//     //         }
//     //         scanf("%s", identity);
//     //         fprintf(fp, "%s", identity);
//     //         fclose(fp);
//     //         return;
//     //     }         
//     // }

//     // //查找失败
//     // printf("抱歉，该学号不存在，请重新输入。\n");
//     // scanf("%s", stu_info);
//     // modify_stu(stu_info);//重新查找

//     #define MAX_LINE_LENGTH 256
//     FILE *fp;
//     char buffer[MAX_LINE_LENGTH];
//     char *lines[MAX_LINE_LENGTH];
//     int line_count = 0;

//     // 读取文件内容到内存
//     fp = fopen("student.txt", "r");
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
//     fp = fopen("student.txt", "w");
//     if (fp == NULL) {
//         printf("文件打开失败\n");
//         return;
//     }

//     //逐行读文件，比较学号
//     int modified = 0;
//     for (int i = 0; i < line_count; i ++){
//         char id[50];
//         sscanf(lines[i], "%49[^,]", id);//读取新学号到字符串
//         if (strcmp(old_id, id) == 0){
//         //     char* rest_of_line = strchr(lines[i], ',');
//         //     sprintf(lines[i], "%s%s", new_id, rest_of_line);//存储新学号
//         //     printf("lines[%d]:%s\n",i,lines[i]);
//         //     modified = 1;//修改的标记
//         //     break;//后面的不需要遍历
//             char* rest_of_line = strchr(lines[i], ','); // 找到逗号的位置
//             if (rest_of_line) {
//                 rest_of_line++; // 移动到逗号后面的第一个字符
//                 char new_line[MAX_LINE_LENGTH];
//                 snprintf(new_line, sizeof(new_line), "%s,%s", new_id, rest_of_line); // 构造新的行
//                 free(lines[i]); // 释放旧行的内存
//                 lines[i] = strdup(new_line); // 用新行替换
//                 modified = 1; // 设置修改标记
//             }
//         }
//         // }
        
//     }
    
//     //查找失败
//     if (!modified){
//         printf("输入的学号不存在，请重新输入。\n");
//         return;
//     }

//     //将内存写回文件
//     for (int i = 0; i < line_count; i ++){
//         fprintf(fp, "%s", lines[i]);
//         free(lines[i]);//释放内存
//     }
//     fclose(fp);
// }

#define MAX_LINE_LENGTH 256

void modify_course0(int item, char* idx, char* new_info) {
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    char *lines[MAX_LINE_LENGTH];
    int line_count = 0;

    // 读取文件内容到内存
    fp = fopen("course.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        lines[line_count] = strdup(buffer); // 保存每一行到内存
        line_count++;
    }
    fclose(fp);

    // 打开文件以修改数据
    fp = fopen("course.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    int modified = 0;
    for (int i = 0; i < line_count; i++) {
        char course_idx[50];
        sscanf(lines[i], "%49[^,]", course_idx); // 读取课程编号
        if (strcmp(idx, course_idx) == 0) {
            char *token;
            char *tokens[10];
            int token_count = 0;

            // 分割行并存储各列数据，去除末尾换行符
            token = strtok(lines[i], ",\n");
            while (token != NULL && token_count < 10) {
                tokens[token_count++] = token;
                token = strtok(NULL, ",\n");
            }

            // 确保item在范围内
            if (item < 1 || item > token_count) {
                printf("指定的项不存在\n");
                return;
            }

            // 替换指定的项
            tokens[item - 1] = new_info;

            // 重新构建行数据
            char new_line[MAX_LINE_LENGTH] = "";
            for (int j = 0; j < token_count; j++) {
                strcat(new_line, tokens[j]);
                if (j < token_count - 1) {
                    strcat(new_line, ",");
                }
            }
            strcat(new_line, "\n");

            // 替换旧行
            free(lines[i]);
            lines[i] = strdup(new_line);

            modified = 1;
            break;
        }
    }

    if (!modified) {
        printf("输入的课号不存在，请重新输入。\n");
    } else {
        // 将内存写回文件
        for (int i = 0; i < line_count; i++) {
            fprintf(fp, "%s", lines[i]);
            free(lines[i]); // 释放内存
        }
    }
    fclose(fp);
}

void modify_stu0(int item, char* id, char* new_info) {
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    char *lines[MAX_LINE_LENGTH];
    int line_count = 0;

    // 读取文件内容到内存
    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        lines[line_count] = strdup(buffer); // 保存每一行到内存
        line_count++;
    }
    fclose(fp);

    // 打开文件以修改数据
    fp = fopen("student.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    int modified = 0;
    for (int i = 0; i < line_count; i++) {
        char stu_id[50];
        sscanf(lines[i], "%49[^,]", stu_id); // 读取课程编号
        if (strcmp(id, stu_id) == 0) {
            char *token;
            char *tokens[10];
            int token_count = 0;

            // 分割行并存储各列数据，去除末尾换行符
            token = strtok(lines[i], ",\n");
            while (token != NULL && token_count < 10) {
                tokens[token_count++] = token;
                token = strtok(NULL, ",\n");
            }

            // 确保item在范围内
            if (item < 1 || item > token_count) {
                printf("指定的项不存在\n");
                return;
            }

            // 替换指定的项
            tokens[item - 1] = new_info;

            // 重新构建行数据
            char new_line[MAX_LINE_LENGTH] = "";
            for (int j = 0; j < token_count; j++) {
                strcat(new_line, tokens[j]);
                if (j < token_count - 1) {
                    strcat(new_line, ",");
                }
            }
            strcat(new_line, "\n");

            // 替换旧行
            free(lines[i]);
            lines[i] = strdup(new_line);

            modified = 1;
            break;
        }
    }

    if (!modified) {
        printf("输入的课号不存在，请重新输入。\n");
    } else {
        // 将内存写回文件
        for (int i = 0; i < line_count; i++) {
            fprintf(fp, "%s", lines[i]);
            free(lines[i]); // 释放内存
        }
    }
    fclose(fp);
}


int main() {
    int item;
    char idx[50], CourseNewInfo[50], id[50], StuNewInfo[50];
    // printf("请输入要修改的项号（例如：1 2 3 4）以及课程编号和新的信息（中间用空格隔开）：\n");
    
    
    // gets(idx);
    // gets(CourseNewInfo);
    // scanf("%d", &item);
    // // modify_course0(item, idx, CourseNewInfo);
    gets(id);
    gets(StuNewInfo);
    scanf("%d",&item);
    modify_stu0(item, id, StuNewInfo);

    return 0;
}


// void modify_course0(char* old_idx, char* new_idx){ //修改课程信息
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

//     //逐行读文件，比较学号
//     int modified = 0;
//     for (int i = 0; i < line_count; i ++){
//         char course_idx[50];
//         sscanf(lines[i], "%49[^,]", course_idx);//读取新学号到字符串
//         if (strcmp(old_idx, course_idx) == 0){
//             char* rest_of_line = strchr(lines[i], ','); // 找到逗号的位置
//             if (rest_of_line) {
//                 rest_of_line++; // 移动到逗号后面的第一个字符
//                 char new_line[MAX_LINE_LENGTH];
//                 snprintf(new_line, sizeof(new_line), "%s,%s", new_idx, rest_of_line); // 构造新的行
//                 free(lines[i]); // 释放旧行的内存
//                 lines[i] = strdup(new_line); // 用新行替换
//                 modified = 1; // 设置修改标记
//             }
//         }
//         // }
        
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

void modify_stu1(char* id, char* new_name){ //修改学生姓名
    #define MAX_LINE_LENGTH 256
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    char *lines[MAX_LINE_LENGTH];
    int line_count = 0;

    // 读取文件内容到内存
    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {    
        lines[line_count] = strdup(buffer); // 保存每一行到内存
        line_count++;
    }
    fclose(fp);

    // 打开文件以修改数据
    fp = fopen("student.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    //逐行读文件，比较学号
    int modified = 0;
    for (int i = 0; i < line_count; i ++){
        char identity[50];
        sscanf(lines[i], "%49[^,]", identity);//读取学号到字符串
        if (strcmp(id, identity) == 0){
            char* rest_of_line = strchr(lines[i], ','); // 找到逗号的位置
            if (rest_of_line) {
                rest_of_line = strchr(rest_of_line + 1, ','); //查找第二个逗号
                rest_of_line++; // 移动到逗号后面的第一个字符
                char new_line[MAX_LINE_LENGTH];
                snprintf(new_line, sizeof(new_line), "%s,%s,%s", identity, new_name, rest_of_line); // 构造新的行
                free(lines[i]); // 释放旧行的内存
                lines[i] = strdup(new_line); // 用新行替换
                modified = 1; // 设置修改标记
            }
        }     
    }
    
    //查找失败
    if (!modified){
        printf("输入的学号不存在，请重新输入。\n");
        return;
    }

    //将内存写回文件
    for (int i = 0; i < line_count; i ++){
        fprintf(fp, "%s", lines[i]);
        free(lines[i]);//释放内存
    }
    fclose(fp);
}

void modify_course1(char* idx, char* new_name){ //修改课程名称
    #define MAX_LINE_LENGTH 256
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    char *lines[MAX_LINE_LENGTH];
    int line_count = 0;

    // 读取文件内容到内存
    fp = fopen("course.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {    
        lines[line_count] = strdup(buffer); // 保存每一行到内存
        line_count++;
    }
    fclose(fp);

    // 打开文件以修改数据
    fp = fopen("course.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    //逐行读文件，比较学号
    int modified = 0;
    for (int i = 0; i < line_count; i ++){
        char course_idx[50];
        sscanf(lines[i], "%49[^,]", course_idx);//读取新学号到字符串
        if (strcmp(idx, course_idx) == 0){
            char* rest_of_line = strchr(lines[i], ','); // 找到第一个逗号的位置
            if (rest_of_line) {
                rest_of_line = strchr(rest_of_line + 1, ','); //查找第二个逗号
                rest_of_line++; // 移动到逗号后面的第一个字符
                char new_line[MAX_LINE_LENGTH];
                snprintf(new_line, sizeof(new_line), "%s,%s,%s", idx, new_name, rest_of_line); // 构造新的行
                free(lines[i]); // 释放旧行的内存
                lines[i] = strdup(new_line); // 用新行替换
                modified = 1; // 设置修改标记
            }
        }
        
    }
    
    //查找失败
    if (!modified){
        printf("输入的课号不存在，请重新输入。\n");
        return;
    }

    //将内存写回文件
    for (int i = 0; i < line_count; i ++){
        fprintf(fp, "%s", lines[i]);
        free(lines[i]);//释放内存
    }
    fclose(fp);
}

// int main(){
//     char OldID[50], NewID[50], OldIdx[50], NewIdx[50], NewCourseName[50], id[50], idx[50], NewStuName;
//     printf("请输入需要修改的学号：\n");
//     scanf("%s", OldID);
//     printf("请输入修改后的学号：\n");
//     scanf("%s", NewID);

//     printf("请输入需要修改姓名的学生学号：\n");
//     scanf("%s", id);
//     printf("请输入修改后的姓名：\n");
//     scanf("%s", NewStuName);

//     printf("请输入需要修改的课程课号：\n");
//     scanf("%s", OldIdx);
//     printf("请输入修改后的课程课号：\n");
//     scanf("%s", NewIdx);
    
//     printf("请输入需要修改的课程课号：\n");
//     gets(idx);
//     printf("请输入修改后的课程名称：\n");
//     // scanf("%s", NewName);
//     // printf("%s", NewName);
//     gets(NewCourseName);
    
    
//     modify_stu0(OldID, NewID);//修改学号
//     modify_stu1(id, NewStuName);
//     modify_course0(OldIdx, NewIdx);//修改课号
//     modify_course1(idx, NewCourseName);

//     return 0;
// }

