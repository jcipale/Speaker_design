#!/bin/sh
clear
rm -f SpeakEasy
echo "---------------------------------------------------------"
echo "            Debug Make File                              "
echo "---------------------------------------------------------"

if [ "$1" = "debug" ]; then
    g++ -std=gnu++17 -g *.cpp -o ./sandbox/SpeakEasy
	cp ./driver.csh ./sandbox/.
	cd ./sandbox
else
    g++ -std=gnu++17 -g *.cpp -o SpeakEasy
fi

exit 0
