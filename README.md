# Notification Microservice

This Microservice will require asking user for their email, then you have to send-through JSON-a txt file that holds the contents of the email for the microservice to then format and send to the users provided email.


# For C users:
// Build JSON request
    json j;
    j["email"] = userEmail;
    j["file"] = filePath;

    // Send POST request to microservice
    httplib::Client cli("http://localhost:8080");
    auto res = cli.Post("/send-email", j.dump(), "application/json");

    // Handle response
    if (res && res->status == 200) {
        std::cout << "Microservice response: " << res->body << std::endl;
    } else {
        std::cout << "Failed to call microservice" << std::endl;
    }

    return 0;

Then run in cmd:
Compile your microservice and run it first:

    g++ email_ms.cpp -o email_ms.exe -lws2_32
    email_ms.exe

Compile your client:

    g++ client.cpp -o client.exe -lws2_32

Run the client while the microservice is running:

    client.exe

Follow the prompts. The email will be sent via your microservice.

# Python users:

Build the JSON request
    data = {
        "email": user_email,
        "file": file_path
    }

        Send POST request to microservice
        url = "http://localhost:8080/send-email"
        response = requests.post(url, data=json.dumps(data), headers={"Content-Type": "application/json"})

        Print response
        if response.status_code == 200:
            print("Microservice response:", response.text)
        else:
            print("Failed to call microservice. Status code:", response.status_code)