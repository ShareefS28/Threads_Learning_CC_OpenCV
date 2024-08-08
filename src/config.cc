#include "config.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace config{
    void load_config(const std::string& config_file){
        string line;
        ifstream file(config_file);
        while(getline(file, line)){
            // Parse and set configuration parameters
            printf("%s\n", line.c_str()); // For demonstration
        }
    }
}