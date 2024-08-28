
void echo(std::string str){std::cout<<str<<"\n";}

void cd_command(){
    //check for flag
    char * flag=strtok(NULL," ");
    std::cout<<"inside cd: "<<flag;

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
        else if(!strcmp(flag,"-")){}
        else if(!strcmp(flag,"~")){
            path="~";
        }
        else if(!flag){
            //reach to home
            path="~";
        }
        else{
            std::cout<<"not defined\n";
        }
    }else{
        //i.e sets home path when no arg
        path="~";
        g_path=home_path;
    }
}
