#include <wchar.h>
// #include "calculateScore.h"
double calculate_score(wchar_t* idx, double score0, double score1){ //计算综合成绩
    if (idx[0] == L'S')//专业课
        return score0 * 0.4 + score1 * 0.6;
    if (idx[0] == L'P')//公共课
        return score0 * 0.3 + score1 * 0.7;
}