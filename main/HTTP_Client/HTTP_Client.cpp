#include "HTTP_Client.h"

HTTP_Client::HTTP_Client(string _url, string _port, string _data_path)
{
    this->url = _url;
    this->port = _port;
    this->data_path = _data_path;
}

HTTP_Client::~HTTP_Client()
{
}

bool HTTP_Client::sendChangedData(string MAC, int DataChanged)
{
        esp_http_client_config_t config = {
        .host = this->url.c_str(),
        .path = "/",
        .disable_auto_redirect = true,
    };
    this->client = esp_http_client_init(&config);

    cJSON *changed_data;
    changed_data = cJSON_CreateObject();

    esp_http_client_set_url(this->client, string("http://").append(this->url).append(":").append(this->port).append(this->data_path).c_str());
    esp_http_client_set_method(this->client, HTTP_METHOD_POST);
    esp_http_client_set_header(this->client, "Content-Type", "application/json");
    esp_http_client_set_post_field(this->client, cJSON_PrintUnformatted(changed_data), strlen(cJSON_PrintUnformatted(changed_data)));

    printf("%s\n\r", cJSON_PrintUnformatted(changed_data));
    printf("POST url %s\n\r", string("http://").append(this->url).append(":").append(this->port).append(this->data_path).c_str());

    esp_err_t err = esp_http_client_perform(this->client);
    esp_http_client_cleanup(this->client);
    return (err == ESP_OK);
    //ESP_ERROR_CHECK(err);
    //printf("%s\n\r", this->client->response->buffer->data);
}

bool HTTP_Client::testThingSpeak(const char *API_KEY, int dev, int count){
    char thingspeak_url[] = "http://api.thingspeak.com/update?api_key=%s&field%d=%d";
    char post_data[200];
     strcpy(post_data, "");
    snprintf(post_data, sizeof(post_data), thingspeak_url, API_KEY, dev, count);
    esp_http_client_config_t config = {
        .host = post_data,
        .path = "/",
        .disable_auto_redirect = true,
    };
    this->client = esp_http_client_init(&config);
    esp_http_client_set_url(this->client, string(post_data).c_str());
    esp_http_client_set_method(this->client, HTTP_METHOD_GET);
    esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");   
    esp_err_t err = esp_http_client_perform(this->client);
    esp_http_client_cleanup(this->client);
    return (err == ESP_OK);
}

bool HTTP_Client::sendThingSpeak(const char *API_KEY, int* count){
    char thingspeak_url[] = "http://api.thingspeak.com/update?api_key=%s&field1=%d&field2=%d&field3=%d&field4=%d&field5=%d&field6=%d&field7=%d&field8=%d";
    char post_data[200];
     strcpy(post_data, "");
    snprintf(post_data, sizeof(post_data), thingspeak_url, API_KEY, count[0], count[1], count[2], count[3], 
    count[4], count[5], count[6], count[7]);
    esp_http_client_config_t config = {
        .host = post_data,
        .path = "/",
        .disable_auto_redirect = true,
    };
    this->client = esp_http_client_init(&config);
    esp_http_client_set_url(this->client, string(post_data).c_str());
    esp_http_client_set_method(this->client, HTTP_METHOD_GET);
    esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");   
    esp_err_t err = esp_http_client_perform(this->client);
    esp_http_client_cleanup(this->client);
    return (err == ESP_OK);
}


bool  HTTP_Client::sendToServer(){
    esp_http_client_config_t config = {
        .host = this->url.c_str(),
        .path = "/",
        .disable_auto_redirect = true,
    };
    this->client = esp_http_client_init(&config);
    esp_http_client_set_url(this->client, string("http://158.193.140.96:3000/data").c_str());
    esp_http_client_set_method(this->client, HTTP_METHOD_GET);
    esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");   
    esp_err_t err = esp_http_client_perform(this->client);
    esp_http_client_cleanup(this->client);
    return (err == ESP_OK);
}