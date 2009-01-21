// include this in a handler c file to include the pito jail
int execve(const char *filename, char *const argv[], char *const envp[]) {
    return PITO_SUPER(execve)(filename, argv, envp);
}

int execv(const char *filename, char *const argv[]) {
    return PITO_SUPER(execv)(filename, argv);
}

int execvp(const char *filename, char *const argv[]) {
    return PITO_SUPER(execvp)(filename, argv);
}
