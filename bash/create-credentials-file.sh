#!/bin/bash

# Execute this script to generate the credentials file and change the values according to your case

projectRootDirectory=".."

echo "Creating Credentials file at: $projectRootDirectory/Credentials.h"

echo '#define BLYNK_TEMPLATE_ID "<UNIQUE_TEMPLATE_ID>"' >> $projectRootDirectory/Credentials.h
echo '#define BLYNK_TEMPLATE_NAME "<TEMPLATE_NAME>"' >> $projectRootDirectory/Credentials.h
echo '#define BLYNK_AUTH_TOKEN "<BLYNK_AUTH_TOKEN>"' >> $projectRootDirectory/Credentials.h
echo "" >> $projectRootDirectory/Credentials.h
echo '#define WIFI_NETWORK_SSID "<WIFI_NAME>"' >> $projectRootDirectory/Credentials.h
echo '#define WIFI_NETWORK_PASSWORD "<WIFI_PASSWORD>"' >> $projectRootDirectory/Credentials.h
