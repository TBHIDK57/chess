#pragma once
#include "chess.hpp"
template <typename TextureType>
bool Knight<TextureType>::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const {
    int rowDiff = std::abs(startRow - endRow);
    int colDiff = std::abs(startCol - endCol);
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2))) {
        return false;
    }
    if (board[endRow][endCol] && *board[endRow][endCol] == *this) {
        return false;
    }
    if (startRow == endRow && startCol == endCol) {
        return false;
    }
    return true;
}

template <typename TextureType>
typename Piece<TextureType>::PieceType Knight<TextureType>::getType() const { 
    return Piece<TextureType>::PieceType::Knight; 
}
