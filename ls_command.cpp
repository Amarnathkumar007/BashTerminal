
/*
struct stat {
    dev_t     st_dev;     // Device ID of the file
    ino_t     st_ino;     // Inode number
    mode_t    st_mode;    // File type and mode (permissions)
    nlink_t   st_nlink;   // Number of hard links
    uid_t     st_uid;     // User ID of the file's owner
    gid_t     st_gid;     // Group ID of the file's group
    dev_t     st_rdev;    // Device ID (if the file is a device)
    off_t     st_size;    // Total size of the file in bytes
    blkcnt_t  st_blocks;  // Number of 512-byte blocks allocated
    blksize_t st_blksize; // Optimal block size for I/O operations
    time_t    st_atime;   // Time of last access
    time_t    st_mtime;   // Time of last modification
    time_t    st_ctime;   // Time of last status change
};
#include <pwd.h>
struct passwd {
    char   *pw_name;   // User name
    char   *pw_passwd; // Password (usually empty or unused for modern systems)
    uid_t   pw_uid;    // User ID
    gid_t   pw_gid;    // Group ID
    char   *pw_gecos;  // GECOS field (usually contains user’s full name or other info)
    char   *pw_dir;    // Home directory
    char   *pw_shell;  // Login shell
};
*/
void get_file_stat(string path,struct stat &file_stat,std::vector<std::pair<std::string,dirent*>> &file_pair,int i){
    if (stat(path.c_str(), &file_stat) != 0) {
        std::string err= "Inside ls -l: failed to info about path: "+path;
        throw err;  
    }
}
void get_detail_file(struct stat &file_stat,std::vector<std::pair<std::string,dirent*>> &file_pair,int i){
        std::string lsData="";
    //permissions
        lsData += (S_ISDIR(file_stat.st_mode) ? 'd' : '-');
        lsData += (file_stat.st_mode & S_IRUSR ? 'r' : '-');
        lsData += (file_stat.st_mode & S_IWUSR ? 'w' : '-');
        lsData += (file_stat.st_mode & S_IXUSR ? 'x' : '-');
        lsData += (file_stat.st_mode & S_IRGRP ? 'r' : '-');
        lsData += (file_stat.st_mode & S_IWGRP ? 'w' : '-');
        lsData += (file_stat.st_mode & S_IXGRP ? 'x' : '-');
        lsData += (file_stat.st_mode & S_IROTH ? 'r' : '-');
        lsData += (file_stat.st_mode & S_IWOTH ? 'w' : '-');
        lsData += (file_stat.st_mode & S_IXOTH ? 'x' : '-');
    //hardlinks
        lsData+="\t";
        lsData+=to_string(file_stat.st_nlink);
        lsData+="\t";


    // file owner
        struct passwd *pw = getpwuid(file_stat.st_uid);
        if(pw == nullptr)
            lsData+="unknown_user";
        else    
            lsData+=pw->pw_name;

        lsData+="\t";
        // lsData+="kali";
        // lsData+="\t";
        // lsData+="kali";
        // lsData+="\t";

    // //file group
        struct group  *gr = getgrgid(file_stat.st_gid);
        if(gr != 0)
            lsData+=gr->gr_name;
        else    
            lsData+="group_owner";
            
        lsData+="\t";

    //size of file
        lsData+=std::to_string(file_stat.st_size);
        lsData+="\t";
    //date & time
        char time[100];
        strftime(time, sizeof(time), "%b %2d %H:%M", localtime(&file_stat.st_mtime));
        lsData += time;

        // lsData+="date_time";
        lsData+="\t";
    //file name
        lsData+=file_pair[i].first;

    std::cout<<lsData<<std::endl;
}
void ls_command(){
    //check flag
    char * flag=strtok(NULL," ");
    // std::cout<<"inside ls: "<<flag;


    DIR* dirp = opendir(g_path.c_str());
    if(!dirp)//if null
        throw "Error in g_path i.e path doesn't exist";
        
    std::vector<dirent *> files;
    std::vector<std::pair<std::string,dirent*>> file_pair; //for sorting

    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        std::pair<std::string,dirent *> p;
        p.first=dp->d_name;
        p.second=dp;
        file_pair.push_back(p);
    }
    sort(file_pair.begin(),file_pair.end());
    for(auto i: file_pair){files.push_back(i.second);}
    closedir(dirp);

    // std::cout<<"printing vector\n";

    if(flag){
        //not null flag
        char * file_input=strtok(NULL," ");
        if(!file_input){
            //when file not given
            //note -a means hidden file
            if(!strcmp(flag,"-a")){
                //all files along with hidden
                std::vector<std::string> files_name;

                for(auto i: files)
                    files_name.push_back(i->d_name);
        
                for(auto i: files_name){
                    std::cout<<i<<"\n";
                }
            }
            if(!strcmp(flag,"-l")){
                int n=files.size();
                for(int i=0;i<n;i++){
                    if(files[i]->d_name[0]=='.'){
                        continue;
                    }
                    std::string path=g_path+"/"+file_pair[i].first;

                    struct stat file_stat;
                    // Get file status
                    get_file_stat(path,file_stat,file_pair,i);
                    get_detail_file(file_stat,file_pair,i);
                }
            }
            else if(!strcmp(flag,"-la") || !strcmp(flag,"-al")){

                int n=files.size();
                for(int i=0;i<n;i++){
                    std::string path=g_path+"/"+file_pair[i].first;

                    struct stat file_stat;
                    // Get file status
                    get_file_stat(path,file_stat,file_pair,i);
                    get_detail_file(file_stat,file_pair,i);
                }
                
            }
            else if(!strcmp(flag,".")){
                //print same directory elements
                std::vector<std::string> files_name;
                for(auto i: files)
                    files_name.push_back(i->d_name);

                for(auto i: files_name){
                    if(i[0]=='.')
                        continue;
                    std::cout<<"\t"<<i<<"\n";
                }
            }
            else if(!strcmp(flag,"..")){
                //go back and check elements
                std::string t_path=g_path;
                //go one level down;
                int len=t_path.size()-1;
                while(len>0){
                    if(t_path[len]=='/'){
                        break;
                    }
                    len--;
                }
                t_path=t_path.substr(0,len);

                DIR* dirp = opendir(t_path.c_str());
                if(!dirp)//if null
                    throw "Inside ls .. : Error in g_path i.e path doesn't exist";

                std::vector<std::pair<std::string,dirent*>> file_pair; //for sorting

                struct dirent * dp;
                while ((dp = readdir(dirp)) != NULL) {
                    std::pair<std::string,dirent *> p;
                    p.first=dp->d_name;
                    p.second=dp;
                    file_pair.push_back(p);
                }
                sort(file_pair.begin(),file_pair.end());
                closedir(dirp);

                for(auto i: file_pair){
                    if(i.first[0]=='.') continue;
                    std::cout<<"\t"<<i.first<<"\n";
                }

                
            }
            else if(!strcmp(flag,"~")){
                //go back and check elements
                std::string t_path=home_path;


                DIR* dirp = opendir(t_path.c_str());
                if(!dirp)//if null
                    throw "Inside ls .. : Error in g_path i.e path doesn't exist";

                std::vector<std::pair<std::string,dirent*>> file_pair; //for sorting

                struct dirent * dp;
                while ((dp = readdir(dirp)) != NULL) {
                    std::pair<std::string,dirent *> p;
                    p.first=dp->d_name;
                    p.second=dp;
                    file_pair.push_back(p);
                }
                sort(file_pair.begin(),file_pair.end());
                closedir(dirp);

                for(auto i: file_pair){
                    if(i.first[0]=='.') continue;
                    std::cout<<"\t"<<i.first<<"\n";
                }
            }
        }else{
            //when file given with flag
            //check if file exist
            int n=files.size();
            // std::cout<<"inside ls -l <file> 1\n";
            //find number of files
            vector<char*> v_parameter;
            v_parameter.push_back(file_input);
            while(file_input){    
                // std::cout<<"inside ls -l <file> 2:  ";
                v_parameter.push_back(file_input);
                file_input=strtok(NULL," "); //not working
            }

            for(int k=0;k<v_parameter.size();k++){
                for(int i=0;i<n;i++){
                    if(!strcmp(v_parameter[k],files[i]->d_name)){
                        // std::cout<<"file_found ";
                        std::string path=g_path+"/"+file_pair[i].first;
                        struct stat file_stat;
                        get_file_stat(path,file_stat,file_pair,i);
                        get_detail_file(file_stat,file_pair,i);
                    }
                }
            }
        }


    }else{
        //if null flag
        std::vector<std::string> files_name;
        for(auto i: files)
            files_name.push_back(i->d_name);

        for(auto i: files_name){
            if(i[0]=='.')
                continue;
            std::cout<<"\t"<<i<<"\n";
        }
    }

}
