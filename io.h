#ifndef IO_H
#define IO_H

#include "util.h"



// 플레이어 차례 알림 + 엔터 대기
void wait_for_enter(char player);

// 한 턴 입력 처리 (입력 검증 및 FLUSH_INPUT 사용)
int player_turn(char player,
                int my_point,
                int opponent_point,
                int last_point);

#endif 
