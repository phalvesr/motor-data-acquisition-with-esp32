## Motor Data Acquisition with ESP32

### Instructions on how to execute the project:

#### Credential file:
You need a header file containing some specific credentiasl to be able to compile this project on Arduino IDE. The credentials file must contain the credentials related to the Arduino IOT Cloud template (such as the device id and your secret key) and your wifi credentials. Your credentials file must be placed on the root of the project when compiling it. The project expects your credentials file to be in the following format:

```c
#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

    // Wifi credentials
    #define WIFI_NETWORK_SSID "<YOUR_WIFI_NETWORK_NAME>"
    #define WIFI_NETWORK_PASSWORD "<YOUR_WIFI_NETWORK_PASSWORD>"

    // Arduino IOT cloud credentials
    #define ARDUINO_IOT_DEVICE_ID "<YOUR_ARDUINO_IOT_DEVICE_ID>"
    #define ARDUINO_IOT_SECRET_KEY "<YOUR_ARDUINO_IOT_SECRET_KEY>"

#endif
```

To generate the Credentials.h file automatically execute the bash script create-credentials-file.sh at the bash folder and fill the macro values with your specific credentials.
