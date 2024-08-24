#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
#include <fcntl.h>
#include <stdlib.h>
#include "student.h"
#include <locale.h>
#include <string.h>
#include <math.h>
#include "course.h"
#include "score.h"
#include "store_info.h"
#include "calculateScore.h"

// TODO: 增加序号

// TODO::成绩保存后计算综合成绩
// setlocale(LC_ALL, "");
// _setmode( _fileno( stdin ), _O_WTEXT );

void enterStu() {
    FILE* fptr;
    // setlocale(LC_CTYPE,"it_IT.UTF-8");
    // setlocale(LC_ALL, "en_US.utf8");
    // fptr = fopen("student.txt", "a+");fopen('test.txt','w','n','UTF-8')
    fptr = fopen("student.txt", "a+");//追加与读取同时进行
    if (fptr == NULL){
        printf("文件打开错误\n");
        return;
    }
    int total = 0;
    printf("请输入需要录入信息的学生数量:\n");
    // while (total < 1){
    wscanf(L"%d",&total);
    getwchar();//吃掉换行符
        // scanf("%d ",&total);
    // }
    // //录入学生基本信息
    //TODO:相同学号则不能保存信息
    struct Student stu, temp;
    // wint_t wc;
    // for (int i = 0; i < total; i ++){
    // scanf("%c",stu.name);
    
    // while (wide_ch = fputwc(wide_ch, fptr) == WEOF){
    //     printf("抱歉,解码错误");
    // }
    char buffer[500];//定义缓冲区
    int sameID = 0; //标记id是否相同
    // fgets(buffer, sizeof(buffer), fptr);

    // for (int i = 0; i < total; i ++){
    //     scanf("%s %s %s %s %s",stu.ID, stu.name, stu.gender, stu.age, stu.profession);
    //     // printf("total:%d\n",total);
    //     // printf("%d %s %s %d %s",stu.ID, stu.name, stu.gender, stu.age, stu.profession);
    //     // fprintf(fptr, "%d    %s    %s    %d    %s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession);
    //     // fscanf(fptr, "%d    %s    %s    %d    %s\n", &stu.ID, stu.name, stu.gender, &stu.age, stu.profession);
    //     // while (stu.name = fputwc(stu.name, fptr) == WEOF){
    //     //     printf("抱歉,解码错误");
    //     // }
    //     // gets(stu.ID);
    //     // gets(stu.name);
    //     // gets(stu.gender);
    //     // gets(stu.age);
    //     // gets(stu.profession);
    //     if (i > 0){ //需要排除相同学号的情况
    //         fseek(fptr, 0, SEEK_SET); // 定位到文件开头
    //         fgets(buffer, sizeof(buffer), fptr); //跳过表头
    //         while (fgets(buffer, sizeof(buffer), fptr)){
    //             // printf("emmn:%s,%s,%s,%s,%s\n", temp.ID, temp.name, temp.gender, temp.age, temp.profession);
    //             if (sscanf(buffer, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", temp.ID, temp.name, temp.gender, temp.age, temp.profession) == 5){ //解析每一行
    //                 // printf("okk:%s,%s,%s,%s,%s\n", temp.ID, temp.name, temp.gender, temp.age, temp.profession);
    //                 if (strcmp(stu.ID, temp.ID) == 0){ //学号重复
    //                     printf("same:i,%d,%s,%s,%s,%s,%s\n", i, temp.ID, temp.name, temp.gender, temp.age, temp.profession);
    //                     sameID = 1;
    //                     break;
    //                 }
    //             }
    //         }
    //     }
    //     if (sameID == 0)
    //         fprintf(fptr, "%s,%s,%s,%s,%s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession);
    //     if (sameID == 1)
    //         printf("学号重复出现，请重新输入\n");
    // }
    // fclose(fptr);
    if (total > 0)
        printf("请输入学生信息 (依次为ID, 姓名, 性别, 年龄和专业，中间使用回车键): \n");
    else{
        printf("录入学生数量错误。\n");
        return;
    }
    wchar_t wbuffer[500];//定义宽字符数组
    for (int i = 0; i < total; i++) {
        sameID = 0;//重置sameID
        fgetws(stu.ID, sizeof(stu.ID), stdin);
        stu.ID[wcslen(stu.ID) - 1] = L'\0';//手动读取换行符

        fgetws(stu.name, sizeof(stu.name), stdin);
        stu.name[wcslen(stu.name) - 1] = L'\0';

        fgetws(stu.gender, sizeof(stu.gender), stdin);
        stu.gender[wcslen(stu.gender) - 1] = L'\0';

        fgetws(stu.age, sizeof(stu.age), stdin);
        stu.age[wcslen(stu.age) - 1] = L'\0';

        fgetws(stu.profession, sizeof(stu.profession), stdin);
        stu.profession[wcslen(stu.profession) - 1] = L'\0';
        // wscanf(L"%ls %ls %ls %ls %ls", stu.ID, stu.name, stu.gender, stu.age, stu.profession);

        // 将文件指针移到开头，排除相同学号的情况
        fseek(fptr, 0, SEEK_SET);

        // 检查学号是否重复
        fgets(buffer, sizeof(buffer), fptr); //跳过表头
        while (fgets(buffer, sizeof(buffer), fptr)){
            //char->wchar_t
            mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));
            if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", temp.ID, temp.name, temp.gender, temp.age, temp.profession) == 5) {//解析宽字符数组
                // wprintf(L"%ls %ls %ls %ls %ls", temp.ID, temp.name, temp.gender, temp.age, temp.profession);
                if (wcscmp(stu.ID, temp.ID) == 0) {
                    sameID = 1;
                    break;
                }
            }
        }

        if (sameID == 0) {
            fwprintf(fptr, L"%ls,%ls,%ls,%ls,%ls\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession);
            // wprintf(L"录入信息：%ls,%ls,%ls,%ls,%ls\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession);//显示录入信息
            printf("学生信息已录入！\n");
        } else {
            printf("学号重复出现，请重新输入。\n");
            i--; // 重新输入当前学生信息
        }
    }
    fclose(fptr);
    // fptr = fopen("student.txt", "r");
    // 刷新缓冲区
    //fflush(fptr);
    
    // 重置文件指针到文件开头
    //fseek(fptr, 0, SEEK_SET);

    // while (fgets(buffer, sizeof(buffer), fptr) != NULL){
    //     printf("%s",buffer);
    // }
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
    // fclose(fptr);
}

void enterCourse(){
    FILE* fptr;
    fptr = fopen("course.txt", "a+"); //追加与读取同时进行
    if (fptr == NULL){
        printf("文件打开错误\n");
        return;
    }
    int total = 0;
    printf("请输入需要录入信息的课程数量：\n");
    wscanf(L"%d",&total);
    getwchar();//吃掉换行符
    //录入课程基本信息
    //TODO:不同课程号码相同，不能保存
    struct Course course, temp;
    int sameIdx = 0;
    char buffer[500];//定义缓冲区
    wchar_t wbuffer[500];//宽字符
    if (total > 0)
        printf("请输入需要录入的课程信息（依次为课号、课名和任课老师，中间按回车键）：\n");
    else{
        printf("录入课程数量错误。\n");
        return;
    }
    for (int i = 0; i < total; i ++){
        sameIdx = 0;//重置sameIdx
        fgetws(course.index, sizeof(course.index), stdin);
        course.index[wcslen(course.index) - 1] = L'\0';//手动读取换行符

        fgetws(course.name, sizeof(course.name), stdin);
        course.name[wcslen(course.name) - 1] = L'\0';//手动读取换行符

        fgetws(course.teacher, sizeof(course.teacher), stdin);
        course.teacher[wcslen(course.teacher) - 1] = L'\0';//手动读取换行符
        // wscanf(L"%ls %ls %ls", course.index, course.name, course.teacher);
        // fprintf(fptr, "%s,%s,%s\n", course.index, course.name, course.teacher);
        // 将文件指针移到开头，排除相同课号的情况
        fseek(fptr, 0, SEEK_SET);

        // 检查学号是否重复
        fgets(buffer, sizeof(buffer), fptr); //跳过表头
        while (fgets(buffer, sizeof(buffer), fptr)) {
            mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
            if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]", temp.index, temp.name, temp.teacher) == 3) {
                if (wcscmp(course.index, temp.index) == 0) {
                    sameIdx = 1;
                    break;
                }
            }
        }

        if (sameIdx == 0) {
            fwprintf(fptr, L"%ls,%ls,%ls\n", course.index, course.name, course.teacher);
            // wprintf(L"录入信息：%ls,%ls,%ls\n", course.index, course.name, course.teacher);//显示录入信息
            printf("课程信息已录入！\n");
        } else {
            printf("课号重复出现，请重新输入。\n");
            i--; // 重新输入当前课程信息
        }
    }
    fclose(fptr);

    //显示课程基本信息
    // fptr = fopen("course.txt", "r"); 
    // while (fgets(buffer, sizeof(buffer), fptr) != NULL){
    //     printf("%s",buffer);
    // }
    // fclose(fptr);

}

// double calculate_score(wchar_t* idx, double score0, double score1){ //计算综合成绩
//     if (idx[0] == L'S')//专业课
//         return score0 * 0.4 + score1 * 0.6;
//     if (idx[0] == L'P')//公共课
//         return score0 * 0.3 + score1 * 0.7;
// }

void enterScore(){
    FILE* fptr;
    fptr = fopen("score.txt", "a");
    if (fptr == NULL){
        printf("文件打开失败\n");
        return;
    }
    int total = 0;
    printf("请输入需要录入成绩的数量：\n");
    wscanf(L"%d",&total);
    getwchar();

    //录入学生成绩信息
    struct Score score;//定义结构体
    int saveLabel;
    printf("请输入需要录入的成绩信息，依次为学号、课号、平时成绩和卷面成绩，中间使用回车键：\n");
    for (int i = 0; i < total; i ++){
        // scanf("%s %s %lf %lf", score.ID, score.index, &score.daily_grade, &score.exam_grade);
        fgetws(score.ID, sizeof(score.ID), stdin);
        score.ID[wcslen(score.ID) - 1] = L'\0';
        fgetws(score.index, sizeof(score.index), stdin);
        score.index[wcslen(score.index) - 1] = L'\0';

        wscanf(L"%lf", &score.daily_grade);
        // wprintf(L"平时：%lf\n", score.daily_grade);
        getwchar();
        wscanf(L"%lf", &score.exam_grade);
        // wprintf(L"卷面：%lf\n", score.exam_grade);
        getwchar();
        printf("请选择是否保存学生成绩：0-是,1-否\n");
        
        wscanf(L"%d", &saveLabel); //选择是否保存成绩
        getwchar();
        if (saveLabel == 0){
            score.score = calculate_score(score.index, score.daily_grade, score.exam_grade);//计算综合成绩
            fwprintf(fptr, L"%ls,%ls,%d,%d,%.1f\n", score.ID, score.index, (int)ceil(score.daily_grade), (int)ceil(score.exam_grade), (float)score.score);
            printf("成绩信息已录入！\n");
        }
    }
    fclose(fptr);
    // //显示成绩信息
    // fptr = fopen("score.txt", "r");
    // if (fptr == NULL){
    //     printf("文件打开错误\n");
    //     return;//退出文件
    // }
    // //逐行读文件
    // int grade_temp1, grade_temp2;
    // while (fscanf(fptr, "%49[^,],%49[^,],%d,%d\n", score.ID, score.index, &grade_temp1, &grade_temp2) == 4){
    //     score.daily_grade = (double)grade_temp1;
    //     score.exam_grade = (double)grade_temp2;
    //     printf("%s,%s,%d,%d\n", score.ID, score.index, (int)score.daily_grade, (int)score.exam_grade);
    // }
    // //处理错误情况
    // // if (ferror(fptr)) {
    // //     printf("读取文件时发生错误\n");
    // // }
    // fclose(fptr);

    

}

// int main(){
//     // setlocale(LC_CTYPE,"it_IT.UTF-8");//区域设置
//     setlocale(LC_ALL, "");
//     _setmode( _fileno( stdin ), _O_WTEXT );
//     enterStu();
// //     // course();
// //     score();

// //     return 0;
// }