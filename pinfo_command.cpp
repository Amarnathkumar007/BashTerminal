// #include <iostream>
// #include <fstream>
// #include <string>
// #include <sstream>
// #include <sys/types.h>
// #include <unistd.h>
// #include <pwd.h>
// #include <limits.h>
// #include <cstring>

void print_pinfo(pid_t pid) {
    std::string pid_str = std::to_string(pid);
    std::string status_file = "/proc/" + pid_str + "/status";
    std::string exe_file = "/proc/" + pid_str + "/exe";

    std::ifstream status_stream(status_file);
    if (!status_stream) {
        std::cerr << "Error: Unable to open status file for PID " << pid << std::endl;
        return;
    }

    // Extract status information
    std::string line;
    std::string process_status;
    std::string memory_usage;
    while (std::getline(status_stream, line)) {
        if (line.find("State:") == 0) {
            // Example line: "State:	R (running)"
            std::string state = line.substr(6);
            // Extract the state code and check for foreground
            char status_char = state[0];
            bool is_foreground = (state.find('+') != std::string::npos);
            if (status_char == 'R') process_status = is_foreground ? "R+" : "R";
            else if (status_char == 'S') process_status = is_foreground ? "S+" : "S";
            else if (status_char == 'Z') process_status = "Z";
            else if (status_char == 'T') process_status = "T";
        }
        if (line.find("VmSize:") == 0) {
            // Example line: "VmSize:    123456 kB"
            size_t pos = line.find_first_of("0123456789");
            if (pos != std::string::npos) {
                memory_usage = line.substr(pos);
            }
        }
    }
    status_stream.close();

    // Get executable path
    char exe_path[PATH_MAX];
    ssize_t len = readlink(exe_file.c_str(), exe_path, sizeof(exe_path) - 1);
    if (len != -1) {
        exe_path[len] = '\0'; // Null-terminate the string
    } else {
        std::cerr << "Error: Unable to get executable path for PID " << pid << std::endl;
        return;
    }

    // Get the username
    struct passwd *pw = getpwuid(getuid());
    std::string username = pw ? pw->pw_name : "unknown";

    // Get the hostname
    char hostname[HOST_NAME_MAX];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        std::cerr << "Error: Unable to get hostname" << std::endl;
        return;
    }

    std::cout << "<" << username << "@" << hostname << ":~>" << std::endl;
    std::cout << "pinfo pid -- " << pid << std::endl;
    std::cout << "Process Status -- {" << process_status << "}" << std::endl;
    std::cout << "memory -- " << memory_usage << " {Virtual Memory}" << std::endl;
    std::cout << "Executable Path -- " << exe_path << std::endl;
}

