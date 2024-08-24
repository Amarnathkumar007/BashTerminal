#include <iostream>
#include <cstring> //strtok
// #include <bits/stdc++.h>
#include <string>
#include <sys/utsname.h>  // For uname
#include <unistd.h>
#include <limits.h>
using namespace std; 

//variables
string path;
string g_path;



void get_username_and_systemname(string& path)
{
    pair<string,string> info;
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

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    try{
        // std::cout<<"program started";
        get_username_and_systemname(path);

        cout<<path<<"~>";
        cout<<"\n"<<g_path<<endl;







    }catch(string ex)
    {
        cout<<ex;
    }    
    
    return 0;
}