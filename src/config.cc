#include "config.h"
#include "object_detection.h"
#include <iostream>
#include <fstream> // std::ifstream
#include <sstream> // std::stringstream
#include <string>

using namespace std;

namespace config{
    void load_config(const string config_file){
        string line;
        ifstream file(config_file);

        if (!file.is_open()) {
            cerr << "Error opening config file" << endl;
            exit(1);
        }

        while(getline(file, line)){
            if(line.empty() || line[0] == '#') continue;    // Ignore empty lines and comments

            stringstream breaking_word(line);   // Breaking input into word
            string key, value;

            // Split the line into key and value
            size_t pos = line.find(':');
            if(getline(breaking_word, key, ':') && getline(breaking_word, value)){

                // Removing leading/trailing whitespace
                key.erase(0, key.find_first_not_of(" \t"));
                value.erase(0, value.find_first_not_of(" \t"));

                // cout << "Key: " << key << ", Value: " << value << endl; // Print key-value pairs for debugging

                // Assign values based on the key
                if (key == "video_sources"){

                } 
                else if (key == "detection_threshold"){
                    
                } 
                else if (key == "cache_expiration"){
    
                } 
                else if (key == "cascade_data_path"){
                    OBJDT::pathOfdata = value;
                    cout << "Key" << key << ", Value: " << OBJDT::pathOfdata << endl; // show assign value completed
                }
            }
        }
    }
}