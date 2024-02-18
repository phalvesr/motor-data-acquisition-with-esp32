#!/bin/bash

# Execute this script to generate the credentials file and change the values according to your case


# Terminal colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

projectRootDirectory=".."
# Only used to print the path to the user
projectRootDirectoryPath="$(echo $(cd .. && pwd))"

credentialsFileDir="$projectRootDirectory/Credentials.h"

if [ -f $credentialsFileDir ]
then
    echo -e "${RED}Credentials file already exists at: $projectRootDirectoryPath. Do you want to overwrite it? (y/n)${NC}"
    read overwrite

    if [ $overwrite != "y" ]
    then
        echo "Exiting..."
        exit 0
    fi
fi

rm -f $credentialsFileDir

echo -e "${GREEN}Creating Credentials file at: $projectRootDirectoryPath${NC}"

cat << EOF > $credentialsFileDir
#ifndef __CREDENTIALS_H__
#define __CREDENTIALS_H__

    // Wifi credentials
    #define WIFI_NETWORK_SSID "<YOUR_WIFI_NETWORK_NAME>"
    #define WIFI_NETWORK_PASSWORD "<YOUR_WIFI_NETWORK_PASSWORD>"

    // Arduino IOT cloud credentials
    #define ARDUINO_IOT_DEVICE_ID "<YOUR_ARDUINO_IOT_DEVICE_ID>"
    #define ARDUINO_IOT_SECRET_KEY "<YOUR_ARDUINO_IOT_SECRET_KEY>"

#endif
EOF
