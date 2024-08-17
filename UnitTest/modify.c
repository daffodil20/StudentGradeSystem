#include <stdio.h>
#include "student.h"
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include "course.h"
#include "score.h"
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include "modify.h"
#include "account.h"
#include "calculateScore.h"

// TODO: 根据姓名与课名修改
// TODO: (possible)变量全局化

// TODO: 如果课程与学生已经有成绩录入，则课号与学号不能修改、删除，只能修改课名、姓名、性别、年龄
// #define MAX_LINE_LENGTH 256

void modify_stu(wchar_t* id, wchar_t* name, wchar_t* new_info, int item) { //根据学号与姓名修改
    FILE *fp;
    struct StudentNode *head = NULL, *last = NULL;
    int modified = 0;
    struct Score score;
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];

    //读取score.txt以判断学号是否能修改
    if (item == 1){
        fp = fopen("score.txt", "r");
        if (fp == NULL) {
            printf("文件打开失败\n");
            return;
        }
        fgets(buffer, sizeof(buffer), fp);
        while (fgets(buffer, sizeof(buffer), fp)) {
            mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t)); //char->wcjar_t
            if (swscanf(wbuffer, L"%49[^,],%49[^,],%d,%d,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){ //解析宽字符数组
                if (wcscmp(score.ID, id) == 0){
                    printf("该学生已经有课程成绩，学号不能修改，可以修改其他项。\n");
                    fclose(fp);
                    return;
                }
            }
        }
    }
    fclose(fp);

    //修改项不存在
    if (item != 1 && item != 2 && item != 3 && item != 4 && item != 5){
        printf("修改项不存在。\n");
        return;
    }

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
    
    while (fgets(buffer, sizeof(buffer), fp)) {
        struct StudentNode *new_node = (struct StudentNode *)malloc(sizeof(struct StudentNode));
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t)); //char->wcjar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", new_node->student.ID, new_node->student.name, new_node->student.gender, new_node->student.age, new_node->student.profession) == 5) {
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
            if (wcscmp(new_node->student.ID, id) == 0 && wcscmp(new_node->student.name, name) == 0) { //学号与姓名都匹配
                if (item == 1) wcscpy(new_node->student.ID, new_info);
                else if (item == 2) wcscpy(new_node->student.name, new_info);
                else if (item == 3) wcscpy(new_node->student.gender, new_info);
                else if (item == 4) wcscpy(new_node->student.age, new_info);
                else if (item == 5) wcscpy(new_node->student.profession, new_info);
                // else printf("修改项不存在\n");
                modified = 1;//修改标记
                printf("修改该学生基本信息成功！\n");//成功提示
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

    // 重新写入表头
    fwprintf(fp, L"学号,姓名,性别,年龄,所在系\n");

    struct StudentNode *current = head;
    while (current != NULL) {
        fwprintf(fp, L"%ls,%ls,%ls,%ls,%ls\n", current->student.ID, current->student.name, current->student.gender, current->student.age, current->student.profession);
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
void modify_course(wchar_t* idx, wchar_t* name, wchar_t* new_info, int item) { //根据课号与课名修改
    FILE *fp;
    struct CourseNode *head = NULL, *last = NULL;
    struct Score score;
    int modified = 0;
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];

    //读取score.txt以判断课号是否能修改
    if (item == 1){
        fp = fopen("score.txt", "r");
        if (fp == NULL) {
            printf("文件打开失败\n");
            return;
        }
        fgets(buffer, sizeof(buffer), fp); //跳过表头
        while (fgets(buffer, sizeof(buffer), fp)) {
            mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
            if (swscanf(wbuffer, L"%49[^,],%49[^,],%d,%d,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
                if (wcscmp(score.index, idx) == 0 && item == 1){
                    printf("该课程已经有学生成绩，课号不能修改，可以修改其他项。\n");
                    fclose(fp);
                    return;
                }
            }
        }
    }
    fclose(fp);

    //修改项不存在
    if (item != 1 && item != 2 && item != 3){
        printf("修改项不存在。\n");
        return;
    }

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
    while (fgets(buffer, sizeof(buffer), fp)) {
        struct CourseNode *new_node = (struct CourseNode *)malloc(sizeof(struct CourseNode));
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", 
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
            if (wcscmp(new_node->course.index, idx) == 0 && wcscmp(new_node->course.name, name) == 0) { //课号和课名都匹配
                if (item == 1) wcscpy(new_node->course.index, new_info);
                else if (item == 2) wcscpy(new_node->course.name, new_info);
                else if (item == 3) wcscpy(new_node->course.teacher, new_info);
                // else printf("修改项不存在\n");
                modified = 1;
                printf("修改该课程基本信息成功！\n");//成功提示
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
    fwprintf(fp, L"课号,课名,任课教师\n");

    struct CourseNode *current = head;
    while (current != NULL) {
        fwprintf(fp, L"%ls,%ls,%ls\n", 
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

// double calculate_score(wchar_t* idx, double score0, double score1){ //计算综合成绩
//     if (idx[0] == L'S')//专业课
//         return score0 * 0.4 + score1 * 0.6;
//     if (idx[0] == L'P')//公共课
//         return score0 * 0.3 + score1 * 0.7;
// }

//修改成绩信息
void modify_score0(wchar_t* accountName, wchar_t* PassWord, wchar_t* id, wchar_t* idx, double new_grade){//是哪个成绩到gui再做，查找需要id和idx
    //定义变量
    FILE *fp;
    int modified = 0;
    char first_line[MAX_LINE_LENGTH], buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    struct ScoreNode *head = NULL, *last = NULL;

    //验证密码准确性
    // char pass_word[50], num[50], account[50];
    struct Account account;
    int passed = 0;

    fp = fopen("account_info.txt", "r");

    while (fgets(buffer, sizeof(buffer), fp)) { //逐行读取
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^\n]", account.user, account.name, account.role, account.password) == 4) { //解析字符串
            if (wcscmp(account.password, PassWord) == 0 && wcscmp(account.user, accountName) == 0){//密码与账号匹配
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
    wchar_t wScoreLine[MAX_LINE_LENGTH];
    // 逐行读取文件并创建链表
    while (fgets(score_line, sizeof(score_line), fp)) {
        struct ScoreNode *new_node = (struct ScoreNode *)malloc(sizeof(struct ScoreNode));
        mbstowcs(wScoreLine, score_line, sizeof(wScoreLine) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wScoreLine, L"%49[^,],%49[^,],%lf,%lf,%lf", new_node->score.ID, new_node->score.index, &new_node->score.daily_grade, &new_node->score.exam_grade, &new_node->score.score) == 5) {
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
            if (wcscmp(new_node->score.ID, id) == 0 && wcscmp(new_node->score.index, idx) == 0) {//学号与课号都相同
                new_node->score.daily_grade = new_grade;//平时成绩修改
                new_node->score.score = calculate_score(idx, new_grade, new_node->score.exam_grade);//调用计算综合成绩的函数
                modified = 1;
                printf("修改该条成绩信息成功！\n");
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
    // fprintf(fp, "%s", first_line);
    fwprintf(fp, L"学号,课号,平时成绩,卷面成绩,综合成绩\n");

    struct ScoreNode *current = head;
    while (current != NULL) {
        fwprintf(fp, L"%ls,%ls,%d,%d,%.1f\n", current->score.ID, current->score.index, (int)current->score.daily_grade, (int)current->score.exam_grade, (float)current->score.score);//.1f控制小数部分为1位
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

void modify_score1(wchar_t* accountName, wchar_t* PassWord, wchar_t* id, wchar_t* idx, double new_grade){//是哪个成绩到gui再做，查找需要id和idx
    //定义变量
    FILE *fp;
    int modified = 0;
    char first_line[MAX_LINE_LENGTH], buffer[MAX_LINE_LENGTH];//存储account.txt
    wchar_t wbuffer[MAX_LINE_LENGTH];
    struct ScoreNode *head = NULL, *last = NULL;

    //验证密码准确性
    // char pass_word[50], num[50], account[50];
    struct Account account;
    int passed = 0;

    fp = fopen("account_info.txt", "r");

    while (fgets(buffer, sizeof(buffer), fp)) { //逐行读取
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^\n]", account.user, account.name, account.role, account.password) == 4) { //解析字符串
            if (wcscmp(account.user, accountName) == 0 && wcscmp(account.password, PassWord) == 0){
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
    wchar_t wScoreLine[MAX_LINE_LENGTH];
    // 逐行读取文件并创建链表
    while (fgets(score_line, sizeof(score_line), fp)) {
        struct ScoreNode *new_node = (struct ScoreNode *)malloc(sizeof(struct ScoreNode));
        mbstowcs(wScoreLine, score_line, sizeof(wScoreLine) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wScoreLine, L"%49[^,],%49[^,],%lf,%lf,%lf", new_node->score.ID, new_node->score.index, &new_node->score.daily_grade, &new_node->score.exam_grade, &new_node->score.score) == 5) {
            // wprintf(L"aaa:%ls,%ls,%lf,%lf,%lf\n", new_node->score.ID, new_node->score.index, new_node->score.daily_grade, new_node->score.exam_grade, new_node->score.score);
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
            if (wcscmp(new_node->score.ID, id) == 0 && wcscmp(new_node->score.index, idx) == 0) {//学号与课号都相同
                // wprintf(L"BBB:%ls,%ls:%ls,%ls\n", new_node->score.ID, id, new_node->score.index, idx);
                new_node->score.exam_grade = new_grade;//卷面成绩修改
                new_node->score.score = calculate_score(idx, new_node->score.daily_grade, new_grade);//调用计算综合成绩的函数
                modified = 1;
                printf("修改该条成绩信息成功！\n");
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
    // fprintf(fp, "%s", first_line);
    fwprintf(fp, L"学号,课号,平时成绩,卷面成绩,综合成绩\n");

    struct ScoreNode *current = head;
    while (current != NULL) {
        fwprintf(fp, L"%ls,%ls,%d,%d,%.1f\n", current->score.ID, current->score.index, (int)current->score.daily_grade, (int)current->score.exam_grade, (float)current->score.score);//.1f控制小数部分为1位
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
//     setlocale(LC_ALL, "");
//     _setmode( _fileno( stdin ), _O_WTEXT );
//     wchar_t idx[50], new_info[50], password[50], id[50], name[50], acc[50];
//     double NewGrade;//平时或卷面成绩
//     int item;

// // //     // printf("请输入课程编号、新信息和要修改的项（1: 课号, 2: 名称，3：老师）：\n");
// // //     gets(idx);
// // //     gets(name);
// // //     gets(new_info);
// // //     scanf("%d", &item);
// // //     modify_course(idx, name, new_info, item);
// //     // gets(password);
    // fgetws(id, sizeof(id), stdin);
// //     // id[wcslen(id) - 1] = L'\0';
    // fgetws(acc, sizeof(acc), stdin);
    // // acc[wcslen(acc) - 1] = L'\0';

    // fgetws(password, sizeof(password), stdin);
    // // password[wcslen(password) - 1] = L'\0';
    
    // fgetws(id, sizeof(id), stdin);
    // // id[wcslen(id) - 1] = L'\0';

    // fgetws(idx, sizeof(idx), stdin);
    // idx[wcslen(idx) - 1] = L'\0';

//     fgetws(name, sizeof(name), stdin);
//     name[wcslen(name) - 1] = L'\0';

    
    // fgetws(new_info, sizeof(new_info), stdin);
    // new_info[wcslen(new_info) - 1] = L'\0';
//     // fgetws(index, sizeof(index), stdin);
//     // index[wcslen(new_info) - 1] = L'\0';
//     // 
    // wscanf(L"%d", &item);
//     wscanf(L"%lf", &NewGrade);
// // // //     // gets(index);
// // // //     // scanf("%lf", &NewGrade);
// // //     modify_stu(id, name, new_info, item);
// // // //     // modify_course(idx, name, new_info, item);
// // // //     // modify_score0(acc, password, id, idx, NewGrade);
//     modify_score1(acc, password, id, idx, NewGrade);

//     return 0;
// }