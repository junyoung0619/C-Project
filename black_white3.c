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
    fflush(stdout);

    getchar();      // 딱 한 번만 엔터 대기
    clear_screen();
}

char* changeNum(int num){
    if(0<=num && num<=9){
        return "Black";
    }

    return "White";
}

// 플레이어 입력 처리
int player_turn(char player, int my_point, int opponent_point, int lastpoint) {
    int input;
    int ret = 0;

    wait_for_enter(player);

    printf("=== Player %c 입력 화면 ===\n", player);
    if(lastpoint!=-1){
        printf("이번 턴에 상대가 제시한 포인트는 %s입니다.\n", changeNum(lastpoint));
    }
    printf("당신의 잔여 포인트: %d\n", my_point);
    printf("상대 포인트 구간: %s\n", get_range_str(opponent_point));

    char buf[32];
    int val, n;

    while (1) {
        printf("사용할 포인트를 제시해주세요(0 ~ %d): \n", my_point);

        if (!fgets(buf, sizeof(buf), stdin)) continue;  // EOF 방어

        if (sscanf(buf, "%d%n", &val, &n) != 1) {
            printf("0 ~ %d 사이의 정수를 입력하세요: \n", my_point);
            continue;
        } else if(buf[n] != '\n'){
            printf("포인트는 1포인트 단위로 사용할 수 있습니다.\n");
            continue;
        }
        if (val < 0 || val > my_point) {
            printf("0 ~ %d 사이의 정수를 입력하세요: \n", my_point);
            continue;
        }
        input = val;
        break;
    }

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

        // 턴 진행
        if (currentFirst == 'A') {
            a = player_turn('A', pointA, pointB,-1);
            pointA -= a;

            b = player_turn('B', pointB, pointA,a);
            pointB -= b;
        } else {
            b = player_turn('B', pointB, pointA,-1);
            pointB -= b;

            a = player_turn('A', pointA, pointB,b);
            pointA -= a;
        }

        // 라운드 결과 출력
        if (a > b) {
            scoreA++;
            printf("\n>> Player A wins this round!\n");
            currentFirst = 'A'; // 이긴 쪽이 선공
        } else if (b > a) {
            scoreB++;
            printf("\n>> Player B wins this round! \n");
            currentFirst = 'B';
        } else {
            printf("\n>> Draw!\n");
            // 무승부면 선플레이어 유지
        }
        
        printf("A가 제시한 포인트: %s, B가 제시한 포인트: %s\n",changeNum(a),changeNum(b));
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
