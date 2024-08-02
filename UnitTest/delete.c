#include "student.h"
#include "course.h"
#include "score.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void delete_stu0(char* old_id){ //根据学生学号删除学生信息
    #define MAX_LINE_LENGTH 256
    FILE *fp;
    char first_line[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];

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
    while (fgets(line, sizeof(line), fp) != NULL){
        struct StudentNode *new_node = (struct StudentNode*)malloc(sizeof(struct StudentNode));//创建节点
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", new_node->student.ID, new_node->student.name, new_node->student.gender, new_node->student.age, new_node->student.profession) == 5){ //解析字符串
            if (strcmp(old_id, new_node->student.ID) == 0){ //判断id是否相同
                free(new_node);//删除对应节点
                deleted = 1;
            }else{
                if (head == NULL)
                    head = new_node;//第一个节点
                else
                    last->next = new_node;//添加节点
                last = new_node;
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
    fprintf(fp, "%s", first_line);//表头
    struct StudentNode *current = head;
    while (current != NULL){
        fprintf(fp, "%s,%s,%s,%s,%s\n", current->student.ID, current->student.name, current->student.gender, current->student.age, current->student.profession);
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

void delete_course0(char *idx){ //根据课程课号删除课程信息
    #define MAX_LINE_LENGTH 256
    FILE *fp;
    char first_line[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];

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
    while (fgets(line, sizeof(line), fp) != NULL){
        struct CourseNode *new_node = (struct CourseNode*)malloc(sizeof(struct CourseNode));//创建节点
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", new_node->course.index, new_node->course.name, new_node->course.teacher) == 3){ //解析字符串
            if (strcmp(idx, new_node->course.index) == 0){ //判断id是否相同
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
    fprintf(fp, "%s", first_line);//表头
    struct CourseNode *current = head;
    while (current != NULL){
        fprintf(fp, "%s,%s,%s\n", current->course.index, current->course.name, current->course.teacher);
        struct CourseNode *temp = current;//保存当前节点地址
        current = current->next;
        free(temp);
        temp = NULL;//防止指针悬挂
    }
    
    //查找失败
    if (!deleted){
        printf("输入的课号不存在，请重新输入。\n");
        return;
    }

    fclose(fp);
}

void delete_score(char* id, char* idx){ //根据学生学号和课程课号删除成绩信息
    #define MAX_LINE_LENGTH 256
    FILE *fp;
    char first_line[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];

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
    while (fgets(line, sizeof(line), fp) != NULL){
        struct ScoreNode *new_node = (struct ScoreNode*)malloc(sizeof(struct ScoreNode));//创建节点
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", new_node->score.ID, new_node->score.index, &new_node->score.daily_grade, &new_node->score.exam_grade, &new_node->score.score) == 5){ //解析字符串
            // printf("%s,%s,%lf,%lf,%lf\n\n\n", new_node->score.ID, new_node->score.index, new_node->score.daily_grade, new_node->score.exam_grade, new_node->score.score);
            if (strcmp(id, new_node->score.ID) == 0 && strcmp(idx, new_node->score.index) == 0){ //判断id,idx是否相同
                // struct ScoreNode *current_temp = new_node;//保存现在的节点地址
                // new_node = new_node->next;//更新new_node
                free(new_node);//删除对应节点
                deleted = 1;
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
    fprintf(fp, "%s", first_line);//表头
    struct ScoreNode *current = head;
    while (current != NULL){
        // if (strcmp(id, current->score.ID) == 0 && strcmp(idx, current->score.index) == 0)//遍历到了删除成绩的节点
        //     fprintf(fp, "%s,%s", current->score.ID, current->score.index);
        // else
        fprintf(fp, "%s,%s,%d,%d,%.1f\n", current->score.ID, current->score.index, (int)current->score.daily_grade, (int)current->score.exam_grade, (float)current->score.score);
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

    fclose(fp);
}

int main(){
    char id[50], index[50];
    // gets(id);
    gets(index);
    // delete_stu0(id);
    // delete_score(id, index);
    delete_course0(index);

    return 0;
}