#include <unistd.h>
#include <sys/wait.h>

void createProcess(int in, int out, const char* pathProcess){
    if (fork() == 0) {
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        close(in);
        close(out);
        execl(pathProcess, nullptr);
        _exit(0);
    }
}

int main()
{
    //std::cout << 14 * 14 * 14 + 21 * 21 * 21 + 28 * 28 * 28;
    const char *pathAProcess = "../../A/cmake-build-debug/A";
    const char *pathMProcess = "../../M/cmake-build-debug/M";
    const char *pathPProcess = "../../P/cmake-build-debug/P";
    const char *pathSProcess = "../../S/cmake-build-debug/S";

    int pipeAM[2];
    int pipeMP[2];
    int pipePS[2];
    int status;

    pipe(pipeAM);
    pipe(pipeMP);
    pipe(pipePS);

    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);
    close(STDIN_FILENO);

    createProcess(in, pipeAM[1], pathAProcess);
    createProcess(pipeAM[0], pipeMP[1], pathMProcess);
    createProcess(pipeMP[0], pipePS[1], pathPProcess);
    createProcess(pipePS[0], out, pathSProcess);

    for (int i = 0; i < 4; ++i) {
        wait(&status);
    }

}
