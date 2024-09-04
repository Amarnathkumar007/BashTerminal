#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>
using namespace std;
// Define the function to be called when ctrl-c (SIGINT) is sent to process
void signal_callback_handler(int signum) {
        switch (signum) {
            case SIGINT:
                std::cout << "Caught SIGINT (Ctrl+C). Ignoring and continuing...\n";
                break;
            case SIGTSTP:
                std::cout << "Caught SIGTSTP (Ctrl+Z). Ignoring and continuing...\n";
                exit(signum);
                break;
            default:
                std::cout << "Unhandled signal: " << signal << "\n";
                break;
    }
}
int main(){
   // Register signal and signal handler
    signal(SIGINT, signal_callback_handler);
    signal(SIGTSTP, signal_callback_handler); // Handle Ctrl+Z
    while(true){
      cout << "Program processing..." << endl;
      sleep(1);
    }
   return EXIT_SUCCESS;
}