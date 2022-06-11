#define _CRT_OBSOLETE_NO_WARNINGS //구식함수 사용 에러 방지
#include <stdio.h>
#include <time.h> // delay 함수 선언된 헤더 파일

// delay 함수 선언부 
void delay(clock_t n) {
	clock_t start = clock();
	while (clock()-start<n);
}

int main() {

	//자동차 세로 직진신호
	int length_straight = 0;

	//자동차 가로 직진신호
	int width_straight = 0;


	//자동차 세로 좌회전신호
	int length_left = 0;


	//자동차 가로 좌회전신호
	int width_left = 0;

	//보행자 세로 파란불신호
	int length_people = 0;

	//보행자 가로 파란불신호
	int width_people = 0;

	while (1) {
		printf("자동차 세로 직진신호입니다.\n세로보행자 파란불입니다.\n");
		++length_straight;
		delay(5000);//5초 동안 정지(사실상 5초 동안 신호등이 켜진상태)
		// sleep 함수 대신 delay 함수 사용 

		printf("자동차 가로 직진신호입니다.\n가로보행자 파란불입니다.\n");
		++width_straight;
		delay(5000);//구현이 잘 되는지 보려고 짧게 5초 한 것이고 실제는 30초로 생각중

		printf("자동차 세로 좌회전신호입니다.\n전체보행자 빨간불입니다.\n");
		++length_left;//++누적신호는 돌발상황때 현재 어떤 신호까지 진행됐는지 확인용으로 사용하려고 저장해놓은 것
		delay(5000);

		printf("자동차 가로 좌회전신호입니다.\n전체보행자 빨간불입니다.\n");
		++width_left;//보행자신호는 자동차 세로, 가로가 좌회전신호일때 모두 빨간불이므로 기준이 되기 어려울 것 같음. 그래서 ++측정은 우선 보류.
		delay(5000);

		printf("세로직진누적횟수:%d\n가로직진누적횟수:%d\n세로좌회전누적횟수:%d\n가로좌회전누적횟수:%d\n", length_straight, width_straight, length_left, width_left);		
	}
	return 0;
}
