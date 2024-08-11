#include "student.h"
#include "score.h"
#include "course.h"
#include <stdio.h>
#include <string.h>
#include "search.h"

// #define MAX_LINE_LENGTH 256
void find_stu(char* id, char* inputName){
    struct Student stu;
    FILE* fp;
    char line[MAX_LINE_LENGTH];
    int searched = 0;
    
    // 输入正确
    fp = fopen("student.txt", "r");
    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
            if (strcmp(stu.name, inputName) == 0 && strcmp(stu.ID, id) == 0){ //匹配成功
                searched = 1; //搜索成功
                printf("学号 姓名 性别 年龄 所在系\n");
                printf("%s,%s,%s,%s,%s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession); //显示学生基本信息
                break;
            }
        }
    }

    if (searched == 0){
        printf("搜索失败,学号或姓名错误.\n");
        return;
    }
    fclose(fp);
}

void find_course(char* idx, char* courseName){ //根据课名与课号查找课程基本信息
    struct Course course;
    FILE* fp;
    char line[MAX_LINE_LENGTH];
    int searched = 0;
    
    // 输入正确
    fp = fopen("course.txt", "r");
    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^\n]",course.index, course.name, course.teacher) == 3){
            if (strcmp(course.name, courseName) == 0 && strcmp(course.index, idx) == 0){ //匹配成功
                searched = 1; //搜索成功
                printf("课号 课名 任课老师\n");
                printf("%s,%s,%s\n", course.index, course.name, course.teacher); //显示课程基本信息
                break;
            }
        }
    }

    if (searched == 0){
        printf("搜索失败,课号或课名错误.\n");
        return;
    }
    fclose(fp);
}

void find_gender(char* gender){ //按性别查找学生基本信息
    struct Student stu;
    FILE* fp;
    char line[MAX_LINE_LENGTH];

    //输入错误
    if (strcmp(gender, "female") != 0 && strcmp(gender, "male") != 0){
        printf("输入错误,请输入男/女:\n");
        return;
    }
    
    // 输入正确
    fp = fopen("student.txt", "r");
    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
            if (strcmp(stu.gender, gender) == 0){ //性别相同
                printf("%s,%s,%s,%s,%s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession); //显示学生基本信息
            }
        }
    }

    fclose(fp);
}

void find_profession(char* profession){
    struct Student stu;
    FILE* fp;
    char line[MAX_LINE_LENGTH];
    int searched = 0;
    
    // 输入正确
    fp = fopen("student.txt", "r");
    while (fgets(line, sizeof(line), fp)){
        if (sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
            if (strcmp(stu.profession, profession) == 0){ //专业相同
                searched = 1; //标记搜索成功
                printf("%s,%s,%s,%s,%s\n", stu.ID, stu.name, stu.gender, stu.age, stu.profession); //显示学生基本信息
            }           
        }
    }

    //输入错误(搜索失败)
    if (searched == 0){
        printf("搜索失败,输入系的名称不存在.\n");
        return;
    }
    
    fclose(fp);
}

void find_score0(char* id, char* name){ //根据学号和姓名查询成绩
    //逐行读score.txt
    struct Score score;
    struct Student stu;
    struct Course course;
    FILE *fp1, *fp2, *fp3;
    char courseLine[MAX_LINE_LENGTH], stuLine[MAX_LINE_LENGTH], scoreLine[MAX_LINE_LENGTH];
    int searched = 0;
    
    // 输入正确
    if (fp1 == NULL){
        printf("文件打开失败\n");
        return;
    }
    fp1 = fopen("score.txt", "r");
    fgets(scoreLine, sizeof(scoreLine), fp1);
    while (fgets(scoreLine, sizeof(scoreLine), fp1)){ //查找有报名课程的学生的id
        if (sscanf(scoreLine, "%49[^,],%49[^,],%lf,%lf,%lf",score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            if (strcmp(score.ID, id) == 0){ //学号匹配
                fp2 = fopen("student.txt", "r"); //标记姓名
                fgets(stuLine, sizeof(stuLine), fp2);

                while (fgets(stuLine, sizeof(stuLine), fp2)){
                    if (sscanf(stuLine, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
                        if (strcmp(stu.ID, id) == 0 && strcmp(stu.name, name) == 0){  //学号与姓名相对应
                            searched = 1; //搜索成功
                            fclose(fp2);
                            break;
                        }
                    }
                }
                if (searched == 1){ //根据课号
                    fp3 = fopen("course.txt", "r");
                    fgets(courseLine, sizeof(courseLine), fp3);

                    while (fgets(courseLine, sizeof(courseLine), fp3)){
                        if (sscanf(courseLine, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){
                            if (strcmp(score.index, course.index) == 0){ //课号相同
                                printf("%s,%s,%d,%d,%.1f\n", score.index, course.name, (int)score.daily_grade, (int)score.exam_grade, (float)score.score);
                                fclose(fp3);
                                break;//停止查找
                            }
                        }
                    }
                }
            }
        }
    }
    
    // 输入错误
    if (searched == 0){
        printf("搜索失败,学号或姓名错误.\n");
        return;
    }
    fclose(fp1);
}

// score.txt(idx)-course.txt(id exist)-student.txt(grade)
void find_score1(char* idx, char* name){ //根据课号和课名查询成绩
    //逐行读score.txt
    struct Score score;
    struct Student stu;
    struct Course course;
    FILE *fp1, *fp2, *fp3;
    char courseLine[MAX_LINE_LENGTH], stuLine[MAX_LINE_LENGTH], scoreLine[MAX_LINE_LENGTH];
    int searched = 0;
    
    // 输入正确
    if (fp1 == NULL){
        printf("文件打开失败\n");
        return;
    }
    fp1 = fopen("score.txt", "r");
    fgets(scoreLine, sizeof(scoreLine), fp1);

    while (fgets(scoreLine, sizeof(scoreLine), fp1)){ //查找有人报名的课程的idx
        if (sscanf(scoreLine, "%49[^,],%49[^,],%lf,%lf,%lf",score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            if (strcmp(score.index, idx) == 0){ //课号匹配

                fp2 = fopen("course.txt", "r"); //查找name
                if (fp2 == NULL){
                    printf("文件打开失败\n");
                    return;
                }
                fgets(courseLine, sizeof(courseLine), fp2);

                while (fgets(courseLine, sizeof(courseLine), fp2)){
                    if (sscanf(courseLine, "%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){
                        if (strcmp(course.name, name) == 0 && strcmp(course.index, idx) == 0){ //课名存在
                            searched = 1; //搜索成功
                            fclose(fp2);
                            break;
                        }
                    }
                }

                if (searched == 1){
                    fp3 = fopen("student.txt", "r");
                    if (fp3 == NULL){
                        printf("文件打开失败\n");
                        return;
                    }
                    fgets(stuLine, sizeof(stuLine), fp3);

                    while (fgets(stuLine, sizeof(stuLine), fp3)){
                        if (sscanf(stuLine, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n],", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
                            if (strcmp(score.ID, stu.ID) == 0){ //学号匹配
                                printf("%s,%s,%d,%d,%.1f\n", stu.ID, stu.name, (int)score.daily_grade, (int)score.exam_grade, (float)score.score);
                                fclose(fp3);
                                break;//停止查找
                            }
                        }
                    }
                }
            }
        }
    }
    
    // 输入错误
    if (searched == 0){
        printf("搜索失败,课号或课名错误.\n");
        return;
    }
    fclose(fp1);
}

// int main(){
//     char sex[50], prof[50], id[50], stuName[50], courseName[50], index[50];
//     // gets(sex);
//     // gets(prof);
//     gets(id);
//     gets(stuName);
//     // gets(index);
//     // gets(courseName);
//     // find_gender(sex);
//     // find_profession(prof);
//     // find_stu(id, stuName);
//     // find_course(index, courseName);
//     find_score0(id, stuName);
//     // find_score1(index, courseName);

//     return 0;
// }