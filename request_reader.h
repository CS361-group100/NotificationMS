#pragma once

#include <string>
//defines structure for the email and file (creates place to store information)
struct Request {
    std::string email;
    std::string file;
};

Request readRequest(std::string path);