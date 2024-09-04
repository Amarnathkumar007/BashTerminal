// Example for inputting a single keystroke in C++ on Linux
// by Adam Pierce <adam@doctort.org>
// This code is freeware. You are free to copy and modify it any way you like.

#include <iostream>
#include <termios.h>
#include <unistd.h>

using namespace std;
int main()

{
    // Black magic to prevent Linux from buffering keystrokes.
        struct termios t;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= ~ICANON;
        tcsetattr(STDIN_FILENO, TCSANOW, &t);

    while(true){
    // Once the buffering is turned off, the rest is simple.
        cout << "Enter a character: ";
        char c = cin.get();
        if(c=='['){
            c=cin.get();
            cout<<"arrow\n";
        }else{
            cout<<"not arrow\n";

        }
        // cout << "\n\tYour character was " << c << endl;
    }


    return 0;
}