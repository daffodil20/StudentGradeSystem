// show feature of score of every course
#include <stdio.h>
#include "score.h"
#include "course.h"
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include "print_format.h"
// #include <wctype.h>
#include "statistics.h"

// #define MAX_LINE_LENGTH 256
// #define MAX_TOTAL_COURSE 100
// #define MAX_STU_PER_COURSE 50
// int calculate_display_width(const wchar_t* str) { //根据是否是汉字技术字符串实际宽度（英文宽字符是1）
//     int width = 0;
//     while (*str) {
//         if (iswprint(*str) && *str > 127) {
//             width += 2; // 宽字符（如汉字）占两个单位宽度
//         } else {
//             width += 1; // 窄字符（如字母、数字）占一个单位宽度
//         }
//         str++;
//     }
//     return width;
// }

void average_score(){ //综合成绩平均分
    FILE *fp;
    struct Score score;
    struct Course course;
    float totalScore[MAX_TOTAL_COURSE] = {0.0};//, aveScore[MAX_TOTAL_COURSE]; //存储课程总分和平均分的数组
    char buffer[MAX_LINE_LENGTH];
    wchar_t courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0};//每门课人数
    int flag = 0;
    
    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(buffer, sizeof(buffer), fp);//跳过表头

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ //解析宽字符串
            wcscpy(courseIdxs[totalCourse], course.index); //记录课号
            wcscpy(courseNames[totalCourse], course.name); //记录课名
            totalCourse ++; //统计课程数量
        }
    } 
    fclose(fp);
    
    //计算每门课程平均分
    fp = fopen("score.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){ //解析宽字符串
            for (int i = 0; i < MAX_TOTAL_COURSE; i ++){
                if (wcscmp(score.index, courseIdxs[i]) == 0){ //课程匹配
                    flag = 1;//说明有课程有人报名
                    totalScore[i] += (float)score.score; //计算total score
                    stuCounter[i] ++;
                    break;
                }
            }
        }
    }
    fclose(fp);

    if (flag == 1)
        wprintf(L"%-5ls%-13ls%-5ls\n", L"课号", L"课名", L"综合成绩平均分");//表头
    else{
        printf("未查到任何课程的综合成绩平均分\n");
        return;
    }
    
    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0){ //有人报名
            int name_width = calculate_display_width(courseNames[i]);//计算课名实际长度
            wprintf(L"%-7ls%-*ls%-3.1f\n", courseIdxs[i], 15 - name_width + wcslen(courseNames[i]), courseNames[i], totalScore[i] / stuCounter[i]);
        }
    }  
}

void average_exam_grade(){ //卷面成绩平均分
    FILE *fp;
    struct Score score;
    struct Course course;
    float totalExamGrade[MAX_TOTAL_COURSE] = {0.0}; //存储课程总分和平均分的数组
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0};//每门课人数
    int flag = 0;
    
    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(buffer, sizeof(buffer), fp);//跳过表头

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            wcscpy(courseIdxs[totalCourse], course.index); //记录课号
            wcscpy(courseNames[totalCourse], course.name); //记录课名
            totalCourse ++; //统计课程数量
        }
    } 
    fclose(fp);
    
    //计算每门课程平均分
    fp = fopen("score.txt", "r");
    fgets(buffer, sizeof(buffer), fp);//跳过表头

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (wcscmp(score.index, courseIdxs[i]) == 0){ //课程匹配
                    flag = 1;//存在课程有人选修
                    totalExamGrade[i] += (float)score.exam_grade; //计算卷面成绩
                    stuCounter[i] ++;
                    break;
                }
            }
        }
    }
    fclose(fp);
    
    if (flag == 1)
        wprintf(L"%-5ls%-13ls%-5ls\n", L"课号", L"课名", L"卷面成绩平均分");//表头
    else{
        printf("未查到任何课程的卷面成绩平均分\n");
        return;
    }

    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0){ //有人报名
            int name_width = calculate_display_width(courseNames[i]);//计算课名实际长度
            wprintf(L"%-7ls%-*ls%-3.1f\n", courseIdxs[i], 15 - name_width + wcslen(courseNames[i]), courseNames[i], totalExamGrade[i] / stuCounter[i]);
        }
    }
}

void max_exam_grade(){ //卷面成绩最高分
    FILE *fp;
    struct Score score;
    struct Course course;
    int ExamGrade[MAX_TOTAL_COURSE][MAX_STU_PER_COURSE] = {0}; //存储不同课程所有选修学生卷面成绩的数组
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0}, tmp;//存储课程数目和选修人数
    int flag = 0;
    
    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            wcscpy(courseIdxs[totalCourse], course.index); //记录课号
            wcscpy(courseNames[totalCourse], course.name); //记录课名
            totalCourse ++; //统计课程数量
        }
    } 
    fclose(fp);
    
    //统计卷面分数
    fp = fopen("score.txt", "r");
    fgets(buffer, sizeof(buffer), fp);
    
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (wcscmp(score.index, courseIdxs[i]) == 0){ //课程匹配
                    flag = 1;
                    ExamGrade[i][stuCounter[i]] = (int)score.exam_grade; //记录该学生该课程的卷面分数
                    stuCounter[i] ++;//统计本课学生数目
                    break;
                }
            }
        }
    }
    fclose(fp);

    //对每门课程的卷面分数排序
    for (int i = 0; i < totalCourse; i ++){  //不同课程
        if (stuCounter[i] > 1){
            for (int j = 0; j < stuCounter[i] - 1; j ++){ //不同学生
                for (int k = j + 1; k < stuCounter[i]; k ++){ //不同学生
                    if (ExamGrade[i][j] < ExamGrade[i][k]){ //交换顺序
                        tmp = ExamGrade[i][j];
                        ExamGrade[i][j] = ExamGrade[i][k];
                        ExamGrade[i][k] = tmp;
                    }
                }
            }
        }
    }
    if (flag == 1)
        wprintf(L"%-5ls%-13ls%-5ls\n", L"课号", L"课名", L"卷面成绩最高分");//表头
    else{
        printf("未查到任何课程的卷面成绩最高分\n");
        return;
    }
    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0){//有人报名
            int name_width = calculate_display_width(courseNames[i]);//计算课名实际长度
            wprintf(L"%-7ls%-*ls%-3d\n", courseIdxs[i], 15 - name_width + wcslen(courseNames[i]), courseNames[i], ExamGrade[i][0]);
        }
    }
}

void max_score(){ //综合成绩最高分
    FILE *fp;
    struct Score score;
    struct Course course;
    double Scores[MAX_TOTAL_COURSE][MAX_STU_PER_COURSE] = {0}; //存储不同课程所有选修学生综合成绩的数组
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0}, tmp;//存储课程数目和选修人数
    int flag = 0;
    
    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            wcscpy(courseIdxs[totalCourse], course.index); //记录课号
            wcscpy(courseNames[totalCourse], course.name); //记录课名
            totalCourse ++; //统计课程数量
        }
    } 
    fclose(fp);
    
    //统计综合成绩
    fp = fopen("score.txt", "r");
    fgets(buffer, sizeof(buffer), fp);
    
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (wcscmp(score.index, courseIdxs[i]) == 0){ //课程匹配
                    flag = 1;
                    Scores[i][stuCounter[i]] = score.score; //记录该学生该课程的综合成绩
                    stuCounter[i] ++;//统计本课学生数目
                    break;
                }
            }
        }
    }
    fclose(fp);

    //对每门课程的卷面分数排序
    for (int i = 0; i < totalCourse; i ++){  //不同课程
        if (stuCounter[i] > 1){
            for (int j = 0; j < stuCounter[i] - 1; j ++){ //不同学生
                for (int k = j + 1; k < stuCounter[i]; k ++){ //不同学生
                    if (Scores[i][j] < Scores[i][k]){ //交换顺序
                        tmp = Scores[i][j];
                        Scores[i][j] = Scores[i][k];
                        Scores[i][k] = tmp;
                    }
                }
            }
        }
    }
    if (flag == 1)
        wprintf(L"%-5ls%-13ls%-5ls\n", L"课号", L"课名", L"综合成绩最高分");//表头
    else{
        printf("未查到任何课程的综合成绩最高分\n");
        return;
    }
    
    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0){ //有人报名
            int name_width = calculate_display_width(courseNames[i]);//计算课名实际长度
            printf("%-7ls%-*ls%-3.1f\n", courseIdxs[i], 15 - name_width + wcslen(courseNames[i]), courseNames[i], (float)Scores[i][0]);
        }
    }
}


void exam_statistics(){ //卷面分数分数段人数统计
    int examSta[MAX_TOTAL_COURSE][6] = {0}; //分数段 
    FILE *fp;
    struct Score score;
    struct Course course;
    int ExamGrade[MAX_TOTAL_COURSE][MAX_STU_PER_COURSE] = {0}; //存储不同课程所有选修学生卷面成绩的数组
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0}, tmp;//存储课程数目和选修人数
    int notSign = 0, flag = 0;

    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){
            wcscpy(courseIdxs[totalCourse], course.index); //记录课号
            wcscpy(courseNames[totalCourse], course.name); //记录课名
            totalCourse ++; //统计课程数量
        }
    } 
    fclose(fp);

    //遍历score.txt
    fp = fopen("score.txt", "r");
    fgets(buffer, sizeof(buffer), fp);
    
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (wcscmp(score.index, courseIdxs[i]) == 0){ //找到对应的课程
                    if (flag == 0)
                        wprintf(L"%-4ls%-18ls%-7ls%-7ls%-7ls%-7ls%-7ls%-7ls\n", L"课号", L"课名", L"0-59分", L"60-69分", L"70-79分", L"80-89分", L"90-99分", L"100分");//表头
                    flag = 1;
                    ExamGrade[i][stuCounter[i]] = score.exam_grade; //记录exam grade
                    stuCounter[i] ++;
                }
            }
        }
    }
    fclose(fp);

    //按分数段统计
    for (int i = 0; i < totalCourse; i ++){
        for (int j = 0; j < stuCounter[i]; j ++){
            if (ExamGrade[i][j] == 100)
                examSta[i][5] ++;
            else if (ExamGrade[i][j] < 100 && ExamGrade[i][j] >= 90)
                examSta[i][4] ++;
            else if (ExamGrade[i][j] < 90 && ExamGrade[i][j] >= 80)
                examSta[i][3] ++;
            else if (ExamGrade[i][j] < 80 && ExamGrade[i][j] >= 70)
                examSta[i][2] ++;
            else if (ExamGrade[i][j] < 70 && ExamGrade[i][j] >= 60)
                examSta[i][1] ++;
            else if (ExamGrade[i][j] < 60 && ExamGrade[i][j] >= 0)
                examSta[i][0] ++;
        }
    }

    //输出每门课的卷面成绩分数段
    for (int i = 0; i < totalCourse; i ++){
        for (int j = 0; j < 6; j ++){
            if (examSta[i][j] > 0){ 
                notSign ++; //
            }
        }
        if (notSign > 0){ 
            int name_width = calculate_display_width(courseNames[i]);
            wprintf(L"%-6ls%-*ls", courseIdxs[i], 20 - name_width + wcslen(courseNames[i]), courseNames[i]); //哪个课程
            for (int k = 0; k < 6; k ++){
                if (k < 5)
                    wprintf(L"%-8d", examSta[i][k]);
                else
                    wprintf(L"%-8d\n", examSta[i][k]);
            }
        }
        notSign = 0;
    }
}

void score_statistics(){ //综合分数分数段人数统计
    int scoreSta[MAX_TOTAL_COURSE][6] = {0}; //综合成绩分数段 
    FILE *fp;
    struct Score score;
    struct Course course;
    int scores[MAX_TOTAL_COURSE][MAX_STU_PER_COURSE] = {0}; //存储不同课程所有选修学生综合成绩的数组
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0}, tmp;//存储课程数目和选修人数
    int notSign = 0, flag = 0;

    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(buffer, sizeof(buffer), fp);

    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ //解析宽字符串
            wcscpy(courseIdxs[totalCourse], course.index); //记录课号
            wcscpy(courseNames[totalCourse], course.name); //记录课名
            totalCourse ++; //统计课程数量
        }
    } 
    fclose(fp);

    //遍历score.txt
    fp = fopen("score.txt", "r");
    fgets(buffer, sizeof(buffer), fp);
    
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){//解析宽字符串
            for (int i = 0; i < totalCourse; i ++){
                if (wcscmp(score.index, courseIdxs[i]) == 0){ //找到对应的课程
                    if (flag == 0)
                        wprintf(L"%-4ls%-18ls%-8ls%-8ls%-8ls%-8ls%-8ls%-8ls\n", L"课号", L"课名", L"0-60分", L"60-70分", L"70-80分", L"80-90分", L"90-100分", L"100分");//表头
                    flag = 1;//非表头
                    scores[i][stuCounter[i]] = score.score; //记录综合成绩score
                    stuCounter[i] ++;
                }
            }
        }
    }
    fclose(fp);

    //按分数段统计
    for (int i = 0; i < totalCourse; i ++){
        for (int j = 0; j < stuCounter[i]; j ++){
            if (scores[i][j] == 100)
                scoreSta[i][5] ++;
            else if (scores[i][j] < 100 && scores[i][j] >= 90)
                scoreSta[i][4] ++;
            else if (scores[i][j] < 90 && scores[i][j] >= 80)
                scoreSta[i][3] ++;
            else if (scores[i][j] < 80 && scores[i][j] >= 70)
                scoreSta[i][2] ++;
            else if (scores[i][j] < 70 && scores[i][j] >= 60)
                scoreSta[i][1] ++;
            else if (scores[i][j] < 60 && scores[i][j] >= 0)
                scoreSta[i][0] ++;
        }
    }

    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        for (int j = 0; j < 6; j ++){
            if (scoreSta[i][j] > 0){ 
                notSign ++; //有人报名
            }
        }
        if (notSign > 0){
            int name_width = calculate_display_width(courseNames[i]);
            wprintf(L"%-6ls%-*ls", courseIdxs[i], 20 - name_width + wcslen(courseNames[i]), courseNames[i]); //哪个课程
            for (int k = 0; k < 6; k ++){
                if (k < 5)
                    wprintf(L"%-9d", scoreSta[i][k]);
                else
                    wprintf(L"%-9d\n", scoreSta[i][k]);
            }
        }
        notSign = 0;
    }
}

// int main(){
//     setlocale(LC_ALL, "");
//     _setmode( _fileno( stdin ), _O_WTEXT );

//     // average_score();
//     // average_exam_grade();
//     // max_exam_grade();
//     // max_score();
//     // exam_statistics();
//     score_statistics();

//     return 0;
// }