#include <stdio.h>
#include "student.h"
#include <locale.h>
#include <string.h>
#include <math.h>
#include "course.h"
#include "score.h"
double calculate(){

    struct Score score;
    FILE* fp;
    fp = fopen("score.txt", "r");
    //逐行读文件
    while (fscanf(fp, "%s %s %d %d", id, idx, &DailyGrade, &ExamGrade) == 2){
        line_counter ++;
        
        score.daily_grade = DailyGrade;   
        score.exam_grade = ExamGrade;
        if (score.index[0] == 'P'){
            score.score = score.daily_grade * 0.3 + score.exam_grade * 0.7;
        } //公共课
        if (score.index[0] == 'S'){
            score.score = score.daily_grade * 0.4 + score.exam_grade * 0.7;
        } //专业课
        
        //定位综合成绩的位置
        fseek(fp, line_counter, SEEK_SET);//行首
        char_counter = 
        fseek(fp, )
    }
    //把综合成绩写入文件
    while ()

}