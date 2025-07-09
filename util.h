#ifndef UTIL_H
#define UTIL_H

// === 설정 매크로 ===
#define MAX_POINT      99
#define MAX_ROUND      9
#define WINNING_SCORE  5

// 입력 버퍼 잔류 문자(초과 입력) 제거 매크로
#define FLUSH_INPUT()            \
    do {                         \
        int _c;                  \
        while ((_c = getchar()) != '\n' && _c != EOF) {} \
    } while (0)
    
// 흑(0~9) / 백(>9) 문자열 반환
const char* changeNum(int num);

// 포인트 구간을 문자열로 반환
const char* get_range_str(int point);

#endif 
