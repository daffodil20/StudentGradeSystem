#include <stdio.h>
#include "student.h"
#include <locale.h>
//#include <wchar.h>
#include <string.h>
#include "course.h"
#include "score.h"
#include <stdlib.h>
#include "modify.h"
#include "account.h"

// TODO: 根据姓名与课名修改
// TODO: (possible)变量全局化

// #define MAX_LINE_LENGTH 256

void modify_stu(char* id, char* name, char* new_info, int item) { //根据学号与姓名修改
    FILE *fp;
    struct StudentNode *head = NULL, *last = NULL;
    int modified = 0;

    // 读取文件内容到链表
    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    // 跳过第一行
    char first_line[MAX_LINE_LENGTH];
    if (fgets(first_line, sizeof(first_line), fp) == NULL) {
        printf("无法读取文件或文件为空\n");
        fclose(fp);
        return;
    }

    // 逐行读取文件并创建链表
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
        struct StudentNode *new_node = (struct StudentNode *)malloc(sizeof(struct StudentNode));
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", new_node->student.ID, new_node->student.name, new_node->student.gender, new_node->student.age, new_node->student.profession) == 5) {
            new_node->next = NULL;
            if (head == NULL) {
                head = new_node;
            } else {
                last->next = new_node;
            }
            last = new_node;
            last->next = NULL;
            // printf("index:%s name:%s teacher:%s\n", new_node->course.index, 
                //    new_node->course.name,
                //    new_node->course.teacher);
            // 查找并修改数据
            if (strcmp(new_node->student.ID, id) == 0 && strcmp(new_node->student.name, name) == 0) { //学号与姓名都匹配
                if (item == 1) strcpy(new_node->student.ID, new_info);
                else if (item == 2) strcpy(new_node->student.name, new_info);
                else if (item == 3) strcpy(new_node->student.gender, new_info);
                else if (item == 4) strcpy(new_node->student.age, new_info);
                else if (item == 5) strcpy(new_node->student.profession, new_info);
                else printf("修改项不存在\n");
                modified = 1;//修改标记
            }
        } else {
            free(new_node); // 释放未用的内存
            break; // 结束循环
        }
    }
    fclose(fp);

    // 写回文件
    fp = fopen("student.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    // 重新写入第一行
    fprintf(fp, "%s", first_line);

    struct StudentNode *current = head;
    while (current != NULL) {
        fprintf(fp, "%s,%s,%s,%s,%s\n", current->student.ID, current->student.name, current->student.gender, current->student.age, current->student.profession);
        struct StudentNode *temp = current;
        current = current->next;
        free(temp); // 释放节点内存
        temp = NULL;
    }
    fclose(fp);

    if (!modified) {
        printf("输入的学号或姓名不存在/学号和姓名不匹配，请重新输入。\n");
    }
}

// 修改课程数据的函数
void modify_course(char* idx, char* name, char* new_info, int item) { //根据课号与课名修改
    FILE *fp;
    struct CourseNode *head = NULL, *last = NULL;
    int modified = 0;

    // 读取文件内容到链表
    fp = fopen("course.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    // 跳过第一行
    char first_line[MAX_LINE_LENGTH];
    if (fgets(first_line, sizeof(first_line), fp) == NULL) {
        printf("无法读取文件或文件为空\n");
        fclose(fp);
        return;
    }

    // 逐行读取文件并创建链表
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
        struct CourseNode *new_node = (struct CourseNode *)malloc(sizeof(struct CourseNode));
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", 
                   new_node->course.index, 
                   new_node->course.name, 
                   new_node->course.teacher) == 3) {
            new_node->next = NULL;
            if (head == NULL) {
                head = new_node;
            } else {
                last->next = new_node;
            }
            last = new_node;
            // printf("index:%s name:%s teacher:%s\n", new_node->course.index, 
            //        new_node->course.name, 
            //        new_node->course.teacher);
            // 查找并修改数据
            if (strcmp(new_node->course.index, idx) == 0 && strcmp(new_node->course.name, name) == 0) { //课号和课名都匹配
                if (item == 1) strcpy(new_node->course.index, new_info);
                else if (item == 2) strcpy(new_node->course.name, new_info);
                else if (item == 3) strcpy(new_node->course.teacher, new_info);
                else printf("修改项不存在\n");
                modified = 1;
            }
        } else {
            free(new_node); // 释放未用的内存
            break; // 结束循环
        }
    }
    fclose(fp);

    // 写回文件
    fp = fopen("course.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    // 重新写入第一行
    fprintf(fp, "%s", first_line);

    struct CourseNode *current = head;
    while (current != NULL) {
        fprintf(fp, "%s,%s,%s\n", 
                current->course.index, 
                current->course.name, 
                current->course.teacher);
        struct CourseNode *temp = current;
        current = current->next;
        free(temp); // 释放节点内存
        temp = NULL;
    }
    fclose(fp);

    if (!modified) {
        printf("输入的课号或课名不存在/课号和课名不匹配，请重新输入。\n");
    }
}

double calculate_score(char* idx, double score0, double score1){ //计算综合成绩
    if (idx[0] == 'S')//专业课
        return score0 * 0.4 + score1 * 0.6;
    if (idx[0] == 'P')//公共课
        return score0 * 0.3 + score1 * 0.7;
}

//修改成绩信息
void modify_score0(char* accountName, char* PassWord, char* id, char* idx, double new_grade){//是哪个成绩到gui再做，查找需要id和idx
    //定义变量
    FILE *fp;
    int modified = 0;
    char first_line[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    struct ScoreNode *head = NULL, *last = NULL;

    //验证密码准确性
    // char pass_word[50], num[50], account[50];
    struct Account account;
    int passed = 0;

    fp = fopen("account_info.txt", "r");

    while (fgets(line, sizeof(line), fp)) { //逐行读取
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^\n]", account.user, account.name, account.role, account.password) == 4) { //解析字符串
            if (strcmp(account.password, PassWord) == 0 && strcmp(account.user, accountName) == 0){//密码与账号匹配
                passed = 1;//密码正确
                break;
            }
        }
    }
    if (passed == 0){
        printf("输入密码错误，请重新输入：\n");
        return;
    }
    fclose(fp);

    // 读取文件内容到链表
    fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    // 跳过第一行   
    if (fgets(first_line, sizeof(first_line), fp) == NULL) {
        printf("无法读取文件或文件为空\n");
        fclose(fp);
        return;
    }

    char score_line[MAX_LINE_LENGTH];
    // 逐行读取文件并创建链表
    while (fgets(score_line, sizeof(score_line), fp)) {
        struct ScoreNode *new_node = (struct ScoreNode *)malloc(sizeof(struct ScoreNode));
        if (sscanf(score_line, "%49[^,],%49[^,],%lf,%lf,%lf", new_node->score.ID, new_node->score.index, &new_node->score.daily_grade, &new_node->score.exam_grade, &new_node->score.score) == 5) {
            // printf("asssseAfzsdreWef\n");
            // printf("WQedd:id:%s,index:%s,daily grade:%lf,exam grade:%lf,score:%lf\n", new_node->score.ID, new_node->score.index, new_node->score.daily_grade, new_node->score.exam_grade, new_node->score.score);
            new_node->next = NULL;
            if (head == NULL) {
                head = new_node;
            } else {
                last->next = new_node;
            }
            last = new_node;
            // printf("id:%s,index:%s,daily grade:%lf,exam grade:%lf,score:%lf\n", new_node->score.ID, new_node->score.index, new_node->score.daily_grade, new_node->score.exam_grade, new_node->score.score);
            // 查找并修改数据
            if (strcmp(new_node->score.ID, id) == 0 && strcmp(new_node->score.index, idx) == 0) {//学号与课号都相同
                new_node->score.daily_grade = new_grade;//平时成绩修改
                new_node->score.score = calculate_score(idx, new_grade, new_node->score.exam_grade);//调用计算综合成绩的函数
                modified = 1;
            }
        } else {
            free(new_node); // 释放未用的内存
            break; // 结束循环
        }
    }
    fclose(fp);

    // 写回文件
    fp = fopen("score.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    // 重新写入第一行
    fprintf(fp, "%s", first_line);

    struct ScoreNode *current = head;
    while (current != NULL) {
        fprintf(fp, "%s,%s,%d,%d,%.1f\n", current->score.ID, current->score.index, (int)current->score.daily_grade, (int)current->score.exam_grade, (float)current->score.score);//.1f控制小数部分为1位
        struct ScoreNode *temp = current;
        current = current->next;
        free(temp); // 释放节点内存
        temp = NULL;
    }
    fclose(fp);

    if (!modified) {
        printf("输入的课号或学号不存在，请重新输入。\n");
        return;
    }
}

void modify_score1(char* accountName, char* PassWord, char* id, char* idx, double new_grade){//是哪个成绩到gui再做，查找需要id和idx
    //定义变量
    FILE *fp;
    int modified = 0;
    char first_line[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];//存储account.txt
    struct ScoreNode *head = NULL, *last = NULL;

    //验证密码准确性
    // char pass_word[50], num[50], account[50];
    struct Account account;
    int passed = 0;

    fp = fopen("account_info.txt", "r");

    while (fgets(line, sizeof(line), fp)) { //逐行读取
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^\n]", account.user, account.name, account.role, account.password) == 4) { //解析字符串
            if (strcmp(account.user, accountName) == 0 && strcmp(account.password, PassWord) == 0){
                passed = 1;//密码正确
                break;
            }
        }
    }
    if (passed == 0){
        printf("输入密码错误，请重新输入：\n");
        return;
    }
    fclose(fp);

    // 读取文件内容到链表
    fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    // 跳过第一行   
    if (fgets(first_line, sizeof(first_line), fp) == NULL) {
        printf("无法读取文件或文件为空\n");
        fclose(fp);
        return;
    }

    char score_line[MAX_LINE_LENGTH];//存储score.txt
    // 逐行读取文件并创建链表
    while (fgets(score_line, sizeof(score_line), fp)) {
        struct ScoreNode *new_node = (struct ScoreNode *)malloc(sizeof(struct ScoreNode));
        if (sscanf(score_line, "%49[^,],%49[^,],%lf,%lf,%lf", new_node->score.ID, new_node->score.index, &new_node->score.daily_grade, &new_node->score.exam_grade, &new_node->score.score) == 5) {
            // printf("asssseAfzsdreWef\n");
            // printf("WQedd:id:%s,index:%s,daily grade:%lf,exam grade:%lf,score:%lf\n", new_node->score.ID, new_node->score.index, new_node->score.daily_grade, new_node->score.exam_grade, new_node->score.score);
            new_node->next = NULL;
            if (head == NULL) {
                head = new_node;
            } else {
                last->next = new_node;
            }
            last = new_node;
            // printf("id:%s,index:%s,daily grade:%lf,exam grade:%lf,score:%lf\n", new_node->score.ID, new_node->score.index, new_node->score.daily_grade, new_node->score.exam_grade, new_node->score.score);
            // 查找并修改数据
            if (strcmp(new_node->score.ID, id) == 0 && strcmp(new_node->score.index, idx) == 0) {//学号与课号都相同
                new_node->score.exam_grade = new_grade;//卷面成绩修改
                new_node->score.score = calculate_score(idx, new_node->score.daily_grade, new_grade);//调用计算综合成绩的函数
                modified = 1;
            }
        } else {
            free(new_node); // 释放未用的内存
            break; // 结束循环
        }
    }
    fclose(fp);

    // 写回文件
    fp = fopen("score.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    // 重新写入第一行
    fprintf(fp, "%s", first_line);

    struct ScoreNode *current = head;
    while (current != NULL) {
        fprintf(fp, "%s,%s,%d,%d,%.1f\n", current->score.ID, current->score.index, (int)current->score.daily_grade, (int)current->score.exam_grade, (float)current->score.score);//.1f控制小数部分为1位
        struct ScoreNode *temp = current;
        current = current->next;
        free(temp); // 释放节点内存
        temp = NULL;
    }
    fclose(fp);

    if (!modified) {
        printf("输入的课号或学号不存在，请重新输入。\n");
        return;
    }
}

// int main() {
//     char idx[50], new_info[50], index[50], password[50], id[50], name[50];
//     double NewGrade;//平时或卷面成绩
//     int item;

//     // printf("请输入课程编号、新信息和要修改的项（1: 课号, 2: 名称，3：老师）：\n");
//     gets(idx);
//     gets(name);
//     gets(new_info);
//     scanf("%d", &item);
//     modify_course(idx, name, new_info, item);
    // gets(password);
    // gets(id);
    // gets(name);
    // gets(new_info);
    // scanf("%d", &item);
    // gets(index);
    // scanf("%lf", &NewGrade);
    // modify_stu(id, name, new_info, item);
    // modify_score0(password, id, index, NewGrade);
    // modify_score1(password, id, index, NewGrade);

//     return 0;
// }