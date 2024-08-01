struct Course{
    char index[50];
    char name[50];
    char teacher[50];
};

struct CourseNode{
    struct Course course;
    struct CourseNode *next;//指向Course结构体类型的指针（链表）
};