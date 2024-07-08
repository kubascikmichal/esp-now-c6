#ifndef __WIFI_H__
#define __WIFI_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include "esp_netif.h"
#include <iostream>

#define EVENT_TAG "wifi_event"
#define CONNECTED_BIT BIT0

#define EXAMPLE_ESP_WIFI_SSID      ""
#define EXAMPLE_ESP_WIFI_PASS      ""
#define EXAMPLE_ESP_MAXIMUM_RETRY  10

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static const char *TAG = "wifi station";

static int s_retry_num = 0;

static EventGroupHandle_t wifi_event_group;

using namespace std;
typedef enum mode
{
    MODE_AP,
    MODE_STA
} MODE;

class WiFi
{

private:
    wifi_init_config_t cfg;
    wifi_config_t conf;
    wifi_auth_mode_t authmode;

public:
    WiFi(string ssid, string password, MODE mode);
    ~WiFi();
    void initWiFiConnection();
};

#endif