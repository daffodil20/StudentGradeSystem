//中文化测试
// #include <string.h>
// #include <wchar.h>
// #include <locale.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <windows.h>
// int main(){
    // system("chcp 65001 & cls");
    // setlocale(LC_ALL, "zh_CN.UTF-8");
    // setlocale(LC_ALL, "");
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);


    // FILE *fp;
//    wchar_t chStr0[8];
    // char chStr[24];
    // short unsigned int  chStr1[15];
//    char chStr1[8];
   
//    wchar_t wide_str[16], input[16];
// //    strcpy(wide_str, "你好同学");
//    fgetws(wide_str, 12, stdin);//你好同学
//    wprintf(L"%ls\n", wide_str);//你好同学可以正确显示


//     char wide_str[16], input[16];
//     fgets(input, 16, stdin);
// //    strcpy(wide_str, input);
// //    fgetws(wide_str, 12, stdin);//你好同学
//     wprintf(L"%ls\n", input);//你好同学可以正确显示
//     for (int i = 0; input[i] != '\0'; i++) {
//         printf("%02X ", (unsigned char)input[i]);
//     }



    // Set the console output and input code page to UTF-16LE
    // SetConsoleOutputCP(1200);  // UTF-16LE code page
    // SetConsoleCP(1200);        // UTF-16LE code page

    // Set the locale to the default wide-character locale
    // setlocale(LC_ALL, "zh_CN");

    // Clear the console with a command appropriate for UTF-16LE
    // system("cls");

    // Example: Print a UTF-16LE string
    // wchar_t input[100];
    // char string[50];
    // // wprintf(L"请输入一些中文字符: ");
    // // fgetws(input, 100, stdin);
    // strcpy(string, "中");
    // // wprintf(L"你输入的是: %ls\n", input);
    // // for (int i = 0; input[i] != '\0'; i++) {
    // //     printf("%02X ", (unsigned char)input[i]);
    // // }

    // for (int i = 0; string[i] != '\0'; i++) {
    //     printf("%02X ", (unsigned char)string[i]);
    // }



// void print_utf8_binary(wchar_t *utf8_char) {
//     int i = 0;
//     while (utf8_char[i] != '\0') {
//         for (int j = 23; j >= 0; j--) {
//             printf("%c", (utf8_char[i] & (1 << j)) ? '1' : '0');
//         }
//         printf(" ");  // Add space between bytes
//         i++;
//     }
//     printf("\n");
// }

// 打印 UTF-8 编码的二进制表示



// int main() {
//     // 使用 system 函数切换到 UTF-8 编码
//     // system("chcp 65001");

//     wchar_t utf8_char[4];  // UTF-8 字符最多需要 4 个字节

//     printf("请输入一个汉字：");
//     // scanf("%s", utf8_char);  // 使用 %s 格式输入汉字
//     fgetws(utf8_char, sizeof(utf8_char), stdin);
//     // scanf("%s", utf8_char);  // 使用 %s 格式输入汉字

//     printf("汉字的 UTF-8 编码为：");
//     print_utf8_binary(utf8_char);

//     return 0;
// }


    // char input[4]; // UTF-8 characters can be up to 4 bytes long
    // printf("请输入一个汉字: ");
    
    // // Reading input, allowing only one character (up to 3 bytes for Chinese character)
    // fgets(input, sizeof(input), stdin);
    
    // printf("输入的汉字的UTF-8编码是: ");
    // for (int i = 0; input[i] != '\0'; i++) {
    //     printf("%02X ", (unsigned char)input[i]);
    // }
    // printf("\n");

    
    

    // wchar_t input[50];
    // // fgets((char *)input, 50, stdin);
    // wscanf(L"%ls", input);
    // // wchar_t *ttt;
    // // ttt = (wchar_t*)input;
    // wprintf(L"%ls", input);


   
    // char *input = (char *)malloc(12 * sizeof(char));  // 为 input 分配内存
    // if (input == NULL) {
    //     printf("Memory allocation failed\n");
    //     return 1;
    // }
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    // wchar_t input[12];
    // // scanf("%s", input);          // 或者使用 scanf 读取输入
    // fgetws(input, sizeof(input), stdin);
    // wprintf(L"%ls\n", input);       // 使用 printf 输出字符串
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

//     return 0;
// }


// #include <stdio.h>
// #include <stdint.h>
// #include <wchar.h>

// int main() {
//     unsigned char utf8_val[100];

//     scanf("%ls", utf8_val);
//     // printf("A: %x\n", *utf8_val);
//     // printf("B: %c\n", *utf8_val);
//     wprintf(L"%ls\n", (wchar_t *)utf8_val);
// }


#include <stdio.h>
#include <stdint.h>
#include <wchar.h>
#include <locale.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main() {
    setlocale(LC_ALL, "");
    // unsigned char utf8_val[60];
    // uint32_t utf8_val[100];
    // uint32_t utf8_val[100];

    unsigned char utf8_val[256];
    char id[50], name[50], gender[50], age[50], prof[50];
    // printf("wchar_t: %lu", sizeof(wchar_t));
    _setmode( _fileno( stdin ), _O_WTEXT );
    // _setmode( _fileno( stdout ), _O_WTEXT );
    // _set_fmode(_O_WTEXT);
    // _set_fmode(_O_BINARY);
    // _setmode( _fileno( stdin ), _O_WTEXT );
    // _setmode( _fileno( stdout ), _O_WTEXT );
    // wscanf(L"%ls", utf8_val);
    // fgetws(utf8_val, sizeof(utf8_val), stdin);
    // wscanf(L"%ls", utf8_val); 
    FILE *fp;
    fp = fopen("student.txt", "r");
    // FILE *fp = _wfopen(L"student.txt", L"r, ccS=UTF-8"); // 打开宽字符文件
    // _setmode( _fileno( fp ), _O_WTEXT );
    // fgetws(utf8_val, sizeof(utf8_val), stdin);
    // fwprintf(fp, L"%ls", utf8_val);
    // fgets(utf8_val, sizeof(utf8_val), fp);
    // // // sscanf(utf8_val, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", id, name, gender, age, prof);
    // // // fwscanf(fp, L"%ls", utf8_val);
    // printf("第一行：%s", utf8_val);
    // printf("第一行：%x", utf8_val[0]);
    // // printf("结果：%s %s %s %s %s", id, name, gender, age, prof);
    // fgets(utf8_val, sizeof(utf8_val), fp);
    // sscanf(utf8_val, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^\n]", id, name, gender, age, prof);
    // printf("结果：%s %c %s %s %s", id, name[0], gender, age, prof);
    // printf("名字：%ls ", (wchar_t *)name);
    // printf("第二行：%s\n", utf8_val);

    // _setmode( _fileno( stdin ), _O_WTEXT );
    // wchar_t input[50];
    // fgetws(input, sizeof(input), stdin);
    // printf("比较编码：%x,%x\n", input[0], name[0]);
    // if (strcmp(name, (char)input) == 0){
    //     printf("字符相同\n");
    // }
    // for (i = 0; i < strlen(name); i ++){
    //     if (strcmp(name, (char)utf8_val) == 0){

    //     }
    // }
    //尝试用fgetws读文件
    char output[256], input[256];
    wchar_t buffer[256];
    // fgetws(input, sizeof(input), stdin);
    // fwprintf(fp, L"%ls", input);
    // fgets(output, sizeof(output), fp);
    
    fgets(output, sizeof(output), fp);
    mbstowcs(buffer,output,sizeof(buffer)/sizeof(wchar_t));
    wprintf(L"result:%ls", buffer);
    // printf("第一行：%x", output[0]);
    
    fclose(fp);
    // char input[50];
    // fgets(input, sizeof(input), stdin);
    // printf("%s")
    // printf("A0: %x\n", utf8_val[0]); 
    // printf("A1: %x\n", utf8_val[1]); 
    // printf("A2: %x\n", utf8_val[2]); 
    // printf("A3: %x\n", utf8_val[3]); 
    // printf("A4: %x\n", utf8_val[4]); 
    // printf("A5: %x\n", utf8_val[5]); 
    // printf("A6: %x\n", utf8_val[6]); 
    // printf("A7: %x\n", utf8_val[7]); 
    // printf("A8: %x\n", utf8_val[8]); 
    // printf("A9: %x\n", utf8_val[9]); 
    // printf("A10: %x\n", utf8_val[10]); 
    // printf("A11: %x\n", utf8_val[11]); 
    // printf("A12: %x\n", utf8_val[12]); 
    // printf("A13: %x\n", utf8_val[13]); 
    // printf("B0: %c\n", utf8_val[0]);
    // printf("B1: %ls\n", utf8_val);

    // wprintf(L"C: %ls\n", utf8_val);
    // wprintf(L"C: %ls\n", utf8_val[0]);
}