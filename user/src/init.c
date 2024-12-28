

void init() {
    int pid = fork();
    if (pid == 0) {
        exec("sh");
    }
}