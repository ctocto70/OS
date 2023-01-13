
#include <stdio.h>
#include <stdlib.h>Д
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    putenv("PROC_TO_KILL=Telegram,WarThunder");
    pid_t pid = fork();
    if (pid == 0) {
        execv("./../../Killer/build/Killer", argv);
        _exit(0);
    }
    else if (pid == -1) {
        fprintf(stderr, "FORK FAILED\n");
        return -1;
    }
    else {
        wait(NULL);
        _exit(0);
    }
    unsetenv("PROC_TO_KILL");
    return 0;
}
