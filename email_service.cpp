//Sends the email
#include <iostream>
#include "email_service.h"

void sendEmail(std::string email, std::string message) {

    std::cout << "Sending email to: " << email << std::endl;
    std::cout << "Message:" << std::endl;
    std::cout << message << std::endl;
}