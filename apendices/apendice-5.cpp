#define INFLUXDB_URL "<URL_INFLUX_DB>"
#define INFLUXDB_TOKEN "<TOKEN_ACESSO>"
#define INFLUXDB_ORG "<ID_ORGANIZACAO_INFLUX_DB>"
#define INFLUXDB_BUCKET "motor-data-acquisition"
#define WIFI_SSID "<NOME_REDE_WIFI>"
#define WIFI_PASSWORD "<SENHA_REDE_WIFI>"

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#if defined(ESP32)
    #include <WiFiMulti.h>
    WiFiMulti wifiMulti;
    #define DEVICE "ESP32"
#elif defined(ESP8266)s
    #include <ESP8266WiFiMulti.h>
    ESP8266WiFiMulti wifiMulti;
    #define DEVICE "ESP8266"
#endif

// Time zone info
#define TZ_INFO "UTC-3"

InfluxDBClient _client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

void ConfigureInfluxDbClient() {
    connectToWifi();
}

void connectToWifi() {
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

    while (wifiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println();
 
    if (_client.validateConnection()) {
        Serial.print("Connected to InfluxDB: ");
        Serial.println(_client.getServerUrl());
    } else {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(_client.getLastErrorMessage());
    }
}