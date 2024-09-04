#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>
#include <string>


auto split = [](std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == std::string::npos || end == std::string::npos) {
        s = "";
    } else {
        s = s.substr(start, end - start + 1);
    }
};

void executeCommandWithRedirection(const std::string& command) {
    // Find the redirection operator
    size_t redirectPos = command.find('>');
    if (redirectPos == std::string::npos) {
        std::cerr << "Redirection operator '>' not found in command" << std::endl;
        return;
    }

    // Split command into command and file parts
    std::string cmdPart = command.substr(0, redirectPos);
    std::string filePart = command.substr(redirectPos + 1);

    // Trim whitespace


    split(cmdPart);
    split(filePart);

    // Open the file for writing (create it if it doesn't exist, truncate if it does)
    int fd = open(filePart.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        close(fd);
        return;
    }

    if (pid == 0) {
        // Child process
        dup2(fd, STDOUT_FILENO); // Redirect stdout to file
        close(fd);

        // Parse the command part
        char* args[100];
        std::string cmdStr = cmdPart;
        size_t pos = 0;
        int i = 0;
        while ((pos = cmdStr.find(' ')) != std::string::npos) {
            args[i++] = strdup(cmdStr.substr(0, pos).c_str());
            cmdStr.erase(0, pos + 1);
        }
        args[i++] = strdup(cmdStr.c_str());
        args[i] = nullptr;

        execvp(args[0], args);
        // perror("execvp"); // execvp failed
        std::cout<<"failed to Execute"<<std::endl;
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(fd);
    waitpid(pid, nullptr, 0);
}


