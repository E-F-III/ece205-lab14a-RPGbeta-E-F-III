#include "util/TextDisplay.hpp"

namespace util {
    const char RESET[]        = "\033[0m";
    const char BOLD[]         = "\033[1m";
    const char UNDERLINE[]    = "\033[4m";

    const char BG_BLACK[]     = "\033[40m";
    const char BG_RED[]       = "\033[41m";
    const char BG_GREEN[]     = "\033[42m";
    const char BG_YELLOW[]    = "\033[43m";
    const char BG_BLUE[]      = "\033[44m";
    const char BG_MAGENTA[]   = "\033[45m";
    const char BG_CYAN[]      = "\033[46m";
    const char BG_WHITE[]     = "\033[47m";

    const char FG_BLACK[]     = "\033[30m";
    const char FG_RED[]       = "\033[31m";
    const char FG_GREEN[]     = "\033[32m";
    const char FG_YELLOW[]    = "\033[33m";
    const char FG_BROWN[]     = "\033[38;5;94m";
    const char FG_BLUE[]      = "\033[34m";
    const char FG_MAGENTA[]   = "\033[35m";
    const char FG_CYAN[]      = "\033[36m";
    const char FG_WHITE[]     = "\033[37m";
    const char CLEAR_LINE[]   = "\033[2K\r";

    void printColor(const std::string& text, const char* fgCode) {
        std::cout << fgCode << text << RESET;
    }

    void printColorBg(const std::string& text, const char* fgCode, const char* bgCode) {
        std::cout << bgCode << fgCode << text << RESET;
    }

    void printType(const std::string& text, int speedMs) {
        for (char c : text) {
            std::cout << c << std::flush;
            if (speedMs > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(speedMs));
            }
        }
    }

    void clearScreen() {
        std::cout << "\033[2J\033[H" << std::flush;
    }

    void showLoadingSpinner(const std::string& text, int durationMs) {
        char spinners[] = {'|', '/', '-', '\\'};
        auto startTime = std::chrono::steady_clock::now();
        int i = 0;
        while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - startTime).count() < durationMs) {
            std::cout << "\r" << text << spinners[i++ % 4] << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << CLEAR_LINE;
    }

    void printProgressBar(int current, int total, char barChar, const char* fgCode) {
        int width = 20;
        if (total <= 0) total = 1;
        if (current < 0) current = 0;
        int percent = (current * 100) / total;
        int filledWidth = (width * current) / total;
        if (filledWidth > width) filledWidth = width;
        std::string filled(filledWidth, barChar);
        std::string empty(width - filledWidth, '.');
        std::cout << "[";
        printColor(filled, fgCode);
        std::cout << empty << "] " << percent << "%";
    }
}
