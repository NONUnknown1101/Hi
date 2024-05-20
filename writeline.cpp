#include <iostream>
#include <string>
#include <regex>

template <typename... Args>
void writeline(const std::string& format, Args... args) {
    std::regex pattern("\\{\\d+:G\\}");
    std::smatch match;

    size_t pos = 0;
    
    while (std::regex_search(format, match, pattern)) {
        std::cout << match.prefix();
        
        size_t index = std::stoi(match.str().substr(1, match.str().find(":") - 1));
        
        if (index < sizeof...(args)) {
            std::cout << std::get<index>(std::make_tuple(args...));
        }
        
        format = match.suffix();
    }
    
    std::cout << format;
}

int main() {
    writeline("Hello, {0:G}!", "world");
    std::cout << std::endl;
    
    writeline("Today is {0:G}, {1:G}!", "Monday", "January 1st");
    std::cout << std::endl;
    
    writeline("{0:G} is {1:G} day. Tomorrow is {2:G}!", "Today", "the first", "Monday");
    std::cout << std::endl;
    
    return 0;
}