#include <stdio.h>
#include "student.h"
#include <locale.h>
//#include <wchar.h>
#include <string.h>
#include "course.h"
#include "score.h"

void modify_stu(char* old_id, char* new_id){
    //r+打开文件
    // FILE *fp;
    // fp = fopen("student.txt", "r+");

    // //读文件，查找学生
    // char identity[50];
    // while (fscanf(fp, "%s", identity) == 1){
    //     if (strcmp(identity, stu_info) == 0){//匹配成功
    //         //修改学生信息
    //         for (int i = 0; i < strlen(identity); i ++){ //清空identity
    //             identity[i] = ' ';
    //         }
    //         scanf("%s", identity);
    //         fprintf(fp, "%s", identity);
    //         fclose(fp);
    //         return;
    //     }         
    // }

    // //查找失败
    // printf("抱歉，该学号不存在，请重新输入。\n");
    // scanf("%s", stu_info);
    // modify_stu(stu_info);//重新查找

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
        sscanf(lines[i], "%s", new_id);//读取新学号到字符串
        if (strcmp(old_id, new_id) == 0){
            char* rest_of_line = strchr(lines[i],',');
            sprintf(lines[i], "%s%s", new_id, rest_of_line);//存储新学号
            modified = 1;//修改的标记
        }
    }
    
    //查找失败
    if (!modified){
        printf("输入的学号不存在，请重新输入。\n");
    }

    //将内存写回文件
    for (int i = 0; i < line_count; i ++){
        fprintf(fp, "%s", lines[i]);
        free(lines[i]);//释放内存
    }
    fclose(fp);
}

int main(){
    char OldID[50], NewID[50];
    scanf("%s %s", OldID, NewID);//输入学生id
    modify_stu(OldID, NewID);

    return 0;
}

