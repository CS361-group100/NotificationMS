//reads files given by user, can be called in other locations
#include <fstream>
#include <sstream>
#include "file_reader.h"

std::string readFile(std::string filename) {

    std::ifstream file(filename);
    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}