## Motor Data Acquisition with ESP32

### Instructions on how to execute the project:

#### Credential file:

You need a header file containing some specific credentiasl to be able to compile this project on Arduino IDE. The credentials file must contain the credentials related to the Arduino IOT Cloud template (such as the device id and your secret key) and your wifi credentials. Your credentials file must be placed on the root of the project when compiling it. The project expects your credentials file to be in the following format:

```c
#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

#define INFLUXDB_URL "<YOUR_INFLUXDB_SERVER_ENDPOINT_URL>"
#define INFLUXDB_TOKEN "<YOUR_INFLUXDB_TOKEN>"
#define INFLUXDB_ORG "<YOUR_INFLUXDB_ORGANIZATION_TOKEN>"
#define INFLUXDB_BUCKET "<YOUR_INFLUXDB_BUCKET_NAME>"

#define WIFI_SSID "<YOUR_WIFI_NETWORK_NAME>"
#define WIFI_PASSWORD "<YOUR_WIFI_NETWORK_PASSWORD>"
#endif
```
