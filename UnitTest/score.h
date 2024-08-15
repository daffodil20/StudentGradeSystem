#include <wchar.h>
struct Score{
    wchar_t ID[50];
    wchar_t index[50];
    double daily_grade;
    double exam_grade;
    double score;
};

struct ScoreNode{
    struct Score score;
    struct ScoreNode *next;
};
