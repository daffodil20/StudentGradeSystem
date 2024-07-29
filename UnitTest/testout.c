#include <stdio.h>
void RecordPassWord(){
    FILE *fp;
    fp = fopen("account_info.txt","a+");
    if (fp == NULL)
        printf("文件不存在");
    char password[20], account[20];
    //输入账号和密码
    scanf("%s",account);
    scanf("%s",password);
    fprintf(fp, "account:%s|password:%s\n", account, password);//写文件
    fprintf(fp, L"账号密码");
    fclose(fp);

}
int main(){
    RecordPassWord();
    
    return 0;
}

