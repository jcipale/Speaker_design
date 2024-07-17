clear
rm -f SpeakEasy
echo "---------------------------------------------------------"
echo "            Debug Make File                              "
echo "---------------------------------------------------------"
#g++ -std=gnu++17 -g main.cpp menus.cpp speaker_easy.cpp -o SpeakEasy
g++ -std=gnu++17 -g *.cpp -o SpeakEasy

exit 0
