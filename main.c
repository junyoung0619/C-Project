#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"
#include "io.h"

int main(void) {
    int pointA = MAX_POINT, pointB = MAX_POINT;
    int scoreA = 0, scoreB = 0;
    int round = 1;
    int a = 0, b = 0;
    char currentFirst;

    // 선후공 결정 (시간 % 2)
    time_t t = time(NULL);
    currentFirst = (t % 2 == 0) ? 'A' : 'B';

    printf("==== 흑과 백 2 ====\n");
    printf("첫 번째 라운드 선플레이어는 Player %c\n", currentFirst);

    // 메인 게임 루프
    while (round <= MAX_ROUND) {
        printf("\n=== Round %d ===\n", round);

        if (currentFirst == 'A') {
            a = player_turn('A', pointA, pointB, -1);
            pointA -= a;
            b = player_turn('B', pointB, pointA, a);
            pointB -= b;
        } else {
            b = player_turn('B', pointB, pointA, -1);
            pointB -= b;
            a = player_turn('A', pointA, pointB, b);
            pointA -= a;
        }

        // 라운드 결과
        if (a > b) {
            scoreA++;
            printf("\n>> Player A wins this round!\n");
            currentFirst = 'A';
        } else if (b > a) {
            scoreB++;
            printf("\n>> Player B wins this round!\n");
            currentFirst = 'B';
        } else {
            printf("\n>> Draw!\n");
        }

        // 상태 출력
        printf("A가 제시한 포인트: %s, B가 제시한 포인트: %s\n",
               changeNum(a), changeNum(b));
        printf("현재 점수: A(%d) - B(%d)\n", scoreA, scoreB);

        round++;

        // 조기 종료
        if (scoreA == WINNING_SCORE || scoreB == WINNING_SCORE) break;
        if (pointA == 0 && pointB == 0) break;
    }

    // 최종 결과
    printf("\n=== 게임 종료 ===\n");
    printf("최종 점수: A(%d) - B(%d)\n", scoreA, scoreB);
    if (scoreA > scoreB)
        printf(">>> 🎉 Player A Wins!\n");
    else if (scoreB > scoreA)
        printf(">>> 🎉 Player B Wins!\n");
    else
        printf(">>> 🤝 It's a Draw.\n");

    return 0;
}
