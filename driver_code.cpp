#include <iostream>
#include <cstring> //strtok

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

// using namespace std; 




//variables
std::string path;
std::string home_path;
std::string user_system_path;//kali@kali:
std::string g_path;

//our functions
#include "cd_pwd_echo_command.cpp"
#include "auto_completation_feature.cpp"
#include "history.cpp"
#include "ls_command.cpp"
#include "operators.cpp"
#include "pinfo_command.cpp"
#include "search_command.cpp"


//functions


//unnecessary functions
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
    {
        throw "get_userNmae_and_systemnam: error1";
    }

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

// void command_cd(){
//     //update path & global path;
// };

void process_command(std::string command){
    //converting string to char*
    char *charCommand = new char[command.size() + 1]; // +1 for null terminator
    std::strcpy(charCommand, command.c_str());

    //making token of string
    char *delim = " "; 
    char *token = strtok(charCommand,delim);
    while(token!=NULL){
        // std::cout<<token<<"\n";
        
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
        if(!strcmp(token,"pwd")){
            std::cout<<g_path;    
        }
        if(!strcmp(token,"cd")){
            cd_command();
        }
        if(!strcmp(token,"ls")){
            ls_command();
        }
        
        token= strtok(NULL,delim);

    }
}
int main(){
    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    std::string command;
    try{
        std::cout<<"program started\n";
        get_username_and_systemname(path);
        std::cout<<path;

        while(true){
            std::cout<<"\n"<<path<<"~>";
            getline(std::cin,command);
            process_command(command);
        }


    }catch(std::string ex)
    {
        std::cout<<ex;
    }    
    
    return 0;
}