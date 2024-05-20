#include "Console.hpp"

using namespace Console;

int main(){
    output("Hello, {0}! I'm {1:U}", "aboba", "zebr", "cabibara");
    output("{0:C} {1:P}", 3.14, 123.45f);
    std::string format = "Hello, {0:U}! Today is {1:Y}.";
    std::string name = "world";
    std::string nw = "1587254061";
    output(format, name, nw);
    time_t now = time(0);
    output("Current is: {0:Y}", now);
    output("Hex: {0:X}", nw);
    output("Round: {0:R}", 123.45f);
    return 0;
}