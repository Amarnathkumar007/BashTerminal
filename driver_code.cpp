#include <iostream>
#include <cstring> //strtok
// #include <bits/stdc++.h>
#include <string>
#include <sys/utsname.h>  // For uname
#include <unistd.h>
#include <limits.h>
// using namespace std; 

//variables
std::string path;
std::string home_path;
std::string g_path;
//functions

//cd start
void change_path_down(std::string& path){
    int n = path.size() - 1;

    while (n >= 0) {
        if (path[n] == '/') {
            break;
        }
        n--;
    }

    std::string final = (n >= 0) ? path.substr(0, n) : path;
}

void cd_back(){
    //going back
    change_path_down(g_path);

    if(path==home_path){
        path=g_path;
    }else{
        change_path_down(path);
    };
}

void cd_next(std::string st){
    //going next
    g_path+=st;
    path+=st;
    std::cout<<st;
}


//cd finishes
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

}

// void command_cd(){
//     //update path & global path;
// };

void process_command(char* command){
    
    char * ptr = strtok(command," ");
    while(ptr!=NULL){

        // std::cout<<ptr<<"\n";
        if(strcmp(ptr,"cd")){
            ptr=strtok(NULL," ");
            if(strcmp(ptr,"..")){
                //cd back function;
                cd_back();
            }else{
                //must be enter command;
                cd_next(ptr);
            }
            continue;    
        }

        ptr=strtok(NULL," ");// ptr=strtok(NULL," ,");//removes space ans comma
    }
}
int main(){
    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    try{
        std::cout<<"program started\n";
        get_username_and_systemname(path);
        std::cout<<path;

        while(true){
            std::cout<<"\n"<<path<<"~>";
            char command[1000];
            std::cin.getline(command,1000);
            process_command(command);
        }


    }catch(std::string ex)
    {
        std::cout<<ex;
    }    
    
    return 0;
}