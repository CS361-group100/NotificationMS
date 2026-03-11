/*@Author: Rachel Luginbill
@Date: March 11, 2026
@Title: Notification Microservice
@Description: This Microservice will require asking user for their email,
 then you have to send-through JSON-a txt file that holds the contents of the 
 email for the microservice to then format and send to the users provided email.
 @purpose: Runs the microservice
*/
#include "httplib.h"
#include "json.hpp"
#include "file_reader.h"
#include "email_service.h"
#include <iostream>

using json = nlohmann::json;

int main() {
    httplib::Server svr;

    svr.Post("/send-email", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json j = json::parse(req.body);
            std::string email = j["email"];
            std::string file = j["file"];

            std::string message = readFile(file); // throws if empty

            sendEmail(email, message);

            json response;
            response["status"] = "complete";
            res.set_content(response.dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content("{\"error\":\"" + std::string(e.what()) + "\"}", "application/json");
        }
    });

    std::cout << "Microservice running on http://localhost:8080\n";
    svr.listen("localhost", 8080);
}