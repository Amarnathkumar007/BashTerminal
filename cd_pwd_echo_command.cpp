
void echo(std::string str){std::cout<<str<<"\n";}

bool is_exists(std::string& path, const std::string& folder_name) {
    // Construct the full path to the folder
    // cout<<"Inside exist: "<<path<<" "<<folder_name<<endl;
    std::string new_path = path + "/" + folder_name;

    // Check if the folder exists
    if (access(new_path.c_str(), F_OK) == 0) {
        // Folder exists, update the path
        path = new_path;
        return true;
    } else {
        // Folder does not exist
        std::cerr << "Folder does not exist: " << new_path << std::endl;
        return false;
    }
}


bool status=false; //initilially cd - not executed
string previous_path;
void cd_command(){
    //check for flag
    char * flag=strtok(NULL," ");
    // std::cout<<"inside cd: "<<flag<<endl;

    if(flag)//not null
    {
        //check which flag
        if(!strcmp(flag,".")){}
        else if(!strcmp(flag,"..")){

            //one step down
            int len=g_path.size()-1;
            while(len>0){
                if(g_path[len]=='/'){
                    break;
                }
                len--;
            }
            g_path=g_path.substr(0,len);
            if(home_path==g_path){
                path=user_system_path;
            }else if(path==user_system_path){//kali@kali
                path=g_path;
            }
            else if(path!=user_system_path){//kali@kali
                len=path.size();
                while(len>0){
                   if(path[len]=='/'){
                        break;
                    }
                    len--;
                }
                    path=path.substr(0,len);
            }
        }
        else if(!strcmp(flag,"-")){
            if(status){
                path=previous_path;
                g_path=previous_path;
                status=!status;
            }else{
                status=!status;
                previous_path=g_path;
                //reduce g_path;
                int len=g_path.size()-1;
                while(len>0){
                    if(g_path[len]=='/'){
                        break;
                    }
                    len--;
                }
                g_path=g_path.substr(0,len);
                //set path;
                path=g_path;
            }
        }
        else if(!strcmp(flag,"~")){
            path="~";
        }
        else if(!flag){
            //reach to home
            path=home_path;
        }
        else{
            is_exists(g_path,flag);
            
            if(g_path==home_path){
                path=user_system_path;
            }else{
                path=g_path;
            }
        }
    }else{
        //i.e sets home path when no arg
        path=user_system_path;
        g_path=home_path;
    }
}
