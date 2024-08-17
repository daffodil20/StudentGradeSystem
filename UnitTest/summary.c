#include <stdio.h>
#include "score.h"
#include "student.h"
#include "course.h"
#include <string.h>
#include "summary.h"
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include "print_format.h"
// #define MAX_LINE_LENGTH 256
// #define MAX_TOTAL_COURSE 100
// #define MAX_STU_PER_COURSE 50
// #define MAX_STU_TOTAL 300
void course_info(){ //显示每门课程的情况：课号、课名、总人数、不及格人数、不及格百分比
    FILE *fp;
    struct Score score;
    struct Course course;
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50]; //存储课号与课名
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0};//存储课程数目和选修人数
    // int notSign = 0;
    int failCounter[MAX_TOTAL_COURSE] = {0}; //存储不同课程几个人数
    float failPercen[MAX_TOTAL_COURSE] = {0.0}; //存储不及格百分比
    int flag = 0;

    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t)); 
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ //解析宽字符串
            wcscpy(courseIdxs[totalCourse], course.index); //记录课号
            wcscpy(courseNames[totalCourse], course.name); //记录课名
            totalCourse ++; //统计课程数量
        }  
    } 
    fclose(fp);

    //统计课程及格情况
    fp = fopen("score.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t)); 
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){ //解析宽字符串
            if (flag == 0)
                wprintf(L"%-4ls%-15ls%-12ls%-12ls%-12ls\n", L"课号", L"课名", L"总人数", L"不及格人数", L"不及格百分比(%)");
            flag = 1;
            //查看课程的课名
            for (int i = 0; i < totalCourse; i ++){
                if (wcscmp(score.index, courseIdxs[i]) == 0){ //课号匹配
                    if (score.score < 60){ //不及格
                        failCounter[i] ++;
                    }
                    stuCounter[i] ++; //记录课程人数
                }
            }
        }
    }
    fclose(fp);
    
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0){
            failPercen[i] = (float)failCounter[i] / stuCounter[i] * 100; //统计不及格百分比
            int name_width = calculate_display_width(courseNames[i]);
            wprintf(L"%-6ls%-*ls%-15d%-17d%-15.1f\n", courseIdxs[i], 17 - name_width + wcslen(courseNames[i]), courseNames[i], stuCounter[i], failCounter[i], failPercen[i]); //显示课程信息及不及格人数 %-4ls%-18ls%-7ls%-7ls%-7ls%-7ls%-7ls%-7ls
        }
        // }else{
        //     printf("%s,%s,%d\n", courseIdxs[i], courseNames[i], stuCounter[i]);
        // }    
    }
    
}

void stu_info(){
    FILE *fp;
    struct Score score;
    struct Student stu;
    // char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50]; //存储课号与课名
    // int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0};//存储课程数目和选修人数
    wchar_t  wbuffer[MAX_LINE_LENGTH], stuIds[MAX_STU_TOTAL][50], stuNames[MAX_STU_TOTAL][50]; //存储每个学生学号与姓名
    char buffer[MAX_LINE_LENGTH];
    int totalStu = 0; //存储总学生个数
    int failCounter[MAX_STU_TOTAL] = {0}; //存储不及格课程数
    int courseCounter[MAX_TOTAL_COURSE] = {0}; //存储每个学生选修课数目
    int flag = 0;

    //遍历student文件
    fp = fopen("student.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t)); 
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession ) == 5){ 
            wcscpy(stuIds[totalStu], stu.ID); //记录学号
            wcscpy(stuNames[totalStu], stu.name); //记录姓名
            totalStu ++; //统计学生数量
        }  
    } 
    fclose(fp);

    //统计课程及格情况
    fp = fopen("score.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t)); 
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){ 
            if (flag == 0)
                wprintf(L"%-4ls%-10ls%-12ls%-12ls\n", L"学号", L"姓名", L"总课数", L"不及格课数");
            flag = 1;
            //查看学生id
            for (int i = 0; i < totalStu; i ++){
                if (wcscmp(score.ID, stuIds[i]) == 0){ //学号匹配
                    if (score.score < 60){ //不及格
                        failCounter[i] ++; //不及格课程数
                    }
                    courseCounter[i] ++; //记录课程人数
                }
            }
        }
    }
    fclose(fp);

    // printf("学号,姓名,总课数,不及格课程数\n");
    for (int i = 0; i < totalStu; i ++){
        if (courseCounter[i] != 0){
            int name_width = calculate_display_width(stuNames[i]);
            wprintf(L"%-6ls%-*ls%-15d%-17d\n", stuIds[i], 12 - name_width + wcslen(stuNames[i]), stuNames[i], courseCounter[i], failCounter[i]); //显示课程信息及不及格人数
        }
        // }else{
        //     printf("%s,%s,%d\n", stuIds[i], stuNames[i], courseCounter[i]);
        // }    
    }
}

// int main(){
//     setlocale(LC_ALL, "");
//     _setmode( _fileno( stdin ), _O_WTEXT );

//     course_info();
//     // stu_info();

//     return 0;
// }