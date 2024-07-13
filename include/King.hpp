#pragma once
template <typename TextureType>
class King : public Piece<TextureType> {
public:
    using Piece<TextureType>::Piece;

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const override;
    typename Piece<TextureType>::PieceType getType() const override;
    void performCastling(int startRow, int startCol, int endCol, Piece<TextureType>*** board);

private:
    const int BOARD_SIZE = 8;
    bool canCastle(int startRow, int startCol, int rookRow, int rookCol, Piece<TextureType>*** board) const;
    bool isSquareUnderAttack(int row, int col, Piece<TextureType>*** board) const;
};
#include "../src/King.cpp"
