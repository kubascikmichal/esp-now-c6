/* Elmod app cominicator

   This project is for reading data from Elmod board - and posting on local website
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <nvs_flash.h>
#include "WIFI/WiFi.h"
#include "HTTP_Client/HTTP_Client.h"
#include "cJSON.h"
#include "NVS/NVS.h"
#include "driver/uart.h"

extern "C"
{
    void app_main();
}

void app_main(void)
{
    const uart_port_t uart_num = UART_NUM_1;
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
    };
    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 18, 9, 4, 5));

    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size,
                                        uart_buffer_size, 10, &uart_queue, 0));

    NVS *sNVS = new NVS();
    WiFi *w = new WiFi("RB157", "ThisIsRb157*", MODE::MODE_STA);
    w->initWiFiConnection();
    HTTP_Client* client = new HTTP_Client("http://api.thingspeak.com/update", "3000", "/data");
    while (true)
    {
        uint8_t data[128];
        int length = 0;
        ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length));
        length = uart_read_bytes(uart_num, data, length, 100);
        if(length > 0){
            //printf("%s\n\r", (char*)data);
            int counts[8]={0};
            sscanf((char*)data, "%d,%d,%d,%d,%d,%d,%d,%d", &counts[0], &counts[1], &counts[2], &counts[3], 
            &counts[4], &counts[5], &counts[6], &counts[7]);
            printf("%d,%d,%d,%d,%d,%d,%d,%d\n\r", counts[0], counts[1], counts[2], counts[3], 
            counts[4], counts[5], counts[6], counts[7]);
            client->sendThingSpeak("AQWIBASIMU7QGW8E",counts);
        }
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    
}
