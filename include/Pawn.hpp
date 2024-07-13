#pragma once
template <typename TextureType>
class Pawn : public Piece<TextureType> {
public:
    using Piece<TextureType>::Piece;

    bool isValidMove(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) const override;
    void move(int startRow, int startCol, int endRow, int endCol, Piece<TextureType>*** board) override;
    typename Piece<TextureType>::PieceType getType() const override;
    bool isEnPassantPossible() const {return enPassantPossible;}

private:
    bool enPassantPossible;
};
#include "../src/Pawn.cpp"

