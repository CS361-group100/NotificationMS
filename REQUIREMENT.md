# Requirements

Libcurl:
1. https://curl.se/windows/
2. Download the “Win64 – Generic” version with SSL and libcurl.
3. Look for a package that includes libcurl.dll and headers.
4. Unzip it somewhere, e.g., C:\curl
5. Link it in your project under C/C++ Configurations (UI)
6. In C/C++ Config under Include path put on a new line "C:/curl-8.19.0_1-win64-mingw/curl-8.19.0_1-win64-mingw/include" or your file path
7. OR when compiling tell g++ where to find it

        g++ main.cpp file_reader.cpp email_service.cpp -o email_ms.exe -I"C:\curl\include" -L"C:\curl\lib" -lcurl -lws2_32

8. It should be able to run now
