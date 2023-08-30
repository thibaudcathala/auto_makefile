#ifndef MY_COLOR_HPP_
    #define MY_COLOR_HPP_

    #include <string>

namespace color {
    constexpr std::string reset = "\e[39m";

    constexpr std::string red = "\e[91m";
    constexpr std::string green = "\e[92m";
    constexpr std::string yellow = "\e[93m";
    constexpr std::string blue = "\e[94m";
    constexpr std::string magenta = "\e[95m";
    constexpr std::string cyan = "\e[96m";
}

#endif /* !MY_COLOR_HPP_ */
