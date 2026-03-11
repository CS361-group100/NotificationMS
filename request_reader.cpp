//this file reads and stores request information
#include <fstream>
#include "request_reader.h"
#include "json.hpp"
#include <iostream>

using json = nlohmann::json;

Request readRequest(std::string path) {

    std::ifstream file(path);

//double checks that it can open file
     if (!file.is_open()) {
        std::cout << "ERROR: Could not open file: " << path << std::endl;
        exit(1);
    }

    json j;
    file >> j;

    //reads the request and assigns values
    Request req;
    req.email = j["email"];
    req.file = j["file"];

    return req;
}