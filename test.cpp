#include<bits/stdc++.h>
#include <iostream>

using namespace std;
int main(){
    stack<string> st1;
    stack<string> st2;

    st1.push("ls");
    st1.push("pwd");
    st1.push("cd");
    st1.push("rst");
    st1.push("search");


    for(int i=0;i<5;i++)
    {
        string temp=st1.top();
        cout<<temp<<endl;
        st1.pop();
        st2.push(temp);
    }

    while(!st2.empty()){
        st1.push(st2.top());
        st2.pop();
    }

}