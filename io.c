#include <stdlib.h>
#include "io.h"
#include <stdio.h>



void wait_for_enter(char player) {
    printf("==================================\n");
    printf("🔔 이번 차례는 Player %c 입니다.\n", player);
    printf("상대는 화면을 보지 말아 주세요!\n");
    printf(">> [엔터]를 누르면 입력 화면이 나옵니다.\n");
    printf("==================================\n");

    // 엔터 대기
    getchar();
    clear_screen();
}

int player_turn(char player,
                int my_point,
                int opponent_point,
                int last_point) {
    char buf[32];
    int input;

    wait_for_enter(player);

    printf("=== Player %c 입력 화면 ===\n", player);
    if (last_point != -1) {
        printf("이번 턴에 상대가 제시한 포인트는 %s입니다.\n",
               changeNum(last_point));
    }
    printf("당신의 잔여 포인트: %d\n", my_point);
    printf("상대 포인트 구간: %s\n", get_range_str(opponent_point));

    while (1) {
        printf("사용할 포인트를 제시해주세요(0 ~ %d): ", my_point);

        if (!fgets(buf, sizeof(buf), stdin))
            continue;  // EOF 방어
        
        char *endp;

        long tmp = strtol(buf, &endp, 10);

        // 1) 숫자가 전혀 없었을 때
        if (endp == buf) {
            FLUSH_INPUT();
            printf("0 ~ %d 사이의 정수를 입력하세요.\n\n", my_point);
            continue;
        }
        // 2) 소수점(.)이 나왔을 때
        if (*endp == '.') {
            FLUSH_INPUT();
            printf("포인트는 1포인트 단위로 입력해야 합니다.\n\n");
            continue;
        }
        // 3) 숫자 뒤에 영문자·특수문자 등이 올 때
        if (*endp != '\n' && *endp != '\0') {
            FLUSH_INPUT();
            printf("0 ~ %d 사이의 정수를 입력하세요.\n\n", my_point);
            continue;
        }
        // 4) 범위 검사
        if (tmp < 0 || tmp > my_point) {
            printf("0 ~ %d 사이의 값을 입력하세요.\n\n", my_point);
            continue;
        }

        input = tmp;
        break;
    }

    clear_screen();
    return input;
}
void clear_screen(void) {
    for (int i = 0; i < 30; i++) {
        putchar('\n');
    }
}