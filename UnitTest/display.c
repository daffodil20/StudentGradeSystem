#include "student.h"
#include "score.h"
#include "course.h"
#include "display.h"
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <wctype.h>
#include "print_format.h"
// show all information of students
//逐行读score.txt
//对照student.txt的id和course.txt的index
//显示信息
// 格式:学生 ID,name,gender,age,profession
//      课程及成绩 course name,s1,s2,s
// #define MAX_LINE_LENGTH 256
void display(){
    FILE *fp1, *fp2, *fp3;
    
    // fp2 = fopen("student.txt", "r");
    // fp3 = fopen("course.txt", "r");
    
    if (fp1 == NULL){
        printf("文件打开失败\n");
        return;
    }

    //建立结构体变量
    struct Student stu;
    struct Score score;
    struct Course course;
    char scoreLine[MAX_LINE_LENGTH], stuLine[MAX_LINE_LENGTH], courseLine[MAX_LINE_LENGTH];
    wchar_t wscoreLine[MAX_LINE_LENGTH], wstuLine[MAX_LINE_LENGTH], wcourseLine[MAX_LINE_LENGTH];
    int matched = 0;//记录学生是否有成绩

    // //跳过表头
    // fgets(scoreLine, sizeof(scoreLine), fp1);

    // while (fgets(scoreLine, sizeof(scoreLine), fp1)){ //逐行读score.txt
    //     if (sscanf(scoreLine, "%49[^,],%49[^,],%lf,%lf,%lf", score.ID, score.index, &(score.daily_grade), &(score.exam_grade), &(score.score)) == 5){ //解析字符串
    //         fp2 = fopen("student.txt", "r");
    //         if (fp2 == NULL){
    //             printf("文件打开失败\n");
    //             return;
    //         }
    //         //跳过表头
    //         fgets(stuLine, sizeof(stuLine), fp2);
    //         while (fgets(stuLine, sizeof(stuLine), fp2)){ //查找student.txt
    //             if (sscanf(stuLine, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
    //                 if (strcmp(stu.ID, score.ID) == 0){ //找到对应的学生信息
    //                     printf("\nstudent:%s,%s,%s,%s,%s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession);
    //                     fclose(fp2);
    //                     break;
    //                 }
    //             }       
    //         }

    //         fp3 = fopen("course.txt", "r");
    //         if (fp3 == NULL){
    //             printf("文件打开失败\n");
    //             return;
    //         }
    //         //跳过表头
    //         fgets(courseLine, sizeof(courseLine), fp3);
    //         while (fgets(courseLine, sizeof(courseLine), fp3)){ //查找course.txt
    //             if (sscanf(courseLine, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ //查找course.txt
    //                 if (strcmp(course.index, score.index) == 0){ //找到对应的课程信息
    //                     printf("course and score:%s,%s,%s,%d,%d,%.1f\n", course.index, course.name, course.teacher, (int)score.daily_grade, (int)score.exam_grade, (float)score.score);
    //                     // fclose(fp3);
    //                     //继续寻找是否有下一门课是这个学生报的
    //                 }
    //             }
    //         }
    //         fclose(fp3);
    //     }
    // }
    fp1 = fopen("student.txt", "r");//只读模式
    fgets(stuLine, sizeof(stuLine), fp1); //跳过表头

    while (fgets(stuLine, sizeof(stuLine), fp1)){ //逐行读student.txt
        mbstowcs(wstuLine, stuLine, sizeof(wstuLine) / sizeof(wchar_t));
        if (swscanf(wstuLine, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){ //解析字符串
            int name_width = calculate_display_width(stu.name);
            wprintf(L"\n%-12ls%-12ls%-5ls%-5ls%-10ls\n", L"学号", L"姓名", L"性别", L"年龄", L"所在系");//
            wprintf(L"%-14ls%-*ls%-6ls%-7ls%-8ls\n", stu.ID, 14 - name_width + wcslen(stu.name), stu.name, stu.gender, stu.age, stu.profession);
            fp2 = fopen("score.txt", "r");
            if (fp2 == NULL){
                printf("文件打开失败\n");
                return;
            }
            //跳过表头
            fgets(scoreLine, sizeof(scoreLine), fp2);

            while (fgets(scoreLine, sizeof(scoreLine), fp2)){ //查找score.txt中的id和index
                mbstowcs(wscoreLine, scoreLine, sizeof(wscoreLine) / sizeof(wchar_t));
                if (swscanf(wscoreLine, L"%49[^,],%49[^,],%lf,%lf,%lf",score.ID, score.index, &(score.daily_grade), &(score.exam_grade), &(score.score)) == 5){
                    if (wcscmp(stu.ID, score.ID) == 0){ //找到对应的成绩信息
                        // printf("\n\nstudent:%s,%s,%s,%s,%s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession);
                        matched = 1;//学生有成绩

                        fp3 = fopen("course.txt", "r");
                        if (fp3 == NULL){
                            printf("文件打开失败\n");
                            return;
                        }
                        //跳过表头
                        fgets(courseLine, sizeof(courseLine), fp3);
                        
                        while (fgets(courseLine, sizeof(courseLine), fp3)){ //查找course.txt中的index
                            mbstowcs(wcourseLine, courseLine, sizeof(wcourseLine) / sizeof(wchar_t));
                            if (swscanf(wcourseLine, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){
                                if (wcscmp(course.index, score.index) == 0){ //找到对应的课程信息
                                    int name_width = calculate_display_width(course.name);
                                    int teacher_width = calculate_display_width(course.teacher);
                                    wprintf(L"%-12ls%-12ls%-12ls\n", L"课号", L"课名", L"任课老师");
                                    wprintf(L"%-14ls%-*ls%-*ls\n", course.index, 14 - name_width + wcslen(course.name), course.name, 12 - teacher_width + wcslen(course.teacher), course.teacher);
                                    wprintf(L"%-10ls%-10ls%-10ls\n", L"平时成绩", L"卷面成绩", L"综合成绩");
                                    wprintf(L"%-14d%-14d%-12.1f\n", (int)score.daily_grade, (int)score.exam_grade, (float)score.score);
                                    fclose(fp3);
                                    break;
                                    // fclose(fp3);
                                    //继续寻找是否有下一门课是这个学生报的
                                }
                            }
                        }
                    }
                }
            }
            fclose(fp2);
            if (matched == 0){
                printf("该学生没有选修课程。\n");
            }
            matched = 0;
        }
    }
    //                     fclose(fp2);
    //                     break;
    //                 }
    //             }       
    //         }

    //         fp3 = fopen("course.txt", "r");
    //         if (fp3 == NULL){
    //             printf("文件打开失败\n");
    //             return;
    //         }
    //         //跳过表头
    //         fgets(courseLine, sizeof(courseLine), fp3);
    //         while (fgets(courseLine, sizeof(courseLine), fp3)){ //查找course.txt
    //             if (sscanf(courseLine, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){ //查找course.txt
    //                 if (strcmp(course.index, score.index) == 0){ //找到对应的课程信息
    //                     printf("course and score:%s,%s,%s,%d,%d,%.1f\n", course.index, course.name, course.teacher, (int)score.daily_grade, (int)score.exam_grade, (float)score.score);
    //                     // fclose(fp3);
    //                     //继续寻找是否有下一门课是这个学生报的
    //                 }
    //             }
    //         }
    //         fclose(fp3);
    //     }
    // }
    
    // 关闭文件
    fclose(fp1);
    // fclose(fp2);
    // fclose(fp3);
    
}

// int main(){
//     setlocale(LC_ALL, "");
//     _setmode( _fileno( stdin ), _O_WTEXT );
//     display();

//     return 0;
// }