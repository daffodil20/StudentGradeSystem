#include <stdio.h>
#include "student.h"
#include <locale.h>
//#include <wchar.h>
#include <string.h>
#include <math.h>
#include "course.h"
#include "score.h"
void student(){
    FILE* fptr;
    // setlocale(LC_CTYPE,"it_IT.UTF-8");
    // setlocale(LC_ALL, "en_US.utf8");
    // fptr = fopen("student.txt", "a+");fopen('test.txt','w','n','UTF-8')
    fptr = fopen("student.txt", "a");
    if (fptr == NULL)
        printf("文件打开错误\n");
    int total = 0;
    printf("请输入需要录入信息的学生数量:");
    while (total < 1){
        scanf("%d",&total);
    }
    // //录入学生基本信息
    //TODO:相同学号则不能保存信息
    struct Student stu;
    // wint_t wc;
    // for (int i = 0; i < total; i ++){
    // scanf("%c",stu.name);
    
    // while (wide_ch = fputwc(wide_ch, fptr) == WEOF){
    //     printf("抱歉,解码错误");
    // }
    char buffer[500];//定义缓冲区
    for (int i = 0; i < total; i ++){
        scanf("%s %s %s %s %s",stu.ID, stu.name, stu.gender, stu.age, stu.profession);
        // printf("total:%d\n",total);
        // printf("%d %s %s %d %s",stu.ID, stu.name, stu.gender, stu.age, stu.profession);
        // fprintf(fptr, "%d    %s    %s    %d    %s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession);
        // fscanf(fptr, "%d    %s    %s    %d    %s\n", &stu.ID, stu.name, stu.gender, &stu.age, stu.profession);
        // while (stu.name = fputwc(stu.name, fptr) == WEOF){
        //     printf("抱歉,解码错误");
        // }
        // gets(stu.ID);
        // gets(stu.name);
        // gets(stu.gender);
        // gets(stu.age);
        // gets(stu.profession);

        fprintf(fptr, "%s,%s,%s,%s,%s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession);

    }
    fclose(fptr);

    fptr = fopen("student.txt", "r");
    // 刷新缓冲区
    //fflush(fptr);
    
    // 重置文件指针到文件开头
    //fseek(fptr, 0, SEEK_SET);

    while (fgets(buffer, sizeof(buffer), fptr) != NULL){
        printf("%s",buffer);
    }
        // for (int j = 0; j < strlen(stu.name); j ++){
    // fputwc(L'a', fptr);
    // fputwc(L'🍌', fptr);
    //     }
        // fputwc(stu.name, fptr);
        // fprint(fptr, &stu.);
        // fputwc(stu.name, fptr);
        // fputwc(stu.name, fptr);
        // 
    // }
    // while ((wc = fgetwc(fptr)) != WEOF){
    //     putwchar(wc);
    // }
    fclose(fptr);
}

void course(){
    FILE* fptr;
    fptr = fopen("course.txt", "a");
    if (fptr == NULL)
        printf("文件打开错误\n");
    int total = 0;
    printf("请输入需要录入信息的课程数量：");
    while (total < 1){
        scanf("%d",&total);
    }

    //录入课程基本信息
    //TODO:不同课程号码相同，不能保存
    struct Course course;
    char buffer[500];//定义缓冲区
    for (int i = 0; i < total; i ++){
        scanf("%s %s %s", course.index, course.name, course.teacher);
        fprintf(fptr, "%s,%s,%s\n", course.index, course.name, course.teacher);
    }
    fclose(fptr);

    //显示课程基本信息
    fptr = fopen("course.txt", "r"); 
    while (fgets(buffer, sizeof(buffer), fptr) != NULL){
        printf("%s",buffer);
    }
    fclose(fptr);

}

void score(){
    FILE* fptr;
    fptr = fopen("score.txt", "a");
    if (fptr == NULL){
        printf("文件打开失败\n");
        return;
    }
    int total = 0;
    printf("请输入需要录入成绩的学生数量：");
    while (total < 1){
        scanf("%d",&total);
    }

    //录入学生成绩信息
    struct Score score;//定义结构体
    for (int i = 0; i < total; i ++){
        scanf("%s %s %lf %lf", score.ID, score.index, &score.daily_grade, &score.exam_grade);
        fprintf(fptr, "%s,%s,%d,%d\n", score.ID, score.index, (int)ceil(score.daily_grade), (int)ceil(score.exam_grade));
    }
    fclose(fptr);

    //显示成绩信息
    fptr = fopen("score.txt", "r");
    if (fptr == NULL){
        printf("文件打开错误\n");
        return;//退出文件
    }
    //逐行读文件
    int grade_temp1, grade_temp2;
    while (fscanf(fptr, "%49[^,],%49[^,],%d,%d\n", score.ID, score.index, &grade_temp1, &grade_temp2) == 4){
        score.daily_grade = (double)grade_temp1;
        score.exam_grade = (double)grade_temp2;
        printf("%s,%s,%d,%d\n", score.ID, score.index, (int)score.daily_grade, (int)score.exam_grade);
    }
    //处理错误情况
    // if (ferror(fptr)) {
    //     printf("读取文件时发生错误\n");
    // }
    fclose(fptr);

}

int main(){
    setlocale(LC_CTYPE,"it_IT.UTF-8");//区域设置

    // student();
    // course();
    score();

    return 0;
}