# Notification Microservice

This Microservice will require asking user for their email, then you have to send-through JSON-a txt file that holds the contents of the email for the microservice to then format and send to the users provided email.


# For C users on windows:
1. Open MSYS2 UCRT64 (more advanced console window)
2. Compile the program with: g++ main.cpp email_service.cpp file_reader.cpp -o service.exe -lcurl -lws2_32
3. Run the application: ./service.exe
4. Should say: Microservice running on http://localhost:8080
5. Test it with an API test platform (recommended Postman but any should work)
6. Enter the URL http://localhost:8080/send-email, and put in your JSON request, should look like this:

        {
        "fromEmail": "senders_email@gmail.com",
        "appPassword": "your_gmail_app_password",
        "toEmail": "users_email@gmail.com",
        "file": "path/to/text.txt"
        }
        
7. Should get a success message printed out and an email in the users inbox!

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


