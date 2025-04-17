#!/bin/sh
clear
rm -f SpeakEasy
echo "---------------------------------------------------------"
echo "            Debug Make File                              "
echo "---------------------------------------------------------"

if [ "$1" = "debug" ]; then
    g++ -Wall -std=gnu++17 -g *.cpp -o ./sandbox/SpeakEasy
	cp ./*.py ./sandbox/.
	cd ./sandbox
	echo "Build is good..."

else
    #g++ -Wall -Wextra -pedantic -std=gnu++17 -g *.cpp -o SpeakEasy
    g++ -std=gnu++17 -g *.cpp -o SpeakEasy
fi

exit 0
