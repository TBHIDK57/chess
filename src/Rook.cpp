#pragma once
#include "chess.hpp"
template <typename TextureType>
bool Rook<TextureType>::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const {
    if ((board[endRow][endCol] && *board[endRow][endCol] == *this) ||
        (startRow == endRow && startCol == endCol)) {
        return false;
    }
    if (startRow == endRow || startCol == endCol) {
        return this->isPathClear(startRow, startCol, endRow, endCol, board);
    }
    return false;
}

template <typename TextureType>
typename Piece<TextureType>::PieceType Rook<TextureType>::getType() const { return Piece<TextureType>::PieceType::Rook; }