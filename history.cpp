#include<vector>
#include<iostream>
#include<string>
using namespace std;

class history
{
    private:

    vector<string> vec;
    int top;

    public:
    history() 
    {     // Constructor
        vec.push_back("$");
        top=1;
    }

    void push(string val){
        vec.push_back(val);
        top++;

        if(top>20){
            //delete by one size;
            //optimization needed
            vec.erase(vec.begin());
            top--;  // update the top pointer;
        }
    }
    void get_data(int val){
        int pointer=top;
        if(val > 20){
            for(int i=0;i<20;i++){
                if(vec[pointer]!="$")
                    cout<<vec[pointer--]<<endl;
                else    
                    break;
            }
        }
        else{
            for(int i=0;i<val;i++){
                if(vec[pointer]!="$")
                    cout<<vec[pointer--]<<endl;
                else    
                    break;
            }
        }   
    }
    ~history(){};
    
};

class process_running{
    std::unordered_set<pid_t> processes;    
    public:

    void add_process(pid_t pid){
            processes.insert(pid);
    }
    void remove_process(pid_t pid){
        processes.erase(processes.find(pid));
    }

    void get_process(){
        for(auto pid : processes)
            cout<<"Process ID: "<<pid<<endl;
    }
};