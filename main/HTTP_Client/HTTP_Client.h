#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include "string.h"
#include "string"
#include "cJSON.h"
#include "esp_http_client.h"

using namespace std;
class HTTP_Client
{
private:
    string url;
    string port;
    string data_path;
    esp_http_client_handle_t client;

public:
    HTTP_Client(string _url, string _port, string _data_path);
    ~HTTP_Client();

    bool sendChangedData(string MAC, int DataChanged);
    bool testThingSpeak(const char *API_KEY,int dev, int count);
    bool sendThingSpeak(const char *API_KEY, int* count);
    bool sendToServer();
};

#endif
