#pragma once
#include "chess.hpp"
template <typename TextureType>
Piece<TextureType>::Piece(const TextureType& texture, bool isWhite) : isWhite(isWhite), moved(false) {
    sprite.setTexture(texture);
    sprite.setScale(0.2f, 0.2f);
}

template <typename TextureType>
void Piece<TextureType>::setTexture(const TextureType& texture) {
    sprite.setTexture(texture);
    sprite.setScale(0.2f, 0.2f);
}

template <typename TextureType>
bool Piece<TextureType>::isPathClear(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const {
    int rowStep = (endRow > startRow) ? 1 : (endRow < startRow) ? -1 : 0;
    int colStep = (endCol > startCol) ? 1 : (endCol < startCol) ? -1 : 0;
    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;
    while (currentRow != endRow || currentCol != endCol) {
        if (board[currentRow][currentCol] != nullptr) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }
    return true;
}    