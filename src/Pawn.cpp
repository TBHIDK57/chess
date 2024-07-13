#pragma once
#include "chess.hpp"
template <typename TextureType>
bool Pawn<TextureType>::isValidMove(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const {
    if ((board[endRow][endCol] && *board[endRow][endCol] == *this) ||
        (startRow == endRow && startCol == endCol)) {
        return false;
    }
    int direction = this->isWhitePiece() ? -1 : 1;
    if (startCol == endCol) {
        if (endRow == startRow + direction && board[endRow][endCol] == nullptr) {
            return true;
        }
        if (startRow == (this->isWhitePiece() ? 6 : 1) &&
            endRow == startRow + 2 * direction &&
            board[startRow + direction][startCol] == nullptr &&
            board[endRow][endCol] == nullptr) {
            return true;
        }
    } else if (std::abs(startCol - endCol) == 1 && endRow == startRow + direction) {
        if (board[endRow][endCol] != nullptr &&
            board[endRow][endCol]->isWhitePiece() != this->isWhitePiece()) {
            return true;
        }
        if (board[endRow][endCol] == nullptr && board[startRow][endCol] != nullptr &&
            board[startRow][endCol]->getType() == Piece<TextureType>::PieceType::Pawn &&
            board[startRow][endCol]->isWhitePiece() != this->isWhitePiece() &&
            static_cast<Pawn<TextureType>*>(board[startRow][endCol])->isEnPassantPossible()) {
            return true;
        }
    }
    return false;
}

template <typename TextureType>
void Pawn<TextureType>::move(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) {
    this->setMoved();
    this->enPassantPossible = (std::abs(startRow - endRow) == 2);
    if (std::abs(startCol - endCol) == 1 && board[endRow][endCol] == nullptr) {
        delete board[startRow][endCol];
        board[startRow][endCol] = nullptr;
    }
}

template <typename TextureType>
typename Piece<TextureType>::PieceType Pawn<TextureType>::getType() const {
    return Piece<TextureType>::PieceType::Pawn; 
}
