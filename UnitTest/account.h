struct Account{
    wchar_t user[50];
    wchar_t name[50];
    wchar_t role[50];
    wchar_t password[50];
};

struct AccountNode{
    struct Account account;
    struct AccountNode *next;
};