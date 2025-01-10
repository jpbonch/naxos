

void init() {
    // int pid = fork();
    // if (pid == 0) {
    //     exec("sh");
    // }
    *((char*)0xB8002) = 'X';
}