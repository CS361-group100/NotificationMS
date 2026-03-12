#include <curl/curl.h>
#include <iostream>
#include <string>

struct UploadStatus {
    size_t bytesRead;
    std::string* data;
};

size_t payloadSource(void* ptr, size_t size, size_t nmemb, void* userp) {
    UploadStatus* upload = static_cast<UploadStatus*>(userp);
    size_t bufferSize = size * nmemb;

    if (upload->bytesRead >= upload->data->size())
        return 0; // No more data

    size_t bytesLeft = upload->data->size() - upload->bytesRead;
    size_t toCopy = (bytesLeft < bufferSize) ? bytesLeft : bufferSize;
    memcpy(ptr, upload->data->c_str() + upload->bytesRead, toCopy);
    upload->bytesRead += toCopy;
    return toCopy;
}

void sendEmail(const std::string& fromEmail, const std::string& appPassword,
               const std::string& toEmail, const std::string& message) {

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl\n";
        return;
    }

    std::string emailMessage = 
        "To: " + toEmail + "\r\n" +
        "From: " + fromEmail + "\r\n" +
        "Subject: Your Notification\r\n\r\n" +
        message + "\r\n";

    UploadStatus upload{0, &emailMessage};

    curl_easy_setopt(curl, CURLOPT_USERNAME, fromEmail.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, appPassword.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, fromEmail.c_str());

    struct curl_slist* recipients = nullptr;
    recipients = curl_slist_append(recipients, toEmail.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payloadSource);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
        std::cerr << "Email failed: " << curl_easy_strerror(res) << std::endl;
    else
        std::cout << "Email sent successfully to " << toEmail << "!\n";

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
}