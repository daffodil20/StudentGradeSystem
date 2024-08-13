struct Student{
    wchar_t ID[50];
    wchar_t name[50];//13
    wchar_t gender[50];
    wchar_t age[50];
    wchar_t profession[50];
};

struct StudentNode{
    struct Student student;
    struct StudentNode *next;
};

