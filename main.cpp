/*@Author: Rachel Luginbill
@Date: March 11, 2026
@Title: Notification Microservice
@Description: This Microservice will require asking user for their email,
 then you have to send-through JSON-a txt file that holds the contents of the 
 email for the microservice to then format and send to the users provided email.
 @purpose: Runs the microservice
*/
#include <iostream>
#include "request_reader.h"
#include "file_reader.h"
#include "email_service.h"

int main() {

    std::string requestFile = "requests/request.json";

    Request req = readRequest(requestFile);

    std::string message = readFile(req.file);

    sendEmail(req.email, message);

    std::cout << "Notification sent to " << req.email << std::endl;

    return 0;
}