#include "student.h"
#include "score.h"
#include "course.h"
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <wctype.h>
// #include "search.h"

#define MAX_LINE_LENGTH 256
int calculate_display_width(const wchar_t* str) { //根据是否是汉字技术字符串实际宽度（英文宽字符是1）
    int width = 0;
    while (*str) {
        if (iswprint(*str) && *str > 127) {
            width += 2; // 宽字符（如汉字）占两个单位宽度
        } else {
            width += 1; // 窄字符（如字母、数字）占一个单位宽度
        }
        str++;
    }
    return width;
}

void find_stu(wchar_t* id, wchar_t* inputName){
    struct Student stu;
    FILE* fp;
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    int searched = 0;//是否查询成功的标志
    
    // 输入正确
    fp = fopen("student.txt", "r");
    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){//解析宽字符串
            if (wcscmp(stu.name, inputName) == 0 && wcscmp(stu.ID, id) == 0){ //匹配成功
                searched = 1; //搜索成功
                wprintf(L"学号：%ls\n", stu.ID);//显示学生基本信息
                wprintf(L"姓名：%ls\n", stu.name);
                wprintf(L"性别：%ls\n", stu.gender);
                wprintf(L"年龄：%ls\n", stu.age);
                wprintf(L"所在系：%ls\n", stu.profession);
                printf("查询该学生信息成功!\n");
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

void find_course(wchar_t* idx, wchar_t* courseName){ //根据课名与课号查找课程基本信息
    struct Course course;
    FILE* fp;
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    int searched = 0;
    
    // 输入正确
    fp = fopen("course.txt", "r");
    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^\n]",course.index, course.name, course.teacher) == 3){
            if (wcscmp(course.name, courseName) == 0 && wcscmp(course.index, idx) == 0){ //匹配成功
                searched = 1; //搜索成功
                wprintf(L"课号：%ls\n课名：%ls\n任课教师：%ls\n", course.index, course.name, course.teacher); //显示课程基本信息
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

void find_gender(wchar_t* gender){ //按性别查找学生基本信息
    struct Student stu;
    FILE* fp;
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    int flag = 0;//是否找到信息

    //输入错误
    if (wcscmp(gender, L"男") != 0 && wcscmp(gender, L"女") != 0){
        printf("输入错误,请输入男/女:\n");
        return;
    }
    
    // 输入正确
    fp = fopen("student.txt", "r");
    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
            if (wcscmp(stu.gender, gender) == 0){ //性别相同
                // wprintf(L"%ls%*ls%*ls%*ls\n", stu.ID, 10 - wcslen(stu.ID) + wcslen(stu.name), stu.name, 6, stu.age, 12 - wcslen(stu.profession)*2 + wcslen(stu.profession), stu.profession); //显示学生基本信息
                int id_width = calculate_display_width(stu.ID);
                int name_width = calculate_display_width(stu.name);
                int age_width = calculate_display_width(stu.age);
                int profession_width = calculate_display_width(stu.profession);
                if (flag  == 0)//第一行
                    wprintf(L"%-3ls%-8ls%-4ls%-12ls\n", L"学号", L"姓名", L"年龄", L"所在系");//表头
                wprintf(L"%-5ls%-*ls%-*ls%-*ls\n", stu.ID, 10 - name_width + wcslen(stu.name), stu.name, 6 - age_width + wcslen(stu.age),  stu.age, 12 - profession_width + wcslen(stu.profession), stu.profession);//补充空格左对齐
                flag = 1;
            }
        }
    }
    fclose(fp);
    if (flag == 0)
        printf("未找到对应的学生\n");
}

void find_profession(wchar_t* profession){
    struct Student stu;
    FILE* fp;
    char buffer[MAX_LINE_LENGTH];
    wchar_t wbuffer[MAX_LINE_LENGTH];
    int searched = 0;//是否搜索成功
    
    // 输入正确
    fp = fopen("student.txt", "r");
    fgets(buffer, sizeof(buffer), fp);
    while (fgets(buffer, sizeof(buffer), fp)){
        mbstowcs(wbuffer, buffer, sizeof(wbuffer) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wbuffer, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
            if (wcscmp(stu.profession, profession) == 0){ //专业相同
                int id_width = calculate_display_width(stu.ID);
                int name_width = calculate_display_width(stu.name);
                int gender_width = calculate_display_width(stu.gender);
                int age_width = calculate_display_width(stu.age);

                if (searched == 0)
                    wprintf(L"%-3ls%-8ls%-4ls%-4ls\n", L"学号", L"姓名", L"性别", L"年龄");//表头
                searched = 1; //标记搜索成功
                wprintf(L"%-5ls%-*ls%-*ls%-*ls\n", stu.ID, 10 - name_width + wcslen(stu.name), stu.name, 6 - gender_width + wcslen(stu.gender), stu.gender, 6 - age_width + wcslen(stu.age), stu.age); //显示学生基本信息
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

void find_score0(wchar_t* id, wchar_t* name){ //根据学号和姓名查询成绩
    //逐行读score.txt
    struct Score score;
    struct Student stu;
    struct Course course;
    FILE *fp1, *fp2, *fp3;
    char courseLine[MAX_LINE_LENGTH], stuLine[MAX_LINE_LENGTH], scoreLine[MAX_LINE_LENGTH];
    wchar_t wcourseLine[MAX_LINE_LENGTH], wstuLine[MAX_LINE_LENGTH], wscoreLine[MAX_LINE_LENGTH];
    int searched = 0;
    
    // 输入正确
    if (fp1 == NULL){
        printf("文件打开失败\n");
        return;
    }
    fp1 = fopen("score.txt", "r");
    fgets(scoreLine, sizeof(scoreLine), fp1);

    while (fgets(scoreLine, sizeof(scoreLine), fp1)){ //查找有报名课程的学生的id
        mbstowcs(wscoreLine, scoreLine, sizeof(wscoreLine) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wscoreLine, L"%49[^,],%49[^,],%lf,%lf,%lf",score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            if (wcscmp(score.ID, id) == 0){ //学号匹配
                fp2 = fopen("student.txt", "r"); //标记姓名
                if (fp2 == NULL){
                    printf("文件打开失败\n");
                    return;
                }
                fgets(stuLine, sizeof(stuLine), fp2);
          
                while (fgets(stuLine, sizeof(stuLine), fp2)){
                    mbstowcs(wstuLine, stuLine, sizeof(wstuLine) / sizeof(wchar_t));//char->wchar_t
                    if (swscanf(wstuLine, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
                        if (wcscmp(stu.ID, id) == 0 && wcscmp(stu.name, name) == 0){  //学号与姓名相对应
                            if (searched == 0)
                                wprintf(L"%-3ls%-10ls%-6ls%-6ls%-6ls\n", L"课号", L"课名", L"平时成绩", L"卷面成绩", L"综合成绩");//表头
                            searched = 1; //搜索成功
                            fclose(fp2);
                            break;
                        }
                    }
                }
                if (searched == 1){ //根据课号
                    fp3 = fopen("course.txt", "r");
                    if (fp3 == NULL){
                        printf("文件打开失败\n");
                        return;
                    }
                    fgets(courseLine, sizeof(courseLine), fp3);

                    while (fgets(courseLine, sizeof(courseLine), fp3)){
                        mbstowcs(wcourseLine, courseLine, sizeof(wcourseLine) / sizeof(wchar_t));//char->wchar_t
                        if (swscanf(wcourseLine, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){
                            if (wcscmp(score.index, course.index) == 0){ //课号相同
                                int name_width = calculate_display_width(course.name);//课名长度
                                wprintf(L"%-5ls%-*ls%-10d%-10d%-10.1f\n", score.index, 12 - name_width + wcslen(course.name), course.name, (int)score.daily_grade, (int)score.exam_grade, (float)score.score);
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
void find_score1(wchar_t* idx, wchar_t* name){ //根据课号和课名查询成绩
    //逐行读score.txt
    struct Score score;
    struct Student stu;
    struct Course course;
    FILE *fp1, *fp2, *fp3;
    char courseLine[MAX_LINE_LENGTH], stuLine[MAX_LINE_LENGTH], scoreLine[MAX_LINE_LENGTH];
    wchar_t wcourseLine[MAX_LINE_LENGTH], wstuLine[MAX_LINE_LENGTH], wscoreLine[MAX_LINE_LENGTH];
    int searched = 0;
    
    // 输入正确
    fp1 = fopen("score.txt", "r");
    if (fp1 == NULL){
        printf("文件打开失败\n");
        return;
    }
    fgets(scoreLine, sizeof(scoreLine), fp1);

    while (fgets(scoreLine, sizeof(scoreLine), fp1)){ //查找有人报名的课程的idx
        mbstowcs(wscoreLine, scoreLine, sizeof(wscoreLine) / sizeof(wchar_t));//char->wchar_t
        if (swscanf(wscoreLine, L"%49[^,],%49[^,],%lf,%lf,%lf",score.ID, score.index, &score.daily_grade, &score.exam_grade, &score.score) == 5){
            if (wcscmp(score.index, idx) == 0){ //课号匹配
                
                fp2 = fopen("course.txt", "r"); //查找name
                if (fp2 == NULL){
                    printf("文件打开失败\n");
                    return;
                }
                fgets(courseLine, sizeof(courseLine), fp2);

                while (fgets(courseLine, sizeof(courseLine), fp2)){
                    mbstowcs(wcourseLine, courseLine, sizeof(wcourseLine) / sizeof(wchar_t));//char->wchar_t
                    if (swscanf(wcourseLine, L"%49[^,],%49[^,],%49[^\n]", course.index, course.name, course.teacher) == 3){
                        if (wcscmp(course.name, name) == 0 && wcscmp(course.index, idx) == 0){ //课名存在
                            if (searched == 0)
                                wprintf(L"%-3ls%-10ls%-6ls%-6ls%-6ls\n", L"学号", L"姓名", L"平时成绩", L"卷面成绩", L"综合成绩");//表头
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
                        mbstowcs(wstuLine, stuLine, sizeof(wstuLine) / sizeof(wchar_t));//char->wchar_t
                        if (swscanf(wstuLine, L"%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", stu.ID, stu.name, stu.gender, stu.age, stu.profession) == 5){
                            if (wcscmp(score.ID, stu.ID) == 0){ //学号匹配
                                int name_width = calculate_display_width(stu.name);//姓名长度
                                wprintf(L"%-5ls%-*ls%-10d%-10d%-10.1f\n", stu.ID, 12 - name_width + wcslen(stu.name), stu.name, (int)score.daily_grade, (int)score.exam_grade, (float)score.score);
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

int main(){
    setlocale(LC_ALL, "");
    _setmode( _fileno( stdin ), _O_WTEXT );
    wchar_t sex[50], prof[50], id[50], stuName[50], courseName[50], index[50];
//     // gets(sex);
//     // gets(prof);
    // fgetws(id, sizeof(id), stdin);
    // id[wcslen(id)-1] = L'\0';
    // fgetws(stuName, sizeof(stuName), stdin);
    // stuName[wcslen(stuName)-1] = L'\0';

    fgetws(index, sizeof(index), stdin);
    index[wcslen(index)-1] = L'\0';
    fgetws(courseName, sizeof(courseName), stdin);
    courseName[wcslen(courseName)-1] = L'\0';

    // fgetws(sex, sizeof(sex), stdin);
    // sex[wcslen(sex)-1] = L'\0';

    // fgetws(prof, sizeof(prof), stdin);
    // prof[wcslen(prof)-1] = L'\0';
//     // gets(index);
//     // gets(courseName);
    // find_gender(sex);
    // find_profession(prof);
    // find_stu(id, stuName);
    // find_course(index, courseName);
    // find_score0(id, stuName);
    find_score1(index, courseName);

    return 0;
}

// 07   张欢                  20   电子
// 05   王小可                 20   计算机