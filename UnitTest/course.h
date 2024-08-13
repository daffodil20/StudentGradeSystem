struct Course{
    wchar_t index[50];
    wchar_t name[50];
    wchar_t teacher[50];
};

struct CourseNode{
    struct Course course;
    struct CourseNode *next;//指向Course结构体类型的指针（链表）
};