#pragma once

#include <string>

void sendEmail(const std::string &fromEmail,
               const std::string &appPassword,
               const std::string &toEmail,
               const std::string &message);