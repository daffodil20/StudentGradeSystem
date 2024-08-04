// show feature of score of every course
#include <stdio.h>
#include "score.h"
#include "course.h"
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_TOTAL_COURSE 100
#define MAX_STU_PER_COURSE 50
void average_score(){ //综合成绩平均分
    FILE *fp;
    struct Score score;
    struct Course course;
    float totalScore[MAX_TOTAL_COURSE] = {0.0};//, aveScore[MAX_TOTAL_COURSE]; //存储课程总分和平均分的数组
    char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0};//每门课人数
    
    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            strcpy(courseIdxs[totalCourse], course.index); //记录课号
            strcpy(courseNames[totalCourse], course.name); //记录课名
        }
        totalCourse ++; //统计课程数量
    } 
    fclose(fp);
    
    //计算每门课程平均分
    fp = fopen("score.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < MAX_TOTAL_COURSE; i ++){
                if (strcmp(score.index, courseIdxs[i]) == 0){ //课程匹配
                    totalScore[i] += (float)score.score; //计算total score
                    stuCounter[i] ++;
                    break;
                }
            }
        }
    }
    fclose(fp);
    
    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0){ //有人报名
            printf("average score: %s,%s,%.1f\n", courseIdxs[i], courseNames[i], totalScore[i] / stuCounter[i]);
        }
    }  
}

void average_exam_grade(){ //卷面成绩平均分
    FILE *fp;
    struct Score score;
    struct Course course;
    float totalExamGrade[MAX_TOTAL_COURSE] = {0.0}; //存储课程总分和平均分的数组
    char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0};//每门课人数
    
    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            strcpy(courseIdxs[totalCourse], course.index); //记录课号
            strcpy(courseNames[totalCourse], course.name); //记录课名
        }
        totalCourse ++; //统计课程数量
    } 
    fclose(fp);
    
    //计算每门课程平均分
    fp = fopen("score.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (strcmp(score.index, courseIdxs[i]) == 0){ //课程匹配
                    totalExamGrade[i] += (float)score.exam_grade; //计算卷面成绩
                    stuCounter[i] ++;
                    break;
                }
            }
        }
    }
    fclose(fp);
    
    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0){ //有人报名
            printf("average exam grade: %s,%s,%.1f\n", courseIdxs[i], courseNames[i], totalExamGrade[i] / stuCounter[i]);
        }
    }  
}

void max_exam_grade(){ //卷面成绩最高分
    FILE *fp;
    struct Score score;
    struct Course course;
    int ExamGrade[MAX_TOTAL_COURSE][MAX_STU_PER_COURSE] = {0}; //存储不同课程所有选修学生卷面成绩的数组
    char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0}, tmp;//存储课程数目和选修人数
    
    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            strcpy(courseIdxs[totalCourse], course.index); //记录课号
            strcpy(courseNames[totalCourse], course.name); //记录课名
        }
        totalCourse ++; //统计课程数量
    } 
    fclose(fp);
    
    //统计卷面分数
    fp = fopen("score.txt", "r");
    fgets(line, sizeof(line), fp);
    
    
    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (strcmp(score.index, courseIdxs[i]) == 0){ //课程匹配
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
    
    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0) //有人报名
            printf("maximum exam grade: %s,%s,%d\n", courseIdxs[i], courseNames[i], ExamGrade[i][0]);
    }
}

void max_score(){ //综合成绩最高分
    FILE *fp;
    struct Score score;
    struct Course course;
    double Scores[MAX_TOTAL_COURSE][MAX_STU_PER_COURSE] = {0}; //存储不同课程所有选修学生综合成绩的数组
    char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0}, tmp;//存储课程数目和选修人数
    
    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            strcpy(courseIdxs[totalCourse], course.index); //记录课号
            strcpy(courseNames[totalCourse], course.name); //记录课名
        }
        totalCourse ++; //统计课程数量
    } 
    fclose(fp);
    
    //统计综合成绩
    fp = fopen("score.txt", "r");
    fgets(line, sizeof(line), fp);
    
    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (strcmp(score.index, courseIdxs[i]) == 0){ //课程匹配
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
    
    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        if (stuCounter[i] != 0) //有人报名
            printf("maximum score: %s,%s,%.1f\n", courseIdxs[i], courseNames[i], (float)Scores[i][0]);
    }
}


void exam_statistics(){ //卷面分数分数段人数统计
    int examSta[MAX_TOTAL_COURSE][6] = {0}; //分数段 
    FILE *fp;
    struct Score score;
    struct Course course;
    int ExamGrade[MAX_TOTAL_COURSE][MAX_STU_PER_COURSE] = {0}; //存储不同课程所有选修学生卷面成绩的数组
    char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0}, tmp;//存储课程数目和选修人数
    int notSign = 0;

    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            strcpy(courseIdxs[totalCourse], course.index); //记录课号
            strcpy(courseNames[totalCourse], course.name); //记录课名
        }
        totalCourse ++; //统计课程数量
    } 
    fclose(fp);

    //遍历score.txt
    fp = fopen("score.txt", "r");
    fgets(line, sizeof(line), fp);
    
    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (strcmp(score.index, courseIdxs[i]) == 0){ //找到对应的课程
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
            else
                printf("成绩范围错误，不计入。\n");
        }
    }

    //输出结果
    for (int i = 0; i < totalCourse; i ++){
        for (int j = 0; j < 6; j ++){
            if (examSta[i][j] > 0){ 
                notSign ++; //
            }
        }
        if (notSign > 0){
            printf("course: %s,%s\n", courseIdxs[i], courseNames[i]); //哪个课程
            printf("0-60: %d ", examSta[i][0]);
            printf("60-70: %d ", examSta[i][1]);
            printf("70-80: %d ", examSta[i][2]);
            printf("80-90: %d ", examSta[i][3]);
            printf("90-100: %d ", examSta[i][4]);
            printf("100: %d\n\n", examSta[i][5]);
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
    char line[MAX_LINE_LENGTH], courseIdxs[MAX_TOTAL_COURSE][50], courseNames[MAX_TOTAL_COURSE][50];
    int totalCourse = 0, stuCounter[MAX_TOTAL_COURSE] = {0}, tmp;//存储课程数目和选修人数
    int notSign = 0;

    //遍历course文件
    fp = fopen("course.txt", "r");
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ 
            strcpy(courseIdxs[totalCourse], course.index); //记录课号
            strcpy(courseNames[totalCourse], course.name); //记录课名
        }
        totalCourse ++; //统计课程数量
    } 
    fclose(fp);

    //遍历score.txt
    fp = fopen("score.txt", "r");
    fgets(line, sizeof(line), fp);
    
    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            for (int i = 0; i < totalCourse; i ++){
                if (strcmp(score.index, courseIdxs[i]) == 0){ //找到对应的课程
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
            else
                printf("成绩范围错误，不计入。\n");
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
            printf("课程: %s,%s\n综合成绩分数段（单位：人）：\n", courseIdxs[i], courseNames[i]); //哪个课程
            printf("0-60分: %d ", scoreSta[i][0]);
            printf("60-70分: %d ", scoreSta[i][1]);
            printf("70-80分: %d ", scoreSta[i][2]);
            printf("80-90分: %d ", scoreSta[i][3]);
            printf("90-100分: %d ", scoreSta[i][4]);
            printf("100分: %d\n\n", scoreSta[i][5]);
        }
        notSign = 0;
    }
}

int main(){
    // average_score();
    // average_exam_grade();
    // max_exam_grade();
    // max_score();
    // exam_statistics();
    score_statistics();

    return 0;
}