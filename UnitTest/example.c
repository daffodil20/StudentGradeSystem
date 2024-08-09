//中文化测试
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main(){
    system("chcp 65001 & cls");
    setlocale(LC_ALL, "zh_CN.UTF-8");
    // FILE *fp;
//    wchar_t chStr0[8];
    // char chStr[24];
    // short unsigned int  chStr1[15];
//    char chStr1[8];

//    wchar_t wide_str[12];
//    fgetws(wide_str, 12, stdin);//你好同学
//    printf("%s\n", wide_str[0]);
//    fputws(wide_str, stdout);//空行
//    printf("%s", wide_str[0]);
 
//    char *ascii_ = "我爱学习";
//    char *input;
//    fgets(input, 12, stdin);
//    scanf("%s", input);
//    puts(input);
//    printf("%s\n", *input);
//    printf("ascii_: %s\n", ascii_);//显示正确
   
    // char *input = (char *)malloc(12 * sizeof(char));  // 为 input 分配内存
    // if (input == NULL) {
    //     printf("Memory allocation failed\n");
    //     return 1;
    // }
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    wchar_t input[12];
    // scanf("%s", input);          // 或者使用 scanf 读取输入
    fgetws(input, sizeof(input), stdin);
    wprintf(L"%ls\n", input);       // 使用 printf 输出字符串
    // 使用 fgets 读取输入，fgets 会保留空格，并读取整行
    // if (fgets(input, 12, stdin) != NULL) {
    //     // 去除输入中的换行符
    //     input[strcspn(input, "\n")] = '\0'; 
    //     printf("You entered: %s\n", input);
    // } else {
    //     printf("Failed to read input\n");
    // }
    // free(input);  // 使用完内存后，释放它


//    wchar_t input[50];
    // wchar_t *wide_str;
   
//    wcscpy(wide_str, input);
//    wprintf(L"%ls", wide_str);

//    wchar_t wide_str[12];
//    fgetws(wide_str, 12, stdin);//你好同学
// //    wchar_t input[50];
//     // wchar_t *wide_str;
   
// //    wcscpy(wide_str, input);
//    wprintf(L"%ls", wide_str);
   
   
    // scanf("%s", chStr);
    // printf("%s", chStr);
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
