#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
class execvp_command{

    public:
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


        // int cpid = fork();

        // if(cpid == 0){
        //     printf("\nChild: I have the PID: %d, I am going to call exec!\n", getpid());
        //     // char* argumentVector[]= {"ps", "-l", NULL}; 
        //     int flag = execvp(args[0], args.data());
        //     if(flag==-1)
        //     {
        //         std::cout<<"execvp :Error in executing child process\n";
        //         exit(-1);     
        //     }
        //     exit(0);
        // }
        // else if(cpid>0){
        //     //parent process waits
        //     wait(NULL);
        // }else{
        //     std::cout<<"execvp :error in calling child prcess\n";
        // }


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
                std::cout<<"execcvp: execvp failed\n";
                exit(EXIT_FAILURE);
            }
            // exit(0);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0); // Wait for the child process to finish
        }

        delete[] cmd;
    }

};