//中文化测试
// #include <wchar.h>
#include <stdio.h>
int main(){
    FILE *fp;
    char chStr[100], ch;
    fp = fopen("student.txt", "a");
    
    // fgetws(chStr, 100, stdin);
    // // wscanf(L"%ls", chStr);
    
    // fflush(stdout);
    // wprintf(L"%ls", chStr);
    // wgets(chStr);
    // wprintf("%s", chStr);
    scanf("%s", chStr);
    printf("%s", chStr);
    fscanf(fp, "%s", chStr);
    fclose(fp);
    
    // printf("你好，同学。\n");
    // scanf("%c", &ch );
    // printf("%c", ch);
    // fflush(stdout);

    return 0;
}