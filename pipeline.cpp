#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

auto trim = [](std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == std::string::npos || end == std::string::npos) {
        s = "";
    } else {
        s = s.substr(start, end - start + 1);
    }
};
void trim_commond(std::string& commandLeft, std::string& commandRight){
    trim(commandLeft);
    trim(commandRight);
};
void executePipeline(const std::string& command) {
    // Parse the command string into commands and arguments
    std::string commandLeft, commandRight;
    size_t pipePos = command.find('|');
    if (pipePos == std::string::npos) {
        // std::cerr << "Invalid command format. Must contain a pipe '|'" << std::endl;
        return;
    }

    commandLeft = command.substr(0, pipePos);
    commandRight = command.substr(pipePos + 1);

    // Trim whitespace

    trim_commond(commandRight,commandRight);


    // Create a pipe
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        // perror("pipe");
        std::cout<<"error in pipe"<<std::endl;
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == -1) {
        // perror("fork");
        std::cout<<"error in fork"<<std::endl;
        return;
    }

    if (pid1 == 0) {
        // First child: execute left command
        close(pipefd[0]); // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to pipe
        close(pipefd[1]);

        // Parse the left command
        char* args[100];
        std::string leftCmdStr = commandLeft;
        size_t pos = 0;
        int i = 0;
        while ((pos = leftCmdStr.find(' ')) != std::string::npos) {
            args[i++] = strdup(leftCmdStr.substr(0, pos).c_str());
            leftCmdStr.erase(0, pos + 1);
        }
        args[i++] = strdup(leftCmdStr.c_str());
        args[i] = nullptr;

        execvp(args[0], args);
        // perror("execvp"); // execvp failed
        std::cout<<"error in executions"<<std::endl;
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        // perror("fork");
        std::cout<<"error in fork"<<std::endl;
        return;
    }

    if (pid2 == 0) {
        // Second child: execute right command
        close(pipefd[1]); // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to pipe
        close(pipefd[0]);

        // Parse the right command
        char* args[100];
        std::string rightCmdStr = commandRight;
        size_t pos = 0;
        int i = 0;
        while ((pos = rightCmdStr.find(' ')) != std::string::npos) {
            args[i++] = strdup(rightCmdStr.substr(0, pos).c_str());
            rightCmdStr.erase(0, pos + 1);
        }
        args[i++] = strdup(rightCmdStr.c_str());
        args[i] = nullptr;

        execvp(args[0], args);
        // perror("execvp"); // execvp failed
        std::cout<<"error in fork"<<std::endl;
        exit(EXIT_FAILURE);
    }

    // Parent process: close pipe ends and wait for children
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);
}

// int main() {
//     // std::string command = "echo \"this is\" | cat";
//     std::string command;
//     getline(std::cin,command);
//     executePipeline(command);
//     return 0;
// }