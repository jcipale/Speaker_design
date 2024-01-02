clear
rm -f SpeakEasy
echo "---------------------------------------------------------"
echo "            Debug Make File                              "
echo "---------------------------------------------------------"
g++ -std=gnu++17 -Wno-coverage-mismatch -g main.cpp compute.cpp menus.cpp speaker_easy.cpp -o SpeakEasy

exit 0
