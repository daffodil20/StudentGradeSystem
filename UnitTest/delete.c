void delete_stu0(char* old_i){ //学生学号
    #define MAX_LINE_LENGTH 256
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
    char *lines[MAX_LINE_LENGTH];
    int line_count = 0;

    // 读取文件内容到内存
    fp = fopen("student.txt", "r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {    
        lines[line_count] = strdup(buffer); // 保存每一行到内存
        line_count++;
    }
    fclose(fp);

    // 打开文件以修改数据
    fp = fopen("student.txt", "w");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }

    //逐行读文件，比较学号
    int modified = 0;
    for (int i = 0; i < line_count; i ++){
        char id[50];
        sscanf(lines[i], "%49[^,]", id);//读取新学号到字符串
        if (strcmp(old_id, id) == 0){
        //     char* rest_of_line = strchr(lines[i], ',');
        //     sprintf(lines[i], "%s%s", new_id, rest_of_line);//存储新学号
        //     printf("lines[%d]:%s\n",i,lines[i]);
        //     modified = 1;//修改的标记
        //     break;//后面的不需要遍历
            char* rest_of_line = strchr(lines[i], ','); // 找到逗号的位置
            if (rest_of_line) {
                rest_of_line++; // 移动到逗号后面的第一个字符
                char new_line[MAX_LINE_LENGTH];
                snprintf(new_line, sizeof(new_line), "%s,%s", new_id, rest_of_line); // 构造新的行
                free(lines[i]); // 释放旧行的内存
                lines[i] = strdup(new_line); // 用新行替换
                modified = 1; // 设置修改标记
            }
        }
        // }
        
    }
    
    //查找失败
    if (!modified){
        printf("输入的学号不存在，请重新输入。\n");
        return;
    }

    //将内存写回文件
    for (int i = 0; i < line_count; i ++){
        fprintf(fp, "%s", lines[i]);
        free(lines[i]);//释放内存
    }
    fclose(fp);
}