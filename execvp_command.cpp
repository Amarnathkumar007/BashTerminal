#include <sys/types.h>
#include <sys/wait.h>
void execute_command(const std::string& command) {
    // Split the command string into arguments

    std::vector<char*> args;
    char* cmd = new char[command.size() + 1];
    std::strcpy(cmd, command.c_str());

    char* token = std::strtok(cmd, " ");
    while (token != nullptr) {
        args.push_back(token);
        token = std::strtok(nullptr, " ");
    }
    args.push_back(nullptr); // execvp requires a null-terminated array

    // Fork a child process
    pid_t pid = fork();
    if (pid == -1) {
        // Fork failed
        std::cerr << "Failed to fork a child process" << std::endl;
        delete[] cmd;
        return;
    } else if (pid == 0) {
        // Child process
        if (execvp(args[0], args.data()) == -1) {
            std::cout<<"failed to execute\n";
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child process to finish
    }

    delete[] cmd;
}