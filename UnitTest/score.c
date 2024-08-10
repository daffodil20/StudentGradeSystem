// #include <stdio.h>
// #include "student.h"
// #include <locale.h>
// #include <string.h>
// #include "score.h"
// void calculate(){
//     int char_counter = 0, line_counter = 0, DailyGrade, ExamGrade;
//     struct Score score;
//     FILE* fp;
//     fp = fopen("score.txt", "r");
   
//     while (fscanf(fp, "%49[^,],%49[^,],%d,%d\n", score.ID, score.index, &DailyGrade, &ExamGrade) == 4){ //逐行读文件
//         fclose(fp);
//         fp = fopen("score.txt", "a");//切换模式
//         line_counter ++;
        
//         score.daily_grade = (double)DailyGrade;//类型转换
//         score.exam_grade = (double)ExamGrade;

//         if (score.index[0] == 'P'){
//             score.score = score.daily_grade * 0.3 + score.exam_grade * 0.7;
//         } //公共课
//         if (score.index[0] == 'S'){
//             score.score = score.daily_grade * 0.4 + score.exam_grade * 0.7;
//         } //专业课
//         printf("grade:%lf\n",score.score);
//         //定位综合成绩的位置
//         fseek(fp, line_counter, SEEK_SET);//行首
//         fprintf(fp, "%d,hello!", line_counter);
//         // //判断成绩是几位数
//         if (DailyGrade / 10 < 10 && DailyGrade / 10 > 0){
//             char_counter += 2;//两位数
//         }
//         if (DailyGrade / 10 >= 10){
//             char_counter += 3;//三位数
//         }
//         if (DailyGrade / 10 == 0){
//             char_counter += 1;
//         }

//         if (ExamGrade / 10 < 10 && ExamGrade / 10 > 0){
//             char_counter += 2;//两位数
//         }
//         if (ExamGrade / 10 >= 10){
//             char_counter += 3;//三位数
//         }
//         if (ExamGrade / 10 == 0){
//             char_counter += 1;
//         }
//         fseek(fp, char_counter + strlen(score.ID) + strlen(score.index) + 3-1, SEEK_CUR);//填写综合成绩的位置
//         fprintf(fp, ",%d", (double)score.score);//录入综合成绩
        
//         fclose(fp);
//         fp = fopen("score.txt", "r");//切换模式
//         char_counter = 0;
//     }
//     fclose(fp);
// }

// int main(){
//     setlocale(LC_CTYPE,"it_IT.UTF-8");//区域设置
//     calculate();
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

#define MAX_LINE_LENGTH 256

void calculate(){ //计算综合成绩
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    char *lines[MAX_LINE_LENGTH];
    int line_count = 0;

    // 读取文件内容到内存
    fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        lines[line_count] = strdup(buffer); // 保存每一行到内存
        line_count++;
    }
    fclose(fp);

    // 打开文件以写入数据
    fp = fopen("score.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    for (int i = 0; i < line_count; i++) {
        struct Score score;
        int DailyGrade, ExamGrade;

        // 解析每一行数据
        sscanf(lines[i], "%49[^,],%49[^,],%d,%d\n", score.ID, score.index, &DailyGrade, &ExamGrade);
        
        score.daily_grade = (double)DailyGrade;
        score.exam_grade = (double)ExamGrade;

        // 计算综合成绩
        if (score.index[0] == 'P') {
            score.score = score.daily_grade * 0.3 + score.exam_grade * 0.7;
        } else if (score.index[0] == 'S') {
            score.score = score.daily_grade * 0.4 + score.exam_grade * 0.6;
        }

        // 写入数据到文件
        fprintf(fp, "%s,%s,%d,%d,%.2f\n", score.ID, score.index, DailyGrade, ExamGrade, score.score);
        free(lines[i]); // 释放内存
    }
    
    fclose(fp);
}

int main() {
    calculate();
    return 0;
}
