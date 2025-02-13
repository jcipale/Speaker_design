#include <cstdlib>
#include <string>

int main() {
    std::string driver_filter = "Pass";  // Or "Woof", "Midr", "Tweet"
    int field_index = 10;  // Replace with the desired field index
    std::string cmd_str = "python Surface_Area.py " + driver_filter + " " + std::to_string(field_index);

    system(cmd_str.c_str());
    return 0;
}

