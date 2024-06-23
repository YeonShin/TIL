#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

void MySleep(int sec) {
    clock_t start = clock();

    sec--;
    while(1){
        if((clock() - start) / CLOCKS_PER_SEC > sec) break;
    }
}

int main() {
    FILE *fp;
    FILE *confession;
    char buf[1024];
    int arr_pid[200] = { -1 };
    int mafia_pid[200] = { -1 };
    int pid;
    int i=0, MafiaIndex=0;

    if((fp = popen("ps -a", "r")) == NULL) {
        return -1;
    }

    while(fgets(buf, sizeof(buf), fp) != NULL) {
        char *cmd;
        cmd = strstr(buf, "linuxtown_class");
        if(cmd != NULL) {
            if(sscanf(buf, "%d", &pid) == 1) {
                if(kill(pid, SIGUSR1) == -1) {
                    perror("error");
                } else {
                    arr_pid[i] = pid;
                    i++;
                }
            }
        }
        // 시그널을 보낼 때 마다 1초간 대기
        MySleep(1);
        printf("Signal %d\n", pid);
    }

    pclose(fp);
    
    MySleep(1);

    confession = fopen("./confession.txt", "r");

    for(int j=0; j<200; j++) {
        fgets(buf, sizeof(buf), confession);
        if(strstr(buf, "!!!") != NULL) {
            mafia_pid[MafiaIndex] = arr_pid[j];
            MafiaIndex++;
        }
    }

    printf("Mafia = %d\n", MafiaIndex);
    printf("Citizen = %d\n", i-MafiaIndex);
    printf("=== Mafia List ===\n");
    for(i = 0; i < MafiaIndex; i++){
        printf("%d\n", mafia_pid[i]);
    }

    fclose(confession);
    return 0;
}