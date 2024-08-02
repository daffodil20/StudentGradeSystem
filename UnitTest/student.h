struct Student{
    char ID[50];
    char name[50];//13
    char gender[50];
    char age[50];
    char profession[50];
};

struct StudentNode{
    struct Student student;
    struct StudentNode *next;
};

