#include <wctype.h>
#include <wchar.h>
#include "print_format.h"
int calculate_display_width(const wchar_t* str){ //根据是否是汉字技术字符串实际宽度（英文宽字符是1）
    int width = 0;
    while (*str) {
        if (iswprint(*str) && *str > 127) {
            width += 2; // 宽字符（如汉字）占两个单位宽度
        } else {
            width += 1; // 窄字符（如字母、数字）占一个单位宽度
        }
        str++;
    }
    return width;
}