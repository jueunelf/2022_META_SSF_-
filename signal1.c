#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#define RED_LAMP        0
#define YELLOW_LAMP     1
#define GREEN_LAMP      2

void signal_lamp(int);

char lamp_name[6];

//현재 시각을 출력하는 함수
void prnTime() {
    time_t timer;
    struct tm *t;

    timer = time(NULL);
    t = localtime(&timer);

    printf("%02d:%02d:%02d",
              t->tm_hour, t->tm_min, t->tm_sec);
}

int main(int argc, char **argv) {

    pid_t pid[4], pid_tmp;
    int i, red, yellow, green, count;

    if ( argc < 5 ) {
        fprintf(stderr, "USEAGE: [%s] [red_lamp_sec] [yellow_lamp_sec] [green_lamp_sec] [count]\n", argv[0]);
        exit(1);
    }
    //사용자의 입력을 String에서 int으로 변경한다.
    red = atoi(argv[1]);
    yellow = atoi(argv[2]);
    green = atoi(argv[3]);
    count = atoi(argv[4]);
    //count 값이 2이하일때 에러메시지를 출력한다.
    if( count <=2 ) {
        printf(" count input error : count(arv[4])>2 \n");
        exit(1);
    }
    //red,yellow,green 켜지는 대기시간이 1보다 작으면 에러메시지 출력한다.
    if( red<1 || yellow<1 || green<1 ) {
        printf(" red,yellow,green wait time error : (red,yellow,green)>=1 \n");
        exit(1);
    }
    //메인Process는 controller역할을 하게 된다.
    //그러므로 메일 Process의 id를 받아온다.
    pid_tmp = getpid();
    //메인 프로세스의 생성을 알린다.
    printf("The controller process has created with pid - %d.\n", pid_tmp);
    //빨간불을 위한 프로세스를 생성한다.
    pid[RED_LAMP] = fork();

    switch ( pid[RED_LAMP] ) {
    case -1:
        perror(argv[0]);
        exit(1);
    case 0:
        //빨간불의 역할을 수행하는 함수를 실행 한다.
        signal_lamp(RED_LAMP);
        exit(1);
    }
    //노란불을 위한 프로세스를 생성한다.
    pid[YELLOW_LAMP] = fork();

    switch ( pid[YELLOW_LAMP] ) {
    case -1:
        perror(argv[0]);
        exit(1);
    case 0:
        //노란불 역할을 수행하는 함수를 실행 한다.
        signal_lamp(YELLOW_LAMP);
        exit(1);
    }
    //파란불을 위한 프로세스를 생성한다.
    pid[GREEN_LAMP] = fork();

    switch ( pid[GREEN_LAMP] ) {
    case -1:
        perror(argv[0]);
        exit(1);
    case 0:
        //파란불 역할을 수행하는 함수를 실행한다.
        signal_lamp(GREEN_LAMP);
        exit(1);
    }


    for ( i = 0 ; i < count ; i++ ) {
        printf("cycle #%d\n", i+1);
        //빨간불 프로세스에게 USER SIGNAL을 보낸다.
        //USER SIGNAL은 Turn On을 하라는 명령이다.
        kill(pid[RED_LAMP], SIGUSR1);
        //관련 정보를 출력한다.
        printf("The controller sent the signal to red at ");
        prnTime();
        printf(".\n");
        sleep(red);

        //마찬 가자리로 노란불 프로세스 에게 Turn on을 하라는
        //USER SIGNAL을 보낸다.
        kill(pid[YELLOW_LAMP], SIGUSR1);
        printf("The controller sent the signal to yellow at ");
        prnTime();
        printf(".\n");
        sleep(yellow);

        //역시 파란불 프로세스에게 Turn On을 하라는
        //USER SIGNAL을 보내나.
        kill(pid[GREEN_LAMP], SIGUSR1);
        printf("The controller sent the signal to green at ");
        prnTime();
        printf(".\n");
        sleep(green);
    }
    //프로세스들이 모든 작업을 수행 했음으로
    //프로세스를 종료하라는 명령을 보낸다.
    for ( i = RED_LAMP ; i <= GREEN_LAMP ; i++ )
        kill(pid[i], SIGUSR2 );
    //프로세스들이 종료되기를 기다렸다가.
    waitpid(pid[0]);
    waitpid(pid[1]);
    waitpid(pid[2]);
    //Controller 프로세스도 종료한다.
    printf("The controller program has exited.\n");
}
//Turn On SIGNAL이 들어왔을 때 수행하는
//SIGNAL HANDLER이다.
void sig_handler_turn_on(int signo) {
    //시그널을 받아서 불을 켰다는 메세지를 남긴다.
    printf("The %s light was turned on at ", lamp_name);
    prnTime();
    printf(".\n");
}
//프로세스의 종료를 명령하는 시글널이 왔을때
//수행되는 시그널 핸들러이다.
void sig_handler_kill(int signo) {
    //시그널을 받았다는 메세지를 남기고
    printf("The %s light process has been killed.\n", lamp_name);
    //프로세스를 종료한다.
    exit(1);
}
//각종 램프 프로세스가 생성되면서
//바로 수행하는 함수이다.
void signal_lamp(int kind_of_lamp) {
    pid_t pid;

    pid = getpid();
    //각종 램프 프로세스가 생성되면
    //해당 인자로써 어떤 프로세스 인지 판단하고
    switch (kind_of_lamp) {
    case RED_LAMP:
        strcpy(lamp_name, "red");
        break;
    case YELLOW_LAMP:
        strcpy(lamp_name, "yellow");
        break;
    case GREEN_LAMP:
        strcpy(lamp_name, "green");
        break;
    }
    //얻어온 자신의 PID와 함께 프로세스가 생성되었음을 알린다.
    printf("The %s light process has created with pid - %d.\n", lamp_name, pid);
    //각각의 시그널이 시그널 핸들러를 연결한다.
    signal(SIGUSR1, (void *) sig_handler_turn_on);
    signal(SIGUSR2, (void *) sig_handler_kill);
    //시그널이 들어올때 까지 대기한다.
    while(1) ;
}
