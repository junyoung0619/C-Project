#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_POINT 99
#define MAX_ROUND 9
#define WINNING_SCORE 5

// 포인트 구간을 문자열로 반환
const char* get_range_str(int point) {
    if (point >= 80) return "80~99";
    else if (point >= 60) return "60~79";
    else if (point >= 40) return "40~59";
    else if (point >= 20) return "20~39";
    else return "0~19";
}

// 스크린 클리어 or 줄 내리기
void clear_screen() {
    for (int i = 0; i < 30; i++) printf("\n");
}

// 플레이어 차례 알림 + 엔터 대기
void wait_for_enter(char player) {
    printf("==================================\n");
    printf("🔔 이번 차례는 Player %c 입니다.\n", player);
    printf("상대는 화면을 보지 말아 주세요!\n");
    printf(">> [엔터]를 누르면 입력 화면이 나옵니다.\n");
    printf("==================================\n");
    getchar(); // 버퍼 비우기
    getchar(); // 실제 대기
}

// 플레이어 입력 처리
int player_turn(char player, int my_point, int opponent_point) {
    int input;
    wait_for_enter(player);
    printf("=== Player %c 입력 화면 ===\n", player);
    printf("당신의 잔여 포인트: %d\n", my_point);
    printf("상대는 현재 %s 구간에 있음.\n", get_range_str(opponent_point));
    do {
        printf("사용할 숫자를 입력하세요 (0 ~ %d): ", my_point);
        scanf("%d", &input);
    } while (input < 0 || input > my_point);
    clear_screen();
    return input;
}

int main() {
    int pointA = MAX_POINT, pointB = MAX_POINT;
    int scoreA = 0, scoreB = 0;
    int round = 1;
    int a = 0, b = 0;
    char currentFirst;

    srand(time(NULL));
    currentFirst = (rand() % 2 == 0) ? 'A' : 'B';
    printf("==== 흑과 백 2 콘솔 시뮬레이터 ====\n");
    printf("첫 번째 라운드 선플레이어는 Player %c\n", currentFirst);

    while (round <= MAX_ROUND) {
        printf("\n=== Round %d ===\n", round);
        printf("현재 점수: A(%d) - B(%d)\n", scoreA, scoreB);

        // 턴 진행
        if (currentFirst == 'A') {
            a = player_turn('A', pointA, pointB);
            pointA -= a;

            b = player_turn('B', pointB, pointA);
            pointB -= b;
        } else {
            b = player_turn('B', pointB, pointA);
            pointB -= b;

            a = player_turn('A', pointA, pointB);
            pointA -= a;
        }

        // 라운드 결과 출력
        if (a > b) {
            scoreA++;
            printf("\n>> Player A wins this round! (%d vs %d)\n", a, b);
            currentFirst = 'B'; // 진 쪽이 선공
        } else if (b > a) {
            scoreB++;
            printf("\n>> Player B wins this round! (%d vs %d)\n", a, b);
            currentFirst = 'A';
        } else {
            printf("\n>> Draw! (%d vs %d)\n", a, b);
            // 무승부면 선플레이어 유지
        }

        printf("현재 점수: A(%d) - B(%d)\n", scoreA, scoreB);
        round++;

        // 조기 종료 조건
        if (scoreA == WINNING_SCORE || scoreB == WINNING_SCORE) break;
        if (pointA == 0 && pointB == 0) break;
    }

    printf("\n=== 게임 종료 ===\n");
    printf("최종 점수: A(%d) - B(%d)\n", scoreA, scoreB);

    if (scoreA >scoreB) printf(">>> 🎉 Player A Wins!\n");
    else if (scoreB > scoreA) printf(">>> 🎉 Player B Wins!\n");
    else printf(">>> 🤝 It's a Draw.\n");

    return 0;
}
