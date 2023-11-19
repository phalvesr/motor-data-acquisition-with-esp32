## Motor Data Acquisition with ESP32

### Instructions on how to execute the project:

#### Credential file:
You need a header file containing some specific data to be able to compile this project on Arduino IDE. The credentials file must contain the credentials related to the Blynk template (such as the template id and your access token) and your wifi credentials. Your credentials file must be placed on the root of the project when compiling the project. The project expects your credentials file to be in the following format:

```c
#define BLYNK_TEMPLATE_ID "<UNIQUE_TEMPLATE_ID>"
#define BLYNK_TEMPLATE_NAME "<TEMPLATE_NAME>"
#define BLYNK_AUTH_TOKEN "<BLYNK_AUTH_TOKEN>"echo

#define WIFI_NETWORK_SSID "<WIFI_NAME>"
#define WIFI_NETWORK_PASSWORD "<WIFI_PASSWORD>"
```

To generate the Credentials.h file automatically execute the bash script create-credentials-file.sh at the bash folder and fill the macro values with your specific credentials 
