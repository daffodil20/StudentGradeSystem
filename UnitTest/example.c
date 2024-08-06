//中文化测试
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
int main(){
    setlocale(LC_ALL, "zh_CN.UTF-8");
    // FILE *fp;
//    wchar_t chStr0[8];
    char chStr[24];
    // short unsigned int  chStr1[15];
//    char chStr1[8];

//    wchar_t *wide_str = L"你好，世界！";
    // wchar_t *wide_str;
//    wprintf(L"%ls", wide_str);
    scanf("%s", chStr);
    printf("%s", chStr);
//    printf("你好"); 
    // wscanf(L"%ls", chStr);
//    fgetws(chStr0, 8, stdin);
//    wprintf(L"%ls", chStr0);
    // fgets(chStr1);
//    if (fgets(chStr1, 12, stdin) != NULL) {
//       wprintf(L"%ls\n", chStr1);
//    //     printf(L"%ls", chStr1);
//    } else {
//       printf("Error reading input.");
//    }
//    scanf("%s", chStr1);
//    printf("%s", chStr1);
    
    // for (i )
    // scanf("%hu", chStr);
    // strcpy(chStr1, L"你好同学");
    // strcpy(chStr1, chStr0);
    // chStr[0] = L"你";
    // chStr[1] = L"好";
    // wprintf(L"%ls\n", chStr1);
    // wprintf(L"%ls\n", wide_str);
    
    // 设置本地化信息，使得程序支持宽字符集
    // setlocale(LC_ALL, "");
    // wchar_t chStr[100];
    // fgetws(chStr, 100, stdin);
    // wprintf(L"你输入的宽字符字符串是：%ls\n", chStr);

    // setlocale(LC_ALL, "zh_CN.UTF-8");

    // wchar_t chStr[100];
    // wprintf(L"请输入宽字符字符串: ");
    
    // if (fgetws(chStr, 200, stdin) != NULL) {
    //     // 去掉可能存在的换行符
    //     size_t len = wcslen(chStr);
    //     if (len > 0 && chStr[len - 1] == L'\n') {
    //         chStr[len - 1] = L'\0';
    //     }

    //     wprintf(L"你输入的宽字符字符串是：%ls\n", chStr);
    // } else {
    //     wprintf(L"读取宽字符字符串失败。\n");
    // }
    // char *current_locale = setlocale(LC_ALL, NULL);
    // printf("Current locale: %s\n", current_locale);
    // fp = fopen("student.txt", "a");
    
    // fgetws(chStr, 100, stdin);
    // // wscanf(L"%ls", chStr);
    
    // fflush(stdout);
    // wprintf(L"%ls", chStr);
    // wgets(chStr);
    // fgetws(chStr, 100, stdin);
    // printf("%s", chStr);
    // wprintf(L"%ls\n", chStr);
    // scanf("%s", chStr);
    // printf("%s", chStr);
    // fscanf(fp, "%s", chStr);
    // fclose(fp);
    
    // printf("你好，同学。\n");
    // scanf("%c", &ch );
    // printf("%c", ch);
    // fflush(stdout);

    return 0;
}
