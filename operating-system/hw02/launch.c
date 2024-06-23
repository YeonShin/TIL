#include <stdio.h>
#include <stdlib.h> // 문자를 숫자로 변환 및 숫자를 문자로 변환하기 위한 함수를 사용하기 위해 헤더 파일 include
#include <unistd.h> // fork(), execlp() 함수를 사용하기 위해 헤더 include
#include <sys/wait.h> // wait 함수를 사용하기 위해 헤더 include

int main(int argc, char *argv[]) {

    if(argc <= 1) {
        // main 함수 인자를 받는데 실패한 경우
        printf("excute failed\n");
        return 0;
    }  

    int status; // 자식 프로세스가 종료되기 전까지의 상태를 저장할 변수 status
    int N = atoi(argv[1]); // 인자로 받은 문자 배열 argv의 2번째 값(전달받은 숫자 N)을 정수형 변수로 변환하여 저장
    int pid; // fork() 함수 실행 후 반환받을 pid 값을 저장할 변수

    if(N < 2) {
        // 2미만의 인자를 받을 경우 프로그램 종료
        printf("Wrong parameter value!\n");
        return 0;
    }
    
    pid = fork(); // fork() 함수를 호출하여 프로세스를 하나 생성한 후 반환 값을 pid에 저장
    if (pid == 0) {
        // 자식 프로세스의 경우
        char buffer[10]; // execlp 함수를 호출할 때 전달할 인자인 숫자 N을 문자 배열로 변환하여 저장할 문자 배열 buffer 선언
        sprintf(buffer, "%d", N); // 정수형 변수 N을 문자 배열으로 변환하여 buffer 배열에 저장
        execlp("./sumfact", "./sumfact", buffer, (char*)NULL); // execlp 함수를 호출하여 자식 프로세스는 "sumfact"를 실행한다 이 때 buffer를 인자로 전달
        printf("exec failed!\n"); // execlp 함수를 호출해 "sumfact"를 실행하는데 실패한 경우 
        return 0;
    }
    else {
        // 부모 프로세스의 경우
        long long int sum = 0; // 1부터 N까지의 합의 결과를 저장할 변수 num 선언 후 0으로 초기화
        for(int i=1; i<=N; i++) {
            // 1부터 N까지 합하면서 num 값 업데이트
            sum += (long long int)i;
        }
        printf("launch: sum = %lld\n", sum); // 1부터 N까지의 합 sum을 출력
        wait(&status); // 자식 프로세스 종료까지 부모 프로세스는 대기
    }
  return 0; // 프로그램 종료
}