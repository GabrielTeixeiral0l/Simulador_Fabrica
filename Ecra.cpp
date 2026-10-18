#include "Ecra.h"
#include <iostream>

Ecra::Ecra(int r, int c) noexcept
    : rows(r), cols(c), cursorRow(0), cursorCol(0) {
    if (rows < 1) {
        rows = 1;
    } else if (rows > Settings::ecra_max_linhas) {
        rows = Settings::ecra_max_linhas;
    }

    if (cols < 1) {
        cols = 1;
    } else if (cols > Settings::ecra_max_colunas) {
        cols = Settings::ecra_max_colunas;
    }

    clear();
}

bool Ecra::isInBounds(int r, int c) const noexcept {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

void Ecra::putChar(int r, int c, char ch) noexcept {
    if (isInBounds(r, c)) {
        buffer[r][c] = ch;
    }
}

void Ecra::clear() noexcept {
    for (int r = 0; r < Settings::ecra_max_linhas; ++r) {
        for (int c = 0; c < Settings::ecra_max_colunas; ++c) {
            buffer[r][c] = ' ';
        }
    }
    cursorRow = 0;
    cursorCol = 0;
}

bool Ecra::gotoxy(int r, int c) noexcept {
    if (isInBounds(r, c)) {
        cursorRow = r;
        cursorCol = c;
        return true;
    }
    return false;
}

void Ecra::write(char c) noexcept {
    if (c == '\n') {
        cursorRow++;
        cursorCol = 0;
        return;
    }

    if (cursorCol >= cols) {
        cursorRow++;
        cursorCol = 0;
    }

    if (isInBounds(cursorRow, cursorCol)) {
        buffer[cursorRow][cursorCol] = c;
        cursorCol++;
    }
}

void Ecra::write(const std::string& text) {
    for (char c : text) {
        write(c);
    }
}

void Ecra::write(int r, int c, char ch) noexcept {
    if (gotoxy(r, c)) {
        write(ch);
    }
}

void Ecra::write(int r, int c, const std::string& text) {
    if (gotoxy(r, c)) {
        write(text);
    }
}

void Ecra::drawFrame(int startRow, int startCol, int height, int width) noexcept {
    if (height < 2 || width < 2) {
        return;
    }

    int endRow = startRow + height - 1;
    int endCol = startCol + width - 1;

    for (int c = startCol + 1; c < endCol; ++c) {
        putChar(startRow, c, '-');
        putChar(endRow, c, '-');
    }

    for (int r = startRow + 1; r < endRow; ++r) {
        putChar(r, startCol, '|');
        putChar(r, endCol, '|');
    }

    putChar(startRow, startCol, '+');
    putChar(startRow, endCol, '+');
    putChar(endRow, startCol, '+');
    putChar(endRow, endCol, '+');
}

void Ecra::show() const {
    std::string output;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            output += buffer[r][c];
        }
        output += '\n';
    }

    std::cout << output;
}

char Ecra::getChar(int r, int c) const noexcept {
    if (isInBounds(r, c)) {
        return buffer[r][c];
    }
    return ' ';
}

int Ecra::getRows() const noexcept {
    return rows;
}

int Ecra::getCols() const noexcept {
    return cols;
}

int Ecra::getCursorRow() const noexcept {
    return cursorRow;
}

int Ecra::getCursorCol() const noexcept {
    return cursorCol;
}