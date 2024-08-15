#include "student.h"
#include "course.h"
#include "score.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdint.h>
// #include "delete.h"
#define MAX_LINE_LENGTH 256
void delete_stu(wchar_t* old_id, wchar_t* old_name){ //根据学生学号和姓名删除学生信息
    FILE *fp;
    char first_line[MAX_LINE_LENGTH], buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    struct Score score;;

    //判断该项是否能删除
    fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%d,%d,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            if (wcscmp(score.ID, old_id) == 0){
                printf("该学生已经有课程成绩，信息不能删除。\n");
                return;
            }
        }
    }
    fclose(fp);

    // 读取文件内容到内存
    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    
    //跳过表头
    if (fgets(first_line, sizeof(first_line), fp) == NULL) {    
        printf("文件为空");
        fclose(fp);
        return;
    }
    
    //创建链表并暂存文件内容
    int deleted = 0;//删除标记
    struct StudentNode *head = NULL, *last = NULL;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        struct StudentNode *new_node = (struct StudentNode*)malloc(sizeof(struct StudentNode));//创建节点
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", new_node->student.ID, new_node->student.name, new_node->student.gender, new_node->student.age, new_node->student.profession) == 5){ //解析字符串
            if (wcscmp(old_id, new_node->student.ID) == 0 && wcscmp(old_name, new_node->student.name) == 0){ //判断id,name是否匹配
                free(new_node);//删除对应节点
                deleted = 1;
                printf("删除该学生基本信息成功！\n");
            }else{
                if (head == NULL)
                    head = new_node;//第一个节点
                else
                    last->next = new_node;//添加节点
                last = new_node;
                last->next = NULL;
            }
        }else{
            free(new_node);//释放多余内存
            break;
        }      
    }
     
    //切换打开文件模式
    fp = fopen("student.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        // fclose(fp);
        return;
    }

    //遍历链表，释放内存，写回文件
    fwprintf(fp, L"学号,姓名,性别,年龄,所在系\n");
    struct StudentNode *current = head;
    while (current != NULL){
        fwprintf(fp, L"%ls,%ls,%ls,%ls,%ls\n", current->student.ID, current->student.name, current->student.gender, current->student.age, current->student.profession);
        struct StudentNode *temp = current;//保存当前节点地址
        current = current->next;
        free(temp);
        temp = NULL;//防止指针悬挂
    }
    
    //查找失败
    if (!deleted){
        printf("输入的学号不存在，请重新输入。\n");
        return;
    }

    fclose(fp);
}

void delete_course(wchar_t *idx, wchar_t *name){ //根据课程课号删除课程信息
    FILE *fp;
    char first_line[MAX_LINE_LENGTH], buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    struct Score score;

    //判断该项是否能删除
    fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%d,%d,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            if (wcscmp(score.index, idx) == 0){
                printf("该课程已经有学生成绩，信息不能删除。\n");
                return;
            }
        }
    }
    fclose(fp);

    // 读取文件内容到内存
    fp = fopen("course.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    
    //跳过表头
    if (fgets(first_line, sizeof(first_line), fp) == NULL) {    
        printf("文件为空");
        fclose(fp);
        return;
    }
    
    //创建链表并暂存文件内容
    int deleted = 0;//删除标记
    struct CourseNode *head = NULL, *last = NULL;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        struct CourseNode *new_node = (struct CourseNode*)malloc(sizeof(struct CourseNode));//创建节点
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", new_node->course.index, new_node->course.name, new_node->course.teacher) == 3){ //解析字符串
            if (wcscmp(idx, new_node->course.index) == 0 && wcscmp(name, new_node->course.name) == 0 ){ //判断id是否相同
                free(new_node);//删除对应节点
                deleted = 1;
            }else{
                if (head == NULL)
                    head = new_node;//第一个节点
                else
                    last->next = new_node;//添加节点
                last = new_node;
                last->next = NULL;//尾指针指向空
            }
        }else{
            free(new_node);//释放多余内存
            break;
        }      
    }
    fclose(fp);
     
    //切换打开文件模式
    fp = fopen("course.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        // fclose(fp);
        return;
    }

    //遍历链表，释放内存，写回文件
    fwprintf(fp, L"课号,课名,任课教师\n");//表头
    struct CourseNode *current = head;
    while (current != NULL){
        fwprintf(fp, L"%ls,%ls,%ls\n", current->course.index, current->course.name, current->course.teacher);
        struct CourseNode *temp = current;//保存当前节点地址
        current = current->next;
        free(temp);
        temp = NULL;//防止指针悬挂
    }
    
    //查找失败
    if (!deleted){
        printf("输入的课号或课名不存在/课号与课名不匹配，请重新输入。\n");
        return;
    }
    printf("删除该课程基本信息成功！\n");

    fclose(fp);
}

void delete_score(wchar_t* id, wchar_t* idx){ //根据学生学号和课程课号删除成绩信息
    #define MAX_LINE_LENGTH 256
    FILE *fp;
    char first_line[MAX_LINE_LENGTH], buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];//存储宽字符

    // 读取文件内容到内存
    fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    
    //跳过表头
    if (fgets(first_line, sizeof(first_line), fp) == NULL) {    
        printf("文件为空");
        fclose(fp);
        return;
    }
    
    //创建链表并暂存文件内容
    int deleted = 0;//删除标记
    struct ScoreNode *head = NULL, *last = NULL;
    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        struct ScoreNode *new_node = (struct ScoreNode*)malloc(sizeof(struct ScoreNode));//创建节点
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", new_node->score.ID, new_node->score.index, &new_node->score.daily_grade, &new_node->score.exam_grade, &new_node->score.score) == 5){ //解析字符串
            // printf("%s,%s,%lf,%lf,%lf\n\n\n", new_node->score.ID, new_node->score.index, new_node->score.daily_grade, new_node->score.exam_grade, new_node->score.score);
            if (wcscmp(id, new_node->score.ID) == 0 && wcscmp(idx, new_node->score.index) == 0){ //判断id,idx是否相同
                // struct ScoreNode *current_temp = new_node;//保存现在的节点地址
                // new_node = new_node->next;//更新new_node
                free(new_node);//删除对应节点
                deleted = 1;
                // printf("删除该条成绩信息成功！\n");
            }else{
                if (head == NULL)
                    head = new_node;//第一个节点
                else
                    last->next = new_node;//添加节点
                last = new_node;
                last->next = NULL;
            }
        }else{
            free(new_node);//释放多余内存
            break;
        } 



        // if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", stuId, inDex, &dailyGrade, &examGrade, &sCore) == 5){
        //     if (strcmp(id, stuId) != 0 || strcmp(idx, inDex) != 0){ //不是删除的record，放入链表
        //         struct ScoreNode *new_node = (struct ScoreNode*)malloc(sizeof(struct ScoreNode));//创建节点
        //         if (head == NULL)
        //             head = new_node;//第一个节点
        //         else
        //             last->next = new_node;//添加节点
        //         last = new_node;
        //     }else //不计入节点
        //         deleted = 1;
        // }else{
        //     free(new_node);//释放多余内存
        //     break;
        // }
    }
    fclose(fp);
     
    //切换打开文件模式
    fp = fopen("score.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        // fclose(fp);
        return;
    }

    //遍历链表，释放内存，写回文件
    fwprintf(fp, L"学号,课号,平时成绩,卷面成绩,综合成绩\n");//表头
    struct ScoreNode *current = head;
    while (current != NULL){
        // if (strcmp(id, current->score.ID) == 0 && strcmp(idx, current->score.index) == 0)//遍历到了删除成绩的节点
        //     fprintf(fp, "%s,%s", current->score.ID, current->score.index);
        // else
        fwprintf(fp, L"%ls,%ls,%d,%d,%.1f\n", current->score.ID, current->score.index, (int)current->score.daily_grade, (int)current->score.exam_grade, (float)current->score.score);
        // printf("%s,%s,%lf,%lf,%lf\n", current->score.ID, current->score.index, current->score.daily_grade, current->score.exam_grade, current->score.score);
        // fprintf(fp, "%s,%s,%s,%s,%s\n", current->student.ID, current->student.name, current->student.gender, current->student.age, current->student.profession);
        struct ScoreNode *temp = current;//保存当前节点地址
        current = current->next;
        free(temp);
        temp = NULL;//防止指针悬挂
    }
    
    //查找失败
    if (!deleted){
        printf("输入的课号或学号不存在，请重新输入。\n");
        return;
    }
    printf("删除该条成绩信息成功！\n");//成功提示

    fclose(fp);
}

int main(){
    setlocale(LC_ALL, "");
    _setmode( _fileno( stdin ), _O_WTEXT );

    wchar_t id[50], index[50], name[50];
    fgetws(id, sizeof(id), stdin);
    id[wcslen(id)-1] = L'\0';

    fgetws(index, sizeof(index), stdin);
    index[wcslen(index)-1] = L'\0';
    // gets(index);
    // fgetws(name, sizeof(name), stdin);
    // name[wcslen(name)-1] = L'\0';
    // gets(index);
    // delete_stu(id, name);
    delete_score(id, index);
    // delete_course(index, name);

    return 0;
}