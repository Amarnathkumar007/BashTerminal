// #include <iostream>
// #include <string.h>

// using namespace std;
// int main(){
//     string path="file1/file2/file3";
//     int len=path.size()-1;
//     while(len>=0){
//         if(path[len]=='/'){
//             break;
//         }
//         len--;
//     }
//     path=path.substr(0,len);
//     cout<<path;
//     return 0;
// }


void search_command(string file_name){
    
    queue<string> q_folders;
    q_folders.push(g_path);

    while(!q_folders.empty()){
        string path = q_folders.front();//
        q_folders.pop();//

        DIR* dirp = opendir(path.c_str());
        if(dirp ==nullptr){throw "Inside search_command: failed to open directory: "+path;}
        struct dirent * dp;

        while ((dp = readdir(dirp)) != nullptr) {
            if (string(dp->d_name) == "." || string(dp->d_name) == "..") {
                continue;
            }
            string t_path=path+"/"+dp->d_name;
            // cout<<"t_path: "<<t_path<<endl;

            struct stat file_type;
            if (stat(t_path.c_str(), &file_type) != 0) {
                std::string err= "Inside ls -l: failed to info about path: "+path;
                throw err;  
            }

            if(S_ISDIR(file_type.st_mode))
                q_folders.push(t_path);
            else if(dp->d_name == file_name){
                cout<<"true\n";
                return;
            }
        }
        closedir(dirp);
    }
    cout<<"false";
}