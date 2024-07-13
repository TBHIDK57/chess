#pragma once
#include "chess.hpp"
template <typename TextureType>
bool King<TextureType>::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const {

    if ((board[endRow][endCol] && *board[endRow][endCol] == *this) || 
        (startRow == endRow && startCol == endCol)) {
        return false;
    }
    if (std::abs(startRow - endRow) <= 1 && std::abs(startCol - endCol) <= 1) {
        return true;
    }
    // Castling logic
    if (startRow == endRow && !this->hasMoved() && !isSquareUnderAttack(startRow, startCol, board)) {
        if (endCol == startCol + 2 && canCastle(startRow, startCol, startRow, 7, board)) {
            return true;
        }
        if (endCol == startCol - 2 && canCastle(startRow, startCol, startRow, 0, board)) {
            return true;
        }
    }
    return false;
}  

template <typename TextureType>
typename Piece<TextureType>::PieceType King<TextureType>::getType() const {
        return Piece<TextureType>::PieceType::King;
}  

template <typename TextureType>
void King<TextureType>::performCastling(int startRow, int startCol, int endCol, Piece<TextureType>*** board) {
    if (endCol == startCol + 2) {
        board[startRow][startCol + 1] = board[startRow][7];
        board[startRow][7] = nullptr;
        board[startRow][startCol + 1]->setMoved();
    } else if (endCol == startCol - 2) {
        board[startRow][startCol - 1] = board[startRow][0];
        board[startRow][0] = nullptr;
        board[startRow][startCol - 1]->setMoved();
    }
}

template <typename TextureType>
bool King<TextureType>::canCastle(int startRow, int startCol, int rookRow, int rookCol, Piece<TextureType>*** board) const {
    if (board[rookRow][rookCol] && 
        board[rookRow][rookCol]->getType() == Piece<TextureType>::PieceType::Rook && 
        !board[rookRow][rookCol]->hasMoved() && 
        this->isPathClear(startRow, startCol, rookRow, rookCol, board)) {
        for (int col = std::min(startCol, rookCol) + 1; col < std::max(startCol, rookCol); ++col) {
            if (isSquareUnderAttack(startRow, col, board)) {
                return false;
            }
        }
        return true;
    }
    return false;
}

template <typename TextureType>
bool King<TextureType>::isSquareUnderAttack(int row, int col, Piece<TextureType>*** board) const {
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            Piece<TextureType>* piece = board[r][c];
            if (piece && piece->isWhitePiece() != this->isWhitePiece()) {
                if (piece->isValidMove(r, c, row, col, board)) {
                    return true;
                }
            }
        }
    }
    return false;
}
