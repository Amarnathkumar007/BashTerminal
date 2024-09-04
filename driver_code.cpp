#include <iostream>
#include <cstring> //strtok
#include <ctime>
// #include <bits/stdc++.h>
#include <string>
#include <pwd.h> //for getpwuid
#include <grp.h> //group id
#include <sys/stat.h>
#include <sys/utsname.h>  // For uname
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h> //for ls comamnd
#include <bits/stdc++.h> //for ls comamnd
#include <signal.h>
using namespace std; 



//variables
string path;
string home_path;
string user_system_path;//kali@kali:
string g_path;

//our functions
#include "cd_pwd_echo_command.cpp"
#include "auto_completation_feature.cpp"
#include "history.cpp"
#include "ls_command.cpp"
#include "operators.cpp"
#include "pinfo_command.cpp"
#include "search_command.cpp"
#include "execvp_command.cpp"
#include "pipeline.cpp"
#include "redirection.cpp"

//functions
history hist_obj; //little work needed in execv
process_running process_obj;

//unnecessary functions
void signal_callback_handler(int signum) {
    switch (signum) {
        case SIGINT:
            std::cout << "Caught SIGINT (Ctrl+C). Ignoring and continuing...\n";
            break;
        case SIGTSTP:
            std::cout << "Caught SIGTSTP (Ctrl+Z). Ignoring and continuing...\n";
            exit(signum);
            break;
        default:
            std::cout << "Unhandled signal: " << signal << "\n";
            break;
    }
}
void execute_pipe(string command){executePipeline(command);}


void get_username_and_systemname(std::string& path)
{
    std::pair<std::string,std::string> info;
    // const char* username = getenv("USER");   

    char hostname[HOST_NAME_MAX],
        username[LOGIN_NAME_MAX];

    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);
    
    info.first=username;
    info.second= hostname;

    //checking error
    if(username == nullptr || hostname == nullptr) 
        throw "get_userNmae_and_systemnam: error1";

    path+=username;
    path+="@";
    path+=hostname;
    path+=":";

    //getting global path;
    char cwd[100];
    getcwd(cwd, 100);
    if(getcwd==nullptr){
        throw "get_userName_and_system: error2";
    }
    g_path=cwd;
    home_path=cwd;
    user_system_path=path;
}



void process_command(std::string command,std::string input_command){
    //converting string to char*

    //
    char *charCommand = new char[command.size() + 1]; // +1 for null terminator
    std::strcpy(charCommand, command.c_str());

    //making token of string
    char *delim = " "; 
    char *token = strtok(charCommand,delim);
    while(token!=NULL){
        // std::cout<<token<<"\n";
            hist_obj.push(command);


        //checking type of command
        if(!strcmp(token,"echo")){
            // std::cout<<"entered\n";
            char *token1=strtok(NULL,"\"");
            echo(token);
            char *token2=strtok(NULL," ");
            if(token==NULL){
                //just print 
                echo(token1);
            }else{
                //check operator
                if(!strcmp(token2,">>")){
                    //handle file here
                    // operator_>>(token1);
                    // char *file_name =strtok(NULL," ");

                }
            }
        }
        else if(!strcmp(token,"pwd")){
            std::cout<<g_path;    
        }
        else if(!strcmp(token,"cd")){
            cd_command();
        }
        else if(!strcmp(token,"ls")){
            ls_command();
        }else if(!strcmp(token,"search")){
            token= strtok(NULL,delim);
            search_command(token);
        }else if(!strcmp(token,"history")){
            
            // token =strtok(NULL,delim);
            if(token==NULL){
                hist_obj.get_data(10);
                break;
            }else
                hist_obj.get_data(stoi(token));
        }
        else if(!strcmp(token,"exit")){
            exit(0);
        }else if(!strcmp(token,"pinfo")){
            token= strtok(NULL,delim);
            // cout<<"inside pinfo"<<endl;
            // cout<<"token"<<token<<endl;
            print_pinfo(stoi(token));
            break;
        }
        else{
            execute_command(input_command);
            break;
        }
    token= strtok(NULL,delim);
    }
}

// std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
//     std::vector<std::string> tokens;
//     size_t pos = 0;
//     std::string token;
//     std::string temp = s; // Create a modifiable copy of the input string
//     while ((pos = temp.find(delimiter)) != std::string::npos) {
//         token = temp.substr(0, pos);
//         tokens.push_back(token);
//         temp.erase(0, pos + delimiter.length());
//     }
//     tokens.push_back(temp);

//     return tokens;
// }

int main(){
    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    process_obj.add_process(getpid()); //adding to process object

    std::string command;
    std::string input_command;
    try{
        //handle signals
        signal(SIGINT, signal_callback_handler);
        signal(SIGTSTP, signal_callback_handler); // Handle Ctrl+Z
        // std::cout<<"program started\n";
        get_username_and_systemname(path);
        // std::cout<<path;
        // std::cout<<"\033[2J\033[1;1H";

        while(true){
            std::cout<<"\n"<<path<<"~>";
            if(getline(std::cin,command)){
                input_command=command;
                //check for pipeline
                if(command.find("|") !=string::npos){
                    // std::cout<<"pipline\n";
                    execute_pipe(command);
                }else if(command.find(">>")!=string::npos)
                {
                    executeCommandWithRedirection(command);
                }
                else{
                    process_command(command,input_command);
                }

            }else{
                //to handle ctrl signal as it return end of file signal
                if (std::cin.eof()) {
                    std::cout << "EOF (Ctrl+D) received. Exiting...\n";
                    cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
                    break;
                } 
            };
        }
    }catch(std::string ex)
    {
        std::cout<<ex;
    }    
    
    return 0;
}