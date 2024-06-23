#include <stdio.h>
#include <stdlib.h> // 문자를 숫자로 변환 및 숫자를 문자로 변환하기 위한 함수를 사용하기 위해 헤더 파일 include
#include <pthread.h> // pthread를 이용하기 위해 헤더 파일 include

long long int factorial(long long int N) {
    // 전달 받은 숫자 N의 팩토리얼 값을 계산하여 반환하는 함수
    if(N == 0) {
        // 마지막으로 1 반환
        return 1;
    }
    else {
        // 재귀적으로 팩토리얼 함수 호출
        return N * factorial(N-1);
    }
}

void *firstThreadFunc(void *data) {
    // 첫 번째로 생성된 스레드가 수행할 함수
    int *N = (int *)data; // 전달받은 인자 *data를 정수형 포인터 변수 *N으로 저장
    long long int result = factorial(*N);  // 팩토리얼의 결과를 저장할 변수 result 선언 후 factorial 함수 호출하여 값 초기화
    printf("sumfact: factorial = %lld\n", result); // 첫 번째 스레드의 팩토리얼 결과 출력
}

void *threadFunc(void *data) {
    // 그 외 스레드가 수행할 함수
    int *N = (int *)data; // 전달받은 인자 *data를 정수형 포인터 변수 *N으로 저장
    long long int sum = 0; // 1부터 N까지 결과 값을 저장할 변수 sum 선언 후 초기화
    for(int i=1; i<=(*N); i++) {
        // 1부터 N까지 반복하면서 sum 값 업데이트
        sum += i;
    }
    printf("sumfact: sum = %lld\n", sum); // 1부터 N까지의 합 결과값 출력
}

int main(int argc, char *argv[]) {
    if(argc <= 1) {
      // main 함수가 인자를 받는데 실패한 경우
        printf("excute failed!\n");
        return 0;
    }
    int N = atoi(argv[1]); // 인자로 받은 문자 배열 argv의 2번째 값(전달받은 숫자 N)을 정수형 변수로 변환하여 저장

    if(N < 2) {
        // 2미만의 인자를 받을 경우 프로그램 종료
        printf("Wrong parameter value!\n");
        return 0;
    }
    
    printf("launch: start sumfact %d\n", N); // 자식 프로세스가 sumfact를 실행하여 sumfact가 시작됐음을 출력 

    pthread_t thread_id[N]; // 스레드의 id 배열 선언

    // 첫 번째 스레드를 생성한다. 이 때 첫 번째 스레드의 경우 팩토리얼 값을 계산하는 함수를 수행하도록 한다.
    pthread_create(&thread_id[0], NULL, firstThreadFunc, (void *)&N); 

    for(int i=1; i<N; i++) {
        // 이 후 나머지 스레드를 총 스레드 개수 N개까지 생성한다. 이 때 콜백 함수는 1부터 N까지 합을 계산하는 함수이다.
        pthread_create(&thread_id[i], NULL, threadFunc, (void *)&N);
    }

    for(int i=0; i<N; i++) {
        // 생성된 스레드들이 종료되기를 기다리도록 pthread_join 함수를 호출한다.
        pthread_join(thread_id[i], NULL);
    }

    return 0; // 프로그램 종료료
}