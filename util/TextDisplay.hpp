#ifndef UTIL_TEXT_DISPLAY_HPP
#define UTIL_TEXT_DISPLAY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

namespace util {
    // --- Global String Constants for ANSI Codes ---
    extern const char RESET[];
    extern const char BOLD[];
    extern const char UNDERLINE[];

    // --- Colors: Background Codes ---
    extern const char BG_BLACK[];
    extern const char BG_RED[];
    extern const char BG_GREEN[];
    extern const char BG_YELLOW[];
    extern const char BG_BLUE[];
    extern const char BG_MAGENTA[];
    extern const char BG_CYAN[];
    extern const char BG_WHITE[];

    // --- Colors: Foreground Codes ---
    extern const char FG_BLACK[];
    extern const char FG_RED[];
    extern const char FG_GREEN[];
    extern const char FG_YELLOW[];
    extern const char FG_BROWN[];
    extern const char FG_BLUE[];
    extern const char FG_MAGENTA[];
    extern const char FG_CYAN[];
    extern const char FG_WHITE[];
    extern const char CLEAR_LINE[];

    void printColor(const std::string& text, const char* fgCode);
    void printColorBg(const std::string& text, const char* fgCode, const char* bgCode);
    void printType(const std::string& text, int speedMs = 50);
    void clearScreen();
    void showLoadingSpinner(const std::string& text, int durationMs = 1000);
    void printProgressBar(int current, int total, char barChar = '#', const char* fgCode = FG_GREEN);
}

#endif // UTIL_TEXT_DISPLAY_HPP
