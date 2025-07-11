#include "util.h"
#include <stdio.h>

const char* changeNum(int num) {
    return (0 <= num && num <= 9) ? "Black" : "White";
}

const char* get_range_str(int point) {
    if (point >= 80) return "80~99";
    else if (point >= 60) return "60~79";
    else if (point >= 40) return "40~59";
    else if (point >= 20) return "20~39";
    else return "0~19";
}


