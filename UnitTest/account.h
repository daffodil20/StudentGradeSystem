struct Account{
    char user[50];
    char name[50];
    char role[50];
    char password[50];
};

struct AccountNode{
    struct Account account;
    struct AccountNode *next;
};