#include <stdio.h>
#include "score.h"
#include "student.h"
#include "course.h"
#include <string.h>
#include "summary.h"

// #define MAX_LINE_LENGTH 256
// #define MAX_TOTAL_COURSE 100
// #define MAX_STU_PER_COURSE 50
// #define MAX_STU_TOTAL 300
void course_info(){ //显示每门课程的情况：课号、课名、总人数、不及格人数、不及格百分比
    FILE *fp;
    struct Score score;
    struct Course course;
    char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50]; //存储课号与课名
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0};//存储课程数目和选修人数
    // int notSign = 0;
    int failCounter[MAX_TOTAL_COURSE] = {0}; //存储不同课程几个人数
    float failPercen[MAX_TOTAL_COURSE] = {0.0}; //存储不及格百分比

    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            strcpy(courseIdxs[totalCourse], course.index); //记录课号
            strcpy(courseNames[totalCourse], course.name); //记录课名
            totalCourse ++; //统计课程数量
        }  
    } 
    fclose(fp);

    //统计课程及格情况
    fp = fopen("score.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){ 
            //查看课程的课名
            for (int i = 0; i < totalCourse; i ++){
                if (strcmp(score.index, courseIdxs[i]) == 0){ //课号匹配
                    if (score.score < 60){ //不及格
                        failCounter[i] ++;
                    }
                    stuCounter[i] ++; //记录课程人数
                }
            }
        }
    }
    fclose(fp);

    printf("课号,课名,总人数,不及格人数,不及格百分比\n");
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0){
            failPercen[i] = (float)failCounter[i] / stuCounter[i]; //统计不及格百分比
            printf("%s,%s,%d,%d,%.2f\n", courseIdxs[i], courseNames[i], stuCounter[i], failCounter[i], failPercen[i]); //显示课程信息及不及格人数
        }else{
            printf("%s,%s,%d\n", courseIdxs[i], courseNames[i], stuCounter[i]);
        }    
    }
    
}

void stu_info(){
    FILE *fp;
    struct Score score;
    struct Student stu;
    // char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50]; //存储课号与课名
    // int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0};//存储课程数目和选修人数
    char stuIds[MAX_STU_TOTAL][50], stuNames[MAX_STU_TOTAL][50]; //存储每个学生学号与姓名
    char line[MAX_LINE_LENGTH];
    int totalStu = 0; //存储总学生个数
    int failCounter[MAX_STU_TOTAL] = {0}; //存储不及格课程数
    int courseCounter[MAX_TOTAL_COURSE] = {0}; //存储每个学生选修课数目

    //遍历student文件
    fp = fopen("student.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession ) == 5){ 
            strcpy(stuIds[totalStu], stu.ID); //记录学号
            strcpy(stuNames[totalStu], stu.name); //记录姓名
            totalStu ++; //统计学生数量
        }  
    } 
    fclose(fp);

    //统计课程及格情况
    fp = fopen("score.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){ 
            //查看学生id
            for (int i = 0; i < totalStu; i ++){
                if (strcmp(score.ID, stuIds[i]) == 0){ //学号匹配
                    if (score.score < 60){ //不及格
                        failCounter[i] ++; //不及格课程数
                    }
                    courseCounter[i] ++; //记录课程人数
                }
            }
        }
    }
    fclose(fp);

    printf("学号,姓名,总课数,不及格课程数\n");
    for (int i = 0; i < totalStu; i ++){
        if (courseCounter[i] != 0){
            printf("%s,%s,%d,%d\n", stuIds[i], stuNames[i], courseCounter[i], failCounter[i]); //显示课程信息及不及格人数
        }else{
            printf("%s,%s,%d\n", stuIds[i], stuNames[i], courseCounter[i]);
        }    
    }
}

// int main(){
//     course_info();
//     stu_info();

//     return 0;
// }