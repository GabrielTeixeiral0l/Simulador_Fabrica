#ifndef SIMULADOR_ECRA_H
#define SIMULADOR_ECRA_H

#include <string>
#include "Settings.h"

class Ecra {
    char buffer[Settings::ecra_max_linhas][Settings::ecra_max_colunas];
    int rows;
    int cols;
    int cursorRow;
    int cursorCol;

    bool isInBounds(int r, int c) const noexcept;
    void putChar(int r, int c, char ch) noexcept;

public:
    explicit Ecra(int r = Settings::ecra_max_linhas, int c = Settings::ecra_max_colunas) noexcept;

    void clear() noexcept;
    bool gotoxy(int r, int c) noexcept;
    void write(char c) noexcept;
    void write(const std::string& text);
    void write(int r, int c, char ch) noexcept;
    void write(int r, int c, const std::string& text);
    void drawFrame(int startRow, int startCol, int height, int width) noexcept;
    void show() const;

    char getChar(int r, int c) const noexcept;
    int getRows() const noexcept;
    int getCols() const noexcept;
    int getCursorRow() const noexcept;
    int getCursorCol() const noexcept;
};

#endif // SIMULADOR_ECRA_H
